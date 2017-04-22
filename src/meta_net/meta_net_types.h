#ifndef _JH_META_NET_META_NET_TYPES_H_
#define _JH_META_NET_META_NET_TYPES_H_

#include <stdio.h>

#define JH_META_NET_READ_SIZE 64
#define JH_META_NET_ACTION_STRING         "/me"
#define JH_META_NET_ACTION_STRING_LENGTH  3

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
