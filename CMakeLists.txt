cmake_minimum_required(VERSION 3.15.0)

# Did not work
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
 message(FATAL_ERROR "In-source build detected! This our way of discouraging that.")
endif()

if(CMAKE_BUILD_TYPE)
  set(set_cbt_pre_project IS_SET)
endif()

project(MCI VERSION 0.0.1 LANGUAGES CXX)

if(NOT set_cbt_pre_project)
  #This overcomes expected WIN32 (but different) behavior.
  unset(CMAKE_BUILD_TYPE CACHE)
endif()

# should these be opposite?
set( bmake_subproject OFF )
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
   set( bmake_subproject ON )
endif()

option(BMAKE_ENABLE_BUILD_TESTING 
        "Enable/Disable Project BUILD_TESTING" ${bmake_subproject} )

if(BMAKE_ENABLE_BUILD_TESTING)
  include(CTest)
endif()

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_files)


include(BMake/CachedVariables)

include(BMake/Options)
  bm_options_general()
include(BMake/Dependencies)

add_subdirectory(src)



#--------------- Purely to test this path -------------
# Cut and Paste just after cmake_minimum_required
#  option(TEST_NONSTANDALONE "Enables non-standalone" OFF)
#  if(TEST_NONSTANDALONE)
#     set(PROJECT_NAME Called_From_Another_Project)
#  endif()
#---------------


