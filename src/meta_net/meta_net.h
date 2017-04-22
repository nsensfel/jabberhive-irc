#ifndef _JH_META_NET_META_NET_H_
#define _JH_META_NET_META_NET_H_

#include "../parameters/parameters_types.h"

#include "../irc/irc_types.h"

#include "meta_net_types.h"

void JH_meta_net_initialize
(
   struct JH_meta_net socket [const restrict static 1]
);

int JH_meta_net_connect
(
   struct JH_meta_net socket [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
);

void JH_meta_net_finalize
(
   struct JH_meta_net socket [const restrict static 1]
);

int JH_meta_net_try_request
(
   struct JH_meta_net socket [const restrict static 1],
   const char string [const restrict static 1],
   const size_t string_size
);

int JH_meta_net_handle_user_message
(
   struct JH_meta_net socket [const restrict static 1],
   const char string [const restrict static 1],
   const size_t string_size
);

int JH_meta_net_handle_user_action
(
   struct JH_meta_net socket [const restrict static 1],
   const char string [const restrict static 1],
   const size_t string_size
);

int JH_meta_net_read
(
   struct JH_meta_net socket [const restrict static 1]
);

/* TODO */
int JH_meta_net_write
(
   struct JH_meta_net socket [const restrict static 1]
);

void JH_meta_net_handle_reply
(
   struct JH_meta_net socket [const restrict static 1],
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
);

int JH_meta_net_pre_select
(
   struct JH_meta_net socket [const restrict static 1],
   const struct JH_parameters params [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1],
   int max_fd [const restrict static 1]
);

int JH_meta_net_post_select
(
   struct JH_meta_net socket [const restrict static 1],
   const struct JH_parameters params [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1]
);

#endif
