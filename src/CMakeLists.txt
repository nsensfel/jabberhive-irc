add_subdirectory(error)
add_subdirectory(parameters)
add_subdirectory(meta_net)
add_subdirectory(irc)

set(
   SRC_FILES ${SRC_FILES}
   ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
