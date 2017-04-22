set(
   SRC_FILES ${SRC_FILES}
   ${CMAKE_CURRENT_SOURCE_DIR}/irc.c
   ${CMAKE_CURRENT_SOURCE_DIR}/irc_handle_connected.c
   ${CMAKE_CURRENT_SOURCE_DIR}/irc_handle_dcc_events.c
   ${CMAKE_CURRENT_SOURCE_DIR}/irc_receive.c
   ${CMAKE_CURRENT_SOURCE_DIR}/irc_select.c
   ${CMAKE_CURRENT_SOURCE_DIR}/irc_send.c
)

set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
