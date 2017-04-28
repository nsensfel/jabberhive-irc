#ifndef _JH_META_NET_META_NET_TYPES_H_
#define _JH_META_NET_META_NET_TYPES_H_

#include <stdio.h>

#define JH_META_NET_READ_SIZE 64
#define JH_META_NET_ACTION_STRING         "/me"
#define JH_META_NET_ACTION_STRING_LENGTH  3

#define JH_META_NET_RPV_STRING            "?RPV"
#define JH_META_NET_RPV_STRING_LENGTH     4
#define JH_META_NET_RPS_STRING            "?RPS"
#define JH_META_NET_RPS_STRING_LENGTH     4
#define JH_META_NET_RL_STRING             "?RL"
#define JH_META_NET_RL_STRING_LENGTH      3
#define JH_META_NET_RR_STRING             "?RR"
#define JH_META_NET_RR_STRING_LENGTH      3
#define JH_META_NET_RLR_STRING            "?RLR"
#define JH_META_NET_RLR_STRING_LENGTH     4

#define JH_META_NET_CPV_STRING            "!CPV"
#define JH_META_NET_CPV_STRING_LENGTH     4
#define JH_META_NET_CPS_STRING            "!CPV"
#define JH_META_NET_CPS_STRING_LENGTH     4
#define JH_META_NET_GR_STRING             "!GR"
#define JH_META_NET_GR_STRING_LENGTH      3
#define JH_META_NET_AI_STRING             "!AI"
#define JH_META_NET_AI_STRING_LENGTH      3
#define JH_META_NET_P_STRING              "!P"
#define JH_META_NET_P_STRING_LENGTH       2
#define JH_META_NET_N_STRING              "!N"
#define JH_META_NET_N_STRING_LENGTH       2
struct JH_meta_net_buffer
{
   char * data;
   size_t capacity;
   size_t length;
   size_t index;
};

struct JH_meta_net
{
   int fd;
   int has_request_in_progress;
   struct JH_meta_net_buffer in;
   struct JH_meta_net_buffer out;
};

#endif
