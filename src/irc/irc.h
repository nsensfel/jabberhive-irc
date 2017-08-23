#ifndef _JH_IRC_IRC_H_
#define _JH_IRC_IRC_H_

#include "../parameters/parameters_types.h"

#include "../meta_net/meta_net.h"

#include "irc_types.h"

int JH_irc_initialize
(
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1],
   struct JH_meta_net meta_net [const restrict static 1]
);

int JH_irc_connect (struct JH_irc irc [const restrict static 1]);

int JH_irc_start_connection_test (struct JH_irc irc [const restrict static 1]);
int JH_irc_is_testing_connection (struct JH_irc irc [const restrict static 1]);

int JH_irc_send_message
(
   struct JH_irc irc [const restrict static 1],
   const char msg [const restrict static 1]
);

int JH_irc_send_action
(
   struct JH_irc irc [const restrict static 1],
   const char msg [const restrict static 1]
);

void JH_irc_finalize (struct JH_irc irc [const restrict static 1]);

int JH_irc_pre_select
(
   struct JH_irc irc [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1],
   int max_fd [const restrict static 1]
);

int JH_irc_post_select
(
   struct JH_irc irc [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1]
);

#endif
