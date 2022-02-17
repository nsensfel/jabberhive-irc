#include <libircclient/libircclient.h>

#include "irc_event_handlers.h"

void JH_irc_handle_dcc_chat_req_event
(
   irc_session_t * session,
   __attribute__((unused)) const char * nick,
   __attribute__((unused)) const char * addr,
   irc_dcc_t dccid
)
{
   irc_dcc_decline(session, dccid);
}

void JH_irc_handle_dcc_send_req_event
(
   irc_session_t * session,
   __attribute__((unused)) const char * nick,
   __attribute__((unused)) const char * addr,
   __attribute__((unused)) const char * filename,
   __attribute__((unused)) unsigned long size,
   irc_dcc_t dccid
)
{
   irc_dcc_decline(session, dccid);
}
