#
# Default Setting CMAKE_BUILD_TYPE
#
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "RelWithDebInfo" 
       CACHE STRING 
       "Build Type - Options are: [None] [Debug] [Release] [RelWithDebInfo] [MinSizeRel]." 
       FORCE 
    )
    message(STATUS " BM: CMAKE_BUILD_TYPE = [${CMAKE_BUILD_TYPE}] (Default)")
else()
    message(STATUS " BM: CMAKE_BUILD_TYPE = [${CMAKE_BUILD_TYPE}] (User Defined)")
endif()


#
# FetchContent's default setting for FETCHCONTENT_BASE_DIR=${CMAKE_BINARY_DIR}/_dep.
#   See URL: https://cmake.org/cmake/help/latest/module/FetchContent.html,
#   and search on [FETCHCONTENT_BASE_DIR] for more.
#
# Note: Do not use include(FetchContent) anywhere before this conditional.
#
# This bit of code assumes that the setting of FETCHCONTENT_BASE_DIR 
# from the commandline is just the replacement part for /_dep of the path.
# Resetting, if FETCHCONTENT_BASE_DIR has been set from commandline.
#
if( FETCHCONTENT_BASE_DIR )
    set( FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/${FETCHCONTENT_BASE_DIR} 
       CACHE PATH 
       "Path To Help With FetchContent" FORCE
    )
endif()
