# Boost Handling Script. 
#  Find in this file the following functions:
#    function( bm_options_boost )
#    function( bm_fetch_github_boost )
#    function( bm_setting_boostassert )
#

function(bm_options_boost)
    option(BMAKE_ENABLE_FINDPACKAGE_BOOST
       "Enables Find_Package for Boost." ON )
    option(BMAKE_FINDPACKAGE_BOOST_REQUIRED
       "Makes Boost Find_Package Option [REQUIRED]. Set OFF for [QUIET]." ON)
    option(BMAKE_ENABLE_FETCH_GITHUB_BOOST
       "FetchContent for Boost from Github." OFF)
    # NOTE: BMAKE_BOOST_ASSERT=OFF is for the future when CJ's catch2ext::CHECK_ASSERT is open sourced and available.'
    #  GPU machines cannot use std::exceptions which BOOST_ASSERT implemented in Bubbamake are based on. See Utilities/ dir.
    option(BMAKE_BOOST_ASSERT
       "Use Boost_Assert Logic in bm_setting_boostassert() (ON). No settings (OFF) goes to <cassert>'s assert() thus abort()." ON)
endfunction(bm_options_boost)

function(bm_fetch_github_boost DPend)
    message(STATUS " -DBMAKE_ENABLE_FETCH_GITHUB_BOOST=ON was used.")
    message(FATAL_ERROR " BM DEPENDENCY: [${DPend}] is not ready with its CMake-Boost Project!!!!")
    
    include(FetchContent)
    FetchContent_Declare(
        ${DPend}
        GIT_REPOSITORY "https://github.com/boostorg/boost.git"
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable( ${DPend} )
endfunction(bm_fetch_github_boost)

function(bm_setting_boostassert)# target)
    if(BMAKE_BOOST_ASSERT)
        set(StateOf_Assert "Enabling BOOST_ASSERT")

        if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
          add_definitions( -DBOOST_ENABLE_ASSERT_HANDLER )
#          target_compile_definitions(${target} PUBLIC
#              -DBOOST_ENABLE_ASSERT_HANDLER
#          )
          set(StateOf_Debugging "Enabling Debugging")
        else()
          set(StateOf_Debugging "Disabling Debugging")

          if( CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" ) 
             add_definitions( -DBOOST_ENABLE_ASSERT_HANDLER)
          elseif( CMAKE_BUILD_TYPE STREQUAL "Release" 
               OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel" )
             add_definitions( -DBOOST_DISABLE_ASSERTS )
             set(StateOf_Assert "Disabling BOOST_ASSERT")
          else()
             message( WARNING " BM BOOST_ASSERT Logic Used: Build Type = ${CMAKE_BUILD_TYPE} is unknown to BOOST_ASSERT Logic." )          
             return()
          endif()
        endif()
        message( STATUS " BM BOOST_ASSERT Logic Used: Build Type = ${CMAKE_BUILD_TYPE}; ${StateOf_Assert}; ${StateOf_Debugging}" )
        
    else()
        add_definitions( -DBM_BOOST_USE_CASSERTS )    
        message( STATUS " BM BOOST_ASSERT Disabled: Build Type = ${CMAKE_BUILD_TYPE}; cassert USED in boost_assert's place with [-DCMAKE_BUILD_TYPE=Debug] ONLY." )
    endif()
endfunction()
