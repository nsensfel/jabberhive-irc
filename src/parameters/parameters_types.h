#ifndef _JH_CLI_PARAMETERS_TYPES_H_
#define _JH_CLI_PARAMETERS_TYPES_H_

#define JH_PARAMETERS_COUNT 5

struct JH_parameters
{
   const char * restrict socket_name;

   const char * server;
   const char * password;
   const char * nick;
   const char * username;
   const char * realname;
   const char * channel;
   unsigned short port;

   int use_ipv6;
};

#endif
