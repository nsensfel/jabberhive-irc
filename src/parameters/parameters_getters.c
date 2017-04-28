#include "parameters.h"

const int JH_parameters_get_print_additional_info
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->print_additional_info;
}

const int JH_parameters_get_print_chat
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->print_chat;
}

const char * JH_parameters_get_socket_name
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->socket_name;
}

const char * JH_parameters_get_irc_server
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->server;
}

unsigned short JH_parameters_get_irc_port
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->port;
}

const char * JH_parameters_get_irc_password
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->password;
}

const char * JH_parameters_get_irc_nick
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->nick;
}

const char * JH_parameters_get_irc_username
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->username;
}

const char * JH_parameters_get_irc_realname
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->realname;
}

const char * JH_parameters_get_irc_channel
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->channel;
}

int JH_parameters_get_irc_is_ipv6
(
   const struct JH_parameters param [const restrict static 1]
)
{
   return param->use_ipv6;
}
