/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2015 Eurecom

    OpenAirInterface is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.


    OpenAirInterface is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenAirInterface.The full GNU General Public License is
    included in this distribution in the file called "COPYING". If not,
    see <http://www.gnu.org/licenses/>.

  Contact Information
  OpenAirInterface Admin: openair_admin@eurecom.fr
  OpenAirInterface Tech : openair_tech@eurecom.fr
  OpenAirInterface Dev  : openair4g-devel@eurecom.fr

  Address      : Eurecom, Campus SophiaTech, 450 Route des Chappes, CS 50193 - 06904 Biot Sophia Antipolis cedex, FRANCE

*******************************************************************************/
/*! \file message_queue.c
 * \brief this is the implementation of a message queue
 * \author Cedric Roux
 * \date November 2015
 * \version 1.0
 * \email: cedric.roux@eurecom.fr
 * @ingroup _mac
 */

#include "message_queue.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

message_queue_t *new_message_queue(void)
{
  message_queue_t *ret = NULL;

  ret = calloc(1, sizeof(message_queue_t));
  if (ret == NULL)
    goto error;

  ret->mutex = calloc(1, sizeof(pthread_mutex_t));
  if (ret->mutex == NULL)
    goto error;
  if (pthread_mutex_init(ret->mutex, NULL))
    goto error;

  ret->cond = calloc(1, sizeof(pthread_cond_t));
  if (ret->cond == NULL)
    goto error;
  if (pthread_cond_init(ret->cond, NULL))
    goto error;

  return ret;

error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  if (ret != NULL) {
    free(ret->mutex);
    free(ret->cond);
    memset(ret, 0, sizeof(message_queue_t));
    free(ret);
  }
  return NULL;
}

int message_put(message_queue_t *queue, void *data, int size, int priority)
{
  message_t *m = NULL;

  m = calloc(1, sizeof(message_t));
  if (m == NULL)
    goto error;

  m->data = data;
  m->size = size;
  m->priority = priority;
  m->next = NULL;

  if (pthread_mutex_lock(queue->mutex))
    goto error;

  if (queue->count == 0)
    queue->head = m;
  else
    queue->tail->next = m;
  queue->tail = m;

  queue->count++;

  if (pthread_cond_signal(queue->cond)) {
    LOG_E(MAC, "%s:%d:%s: fatal error\n", __FILE__, __LINE__, __FUNCTION__);
    pthread_mutex_unlock(queue->mutex);
    exit(1);
  }
  if (pthread_mutex_unlock(queue->mutex)) {
    LOG_E(MAC, "%s:%d:%s: fatal error\n", __FILE__, __LINE__, __FUNCTION__);
    exit(1);
  }

  return 0;

error:
  free(m);
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

int message_get(message_queue_t *queue, void **data, int *size, int *priority)
{
  message_t *m;

  if (pthread_mutex_lock(queue->mutex))
    goto error;

  while (queue->count == 0) {
    if (pthread_cond_wait(queue->cond, queue->mutex)) {
      pthread_mutex_unlock(queue->mutex);
      goto error;
    }
  }

  m = queue->head;
  queue->head = queue->head->next;
  if (queue->head == NULL)
    queue->tail = NULL;

  queue->count--;

  if (pthread_mutex_unlock(queue->mutex))
    goto error;

  *data = m->data;
  *size = m->size;
  *priority = m->priority;
  free(m);

  return 0;

error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

/* when calling this function, the queue must not be used anymore (we don't lock it) */
/* we suppose that the data pointer in messages was allocated by malloc/calloc/realloc */
void destroy_message_queue(message_queue_t *queue)
{
  while (queue->head) {
    message_t *m = queue->head;
    queue->head = queue->head->next;
    free(m->data);
    memset(m, 0, sizeof(message_t));
    free(m);
  }
  free(queue->mutex);
  free(queue->cond);
  memset(queue, 0, sizeof(message_queue_t));
  free(queue);
}

#ifdef TEST

/* some very basic tests */
int main(void)
{
  void *data;
  int size;
  int priority;
  message_queue_t *q;
  char *s;

  q = new_message_queue();
  if (q == NULL) goto error;

  if (message_put(q, "hello", 6, 0)) goto error;
  if (message_put(q, "world", 6, 1)) goto error;

  if (message_get(q, &data, &size, &priority)) goto error;
  printf("message:\n  data: '%s'\n  size: %d\n  priority: %d\n",
         (char *)data, size, priority);
  if (message_get(q, &data, &size, &priority)) goto error;
  printf("message:\n  data: '%s'\n  size: %d\n  priority: %d\n",
         (char *)data, size, priority);

  /* let's put a message before destroying the queue */
  s = malloc(10); if (s == NULL) goto error;
  sprintf(s, "hello");
  if (message_put(q, s, 6, 0)) goto error;
  destroy_message_queue(q);

  return 0;

error:
  printf("error\n");
  return 1;
}

#endif
