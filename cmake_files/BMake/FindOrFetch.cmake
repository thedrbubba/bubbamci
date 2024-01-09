#
# FindOrFetch.make: https://xcp-gitlab.lanl.gov/tadams/cmakefindorfetch
# C.J. Solomon and T. Adams
#
# Several Functions:
#
# - find_or_fetch         (external Primary function)
#   * set_default_options (internal function)
#   * fetched_check       (internal function)
#   * fetched_configure   (internal function)
#   * messageFoF          (internal function)
#
#
include_guard(GLOBAL)

include(FetchContent)
include(CMakePackageConfigHelpers)

option(FoFPrint "Toggles messages in this module file. Default: OFF" OFF)


# Function: find_or_fetch
#
function(find_or_fetch package)
    messageFoF(" FindOrFetch.cmake::find_or_fetch() - Looking for package = [${package}]")
   
  # parse arguments from ARGN
  set(options)
  set(one_value_args "COMPATIBILITY")
  set(multi_value_args "FINDPACKAGE_ARGS" "FETCHCONTENT_ARGS" "FETCHED_MODULE_PATHS") #TODO: TRA - FETCHED_MODULE_FILES
  cmake_parse_arguments(FindOrFetch "${options}" "${one_value_args}"
    "${multi_value_args}" ${ARGN})

  set_default_options()
    messageFoF(" version       = [${version}]")
    messageFoF(" COMPATIBILITY = [${FindOrFetch_COMPATIBILITY}]")
  fetched_check(${package})

  find_package(${package} ${FindOrFetch_FINDPACKAGE_ARGS})
  if( ${package}_FOUND )
     set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
       messageFoF(" ${package}_FOUND with find_package")
     return()
  elseif( NOT FindOrFetch_FETCHCONTENT_ARGS )
     message(WARNING "[${package}] NOT Found. FETCHCONTENT_ARGS were NOT supplied.\n")
     return()
  endif()


  FetchContent_Declare(${package} "${FindOrFetch_FETCHCONTENT_ARGS}")
  FetchContent_Populate(${package})
    messageFoF(" ${package} FetchContent-ed")

  fetched_configure(${package}) 

  # <package>Config.cmake has the information needed as if we have set it directly explicitly after FetchContent_Populate.
  # This, also, overcomes a multiple-call error for add_subdirectory if done explicitly after FetchContent_Populate. 
  find_package(${package} REQUIRED)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
    messageFoF(" ${package}Config.cmake script was tested in a find_package call (found and used) after creation.")

endfunction()


# Support functions below here ..........................................................

# Function: set_default_options
#  Used by find_or_fetch function above.
#
function(set_default_options)
  #  If NO {*}_ARGS are provided, then it will fall thru and find_package with REQUIRED is the default.
  if( FindOrFetch_FINDPACKAGE_ARGS OR FindOrFetch_FETCHCONTENT_ARGS )
     #  If NO find_package ARGS are set to REQUIRED or QUIET, then default to QUIET
     if(NOT (("REQUIRED" IN_LIST FindOrFetch_FINDPACKAGE_ARGS) OR
             ("QUIET"    IN_LIST FindOrFetch_FINDPACKAGE_ARGS)) )
        list(APPEND FindOrFetch_FINDPACKAGE_ARGS "QUIET")
        set(FindOrFetch_FINDPACKAGE_ARGS ${FindOrFetch_FINDPACKAGE_ARGS} PARENT_SCOPE)   
     endif()
  endif()

  # Default FindOrFetch_COMPATIBILITY if not provided
  if( NOT DEFINED FindOrFetch_COMPATIBILITY )
    set(FindOrFetch_COMPATIBILITY "SameMajorVersion" PARENT_SCOPE)
  endif()

  # Look for and handle version number if passed in FindOrFetch_FINDPACKAGE_ARGS
  list(GET FindOrFetch_FINDPACKAGE_ARGS 0 maybe_version)
  if( "${maybe_version}" MATCHES "^[0-9]+(\.[0-9]+(\.[0-9]+(\.[0-9]+)?)?)?" )
    set(version ${maybe_version} PARENT_SCOPE)
  else()
    set(version 0.0.0 PARENT_SCOPE)
    set(FindOrFetch_COMPATIBILITY "AnyNewerVersion" PARENT_SCOPE)
  endif()

endfunction()


# Function: fetched_check
#  Used by find_or_fetch function above.
#
function(fetched_check package)
  string(TOLOWER ${package} package_lower)

  FetchContent_GetProperties(${package})

  if(${package_lower}_POPULATED)
     # Should be find_package(<package> REQUIRED)
    if( NOT "REQUIRED" IN_LIST FindOrFetch_FINDPACKAGE_ARGS )
      list(REMOVE_ITEM FindOrFetch_FINDPACKAGE_ARGS "QUIET")
      list(APPEND FindOrFetch_FINDPACKAGE_ARGS "REQUIRED")
    endif()
    set(FindOrFetch_FINDPACKAGE_ARGS ${FindOrFetch_FINDPACKAGE_ARGS} PARENT_SCOPE)
  else()
     # Need to cleanup in case FetchContent is used to Configure.
    set(${package}_DIR "" CACHE PATH "" FORCE)
    if(${package}_FAUX_DIR)
       # Safer to remove than <package>_DIR.
       file(REMOVE_RECURSE ${${package}_FAUX_DIR})
    endif()
  endif()

endfunction()


# Function: fetched_configure
#  Used by find_or_fetch function above.
#
function(fetched_configure package)
  string(TOLOWER ${package} package_lower)

   # FAUX_DIR is created so we go check on it somewhere else, and can remove it safely if needed. 
   # And NOT unsafely remove <package>_DIR which might point to a "real" installed package. 
  set(${package}_FAUX_DIR ${FETCHCONTENT_BASE_DIR}/${package_lower}-faux)
  set(${package}_DIR ${${package}_FAUX_DIR} CACHE PATH "" FORCE)

  # write a ${package}Config.cmake file that will add_subdirectory the fetched content only once
  file(MAKE_DIRECTORY ${${package}_DIR})
  file(WRITE ${${package}_DIR}/${package}Config.cmake "include_guard(GLOBAL)\n")
  if(DEFINED FindOrFetch_FETCHED_MODULE_PATHS)
    foreach(Arg ${FindOrFetch_FETCHED_MODULE_PATHS})
       file(APPEND ${${package}_DIR}/${package}Config.cmake 
                   "list(APPEND CMAKE_MODULE_PATH ${${package_lower}_SOURCE_DIR}/${Arg})\n")
    endforeach()
  endif()
  file(APPEND ${${package}_DIR}/${package}Config.cmake "add_subdirectory(${${package_lower}_SOURCE_DIR} ${${package_lower}_BINARY_DIR})\n")

  # write a ${package}ConfigVersion.cmake that adheres to the version requirements if specified
  write_basic_package_version_file(${${package}_DIR}/${package}ConfigVersion.cmake
    VERSION ${version}
    COMPATIBILITY ${FindOrFetch_COMPATIBILITY}
  )

  set(${package}_FOUND 1 PARENT_SCOPE)

endfunction()


# Function: controls diagnostic output
#
#
function(messageFoF StreamFoF)
   if(FoFPrint)
      message(STATUS "${StreamFoF}")
   endif()
endfunction()
