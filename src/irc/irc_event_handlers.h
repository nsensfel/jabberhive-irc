#ifndef _JH_IRC_IRC_EVENT_HANDLERS_H_
#define _JH_IRC_IRC_EVENT_HANDLERS_H_

#include <libircclient/libircclient.h>

void JH_irc_do_nothing
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
);

void JH_irc_handle_connected_event
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
);

void JH_irc_handle_channel_message_event
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
);

void JH_irc_handle_ctcp_action_event
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
);

void JH_irc_handle_numeric_event
(
   irc_session_t * session,
   unsigned int event,
   const char * origin,
   const char ** params,
   unsigned int count
);

void JH_irc_handle_dcc_chat_req_event
(
   irc_session_t * session,
   const char * nick,
   const char * addr,
   irc_dcc_t dccid
);

void JH_irc_handle_dcc_send_req_event
(
   irc_session_t * session,
   const char * nick,
   const char * addr,
   const char * filename,
   unsigned long size,
   irc_dcc_t dccid
);

#endif
