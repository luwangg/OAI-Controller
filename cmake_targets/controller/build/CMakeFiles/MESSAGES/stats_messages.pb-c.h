/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: stats_messages.proto */

#ifndef PROTOBUF_C_stats_5fmessages_2eproto__INCLUDED
#define PROTOBUF_C_stats_5fmessages_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1002001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "stats_common.pb-c.h"

typedef struct _Protocol__PrpCompleteStatsRequest Protocol__PrpCompleteStatsRequest;
typedef struct _Protocol__PrpCellStatsRequest Protocol__PrpCellStatsRequest;
typedef struct _Protocol__PrpUeStatsRequest Protocol__PrpUeStatsRequest;
typedef struct _Protocol__PrpCellStatsReport Protocol__PrpCellStatsReport;
typedef struct _Protocol__PrpUeStatsReport Protocol__PrpUeStatsReport;


/* --- enums --- */

/*
 *Types of statistics requested by the controller
 */
typedef enum _Protocol__PrpStatsType {
  PROTOCOL__PRP_STATS_TYPE__PRST_COMPLETE_STATS = 0,
  PROTOCOL__PRP_STATS_TYPE__PRST_CELL_STATS = 1,
  PROTOCOL__PRP_STATS_TYPE__PRST_UE_STATS = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_STATS_TYPE)
} Protocol__PrpStatsType;
/*
 * Report frequency for the requested statistics
 */
typedef enum _Protocol__PrpStatsReportFreq {
  PROTOCOL__PRP_STATS_REPORT_FREQ__PRSRF_ONCE = 0,
  PROTOCOL__PRP_STATS_REPORT_FREQ__PRSRF_PERIODICAL = 1,
  PROTOCOL__PRP_STATS_REPORT_FREQ__PRSRF_CONTINUOUS = 2,
  PROTOCOL__PRP_STATS_REPORT_FREQ__PRSRF_OFF = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_STATS_REPORT_FREQ)
} Protocol__PrpStatsReportFreq;
/*
 * Flags for cell statistics
 */
typedef enum _Protocol__PrpCellStatsType {
  PROTOCOL__PRP_CELL_STATS_TYPE__PRCST_NOISE_INTERFERENCE = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_CELL_STATS_TYPE)
} Protocol__PrpCellStatsType;
/*
 * Flags for UE-related statistics
 */
typedef enum _Protocol__PrpUeStatsType {
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_BSR = 1,
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_PRH = 2,
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_RLC_BS = 4,
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_MAC_CE_BS = 8,
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_DL_CQI = 16,
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_PBS = 32,
  /*
   * To be extended with more types of stats
   */
  PROTOCOL__PRP_UE_STATS_TYPE__PRUST_UL_CQI = 64
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(PROTOCOL__PRP_UE_STATS_TYPE)
} Protocol__PrpUeStatsType;

/* --- messages --- */

struct  _Protocol__PrpCompleteStatsRequest
{
  ProtobufCMessage base;
  protobuf_c_boolean has_report_frequency;
  Protocol__PrpStatsReportFreq report_frequency;
  protobuf_c_boolean has_sf;
  uint32_t sf;
  protobuf_c_boolean has_cell_report_flags;
  uint32_t cell_report_flags;
  protobuf_c_boolean has_ue_report_flags;
  uint32_t ue_report_flags;
};
#define PROTOCOL__PRP_COMPLETE_STATS_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_complete_stats_request__descriptor) \
    , 0,0, 0,0, 0,0, 0,0 }


struct  _Protocol__PrpCellStatsRequest
{
  ProtobufCMessage base;
  size_t n_cell;
  uint32_t *cell;
  protobuf_c_boolean has_flags;
  uint32_t flags;
};
#define PROTOCOL__PRP_CELL_STATS_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_cell_stats_request__descriptor) \
    , 0,NULL, 0,0 }


struct  _Protocol__PrpUeStatsRequest
{
  ProtobufCMessage base;
  size_t n_rnti;
  uint32_t *rnti;
  protobuf_c_boolean has_flags;
  uint32_t flags;
};
#define PROTOCOL__PRP_UE_STATS_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_ue_stats_request__descriptor) \
    , 0,NULL, 0,0 }


/*
 * The full statistics report for a specific cell
 */
struct  _Protocol__PrpCellStatsReport
{
  ProtobufCMessage base;
  protobuf_c_boolean has_carrier_index;
  uint32_t carrier_index;
  protobuf_c_boolean has_flags;
  uint32_t flags;
  Protocol__PrpNoiseInterferenceReport *noise_inter_report;
};
#define PROTOCOL__PRP_CELL_STATS_REPORT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_cell_stats_report__descriptor) \
    , 0,0, 0,0, NULL }


/*
 * Statistics report for a specific UE
 */
struct  _Protocol__PrpUeStatsReport
{
  ProtobufCMessage base;
  protobuf_c_boolean has_rnti;
  uint32_t rnti;
  protobuf_c_boolean has_flags;
  uint32_t flags;
  size_t n_bsr;
  uint32_t *bsr;
  protobuf_c_boolean has_phr;
  uint32_t phr;
  size_t n_rlc_report;
  Protocol__PrpRlcBsr **rlc_report;
  protobuf_c_boolean has_pending_mac_ces;
  uint32_t pending_mac_ces;
  Protocol__PrpDlCqiReport *dl_cqi_report;
  Protocol__PrpPagingBufferReport *pbr;
  Protocol__PrpUlCqiReport *ul_cqi_report;
};
#define PROTOCOL__PRP_UE_STATS_REPORT__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&protocol__prp_ue_stats_report__descriptor) \
    , 0,0, 0,0, 0,NULL, 0,0, 0,NULL, 0,0, NULL, NULL, NULL }


/* Protocol__PrpCompleteStatsRequest methods */
void   protocol__prp_complete_stats_request__init
                     (Protocol__PrpCompleteStatsRequest         *message);
size_t protocol__prp_complete_stats_request__get_packed_size
                     (const Protocol__PrpCompleteStatsRequest   *message);
size_t protocol__prp_complete_stats_request__pack
                     (const Protocol__PrpCompleteStatsRequest   *message,
                      uint8_t             *out);
size_t protocol__prp_complete_stats_request__pack_to_buffer
                     (const Protocol__PrpCompleteStatsRequest   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpCompleteStatsRequest *
       protocol__prp_complete_stats_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_complete_stats_request__free_unpacked
                     (Protocol__PrpCompleteStatsRequest *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpCellStatsRequest methods */
void   protocol__prp_cell_stats_request__init
                     (Protocol__PrpCellStatsRequest         *message);
size_t protocol__prp_cell_stats_request__get_packed_size
                     (const Protocol__PrpCellStatsRequest   *message);
size_t protocol__prp_cell_stats_request__pack
                     (const Protocol__PrpCellStatsRequest   *message,
                      uint8_t             *out);
size_t protocol__prp_cell_stats_request__pack_to_buffer
                     (const Protocol__PrpCellStatsRequest   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpCellStatsRequest *
       protocol__prp_cell_stats_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_cell_stats_request__free_unpacked
                     (Protocol__PrpCellStatsRequest *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpUeStatsRequest methods */
void   protocol__prp_ue_stats_request__init
                     (Protocol__PrpUeStatsRequest         *message);
size_t protocol__prp_ue_stats_request__get_packed_size
                     (const Protocol__PrpUeStatsRequest   *message);
size_t protocol__prp_ue_stats_request__pack
                     (const Protocol__PrpUeStatsRequest   *message,
                      uint8_t             *out);
size_t protocol__prp_ue_stats_request__pack_to_buffer
                     (const Protocol__PrpUeStatsRequest   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpUeStatsRequest *
       protocol__prp_ue_stats_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_ue_stats_request__free_unpacked
                     (Protocol__PrpUeStatsRequest *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpCellStatsReport methods */
void   protocol__prp_cell_stats_report__init
                     (Protocol__PrpCellStatsReport         *message);
size_t protocol__prp_cell_stats_report__get_packed_size
                     (const Protocol__PrpCellStatsReport   *message);
size_t protocol__prp_cell_stats_report__pack
                     (const Protocol__PrpCellStatsReport   *message,
                      uint8_t             *out);
size_t protocol__prp_cell_stats_report__pack_to_buffer
                     (const Protocol__PrpCellStatsReport   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpCellStatsReport *
       protocol__prp_cell_stats_report__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_cell_stats_report__free_unpacked
                     (Protocol__PrpCellStatsReport *message,
                      ProtobufCAllocator *allocator);
/* Protocol__PrpUeStatsReport methods */
void   protocol__prp_ue_stats_report__init
                     (Protocol__PrpUeStatsReport         *message);
size_t protocol__prp_ue_stats_report__get_packed_size
                     (const Protocol__PrpUeStatsReport   *message);
size_t protocol__prp_ue_stats_report__pack
                     (const Protocol__PrpUeStatsReport   *message,
                      uint8_t             *out);
size_t protocol__prp_ue_stats_report__pack_to_buffer
                     (const Protocol__PrpUeStatsReport   *message,
                      ProtobufCBuffer     *buffer);
Protocol__PrpUeStatsReport *
       protocol__prp_ue_stats_report__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   protocol__prp_ue_stats_report__free_unpacked
                     (Protocol__PrpUeStatsReport *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Protocol__PrpCompleteStatsRequest_Closure)
                 (const Protocol__PrpCompleteStatsRequest *message,
                  void *closure_data);
typedef void (*Protocol__PrpCellStatsRequest_Closure)
                 (const Protocol__PrpCellStatsRequest *message,
                  void *closure_data);
typedef void (*Protocol__PrpUeStatsRequest_Closure)
                 (const Protocol__PrpUeStatsRequest *message,
                  void *closure_data);
typedef void (*Protocol__PrpCellStatsReport_Closure)
                 (const Protocol__PrpCellStatsReport *message,
                  void *closure_data);
typedef void (*Protocol__PrpUeStatsReport_Closure)
                 (const Protocol__PrpUeStatsReport *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    protocol__prp_stats_type__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_stats_report_freq__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_cell_stats_type__descriptor;
extern const ProtobufCEnumDescriptor    protocol__prp_ue_stats_type__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_complete_stats_request__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_cell_stats_request__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_ue_stats_request__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_cell_stats_report__descriptor;
extern const ProtobufCMessageDescriptor protocol__prp_ue_stats_report__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_stats_5fmessages_2eproto__INCLUDED */
