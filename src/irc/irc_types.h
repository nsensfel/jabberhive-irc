#ifndef _JH_IRC_IRC_TYPES_H_
#define _JH_IRC_IRC_TYPES_H_

#include <libircclient/libircclient.h>

struct JH_irc
{
   irc_callbacks_t callbacks;
   irc_session_t * session;
   const struct JH_parameters * params;
   struct JH_meta_net * jh_net;
   int is_testing_connection;
};

#endif
