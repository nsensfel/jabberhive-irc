set(
   SRC_FILES ${SRC_FILES}
   ${CMAKE_CURRENT_SOURCE_DIR}/meta_net.c
   ${CMAKE_CURRENT_SOURCE_DIR}/meta_net_handle_reply.c
   ${CMAKE_CURRENT_SOURCE_DIR}/meta_net_select.c
   ${CMAKE_CURRENT_SOURCE_DIR}/meta_net_try_request.c
)

set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
