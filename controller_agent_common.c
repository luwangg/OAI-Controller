/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2014 Eurecom

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
  OpenAirInterface Dev  : openair4g-devel@lists.eurecom.fr

  Address      : Eurecom, Compus SophiaTech 450, route des chappes, 06451 Biot, France.

 *******************************************************************************/

/*! \file controller_agent_common.c
 * \brief common primitives for all agents 
 * \author Navid Nikaein and Xenofon Foukas
 * \date 2016
 * \version 0.1
 */


#include "controller_agent_common.h"
// #include "PHY/extern.h"
#include "log.h"


// void * enb[NUM_MAX_CONTROLLER];
// void * enb_ue[NUM_MAX_CONTROLLER];
// void * enb_rrc[NUM_MAX_CONTROLLER];
/*
 * message primitives
 */

int controller_agent_serialize_message(Protocol__ProgranMessage *msg, void **buf, int *size) {

  *size = protocol__progran_message__get_packed_size(msg);
  
  *buf = malloc(*size);
  if (buf == NULL)
    goto error;
  
  protocol__progran_message__pack(msg, *buf);
  
  return 0;
  
 error:
  LOG_E(CONTROLLER_AGENT, "an error occured\n"); // change the com
  return -1;
}



/* We assume that the buffer size is equal to the message size.
   Should be chekced durint Tx/Rx */
int controller_agent_deserialize_message(void *data, int size, Protocol__ProgranMessage **msg) {
  *msg = protocol__progran_message__unpack(NULL, size, data);
  if (*msg == NULL)
    goto error;

  return 0;
  
 error:
  //LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}



int prp_create_header(xid_t xid, Protocol__PrpType type,  Protocol__PrpHeader **header) {
  
  *header = malloc(sizeof(Protocol__PrpHeader));
  if(*header == NULL)
    goto error;
  
  protocol__prp_header__init(*header);
  (*header)->version = PROGRAN_VERSION;
  (*header)->has_version = 1; 
  // check if the type is set
  (*header)->type = type;
  (*header)->has_type = 1;
  (*header)->xid = xid;
  (*header)->has_xid = 1;
  return 0;

 error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

// Not needed but uncommented for compiling purposes
int controller_agent_hello(mid_t mod_id, const void *params, Protocol__ProgranMessage **msg) {
 
  Protocol__PrpHeader *header;
  /*TODO: Need to set random xid or xid from received hello message*/
  xid_t xid = 1;
  if (prp_create_header(xid, PROTOCOL__PRP_TYPE__PRPT_HELLO, &header) != 0)
    goto error;

  Protocol__PrpHello *hello_msg;
  hello_msg = malloc(sizeof(Protocol__PrpHello));
  if(hello_msg == NULL)
    goto error;
  protocol__prp_hello__init(hello_msg);
  hello_msg->header = header;

  *msg = malloc(sizeof(Protocol__ProgranMessage));
  if(*msg == NULL)
    goto error;
  
  protocol__progran_message__init(*msg);
  (*msg)->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_HELLO_MSG;
  (*msg)->msg_dir = PROTOCOL__PROGRAN_DIRECTION__SUCCESSFUL_OUTCOME;
  (*msg)->has_msg_dir = 1;
  (*msg)->hello_msg = hello_msg;
  return 0;
  
 error:
  if(header != NULL)
    free(header);
  if(hello_msg != NULL)
    free(hello_msg);
  if(*msg != NULL)
    free(*msg);
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_hello(Protocol__ProgranMessage *msg) {
  
  if(msg->msg_case != PROTOCOL__PROGRAN_MESSAGE__MSG_HELLO_MSG)
    goto error;
  
  free(msg->hello_msg->header);
  free(msg->hello_msg);
  free(msg);
  return 0;

 error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}


// int controller_agent_echo_request(mid_t mod_id, const void* params, Protocol__ProgranMessage **msg) {
//   Protocol__PrpHeader *header;
//   /*TODO: Need to set a random xid*/
//   xid_t xid = 1;
//   if (prp_create_header(xid, PROTOCOL__PRP_TYPE__PRPT_ECHO_REQUEST, &header) != 0)
//     goto error;

//   Protocol__PrpEchoRequest *echo_request_msg;
//   echo_request_msg = malloc(sizeof(Protocol__PrpEchoRequest));
//   if(echo_request_msg == NULL)
//     goto error;
//   protocol__prp_echo_request__init(echo_request_msg);
//   echo_request_msg->header = header;

//   *msg = malloc(sizeof(Protocol__ProgranMessage));
//   if(*msg == NULL)
//     goto error;
//   protocol__progran_message__init(*msg);
//   (*msg)->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_ECHO_REQUEST_MSG;
//   (*msg)->msg_dir = PROTOCOL__PROGRAN_DIRECTION__INITIATING_MESSAGE;
//   (*msg)->echo_request_msg = echo_request_msg;
//   return 0;

//  error:
//   if(header != NULL)
//     free(header);
//   if(echo_request_msg != NULL)
//     free(echo_request_msg);
//   if(*msg != NULL)
//     free(*msg);
//   //LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
//   return -1;
// }

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_echo_request(Protocol__ProgranMessage *msg) {
  if(msg->msg_case != PROTOCOL__PROGRAN_MESSAGE__MSG_ECHO_REQUEST_MSG)
    goto error;
  
  free(msg->echo_request_msg->header);
  free(msg->echo_request_msg);
  free(msg);
  return 0;
  
 error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}


// Not needed but uncommented for compiling purposes
int controller_agent_echo_reply(mid_t mod_id, const void *params, Protocol__ProgranMessage **msg) {
  
  xid_t xid;
  Protocol__ProgranMessage *input = (Protocol__ProgranMessage *)params;
  Protocol__PrpEchoRequest *echo_req = input->echo_request_msg;
  xid = (echo_req->header)->xid;

  Protocol__PrpHeader *header;
  if (prp_create_header(xid, PROTOCOL__PRP_TYPE__PRPT_ECHO_REPLY, &header) != 0)
    goto error;

  Protocol__PrpEchoReply *echo_reply_msg;
  echo_reply_msg = malloc(sizeof(Protocol__PrpEchoReply));
  if(echo_reply_msg == NULL)
    goto error;
  protocol__prp_echo_reply__init(echo_reply_msg);
  echo_reply_msg->header = header;

  *msg = malloc(sizeof(Protocol__ProgranMessage));
  if(*msg == NULL)
    goto error;
  protocol__progran_message__init(*msg);
  (*msg)->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_ECHO_REPLY_MSG;
  (*msg)->msg_dir = PROTOCOL__PROGRAN_DIRECTION__SUCCESSFUL_OUTCOME;
  (*msg)->has_msg_dir = 1;
  (*msg)->echo_reply_msg = echo_reply_msg;
  return 0;

 error:
  if(header != NULL)
    free(header);
  if(echo_reply_msg != NULL)
    free(echo_reply_msg);
  if(*msg != NULL)
    free(*msg);
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_echo_reply(Protocol__ProgranMessage *msg) {
  if(msg->msg_case != PROTOCOL__PROGRAN_MESSAGE__MSG_ECHO_REPLY_MSG)
    goto error;
  
  free(msg->echo_reply_msg->header);
  free(msg->echo_reply_msg);
  free(msg);
  return 0;
  
 error:
  LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
  return -1;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_enb_config_reply(Protocol__ProgranMessage *msg) {
	if(msg->msg_case != PROTOCOL__PROGRAN_MESSAGE__MSG_ENB_CONFIG_REPLY_MSG)
		goto error;
	free(msg->enb_config_reply_msg->header);
	int i, j;
	Protocol__PrpEnbConfigReply *reply = msg->enb_config_reply_msg;

	for(i = 0; i < reply->n_cell_config;i++){
		free(reply->cell_config[i]->mbsfn_subframe_config_rfoffset);
		free(reply->cell_config[i]->mbsfn_subframe_config_rfperiod);
		free(reply->cell_config[i]->mbsfn_subframe_config_sfalloc);
		for(j = 0; j < reply->cell_config[i]->si_config->n_si_message;j++){
			free(reply->cell_config[i]->si_config->si_message[j]);
		}
		free(reply->cell_config[i]->si_config->si_message);
		free(reply->cell_config[i]->si_config);
		free(reply->cell_config[i]);
	}
	free(reply->cell_config);
	free(reply);
	free(msg);

	return 0;
	error:
	//LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
	return -1;
}

// int controller_agent_ue_config_reply(mid_t mod_id, const void *params, Protocol__ProgranMessage **msg) {
//   /* TODO: Create a reply progRAN message with the current UE configurations */
//   return 0;
// }

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_ue_config_reply(Protocol__ProgranMessage *msg) {
  /*TODO: Deallocate memory for a dynamically allocated UE config message */
  return 0;
}

// Not needed but uncommented for compiling purposes
int controller_agent_lc_config_reply(mid_t mod_id, const void *params, Protocol__ProgranMessage **msg) {
  /* TODO: Create a reply progRAN message with the current LC configurations */
  return 0;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_lc_config_reply(Protocol__ProgranMessage *msg) {
  /* TODO: Deallocate memory for a dynamically allocated LC config message */
  return 0;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_enb_config_request(Protocol__ProgranMessage *msg) {
	if(msg->msg_case != PROTOCOL__PROGRAN_MESSAGE__MSG_ENB_CONFIG_REQUEST_MSG)
		goto error;
	free(msg->enb_config_request_msg->header);
	free(msg->enb_config_request_msg);
	free(msg);
	return 0;

	error:
	//LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
	return -1;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_ue_config_request(Protocol__ProgranMessage *msg) {
  /* TODO: Deallocate memory for a dynamically allocated UE config message */
  return 0;
}

// Not needed but uncommented for compiling purposes
int controller_agent_destroy_lc_config_request(Protocol__ProgranMessage *msg) {
  /* TODO: Deallocate memory for a dynamically allocated LC config message */
  return 0;
}

/*
 * get generic info from RAN
 */

// int get_current_time_ms (mid_t mod_id, int subframe_flag){

//   if (subframe_flag == 1){
//     return ((eNB_MAC_INST *)enb[mod_id])->frame*10 + ((eNB_MAC_INST *)enb[mod_id])->subframe;
//   }else {
//     return ((eNB_MAC_INST *)enb[mod_id])->frame*10;
//   }
   
// }

// unsigned int get_current_frame (mid_t mod_id) {

//   #warning "SFN will not be in [0-1023] when oaisim is used"
//   return ((eNB_MAC_INST *)enb[mod_id])->frame;
  
// }

// unsigned int get_current_system_frame_num(mid_t mod_id) {
//   return (get_current_frame(mod_id) %1024);
// }

// unsigned int get_current_subframe (mid_t mod_id) {

//   return ((eNB_MAC_INST *)enb[mod_id])->subframe;
  
// }

// uint16_t get_sfn_sf (mid_t mod_id) {
  
//   frame_t frame;
//   sub_frame_t subframe;
//   uint16_t sfn_sf, frame_mask, sf_mask;
  
//   frame = (frame_t) get_current_system_frame_num(mod_id);
//   subframe = (sub_frame_t) get_current_subframe(mod_id);
//   frame_mask = ((1<<12) - 1);
//   sf_mask = ((1<<4) -1);
//   sfn_sf = (subframe & sf_mask) | ((frame & frame_mask) << 4);
  
//   return sfn_sf;
// }

// int get_num_ues (mid_t mod_id){

//   return  ((UE_list_t *)enb_ue[mod_id])->num_UEs;
// }

// int get_ue_crnti (mid_t mod_id, mid_t ue_id){

//   return  ((UE_list_t *)enb_ue[mod_id])->eNB_UE_stats[UE_PCCID(mod_id,ue_id)][ue_id].crnti;
// }

// int get_ue_bsr (mid_t mod_id, mid_t ue_id, lcid_t lcid) {

//   return ((UE_list_t *)enb_ue[mod_id])->UE_template[UE_PCCID(mod_id,ue_id)][ue_id].bsr_info[lcid];
// }

// int get_ue_phr (mid_t mod_id, mid_t ue_id) {

//   return ((UE_list_t *)enb_ue[mod_id])->UE_template[UE_PCCID(mod_id,ue_id)][ue_id].phr_info;
// }

// int get_ue_wcqi (mid_t mod_id, mid_t ue_id) {

//   return ((UE_list_t *)enb_ue[mod_id])->eNB_UE_stats[UE_PCCID(mod_id,ue_id)][ue_id].dl_cqi;
// }
// int get_tx_queue_size(mid_t mod_id, mid_t ue_id, logical_chan_id_t channel_id)
// {
// 	rnti_t rnti = get_ue_crnti(mod_id,ue_id);
// 	uint16_t frame = (uint16_t) get_current_frame(mod_id);
// 	mac_rlc_status_resp_t rlc_status = mac_rlc_status_ind(mod_id,rnti, mod_id,frame,ENB_FLAG_YES,MBMS_FLAG_NO,channel_id,0);
// 	return rlc_status.bytes_in_buffer;
// }

// int get_MAC_CE_bitmap_TA(mid_t mod_id, mid_t ue_id)
// {
// 	if((((UE_list_t *)enb_ue[mod_id])->UE_sched_ctrl[ue_id].ta_update) > 0)
// 		return 1;
// 	else
// 		return 0;
// }

// int get_active_CC(mid_t mod_id, mid_t ue_id)
// {
// 	return ((UE_list_t *)enb_ue[mod_id])->numactiveCCs[ue_id];
// }

// int get_current_RI(mid_t mod_id, mid_t ue_id, int CC_id)
// {
// 	LTE_eNB_UE_stats *eNB_UE_stats = NULL;

// 	int pCCid = UE_PCCID(mod_id,ue_id);
// 	rnti_t rnti = get_ue_crnti(mod_id,ue_id);

// 	eNB_UE_stats = mac_xface->get_eNB_UE_stats(mod_id,CC_id,rnti);
// 	return eNB_UE_stats[CC_id].rank;
// }


/*
 * ************************************
 * Get Messages for eNB Configuration Reply
 * ************************************
 */

// int get_hopping_offset(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pusch_config_common.pusch_HoppingOffset;
// }
// int get_hopping_mode(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pusch_config_common.hoppingMode;
// }
// int get_n_SB(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pusch_config_common.n_SB;
// }
// int get_enable64QAM(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pusch_config_common.enable64QAM;
// }
// int get_phich_duration(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->phich_config_common.phich_duration;
// }
// int get_phich_resource(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	if(frame_parms->phich_config_common.phich_resource == oneSixth)
// 		return 0;
// 	else if(frame_parms->phich_config_common.phich_resource == half)
// 		return 1;
// 	else if(frame_parms->phich_config_common.phich_resource == one)
// 		return 2;
// 	else if(frame_parms->phich_config_common.phich_resource == two)
// 		return 3;

// 	return -1;
// }
// int get_n1pucch_an(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pucch_config_common.n1PUCCH_AN;
// }
// int get_nRB_CQI(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pucch_config_common.nRB_CQI;
// }
// int get_deltaPUCCH_Shift(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->pucch_config_common.deltaPUCCH_Shift;
// }
// int get_prach_ConfigIndex(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->prach_config_common.prach_ConfigInfo.prach_ConfigIndex;
// }
// int get_prach_FreqOffset(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->prach_config_common.prach_ConfigInfo.prach_FreqOffset;
// }
// int get_maxHARQ_Msg3Tx(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->maxHARQ_Msg3Tx;
// }
// int get_ul_cyclic_prefix_length(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->Ncp_UL;
// }
// int get_dl_cyclic_prefix_length(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->Ncp;
// }
// int get_cell_id(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->Nid_cell;
// }
// int get_srs_BandwidthConfig(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->soundingrs_ul_config_common.srs_BandwidthConfig;
// }
// int get_srs_SubframeConfig(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->soundingrs_ul_config_common.srs_SubframeConfig;
// }
// int get_srs_MaxUpPts(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->soundingrs_ul_config_common.srs_MaxUpPts;
// }
// int get_N_RB_DL(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->N_RB_DL;
// }
// int get_N_RB_UL(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->N_RB_UL;
// }
// int get_subframe_assignment(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->tdd_config;
// }
// int get_special_subframe_assignment(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	return frame_parms->tdd_config_S;
// }
// int get_ra_ResponseWindowSize(mid_t mod_id, int CC_id)
// {
// 	Enb_properties_array_t *enb_properties;
// 	enb_properties = enb_config_get();
// 	return enb_properties->properties[mod_id]->rach_raResponseWindowSize[CC_id];
// }
// int get_mac_ContentionResolutionTimer(mid_t mod_id, int CC_id)
// {
// 	Enb_properties_array_t *enb_properties;
// 	enb_properties = enb_config_get();
// 	return enb_properties->properties[mod_id]->rach_macContentionResolutionTimer[CC_id];
// }
// int get_duplex_mode(mid_t mod_id, int CC_id)
// {
// 	LTE_DL_FRAME_PARMS   *frame_parms;

// 	frame_parms = mac_xface->get_lte_frame_parms(mod_id, CC_id);
// 	if(frame_parms->frame_type == 0)
// 		return 1;
// 	else if (frame_parms->frame_type == 1)
// 		return 0;

// 	return -1;
// }
// long get_si_window_length(mid_t mod_id, int CC_id)
// {
// 	return  ((eNB_RRC_INST *)enb_rrc[mod_id])->carrier[CC_id].sib1->si_WindowLength;
// }
// int get_sib1_length(mid_t mod_id, int CC_id)
// {
// 	return  ((eNB_RRC_INST *)enb_rrc[mod_id])->carrier[CC_id].sizeof_SIB1;
// }
// int get_num_pdcch_symb(mid_t mod_id, int CC_id)
// {
// 	/*TODO: add these values to some struct in MAC
// 	LTE_UE_PDCCH *lte_ue_pdcch;
// 	lte_ue_pdcch = mac_xface->get_lte_ue_pdcch(mod_id, CC_id, mod_id);
// 	*/
// 	return (PHY_vars_UE_g[mod_id][CC_id]->lte_ue_pdcch_vars[mod_id]->num_pdcch_symbols);
// }

/*
 * timer primitives
 */

/*
 * ************************************
 * eNB Configuration Request and Reply
 * ************************************
 */

// int controller_agent_enb_config_request(mid_t mod_id, const void* params, Protocol__ProgranMessage **msg) {

// 	Protocol__PrpHeader *header;
// 	xid_t xid = 1;
// 	if(prp_create_header(xid,PROTOCOL__PRP_TYPE__PRPT_GET_ENB_CONFIG_REQUEST, &header) != 0)
// 		goto error;

// 	Protocol__PrpEnbConfigRequest *enb_config_request_msg;
// 	enb_config_request_msg = malloc(sizeof(Protocol__PrpEnbConfigRequest));

// 	if(enb_config_request_msg == NULL)
// 		goto error;

// 	protocol__prp_enb_config_request__init(enb_config_request_msg);
// 	enb_config_request_msg->header = header;

// 	*msg = malloc(sizeof(Protocol__ProgranMessage));
// 	if(*msg == NULL)
// 		goto error;

// 	protocol__progran_message__init(*msg);
// 	(*msg)->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_ENB_CONFIG_REQUEST_MSG;
// 	(*msg)->msg_dir = PROTOCOL__PROGRAN_DIRECTION__INITIATING_MESSAGE;
// 	(*msg)->enb_config_request_msg = enb_config_request_msg;
// 	return 0;

// 	error:
// 	  // TODO: Need to make proper error handling
// 	  if (header != NULL)
// 	    free(header);
// 	  if (enb_config_request_msg != NULL)
// 	    free(enb_config_request_msg);
// 	  if(*msg != NULL)
// 	    free(*msg);
// 	  //LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
// 	  return -1;
// }

// int controller_agent_enb_config_reply(mid_t mod_id, const void *params, Protocol__ProgranMessage **msg) {

// 	xid_t xid;
// 	Protocol__ProgranMessage *input = (Protocol__ProgranMessage *)params;
// 	Protocol__PrpEnbConfigRequest *enb_config_req_msg = input->enb_config_request_msg;
// 	xid = (enb_config_req_msg->header)->xid;

// 	int i, j, k;
// 	int cc_id = 0;
// 	int ctrl_id = mod_id;


// 	Protocol__PrpHeader *header;
// 	if(prp_create_header(xid, PROTOCOL__PRP_TYPE__PRPT_GET_ENB_CONFIG_REPLY, &header) != 0)
// 		goto error;

// 	Protocol__PrpEnbConfigReply *enb_config_reply_msg;
// 	enb_config_reply_msg = malloc(sizeof(Protocol__PrpEnbConfigReply));
// 	if(enb_config_reply_msg == NULL)
// 		goto error;
// 	protocol__prp_enb_config_reply__init(enb_config_reply_msg);
// 	enb_config_reply_msg->header = header;

// 	enb_config_reply_msg->ctrl_id = mod_id;


// 	enb_config_reply_msg->n_cell_config = MAX_NUM_CCs;

// 	Protocol__PrpCellConfig **cell_conf;
// 	if(enb_config_reply_msg->n_cell_config > 0){
// 		cell_conf = malloc(sizeof(Protocol__PrpCellConfig *) * enb_config_reply_msg->n_cell_config);
// 		if(cell_conf == NULL)
// 			goto error;
// 		for(i = 0; i < enb_config_reply_msg->n_cell_config; i++){
// 			cell_conf[i] = malloc(sizeof(Protocol__PrpCellConfig));
// 			protocol__prp_cell_config__init(cell_conf[i]);
// 			//TODO: Fill in with actual value, the PCI of this cell
// 			cell_conf[i]->phy_cell_id = 1;
// 			cell_conf[i]->has_phy_cell_id = 1;
// 			//TODO: Fill in with actual value, the PLMN cell id of this cell
// 			cell_conf[i]->cell_id = get_cell_id(ctrl_id,i);
// 			cell_conf[i]->has_cell_id = 1;
// 			//TODO: Fill in with actual value, PUSCH resources in RBs for hopping
// 			cell_conf[i]->pusch_hopping_offset = get_hopping_offset(ctrl_id,i);
// 			cell_conf[i]->has_pusch_hopping_offset = 1;
// 			//TODO: Fill in with actual value
// 			cell_conf[i]->hopping_mode = get_hopping_mode(ctrl_id,i);
// 			cell_conf[i]->has_hopping_mode = 1;
// 			//TODO: Fill in with actual value, the number of subbands
// 			cell_conf[i]->n_sb = get_n_SB(ctrl_id,i);
// 			cell_conf[i]->has_n_sb = 1;
// 			//TODO: Fill in with actual value, The number of resource element groups used for PHICH. One of PRPR_
// 			cell_conf[i]->phich_resource = get_phich_resource(ctrl_id,i);
// 			cell_conf[i]->has_phich_resource = 1;
// 			//TODO: Fill in with actual value, one of the PRPD_ values
// 			cell_conf[i]->phich_duration = get_phich_duration(ctrl_id,i);
// 			cell_conf[i]->has_phich_duration = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, section 6.9
// 			cell_conf[i]->init_nr_pdcch_ofdm_sym = get_num_pdcch_symb(ctrl_id,i);
// 			cell_conf[i]->has_init_nr_pdcch_ofdm_sym = 1;
// 			//TODO: Fill in with actual value
// 			Protocol__PrpSiConfig *si_config;
// 			si_config = malloc(sizeof(Protocol__PrpSiConfig));
// 			if(si_config == NULL)
// 				goto error;
// 			protocol__prp_si_config__init(si_config);
// 			//TODO: Fill in with actual value, Frame number to apply the SI configuration
// 			si_config->sfn = 1;
// 			si_config->has_sfn = 1;
// 			//TODO: Fill in with actual value, the length of SIB1 in bytes
// 			si_config->sib1_length = get_sib1_length(ctrl_id,i);
// 			si_config->has_sib1_length = 1;
// 			//TODO: Fill in with actual value, Scheduling window for all SIs in SF
// 			si_config->si_window_length = (uint32_t) get_si_window_length(ctrl_id,i);
// 			si_config->has_si_window_length = 1;
// 			//TODO: Fill in with actual value, the number of SI messages
// 			si_config->n_si_message=1;
// 			Protocol__PrpSiMessage **si_message;
// 			si_message = malloc(sizeof(Protocol__PrpSiMessage *) * si_config->n_si_message);
// 			if(si_message == NULL)
// 				goto error;
// 			for(j = 0; j < si_config->n_si_message; j++){
// 				si_message[j] = malloc(sizeof(Protocol__PrpSiMessage));
// 				if(si_message[j] == NULL)
// 					goto error;
// 				protocol__prp_si_message__init(si_message[j]);
// 				//TODO: Fill in with actual value, Periodicity of SI msg in radio frames
// 				si_message[j]->periodicity = 1;				//SIPeriod
// 				si_message[j]->has_periodicity = 1;
// 				//TODO: Fill in with actual value, rhe length of the SI message in bytes
// 				si_message[j]->length = 10;
// 				si_message[j]->has_length = 1;
// 			}
// 			if(si_config->n_si_message > 0){
// 				si_config->si_message = si_message;
// 			}
// 			cell_conf[i]->si_config = si_config;

// 			//TODO: Fill in with actual value, the DL transmission bandwidth in RBs
// 			cell_conf[i]->dl_bandwidth = get_N_RB_DL(ctrl_id,i);
// 			cell_conf[i]->has_dl_bandwidth = 1;
// 			//TODO: Fill in with actual value, the UL transmission bandwidth in RBs
// 			cell_conf[i]->ul_bandwidth = get_N_RB_UL(ctrl_id,i);
// 			cell_conf[i]->has_ul_bandwidth = 1;
// 			//TODO: Fill in with actual value, one of PRUCPL values
// 			cell_conf[i]->ul_cyclic_prefix_length = get_ul_cyclic_prefix_length(ctrl_id,i);
// 			cell_conf[i]->has_ul_cyclic_prefix_length = 1;
// 			//TODO: Fill in with actual value, one of PRUCPL values
// 			cell_conf[i]->dl_cyclic_prefix_length = get_dl_cyclic_prefix_length(ctrl_id,i);
// 			cell_conf[i]->has_dl_cyclic_prefix_length = 1;
// 			//TODO: Fill in with actual value, number of cell specific antenna ports
// 			cell_conf[i]->antenna_ports_count = 1;
// 			cell_conf[i]->has_antenna_ports_count = 1;
// 			//TODO: Fill in with actual value, one of PRDM values
// 			cell_conf[i]->duplex_mode = get_duplex_mode(ctrl_id,i);
// 			cell_conf[i]->has_duplex_mode = 1;
// 			//TODO: Fill in with actual value, DL/UL subframe assignment. TDD only
// 			cell_conf[i]->subframe_assignment = get_subframe_assignment(ctrl_id,i);
// 			cell_conf[i]->has_subframe_assignment = 1;
// 			//TODO: Fill in with actual value, TDD only. See TS 36.211, table 4.2.1
// 			cell_conf[i]->special_subframe_patterns = get_special_subframe_assignment(ctrl_id,i);
// 			cell_conf[i]->has_special_subframe_patterns = 1;
// 			//TODO: Fill in with actual value, The MBSFN radio frame period
// 			cell_conf[i]->n_mbsfn_subframe_config_rfperiod = 5;
// 			uint32_t *elem_rfperiod;
// 			elem_rfperiod = (uint32_t *) malloc(sizeof(uint32_t) *cell_conf[i]->n_mbsfn_subframe_config_rfperiod);
// 			if(elem_rfperiod == NULL)
// 				goto error;
// 			for(j = 0; j < cell_conf[i]->n_mbsfn_subframe_config_rfperiod; j++){
// 				elem_rfperiod[j] = 1;
// 			}
// 			cell_conf[i]->mbsfn_subframe_config_rfperiod = elem_rfperiod;

// 			//TODO: Fill in with actual value, The MBSFN radio frame offset
// 			cell_conf[i]->n_mbsfn_subframe_config_rfoffset = 5;
// 			uint32_t *elem_rfoffset;
// 			elem_rfoffset = (uint32_t *) malloc(sizeof(uint32_t) *cell_conf[i]->n_mbsfn_subframe_config_rfoffset);
// 			if(elem_rfoffset == NULL)
// 				goto error;
// 			for(j = 0; j < cell_conf[i]->n_mbsfn_subframe_config_rfoffset; j++){
// 				elem_rfoffset[j] = 1;
// 			}
// 			cell_conf[i]->mbsfn_subframe_config_rfoffset = elem_rfoffset;

// 			//TODO: Fill in with actual value, Bitmap indicating the MBSFN subframes
// 			cell_conf[i]->n_mbsfn_subframe_config_sfalloc = 5;
// 			uint32_t *elem_sfalloc;
// 			elem_sfalloc = (uint32_t *) malloc(sizeof(uint32_t) *cell_conf[i]->n_mbsfn_subframe_config_sfalloc);
// 			if(elem_sfalloc == NULL)
// 				goto error;
// 			for(j = 0; j < cell_conf[i]->n_mbsfn_subframe_config_sfalloc; j++){
// 				elem_sfalloc[j] = 1;
// 			}
// 			cell_conf[i]->mbsfn_subframe_config_sfalloc = elem_sfalloc;

// 			//TODO: Fill in with actual value, See TS 36.211, section 5.7.1
// 			cell_conf[i]->prach_config_index = get_prach_ConfigIndex(ctrl_id,i);
// 			cell_conf[i]->has_prach_config_index = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, section 5.7.1
// 			cell_conf[i]->prach_freq_offset = get_prach_FreqOffset(ctrl_id,i);
// 			cell_conf[i]->has_prach_freq_offset = 1;
// 			//TODO: Fill in with actual value, Duration of RA response window in SF
// 			cell_conf[i]->ra_response_window_size = get_ra_ResponseWindowSize(ctrl_id,i);
// 			cell_conf[i]->has_ra_response_window_size = 1;
// 			//TODO: Fill in with actual value, Timer used for RA
// 			cell_conf[i]->mac_contention_resolution_timer = get_mac_ContentionResolutionTimer(ctrl_id,i);
// 			cell_conf[i]->has_mac_contention_resolution_timer = 1;
// 			//TODO: Fill in with actual value, See TS 36.321
// 			cell_conf[i]->max_harq_msg3tx = get_maxHARQ_Msg3Tx(ctrl_id,i);
// 			cell_conf[i]->has_max_harq_msg3tx = 1;
// 			//TODO: Fill in with actual value, See TS 36.213, section 10.1
// 			cell_conf[i]->n1pucch_an = get_n1pucch_an(ctrl_id,i);
// 			cell_conf[i]->has_n1pucch_an = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, section 5.4
// 			cell_conf[i]->deltapucch_shift = get_deltaPUCCH_Shift(ctrl_id,i);
// 			cell_conf[i]->has_deltapucch_shift = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, section 5.4
// 			cell_conf[i]->nrb_cqi = get_nRB_CQI(ctrl_id,i);
// 			cell_conf[i]->has_nrb_cqi = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, table 5.5.3.3-1 and 2
// 			cell_conf[i]->srs_subframe_config = get_srs_SubframeConfig(ctrl_id,i);
// 			cell_conf[i]->has_srs_subframe_config = 1;
// 			//TODO: Fill in with actual value, See TS 36.211, section 5.5.3.2
// 			cell_conf[i]->srs_bw_config = get_srs_BandwidthConfig(ctrl_id,i);
// 			cell_conf[i]->has_srs_bw_config = 1;
// 			//TODO: Fill in with actual value, Boolean value. See TS 36.211, section 5.5.3.2. TDD only
// 			cell_conf[i]->srs_mac_up_pts = get_srs_MaxUpPts(ctrl_id,i);
// 			cell_conf[i]->has_srs_mac_up_pts = 1;
// 			//TODO: Fill in with actual value, One of the PREQ_ values
// 			cell_conf[i]->enable_64qam = get_enable64QAM(ctrl_id,i);
// 			cell_conf[i]->has_enable_64qam = 1;
// 			//TODO: Fill in with actual value, Carrier component index
// 			cell_conf[i]->carrier_index = i;
// 			cell_conf[i]->has_carrier_index = 1;
// 		}
// 		enb_config_reply_msg->cell_config=cell_conf;
// 	}
// 	*msg = malloc(sizeof(Protocol__ProgranMessage));
// 	if(*msg == NULL)
// 		goto error;
// 	protocol__progran_message__init(*msg);
// 	(*msg)->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_ENB_CONFIG_REPLY_MSG;
// 	(*msg)->msg_dir = PROTOCOL__PROGRAN_DIRECTION__SUCCESSFUL_OUTCOME;
// 	(*msg)->enb_config_reply_msg = enb_config_reply_msg;
// 	return 0;

// 	 error:
// 	  // TODO: Need to make proper error handling
// 	 if (header != NULL)
// 	   free(header);
// 	 if (enb_config_reply_msg != NULL)
// 	   free(enb_config_reply_msg);
// 	 if(*msg != NULL)
// 	   free(*msg);
// 	 //LOG_E(MAC, "%s: an error occured\n", __FUNCTION__);
// 	 return -1;
// }


// //struct controller_agent_map agent_map;
// controller_agent_timer_instance_t timer_instance;
// err_code_t controller_agent_init_timer(void){
  
//   LOG_I(CONTROLLER_AGENT, "init RB tree\n");

//   RB_INIT(&timer_instance.controller_agent_head);
 
//   /*
//     struct controller_agent_timer_element_s e;
//   memset(&e, 0, sizeof(controller_agent_timer_element_t));
//   RB_INSERT(controller_agent_map, &agent_map, &e); 
//   */
//  return PROTOCOL__PROGRAN_ERR__NO_ERR;
// }

// RB_GENERATE(controller_agent_map,controller_agent_timer_element_s, entry, controller_agent_compare_timer);

// /* The timer_id might not be the best choice for the comparison */
// int controller_agent_compare_timer(struct controller_agent_timer_element_s *a, struct controller_agent_timer_element_s *b){

//   if (a->timer_id < b->timer_id) return -1;
//   if (a->timer_id > b->timer_id) return 1;

//   // equal timers
//   return 0;
// }

// err_code_t controller_agent_create_timer(uint32_t interval_sec,
// 				  uint32_t interval_usec,
// 				  agent_id_t     agent_id,
// 				  instance_t     instance,
// 				  uint32_t timer_type,
// 				  xid_t xid,
// 				  controller_agent_timer_callback_t cb,
// 				  void*    timer_args,
// 				  long *timer_id){
  
//   struct controller_agent_timer_element_s *e = calloc(1, sizeof(*e));
//   DevAssert(e != NULL);
  
// //uint32_t timer_id;
//   int ret=-1;
  
//   if ((interval_sec == 0) && (interval_usec == 0 ))
//     return TIMER_NULL;
  
//   if (timer_type >= CONTROLLER_AGENT_TIMER_TYPE_MAX)
//     return TIMER_TYPE_INVALIDE;
  
//   if (timer_type  ==   CONTROLLER_AGENT_TIMER_TYPE_ONESHOT){ 
//     ret = timer_setup(interval_sec, 
// 		      interval_usec, 
// 		      TASK_CONTROLLER_AGENT, 
// 		      instance, 
// 		      TIMER_ONE_SHOT,
// 		      timer_args,
// 		      timer_id);
    
//     e->type = TIMER_ONE_SHOT;
//   }
//   else if (timer_type  ==   CONTROLLER_AGENT_TIMER_TYPE_PERIODIC ){
//     ret = timer_setup(interval_sec, 
// 		      interval_usec, 
// 		      TASK_CONTROLLER_AGENT, 
// 		      instance, 
// 		      TIMER_PERIODIC,
// 		      timer_args,
// 		      timer_id);
    
//     e->type = TIMER_PERIODIC;
//   }
  
//   if (ret < 0 ) {
//     return TIMER_SETUP_FAILED; 
//   }

//   e->agent_id = agent_id;
//   e->instance = instance;
//   e->state = CONTROLLER_AGENT_TIMER_STATE_ACTIVE;
//   e->timer_id = *timer_id;
//   e->xid = xid;
//   e->timer_args = timer_args; 
//   e->cb = cb;
//   /*element should be a real pointer*/
//   RB_INSERT(controller_agent_map, &timer_instance.controller_agent_head, e); 
  
//   LOG_I(CONTROLLER_AGENT,"Created a new timer with id 0x%lx for agent %d, instance %d \n",
// 	e->timer_id, e->agent_id, e->instance);
 
//   return 0; 
// }

// err_code_t controller_agent_destroy_timer(long timer_id){
  
//   struct controller_agent_timer_element_s *e = get_timer_entry(timer_id);

//   if (e != NULL ) {
//     RB_REMOVE(controller_agent_map, &timer_instance.controller_agent_head, e);
//     controller_agent_destroy_progran_message(e->timer_args->msg);
//     free(e);
//   }
  
//   if (timer_remove(timer_id) < 0 ) 
//     goto error;
  
//   return 0;

//  error:
//   LOG_E(CONTROLLER_AGENT, "timer can't be removed\n");
//   return TIMER_REMOVED_FAILED ;
// }

// err_code_t controller_agent_destroy_timer_by_task_id(xid_t xid) {
//   struct controller_agent_timer_element_s *e = NULL;
//   long timer_id;
//   RB_FOREACH(e, controller_agent_map, &timer_instance.controller_agent_head) {
//     if (e->xid == xid) {
//       timer_id = e->timer_id;
//       RB_REMOVE(controller_agent_map, &timer_instance.controller_agent_head, e);
//       controller_agent_destroy_progran_message(e->timer_args->msg);
//       free(e);
//       if (timer_remove(timer_id) < 0 ) { 
// 	goto error;
//       }
//     }
//   }
//   return 0;

//  error:
//   LOG_E(CONTROLLER_AGENT, "timer can't be removed\n");
//   return TIMER_REMOVED_FAILED ;
// }

// err_code_t controller_agent_destroy_timers(void){
  
//   struct controller_agent_timer_element_s *e = NULL;
  
//   RB_FOREACH(e, controller_agent_map, &timer_instance.controller_agent_head) {
//     RB_REMOVE(controller_agent_map, &timer_instance.controller_agent_head, e);
//     timer_remove(e->timer_id);
//     controller_agent_destroy_progran_message(e->timer_args->msg);
//     free(e);
//   }  

//   return 0;

// }

// void controller_agent_sleep_until(struct timespec *ts, int delay) {
//   ts->tv_nsec += delay;
//   if(ts->tv_nsec >= 1000*1000*1000){
//     ts->tv_nsec -= 1000*1000*1000;
//     ts->tv_sec++;
//   }
//   clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  NULL);
// }

// /*
//  int i =0;
//   RB_FOREACH(e, controller_agent_map, &controller_agent_head) {
//     printf("%d: %p\n", i, e); i++;
//     }
// */


// err_code_t controller_agent_stop_timer(long timer_id){
  
//   struct controller_agent_timer_element_s *e=NULL;
//   struct controller_agent_timer_element_s search;
//   memset(&search, 0, sizeof(struct controller_agent_timer_element_s));
//   search.timer_id = timer_id;

//   e = RB_FIND(controller_agent_map, &timer_instance.controller_agent_head, &search);

//   if (e != NULL ) {
//     e->state =  CONTROLLER_AGENT_TIMER_STATE_STOPPED;
//   }
  
//   timer_remove(timer_id);
  
//   return 0;
// }

// struct controller_agent_timer_element_s * get_timer_entry(long timer_id) {
  
//   struct controller_agent_timer_element_s search;
//   memset(&search, 0, sizeof(struct controller_agent_timer_element_s));
//   search.timer_id = timer_id;

//   return  RB_FIND(controller_agent_map, &timer_instance.controller_agent_head, &search); 
// }

/*
// this will change the timer_id
err_code_t controller_agent_restart_timer(uint32_t *timer_id){
  
  struct controller_agent_timer_element_s *e=NULL;
    
  RB_FOREACH(e, controller_agent_map, &controller_agent_head) {
    if (e->timer_id == timer_id)
      break;
  }

  if (e != NULL ) {
    e->state =  CONTROLLER_AGENT_TIMER_STATE_ACTIVE;
  }
  
  ret = timer_setup(e->interval_sec, 
		    e->interval_usec, 
		    e->agent_id, 
		    e->instance, 
		    e->type,
		    e->timer_args,
		    &timer_id);
    
  }

  if (ret < 0 ) {
    return PROTOCOL__PROGRAN_ERR__TIMER_SETUP_FAILED; 
  }
  
  return 0;

}

*/
