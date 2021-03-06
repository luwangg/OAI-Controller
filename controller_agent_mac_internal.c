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

/*! \file controller_agent_mac_internal.c
 * \brief Helper functions for the MAC agent
 * \author Xenofon Foukas
 * \date 2016
 * \version 0.1
 */

#include "controller_agent_mac_internal.h"

Protocol__ProgranMessage * controller_agent_generate_diff_mac_stats_report(Protocol__ProgranMessage *new_message,
								    Protocol__ProgranMessage *old_message) {

  int i, j;
  
  Protocol__PrpStatsReply *old_report, *new_report;

  Protocol__PrpStatsReply *stats_reply_msg = NULL;
  Protocol__ProgranMessage *msg = NULL;
  
  Protocol__PrpUeStatsReport **ue_report;
  Protocol__PrpUeStatsReport *tmp_ue_report[NUM_MAX_UE];
  Protocol__PrpCellStatsReport **cell_report;
  Protocol__PrpCellStatsReport *tmp_cell_report[NUM_MAX_UE];
  
  old_report = old_message->stats_reply_msg;
  new_report = new_message->stats_reply_msg;

  /*Flags to designate changes in various levels of the message*/
  int stats_had_changes = 0;
  int ue_had_change = 0;
  int cell_had_change = 0;

  /*See how many and which UE reports should be included in the final stats message*/
  int n_ue_report = 0;
  int ue_found = 0;
  
  /*Go through each RNTI of the new report and see if it exists in the old one*/
  for (i = 0; i < new_report->n_ue_report; i++) {
    for (j = 0; j < old_report->n_ue_report; i++) {
     if (new_report->ue_report[i]->rnti == old_report->ue_report[j]->rnti) {
  	ue_found = 1;
	/*Need to check if something changed*/
	if (compare_ue_stats_reports(new_report->ue_report[i], old_report->ue_report[j]) != 0) {
	  tmp_ue_report[n_ue_report] = copy_ue_stats_report(new_report->ue_report[i]);
	  n_ue_report++;
	}
	break;
     }
    }
    if (!ue_found) {
      tmp_ue_report[n_ue_report] = copy_ue_stats_report(new_report->ue_report[i]);
      n_ue_report++;
    }
    ue_found = 0;
  }

  /*See how many and which cell reports should be included in the final stats message*/
  int n_cell_report = 0;
  int cell_found = 0;
  
  /*Go through each cell of the new report and see if it exists in the old one*/
  for (i = 0; i < new_report->n_cell_report; i++) {
    for (j = 0; j < old_report->n_cell_report; i++) {
     if (new_report->cell_report[i]->carrier_index == old_report->cell_report[j]->carrier_index) {
  	cell_found = 1;
	/*Need to check if something changed*/
	if (compare_cell_stats_reports(new_report->cell_report[i], old_report->cell_report[j]) != 0) {
	  tmp_cell_report[n_cell_report] = copy_cell_stats_report(new_report->cell_report[i]);
	  n_cell_report++;
	}
	break;
     }
    }
    if (!cell_found) {
      tmp_cell_report[n_cell_report] = copy_cell_stats_report(new_report->cell_report[i]);
      n_cell_report++;
    }
    cell_found = 0;
  }

  /*TODO: create the reply message based on the findings*/
  /*Create ue report list*/
  if (n_ue_report > 0) {
    ue_report = malloc(sizeof(Protocol__PrpUeStatsReport *));
    for (i = 0; i<n_ue_report; i++) {
      ue_report[i] = tmp_ue_report[i];
    }
  }

  /*Create cell report list*/
  if (n_cell_report > 0) {
    cell_report = malloc(sizeof(Protocol__PrpCellStatsReport *));
    for (i = 0; i<n_cell_report; i++) {
      cell_report[i] = tmp_cell_report[i];
    }
  }
  
  if (n_cell_report > 0 || n_ue_report > 0) {
    /*Create header*/
    int xid = old_report->header->xid;
    Protocol__PrpHeader *header;
    if (prp_create_header(xid, PROTOCOL__PRP_TYPE__PRPT_STATS_REPLY, &header) != 0) {
    goto error;
    }
    stats_reply_msg = malloc(sizeof(Protocol__PrpStatsReply));
    protocol__prp_stats_reply__init(stats_reply_msg);
    stats_reply_msg->header = header;
    stats_reply_msg->n_ue_report = n_ue_report;
    stats_reply_msg->ue_report = ue_report;
    stats_reply_msg->n_cell_report = n_cell_report;
    stats_reply_msg->cell_report = cell_report;
    msg = malloc(sizeof(Protocol__ProgranMessage));
    if(msg == NULL)
      goto error;
    protocol__progran_message__init(msg);
    msg->msg_case = PROTOCOL__PROGRAN_MESSAGE__MSG_STATS_REPLY_MSG;
    msg->msg_dir = PROTOCOL__PROGRAN_DIRECTION__SUCCESSFUL_OUTCOME;
    msg->stats_reply_msg = stats_reply_msg;
  }
  return msg;
  
 error:
   return NULL;
}

int compare_ue_stats_reports(Protocol__PrpUeStatsReport *rep1,
			    Protocol__PrpUeStatsReport *rep2) {
  return 1;
}

int compare_cell_stats_reports(Protocol__PrpCellStatsReport *rep1,
			      Protocol__PrpCellStatsReport *rep2) {
  return 1;
}

Protocol__PrpUeStatsReport * copy_ue_stats_report(Protocol__PrpUeStatsReport * original) {
  int i;
  Protocol__PrpUeStatsReport *copy =  malloc(sizeof(Protocol__PrpUeStatsReport));
  if (copy == NULL)
    goto error;
  protocol__prp_ue_stats_report__init(copy);
  copy->rnti = original->rnti;
  copy->has_rnti = original->has_rnti;
  copy->flags = original->flags;
  copy->has_flags = original->has_flags;
  
  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_BSR) {
    copy->n_bsr = original->n_bsr;
    if (copy->n_bsr > 0) {
      uint32_t *elem;
      elem = (uint32_t *) malloc(sizeof(uint32_t)*copy->n_bsr);
      if (elem == NULL)
	goto error;
      for (i = 0; i < original->n_bsr; i++) {
	elem[i] = original->bsr[i];
      }
      copy->bsr = elem;
    }
  }

  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_PRH) {
    copy->has_phr = original->has_phr;
    copy->phr = original->phr;
  }

  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_RLC_BS) {
    copy->n_rlc_report = original->n_rlc_report; 
    if (copy->n_rlc_report > 0) {
      Protocol__PrpRlcBsr ** rlc_reports;
      rlc_reports = malloc(sizeof(Protocol__PrpRlcBsr) * copy->n_rlc_report);
      if (rlc_reports == NULL)
	goto error;
      for (i = 0; i < copy->n_rlc_report; i++) {
	rlc_reports[i] = copy_rlc_report(original->rlc_report[i]);
      }
      copy->rlc_report = rlc_reports;
    }
  }

  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_MAC_CE_BS) {
    copy->has_pending_mac_ces = original->has_pending_mac_ces;
    copy->pending_mac_ces = original->pending_mac_ces;
  
  }
  
  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_DL_CQI) {
    copy->dl_cqi_report = copy_dl_cqi_report(original->dl_cqi_report);
  }

  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_PBS) {  
    /*Copy the Paging Buffer report*/
    copy->pbr = copy_paging_buffer_report(original->pbr);
  }

  if (copy->flags & PROTOCOL__PRP_UE_STATS_TYPE__PRUST_UL_CQI) {
    /*TODO: Copy the UL report*/  
    copy->ul_cqi_report = copy_ul_cqi_report(original->ul_cqi_report);
  }

  return copy;

 error:
  return NULL;
}

Protocol__PrpRlcBsr * copy_rlc_report(Protocol__PrpRlcBsr * original) {
  Protocol__PrpRlcBsr * copy = malloc(sizeof(Protocol__PrpRlcBsr));
  if (copy == NULL)
    goto error;
  protocol__prp_rlc_bsr__init(copy);
  copy->lc_id = original->lc_id;
  copy->has_lc_id = original->has_lc_id;
  copy->tx_queue_size = original->tx_queue_size;
  copy->has_tx_queue_size = original->has_tx_queue_size;
  copy->tx_queue_hol_delay = original->tx_queue_hol_delay;
  copy->has_tx_queue_hol_delay = original->has_tx_queue_hol_delay;
  copy->retransmission_queue_size = original->retransmission_queue_size;
  copy->has_retransmission_queue_size = original->has_retransmission_queue_size;
  copy->retransmission_queue_hol_delay = original->retransmission_queue_hol_delay;
  copy->has_retransmission_queue_hol_delay = original->has_retransmission_queue_hol_delay;
  copy->status_pdu_size = original->status_pdu_size;
  copy->has_status_pdu_size = original->has_status_pdu_size;
  
  return copy;

 error:
  return NULL;
}

Protocol__PrpUlCqiReport * copy_ul_cqi_report(Protocol__PrpUlCqiReport * original) {
  int i, j;
  
  //Fill in the full UL CQI report of the UE
  Protocol__PrpUlCqiReport *full_ul_report;
  full_ul_report = malloc(sizeof(Protocol__PrpUlCqiReport));
  if(full_ul_report == NULL) {
    goto error;
  }
  protocol__prp_ul_cqi_report__init(full_ul_report);
  //TODO:Set the SFN and SF of the generated report
  full_ul_report->sfn_sn = original->sfn_sn;
  full_ul_report->has_sfn_sn = original->has_sfn_sn;
  full_ul_report->n_cqi_meas = original->n_cqi_meas;

  Protocol__PrpUlCqi **ul_report;
  ul_report = malloc(sizeof(Protocol__PrpUlCqi *) * full_ul_report->n_cqi_meas);
  if(ul_report == NULL)
    goto error;
  for(i = 0; i++; i < full_ul_report->n_cqi_meas) {
    ul_report[i] = malloc(sizeof(Protocol__PrpUlCqi));
    if(ul_report[i] == NULL)
      goto error;
    protocol__prp_ul_cqi__init(ul_report[i]);
    ul_report[i]->type = original->cqi_meas[i]->type;
    ul_report[i]->has_type = original->cqi_meas[i]->has_type;
    ul_report[i]->n_sinr = original->cqi_meas[i]->n_sinr;
    uint32_t *sinr_meas;
    sinr_meas = (uint32_t *) malloc(sizeof(uint32_t) * ul_report[i]->n_sinr);
    if (sinr_meas == NULL)
      goto error;
    for (j = 0; j < ul_report[i]->n_sinr; j++) {
      sinr_meas[j] = original->cqi_meas[i]->sinr[j];
    }
    ul_report[i]->sinr = sinr_meas;
    ul_report[i]->serv_cell_index = original->cqi_meas[i]->serv_cell_index;
    ul_report[i]->has_serv_cell_index = original->cqi_meas[i]->has_serv_cell_index;
  }
  full_ul_report->cqi_meas = ul_report;

  return full_ul_report;
  
  error:
    return NULL;
}

Protocol__PrpDlCqiReport * copy_dl_cqi_report(Protocol__PrpDlCqiReport * original) {
  int i;
  /*Copy the DL report*/
  Protocol__PrpDlCqiReport * dl_report;
  dl_report = malloc(sizeof(Protocol__PrpDlCqiReport));
  if (dl_report == NULL)
    goto error;
  protocol__prp_dl_cqi_report__init(dl_report);

  dl_report->sfn_sn = original->sfn_sn;
  dl_report->has_sfn_sn = original->has_sfn_sn;
  dl_report->n_csi_report = original->n_csi_report;

  Protocol__PrpDlCsi **csi_reports;
  csi_reports = malloc(sizeof(Protocol__PrpDlCsi *) * dl_report->n_csi_report);
  if (csi_reports == NULL)
    goto error;
  
  for (i = 0; i < dl_report->n_csi_report; i++) {
    csi_reports[i] = copy_csi_report(original->csi_report[i]); 
  }
  dl_report->csi_report = csi_reports;
  return dl_report;

 error:
  /*TODO: Must free memory properly*/
  return NULL;
}

Protocol__PrpPagingBufferReport * copy_paging_buffer_report(Protocol__PrpPagingBufferReport *original) {
  
  int i;
  Protocol__PrpPagingBufferReport *copy;
  copy = malloc(sizeof(Protocol__PrpPagingBufferReport));
  if (copy == NULL)
    goto error;
  
  protocol__prp_paging_buffer_report__init(copy);
  copy->n_paging_info = original->n_paging_info;
  
  Protocol__PrpPagingInfo **p_info;
  p_info = malloc(sizeof(Protocol__PrpPagingInfo *) * copy->n_paging_info);
  if (p_info == NULL)
    goto error;
  for (i = 0; i < copy->n_paging_info; i++) {
    p_info[i] = malloc(sizeof(Protocol__PrpPagingInfo));
    if(p_info[i] == NULL)
      goto error;
    protocol__prp_paging_info__init(p_info[i]);
    p_info[i]->paging_index = original->paging_info[i]->paging_index;
    p_info[i]->has_paging_index = original->paging_info[i]->has_paging_index;;
    p_info[i]->paging_message_size = original->paging_info[i]->paging_message_size;
    p_info[i]->has_paging_message_size =  original->paging_info[i]->has_paging_message_size;
    p_info[i]->paging_subframe = original->paging_info[i]->paging_subframe;
    p_info[i]->has_paging_subframe = original->paging_info[i]->has_paging_subframe;
    p_info[i]->carrier_index = original->paging_info[i]->carrier_index;
    p_info[i]->has_carrier_index = original->paging_info[i]->has_carrier_index;
  }
  copy->paging_info = p_info;
  return copy;

 error:
  /*TODO: free memory properly*/
  return NULL;
}

Protocol__PrpDlCsi * copy_csi_report(Protocol__PrpDlCsi * original) {
  int i, j;
  Protocol__PrpDlCsi *copy = malloc(sizeof(Protocol__PrpDlCsi));
  if (copy == NULL)
    goto error;
  protocol__prp_dl_csi__init(copy);
  copy->serv_cell_index = original->serv_cell_index;
  copy->has_serv_cell_index = original->has_serv_cell_index;
  copy->ri = original->ri;
  copy->has_ri = original->ri;

  copy->type = original->type;
  copy->has_type = original->has_type;
  copy->report_case = original->report_case;
  
  switch (copy->report_case) {
  case PROTOCOL__PRP_DL_CSI__REPORT_P10CSI:
    copy->p10csi->wb_cqi = original->p10csi->wb_cqi;
    copy->p10csi->has_wb_cqi = original->p10csi->has_wb_cqi;
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_P11CSI:
    copy->p11csi->n_wb_cqi = original->p11csi->n_wb_cqi;
    copy->p11csi->wb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->p11csi->n_wb_cqi);
    for (i = 0; i < copy->p11csi->n_wb_cqi; i++) {
      copy->p11csi->wb_cqi[i] = original->p11csi->wb_cqi[i];
    }
    copy->p11csi->has_wb_pmi = original->p11csi->has_wb_pmi;
    copy->p11csi->wb_pmi = original->p11csi->wb_pmi;
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_P20CSI:
    copy->p20csi->has_wb_cqi = original->p20csi->has_wb_cqi;
    copy->p20csi->wb_cqi = original->p20csi->wb_cqi;
    copy->p20csi->has_sb_cqi = original->p20csi->has_sb_cqi;
    copy->p20csi->sb_cqi = original->p20csi->sb_cqi;
    copy->p20csi->has_bandwidth_part_index = original->p20csi->has_bandwidth_part_index;
    copy->p20csi->bandwidth_part_index = original->p20csi->bandwidth_part_index;
    copy->p20csi->has_sb_index = original->p20csi->has_sb_index;
    copy->p20csi->sb_index = original->p20csi->sb_index;
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_P21CSI:
    copy->p21csi->n_wb_cqi = original->p21csi->n_wb_cqi;
    copy->p21csi->wb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->p21csi->n_wb_cqi);
    for (i = 0; i < copy->p21csi->n_wb_cqi; i++) {
      copy->p21csi->wb_cqi[i] = original->p21csi->wb_cqi[i];
    }
    copy->p21csi->has_wb_pmi = original->p21csi->has_wb_pmi;
    copy->p21csi->wb_pmi = original->p21csi->wb_pmi;
    copy->p21csi->n_sb_cqi = original->p21csi->n_sb_cqi;
    copy->p21csi->sb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->p21csi->n_sb_cqi);
    for (i = 0; i < copy->p21csi->n_sb_cqi; i++) {
      copy->p21csi->sb_cqi[i] = original->p21csi->sb_cqi[i];
    }
     copy->p21csi->has_badwidth_part_index = original->p21csi->has_badwidth_part_index;
    copy->p21csi->badwidth_part_index = original->p21csi->badwidth_part_index;
    copy->p21csi->has_sb_index = original->p21csi->has_sb_index;
    copy->p21csi->sb_index = original->p21csi->sb_index;
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_A12CSI:
    copy->a12csi->n_wb_cqi = original->a12csi->n_wb_cqi;
    copy->a12csi->wb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a12csi->n_wb_cqi);
    for (i = 0; i < copy->a12csi->n_wb_cqi; i++) {
      copy->a12csi->wb_cqi[i] = original->a12csi->wb_cqi[i];
    }
    copy->a12csi->n_sb_pmi = original->a12csi->n_sb_pmi;
    copy->a12csi->sb_pmi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a12csi->n_sb_pmi);
    for (i = 0; i < copy->a12csi->n_sb_pmi; i++) {
      copy->a12csi->sb_pmi[i] = original->a12csi->sb_pmi[i];
    }
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_A22CSI:
    copy->a22csi->n_wb_cqi = original->a22csi->n_wb_cqi;
    copy->a22csi->wb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a22csi->n_wb_cqi);
    for (i = 0; i < copy->a22csi->n_wb_cqi; i++) {
      copy->a22csi->wb_cqi[i] = original->a22csi->wb_cqi[i];
    }
    copy->a22csi->n_sb_cqi = original->a22csi->n_sb_cqi;
    copy->a22csi->sb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a22csi->n_sb_cqi);
    for (i = 0; i < copy->a22csi->n_sb_cqi; i++) {
      copy->a22csi->sb_cqi[i] = original->a22csi->sb_cqi[i];
    }
    copy->a22csi->has_wb_pmi = original->a22csi->has_wb_pmi;
    copy->a22csi->wb_pmi = original->a22csi->wb_pmi;
    copy->a22csi->has_sb_pmi = original->a22csi->has_sb_pmi;
    copy->a22csi->sb_pmi = original->a22csi->sb_pmi;
    copy->a22csi->n_sb_list = original->a22csi->n_sb_list;
    copy->a22csi->sb_list = (uint32_t *) malloc(sizeof(uint32_t) * copy->a22csi->n_sb_list);
    for (i = 0; i < copy->a22csi->n_sb_list; i++) {
      copy->a22csi->sb_list[i] = original->a22csi->sb_list[i];
    }
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_A20CSI:
    copy->a20csi->has_wb_cqi = original->a20csi->has_wb_cqi;
    copy->a20csi->wb_cqi = original->a20csi->wb_cqi;
    copy->a20csi->has_sb_cqi = original->a20csi->has_sb_cqi;
    copy->a20csi->sb_cqi = original->a20csi->sb_cqi;
    copy->a20csi->n_sb_list = original->a20csi->n_sb_list;
    copy->a20csi->sb_list = (uint32_t *) malloc(sizeof(uint32_t) * copy->a20csi->n_sb_list);
    for (i = 0; i < copy->a20csi->n_sb_list; i++) {
      copy->a20csi->sb_list[i] = original->a20csi->sb_list[i];
    }
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_A30CSI:
    copy->a30csi->has_wb_cqi = original->a30csi->has_wb_cqi;
    copy->a30csi->wb_cqi = original->a30csi->wb_cqi;
    copy->a30csi->n_sb_cqi = original->a30csi->n_sb_cqi;
    copy->a30csi->sb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a30csi->n_sb_cqi);
    for (i = 0; i < copy->a30csi->n_sb_cqi; i++) {
      copy->a30csi->sb_cqi[i] = original->a30csi->sb_cqi[i];
    }
    break;
  case PROTOCOL__PRP_DL_CSI__REPORT_A31CSI:
    copy->a31csi->n_wb_cqi = original->a31csi->n_wb_cqi;
    copy->a31csi->wb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a31csi->n_wb_cqi);
    for (i = 0; i < copy->a31csi->n_wb_cqi; i++) {
      copy->a31csi->wb_cqi[i] = original->a31csi->wb_cqi[i];
    }
    copy->a31csi->has_wb_pmi = original->a31csi->has_wb_pmi;
    copy->a31csi->wb_pmi = original->a31csi->wb_pmi;
    copy->a31csi->n_sb_cqi = original->a31csi->n_sb_cqi;
    copy->a31csi->sb_cqi = malloc(sizeof(Protocol__PrpMsbCqi *) * copy->a31csi->n_sb_cqi);
    if (copy->a31csi == NULL) {
      goto error;
    }
    for (i = 0; i < copy->a31csi->n_sb_cqi; i++) {
      copy->a31csi->sb_cqi[i] = malloc(sizeof(Protocol__PrpMsbCqi));
      if (copy->a31csi->sb_cqi[i] == NULL) {
	goto error;
      }
      protocol__prp_msb_cqi__init(copy->a31csi->sb_cqi[i]);
      copy->a31csi->sb_cqi[i]->n_sb_cqi = original->a31csi->sb_cqi[i]->n_sb_cqi;
      copy->a31csi->sb_cqi[i]->sb_cqi = (uint32_t *) malloc(sizeof(uint32_t) * copy->a31csi->sb_cqi[i]->n_sb_cqi);
      for (j = 0; j < copy->a31csi->sb_cqi[i]->n_sb_cqi; j++) {
	copy->a31csi->sb_cqi[i]->sb_cqi[j] = original->a31csi->sb_cqi[i]->sb_cqi[j];
      }
    }
    break;
  default:
    goto error;
  }
  return copy;

 error:
  return NULL;
}

Protocol__PrpCellStatsReport * copy_cell_stats_report(Protocol__PrpCellStatsReport *original) {
 
  Protocol__PrpCellStatsReport * copy =  malloc(sizeof(Protocol__PrpCellStatsReport));
  
  if(copy == NULL) {
    goto error;
  }
  protocol__prp_cell_stats_report__init(copy);
  copy->carrier_index = original->carrier_index;
  copy->has_carrier_index = original->has_carrier_index;
  copy->flags = original->flags;
  copy->has_flags = original->has_flags;

   if(copy->flags & PROTOCOL__PRP_CELL_STATS_TYPE__PRCST_NOISE_INTERFERENCE) {
     copy->noise_inter_report = copy_noise_inter_report(original->noise_inter_report);
   }

   return copy;

 error:
   return NULL;
}

Protocol__PrpNoiseInterferenceReport * copy_noise_inter_report(Protocol__PrpNoiseInterferenceReport *original) {
  Protocol__PrpNoiseInterferenceReport *ni_report;
  ni_report = malloc(sizeof(Protocol__PrpNoiseInterferenceReport));
  if(ni_report == NULL) {
    goto error;
  }
  protocol__prp_noise_interference_report__init(ni_report);
  // Current frame and subframe number
  ni_report->sfn_sf = original->sfn_sf;
  ni_report->has_sfn_sf = original->sfn_sf;
  // Received interference power in dbm
  ni_report->rip = original->rip;
  ni_report->has_rip = original->has_rip;
  // Thermal noise power in dbm
  ni_report->tnp = original->tnp;
  ni_report->has_tnp = original->has_tnp;
  
  return ni_report;
  
 error:
  return NULL;
}
