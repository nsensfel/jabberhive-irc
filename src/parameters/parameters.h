#ifndef _JH_CLI_PARAMETERS_H_
#define _JH_CLI_PARAMETERS_H_

#include "parameters_types.h"

int JH_parameters_initialize
(
   struct JH_parameters param [const restrict static 1],
   int const argc,
   const char * argv [const static argc]
);

int JH_parameters_get_request_pipelining
(
   const struct JH_parameters param [const restrict static 1]
);

int JH_parameters_get_print_additional_info
(
   const struct JH_parameters param [const restrict static 1]
);

int JH_parameters_get_print_chat
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_socket_name
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_irc_server
(
   const struct JH_parameters param [const restrict static 1]
);

unsigned short JH_parameters_get_irc_port
(
   const struct JH_parameters param [const restrict static 1]
);

/* Having it as an invocation parameter makes it readable by other users on the
 * machine.
 */
const char * JH_parameters_get_irc_password
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_irc_nick
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_irc_username
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_irc_realname
(
   const struct JH_parameters param [const restrict static 1]
);

const char * JH_parameters_get_irc_channel
(
   const struct JH_parameters param [const restrict static 1]
);

int JH_parameters_get_irc_is_ipv6
(
   const struct JH_parameters param [const restrict static 1]
);
#endif
