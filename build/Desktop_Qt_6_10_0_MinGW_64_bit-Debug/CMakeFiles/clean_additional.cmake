# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BSVault_autogen"
  "CMakeFiles\\BSVault_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BSVault_autogen.dir\\ParseCache.txt"
  )
endif()
