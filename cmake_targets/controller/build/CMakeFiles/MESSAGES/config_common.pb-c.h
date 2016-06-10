/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: config_common.proto */

#ifndef PROTOBUF_C_config_5fcommon_2eproto__INCLUDED
#define PROTOBUF_C_config_5fcommon_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1002001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Protocol__PrpSiConfig Protocol__PrpSiConfig;
typedef struct _Protocol__PrpSiMessage Protocol__PrpSiMessage;
typedef struct _Protocol__PrpDrxConfig Protocol__PrpDrxConfig;
typedef struct _Protocol__PrpSpsConfig Protocol__PrpSpsConfig;
typedef struct _Protocol__PrpSrConfig Protocol__PrpSrConfig;
typedef struct _Protocol__PrpCqiConfig Protocol__PrpCqiConfig;
typedef struct _Protocol__PrpUeCapabilities Protocol__PrpUeCapabilities;
typedef struct _Protocol__PrpScellConfig Protocol__PrpScellConfig;
typedef struct _Protocol__PrpLcConfig Protocol__PrpLcConfig;


/* --- enums --- */

typedef enum _Protocol__PrpHoppingMode {
  PROTOCOL__PRP_HOPPING_MODE__PRHM_INTER = 0,
  PROTOCOL__PRP_HOPPING_MODE__PRHM_INTERINTRA = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_HOPPING_MODE)
} Protocol__PrpHoppingMode;
typedef enum _Protocol__PrpPhichResource {
  PROTOCOL__PRP_PHICH_RESOURCE__PRPR_ONE_SIXTH = 0,
  PROTOCOL__PRP_PHICH_RESOURCE__PRPR_HALF = 1,
  PROTOCOL__PRP_PHICH_RESOURCE__PRPR_ONE = 2,
  PROTOCOL__PRP_PHICH_RESOURCE__PRPR_TWO = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_PHICH_RESOURCE)
} Protocol__PrpPhichResource;
typedef enum _Protocol__PrpPhichDuration {
  PROTOCOL__PRP_PHICH_DURATION__PRPD_NORMAL = 0,
  PROTOCOL__PRP_PHICH_DURATION__PRPD_EXTENDED = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_PHICH_DURATION)
} Protocol__PrpPhichDuration;
typedef enum _Protocol__PrpUlCyclicPrefixLength {
  PROTOCOL__PRP_UL_CYCLIC_PREFIX_LENGTH__PRUCPL_NORMAL = 0,
  PROTOCOL__PRP_UL_CYCLIC_PREFIX_LENGTH__PRUCPL_EXTENDED = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_UL_CYCLIC_PREFIX_LENGTH)
} Protocol__PrpUlCyclicPrefixLength;
typedef enum _Protocol__PrpDlCyclicPrefixLength {
  PROTOCOL__PRP_DL_CYCLIC_PREFIX_LENGTH__PRDCPL_NORMAL = 0,
  PROTOCOL__PRP_DL_CYCLIC_PREFIX_LENGTH__PRDCPL_EXTENDED = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_DL_CYCLIC_PREFIX_LENGTH)
} Protocol__PrpDlCyclicPrefixLength;
typedef enum _Protocol__PrpDuplexMode {
  PROTOCOL__PRP_DUPLEX_MODE__PRDM_TDD = 0,
  PROTOCOL__PRP_DUPLEX_MODE__PRDM_FDD = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_DUPLEX_MODE)
} Protocol__PrpDuplexMode;
typedef enum _Protocol__PrpQam {
  PROTOCOL__PRP_QAM__PREQ_MOD_16QAM = 0,
  PROTOCOL__PRP_QAM__PREQ_MOD_64QAM = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_QAM)
} Protocol__PrpQam;
typedef enum _Protocol__PrpMeasGapConfigPattern {
  PROTOCOL__PRP_MEAS_GAP_CONFIG_PATTERN__PRMGCP_GP1 = 0,
  PROTOCOL__PRP_MEAS_GAP_CONFIG_PATTERN__PRMGCP_GP2 = 1,
  PROTOCOL__PRP_MEAS_GAP_CONFIG_PATTERN__PRMGCP_OFF = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_MEAS_GAP_CONFIG_PATTERN)
} Protocol__PrpMeasGapConfigPattern;
typedef enum _Protocol__PrpSetupReleaseAction {
  PROTOCOL__PRP_SETUP_RELEASE_ACTION__PRSRA_SETUP = 0,
  PROTOCOL__PRP_SETUP_RELEASE_ACTION__PRSRA_RELEASE = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_SETUP_RELEASE_ACTION)
} Protocol__PrpSetupReleaseAction;
typedef enum _Protocol__PrpUeTransmissionAntenna {
  PROTOCOL__PRP_UE_TRANSMISSION_ANTENNA__PRUTA_NONE = 0,
  PROTOCOL__PRP_UE_TRANSMISSION_ANTENNA__PRUTA_OPEN_LOOP = 1,
  PROTOCOL__PRP_UE_TRANSMISSION_ANTENNA__PRUTA_CLOSED_LOOP = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_UE_TRANSMISSION_ANTENNA)
} Protocol__PrpUeTransmissionAntenna;
typedef enum _Protocol__PrpAperiodicCqiReportMode {
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_RM12 = 0,
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_RM20 = 1,
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_RM22 = 2,
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_RM30 = 3,
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_RM31 = 4,
  PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE__PRACRM_NONE = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_APERIODIC_CQI_REPORT_MODE)
} Protocol__PrpAperiodicCqiReportMode;
typedef enum _Protocol__PrpTddAckNackFeedbackMode {
  PROTOCOL__PRP_TDD_ACK_NACK_FEEDBACK_MODE__PRTANFM_BUNDLING = 0,
  PROTOCOL__PRP_TDD_ACK_NACK_FEEDBACK_MODE__PRTANFM_MULTIPLEXING = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_TDD_ACK_NACK_FEEDBACK_MODE)
} Protocol__PrpTddAckNackFeedbackMode;
typedef enum _Protocol__PrpLcDirection {
  PROTOCOL__PRP_LC_DIRECTION__PRLCD_UL = 0,
  PROTOCOL__PRP_LC_DIRECTION__PRLCD_DL = 1,
  PROTOCOL__PRP_LC_DIRECTION__PRLCD_BOTH = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_LC_DIRECTION)
} Protocol__PrpLcDirection;
typedef enum _Protocol__PrpQosBearerType {
  PROTOCOL__PRP_QOS_BEARER_TYPE__PRQBT_NON_GBR = 0,
  PROTOCOL__PRP_QOS_BEARER_TYPE__PRQBT_GBR = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_QOS_BEARER_TYPE)
} Protocol__PrpQosBearerType;
typedef enum _Protocol__PrpUeStateChangeType {
  PROTOCOL__PRP_UE_STATE_CHANGE_TYPE__PRUESC_UPDATED = 0,
  PROTOCOL__PRP_UE_STATE_CHANGE_TYPE__PRUESC_ACTIVATED = 1,
  PROTOCOL__PRP_UE_STATE_CHANGE_TYPE__PRUESC_DEACTIVATED = 2,
  PROTOCOL__PRP_UE_STATE_CHANGE_TYPE__PRUESC_MOVED = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_UE_STATE_CHANGE_TYPE)
} Protocol__PrpUeStateChangeType;

/* --- messages --- */

struct  _Protocol__PrpSiConfig
{
  ProtobufCMessage base;
  protobuf_c_boolean has_sfn;
  uint32_t sfn;
  /*
   * The length of SIB1 in bytes
   */
  protobuf_c_boolean has_sib1_length;
  uint32_t sib1_length;
  /*
   * The scheduling window for all SIs in SF
   */
  protobuf_c_boolean has_si_window_length;
  uint32_t si_window_length;
  /*
   * List of SI messages to be sent.
   */
  size_t n_si_message;
  Protocol__PrpSiMessage **si_message;
};
#define PROTOCOL__PRP_SI_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_si_config__descriptor) \
    , 0,0, 0,0, 0,0, 0,NULL }


struct  _Protocol__PrpSiMessage
{
  ProtobufCMessage base;
  /*
   * Periodicity of SI msg in radio frames
   */
  protobuf_c_boolean has_periodicity;
  uint32_t periodicity;
  /*
   * The length of the SI message in bytes
   */
  protobuf_c_boolean has_length;
  uint32_t length;
};
#define PROTOCOL__PRP_SI_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_si_message__descriptor) \
    , 0,0, 0,0 }


struct  _Protocol__PrpDrxConfig
{
  ProtobufCMessage base;
  /*
   * Timer in SF. See TS 36.321
   */
  protobuf_c_boolean has_on_duration_timer;
  uint32_t on_duration_timer;
  /*
   * Timer in SF. See TS 36.321
   */
  protobuf_c_boolean has_drx_inactivity_timer;
  uint32_t drx_inactivity_timer;
  /*
   * Timer in SF. See TS 36.321
   */
  protobuf_c_boolean has_drx_retransmission_timer;
  uint32_t drx_retransmission_timer;
  /*
   * In SF. See TS 36.321
   */
  protobuf_c_boolean has_long_drx_cycle;
  uint32_t long_drx_cycle;
  /*
   * See TS 36.321
   */
  protobuf_c_boolean has_long_drx_cycle_start_offset;
  uint32_t long_drx_cycle_start_offset;
  /*
   * In SF
   */
  protobuf_c_boolean has_short_drx_cycle;
  uint32_t short_drx_cycle;
  /*
   * Timer in subframes. See TS 36.321
   */
  protobuf_c_boolean has_drx_short_cycle_timer;
  uint32_t drx_short_cycle_timer;
};
#define PROTOCOL__PRP_DRX_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_drx_config__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0 }


struct  _Protocol__PrpSpsConfig
{
  ProtobufCMessage base;
  /*
   * SPS UL scheduling interval in SF
   */
  protobuf_c_boolean has_semi_persistent_sched_interval_ul;
  uint32_t semi_persistent_sched_interval_ul;
  /*
   * SPS DL scheduling interval in SF
   */
  protobuf_c_boolean has_semi_persistent_sched_interval_dl;
  uint32_t semi_persistent_sched_interval_dl;
  /*
   * Number of SPS HARQ processes. See TS 36.321
   */
  protobuf_c_boolean has_num_of_conf_sps_proc;
  uint32_t num_of_conf_sps_proc;
  /*
   * See TS36.213. Ignored when config is used
   */
  size_t n_n1_pucch_an_persistent_element;
  uint32_t *n1_pucch_an_persistent_element;
  /*
   * as part of PRPT_SET_UE_CONFIG
   */
  /*
   * number of empty transmissions before release of SPS
   */
  protobuf_c_boolean has_implicit_release_after;
  uint32_t implicit_release_after;
};
#define PROTOCOL__PRP_SPS_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_sps_config__descriptor) \
    , 0,0, 0,0, 0,0, 0,NULL, 0,0 }


struct  _Protocol__PrpSrConfig
{
  ProtobufCMessage base;
  /*
   * Indicates if SR config should be changed or released
   */
  protobuf_c_boolean has_sr_action;
  uint32_t sr_action;
  /*
   * One of the PRSRA_* enum values
   */
  /*
   * SR scheduling interval in SF
   */
  protobuf_c_boolean has_sched_interval;
  uint32_t sched_interval;
  /*
   * See TS 36.213
   */
  protobuf_c_boolean has_dsr_trans_max;
  uint32_t dsr_trans_max;
};
#define PROTOCOL__PRP_SR_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_sr_config__descriptor) \
    , 0,0, 0,0, 0,0 }


struct  _Protocol__PrpCqiConfig
{
  ProtobufCMessage base;
  /*
   * Indicats if CQI changed or released.
   */
  protobuf_c_boolean has_cqi_action;
  uint32_t cqi_action;
  /*
   * One of the PRSRA_* enum values
   */
  /*
   * CQI scheduling interval in SF
   */
  protobuf_c_boolean has_cqi_sched_interval;
  uint32_t cqi_sched_interval;
  /*
   * RI scheduling interval in SF
   */
  protobuf_c_boolean has_ri_sched_interval;
  uint32_t ri_sched_interval;
};
#define PROTOCOL__PRP_CQI_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_cqi_config__descriptor) \
    , 0,0, 0,0, 0,0 }


struct  _Protocol__PrpUeCapabilities
{
  ProtobufCMessage base;
  /*
   * Boolean value. Only half duplex support. FDD operation
   */
  protobuf_c_boolean has_half_duplex;
  uint32_t half_duplex;
  /*
   * Support for intra-subframe hopping. Boolean value
   */
  protobuf_c_boolean has_intra_sf_hopping;
  uint32_t intra_sf_hopping;
  /*
   * Support for type 2 hopping with n_sb > 1
   */
  protobuf_c_boolean has_type2_sb_1;
  uint32_t type2_sb_1;
  protobuf_c_boolean has_ue_category;
  uint32_t ue_category;
  /*
   * Boolean value. UE support for resource allocation type 1
   */
  protobuf_c_boolean has_res_alloc_type1;
  uint32_t res_alloc_type1;
};
#define PROTOCOL__PRP_UE_CAPABILITIES__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_ue_capabilities__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0 }


struct  _Protocol__PrpScellConfig
{
  ProtobufCMessage base;
  /*
   * Id of the carrier component
   */
  protobuf_c_boolean has_carrier_index;
  uint32_t carrier_index;
  /*
   * Index of this Scell (RRC SCellIndex)
   */
  protobuf_c_boolean has_scell_index;
  uint32_t scell_index;
  /*
   * Boolean value. Indicates if cross-carrier scheduling
   */
  protobuf_c_boolean has_use_ccs;
  uint32_t use_ccs;
  /*
   * is used by this SCell
   */
  /*
   * Index of the cell responsible for scheduling
   */
  protobuf_c_boolean has_sched_cell_index;
  uint32_t sched_cell_index;
  /*
   * this SCell if cross-carrier scheduling is enabled
   */
  /*
   * Starting OFDM symbol of PDSCH data region for this SCell
   */
  protobuf_c_boolean has_pdsch_start;
  uint32_t pdsch_start;
};
#define PROTOCOL__PRP_SCELL_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_scell_config__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0 }


struct  _Protocol__PrpLcConfig
{
  ProtobufCMessage base;
  /*
   * The logical channel id
   */
  protobuf_c_boolean has_lcid;
  uint32_t lcid;
  /*
   * The logical channel group (0..3) the LC is mapped to
   */
  protobuf_c_boolean has_lcg;
  uint32_t lcg;
  /*
   * The LC direction. One of the PRLCD_* enum values
   */
  protobuf_c_boolean has_direction;
  uint32_t direction;
  /*
   * GBR or NGBR bearer. One of the PRQBT_* enum values
   */
  protobuf_c_boolean has_qos_bearer_type;
  uint32_t qos_bearer_type;
  /*
   * The QCI defined in TS 23.203, coded as defined in TS 36.413
   */
  protobuf_c_boolean has_qci;
  uint32_t qci;
  /*
   * One less than the actual QCI value
   */
  /*
   * In bps (GBR only)
   */
  protobuf_c_boolean has_e_rab_max_bitrate_ul;
  uint64_t e_rab_max_bitrate_ul;
  /*
   * In bps (GBR only)
   */
  protobuf_c_boolean has_e_rab_max_bitrate_dl;
  uint64_t e_rab_max_bitrate_dl;
  /*
   * In bps (GBR only)
   */
  protobuf_c_boolean has_e_rab_guaranteed_bitrate_ul;
  uint64_t e_rab_guaranteed_bitrate_ul;
  /*
   * In bps (GBR only)
   */
  protobuf_c_boolean has_e_rab_guaranteed_bitrate_dl;
  uint64_t e_rab_guaranteed_bitrate_dl;
};
#define PROTOCOL__PRP_LC_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_lc_config__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0 }


/* Protocol__PrpSiConfig methods */
void   protocol__prp_si_config__init
                     (Protocol__PrpSiConfig         *message);
size_t protocol__prp_si_config__get_packed_size
                     (const Protocol__PrpSiConfig   *message);
size_t protocol__prp_si_config__pack
                     (const Protocol__PrpSiConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_si_config__pack_to_buffer
                     (const Protocol__PrpSiConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpSiConfig *
       protocol__prp_si_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_si_config__free_unpacked
                     (Protocol__PrpSiConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpSiMessage methods */
void   protocol__prp_si_message__init
                     (Protocol__PrpSiMessage         *message);
size_t protocol__prp_si_message__get_packed_size
                     (const Protocol__PrpSiMessage   *message);
size_t protocol__prp_si_message__pack
                     (const Protocol__PrpSiMessage   *message,
                      uint8_t             *out);
size_t protocol__prp_si_message__pack_to_buffer
                     (const Protocol__PrpSiMessage   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpSiMessage *
       protocol__prp_si_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_si_message__free_unpacked
                     (Protocol__PrpSiMessage *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpDrxConfig methods */
void   protocol__prp_drx_config__init
                     (Protocol__PrpDrxConfig         *message);
size_t protocol__prp_drx_config__get_packed_size
                     (const Protocol__PrpDrxConfig   *message);
size_t protocol__prp_drx_config__pack
                     (const Protocol__PrpDrxConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_drx_config__pack_to_buffer
                     (const Protocol__PrpDrxConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpDrxConfig *
       protocol__prp_drx_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_drx_config__free_unpacked
                     (Protocol__PrpDrxConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpSpsConfig methods */
void   protocol__prp_sps_config__init
                     (Protocol__PrpSpsConfig         *message);
size_t protocol__prp_sps_config__get_packed_size
                     (const Protocol__PrpSpsConfig   *message);
size_t protocol__prp_sps_config__pack
                     (const Protocol__PrpSpsConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_sps_config__pack_to_buffer
                     (const Protocol__PrpSpsConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpSpsConfig *
       protocol__prp_sps_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_sps_config__free_unpacked
                     (Protocol__PrpSpsConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpSrConfig methods */
void   protocol__prp_sr_config__init
                     (Protocol__PrpSrConfig         *message);
size_t protocol__prp_sr_config__get_packed_size
                     (const Protocol__PrpSrConfig   *message);
size_t protocol__prp_sr_config__pack
                     (const Protocol__PrpSrConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_sr_config__pack_to_buffer
                     (const Protocol__PrpSrConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpSrConfig *
       protocol__prp_sr_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_sr_config__free_unpacked
                     (Protocol__PrpSrConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpCqiConfig methods */
void   protocol__prp_cqi_config__init
                     (Protocol__PrpCqiConfig         *message);
size_t protocol__prp_cqi_config__get_packed_size
                     (const Protocol__PrpCqiConfig   *message);
size_t protocol__prp_cqi_config__pack
                     (const Protocol__PrpCqiConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_cqi_config__pack_to_buffer
                     (const Protocol__PrpCqiConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpCqiConfig *
       protocol__prp_cqi_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_cqi_config__free_unpacked
                     (Protocol__PrpCqiConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpUeCapabilities methods */
void   protocol__prp_ue_capabilities__init
                     (Protocol__PrpUeCapabilities         *message);
size_t protocol__prp_ue_capabilities__get_packed_size
                     (const Protocol__PrpUeCapabilities   *message);
size_t protocol__prp_ue_capabilities__pack
                     (const Protocol__PrpUeCapabilities   *message,
                      uint8_t             *out);
size_t protocol__prp_ue_capabilities__pack_to_buffer
                     (const Protocol__PrpUeCapabilities   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpUeCapabilities *
       protocol__prp_ue_capabilities__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_ue_capabilities__free_unpacked
                     (Protocol__PrpUeCapabilities *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpScellConfig methods */
void   protocol__prp_scell_config__init
                     (Protocol__PrpScellConfig         *message);
size_t protocol__prp_scell_config__get_packed_size
                     (const Protocol__PrpScellConfig   *message);
size_t protocol__prp_scell_config__pack
                     (const Protocol__PrpScellConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_scell_config__pack_to_buffer
                     (const Protocol__PrpScellConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpScellConfig *
       protocol__prp_scell_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_scell_config__free_unpacked
                     (Protocol__PrpScellConfig *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpLcConfig methods */
void   protocol__prp_lc_config__init
                     (Protocol__PrpLcConfig         *message);
size_t protocol__prp_lc_config__get_packed_size
                     (const Protocol__PrpLcConfig   *message);
size_t protocol__prp_lc_config__pack
                     (const Protocol__PrpLcConfig   *message,
                      uint8_t             *out);
size_t protocol__prp_lc_config__pack_to_buffer
                     (const Protocol__PrpLcConfig   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpLcConfig *
       protocol__prp_lc_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_lc_config__free_unpacked
                     (Protocol__PrpLcConfig *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Protocol__PrpSiConfig_Closure)
                 (const Protocol__PrpSiConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpSiMessage_Closure)
                 (const Protocol__PrpSiMessage *message,
                  void *closure_data);
typedef void (*Protocol__PrpDrxConfig_Closure)
                 (const Protocol__PrpDrxConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpSpsConfig_Closure)
                 (const Protocol__PrpSpsConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpSrConfig_Closure)
                 (const Protocol__PrpSrConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpCqiConfig_Closure)
                 (const Protocol__PrpCqiConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpUeCapabilities_Closure)
                 (const Protocol__PrpUeCapabilities *message,
                  void *closure_data);
typedef void (*Protocol__PrpScellConfig_Closure)
                 (const Protocol__PrpScellConfig *message,
                  void *closure_data);
typedef void (*Protocol__PrpLcConfig_Closure)
                 (const Protocol__PrpLcConfig *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    protocol__prp_hopping_mode__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_phich_resource__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_phich_duration__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_ul_cyclic_prefix_length__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_dl_cyclic_prefix_length__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_duplex_mode__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_qam__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_meas_gap_config_pattern__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_setup_release_action__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_ue_transmission_antenna__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_aperiodic_cqi_report_mode__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_tdd_ack_nack_feedback_mode__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_lc_direction__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_qos_bearer_type__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_ue_state_change_type__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_si_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_si_message__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_drx_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_sps_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_sr_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_cqi_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_ue_capabilities__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_scell_config__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_lc_config__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_config_5fcommon_2eproto__INCLUDED */