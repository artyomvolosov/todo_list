# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\todo_list_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\todo_list_autogen.dir\\ParseCache.txt"
  "todo_list_autogen"
  )
endif()
