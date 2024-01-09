# BMake Catch find package script
#   This is NOT in a function since certain variables lose scope after being set.
#   For example: CMAKE_MODULES_PATH when used with find_package. 
#
#   The following adds the several cmake into the path for catch_discover_tests:
#     list( APPEND CMAKE_MODULE_PATH ${${DPend}_SOURCE_DIR}/contrib )
#

set(DPend Catch2)
set(DPend_Version 2.13.0)
string(TOLOWER ${DPend} DPend_Lower) 

if(BMAKE_ENABLE_FINDPACKAGE_CATCH)
   set(FindPackage_Option QUIET)
   if(BMAKE_FINDPACKAGE_CATCH_REQUIRED)
      set(FindPackage_Option REQUIRED)
   endif()

   find_package(${DPend} ${FindPackage_Option})
endif()

if(${DPend}_FOUND)
    message(STATUS "BM DEPENDENCY: [${DPend}] found in directory = [${${DPend}_DIR}]")
elseif(BMAKE_ENABLE_FETCH_GITHUB_CATCH)
    include(Dep/BMake_Catch_Funcs)
     bm_fetch_github_catch( ${DPend} )
    list( APPEND CMAKE_MODULE_PATH ${${DPend}_SOURCE_DIR}/contrib )
else()
    include(Dep/BMake_Catch_Funcs)
     bm_fetch_depdir_catch( ${DPend} )
    list( APPEND CMAKE_MODULE_PATH ${${DPend}_SOURCE_DIR}/contrib )
endif()


# Target and compile setup set here, once, for testing and used by Catch_Funcs.cmake::setup_catch
add_library(catch_testing INTERFACE)
target_link_libraries(catch_testing INTERFACE Catch2::Catch2)
include(BMake/Target_Compile)
  bm_target_compile(catch_testing)
