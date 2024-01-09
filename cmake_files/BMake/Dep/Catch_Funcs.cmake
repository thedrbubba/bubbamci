# BMake Catch helper functions
#   function(bm_options_catch)
#   function(bm_setup_catch test_name)
# 

function(bm_options_catch)
    option(BMAKE_ENABLE_FINDPACKAGE_CATCH
       "Enables Find_Package for Catch." ON )
    option(BMAKE_FINDPACKAGE_CATCH_REQUIRED
       "Makes Catch Find_Package Option [REQUIRED]. Default: OFF [QUIET]." OFF)
    option(BMAKE_ENABLE_FETCH_GITHUB_CATCH
       "FetchContent for Catch from Github." OFF)
    option(BMAKE_ENABLE_CTEST_SETUP_CATCH 
       "Enables the automatic Catch CTest setup CMake Module" ON)

    include(CMakeDependentOption)
    cmake_dependent_option(BMAKE_USE_CTEST_SETUP_CATCH
	    "Use the catch_discover_tests to discovery tests and setup in ctest." ON
	    "BMAKE_ENABLE_CTEST_SETUP_CATCH;BMAKE_ENABLE_BUILD_TESTING" OFF)
endfunction()

function(bm_fetch_github_catch DPend)
    include(FetchContent)
    message(STATUS "BM DEPENDENCY: [${DPend}] being fetched from Github")    
    FetchContent_Declare( ${DPend}
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable( ${DPend} )
endfunction()


function(bm_fetch_depdir_catch DPend)
    include(FetchContent)
    message(STATUS "BM DEPENDENCY: [${DPend}] being populated from the dependencies/ directory")
    FetchContent_Declare( ${DPend}
        SUBBUILD_DIR ${FETCHCONTENT_BASE_DIR}/_dep/${DPend}-subbuild
        BINARY_DIR   ${FETCHCONTENT_BASE_DIR}/_dep/${DPend}-build
        SOURCE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${DPend}
    )
    FetchContent_MakeAvailable( ${DPend} )
endfunction()


# This function requires the file calling it
# to setup source_list, library_list, and include_list before calling this function.
# Also, the target catch_testing is used.
#
function(bm_setup_catch test_name)

    add_executable(${test_name} 
        ${CMAKE_SOURCE_DIR}/dependencies/test_mains/main_catch.cc
        ${source_list}
    )
    target_link_libraries(${test_name}  PRIVATE
        catch_testing
        ${library_list}
    )
    target_include_directories( ${test_name} PRIVATE 
         ${include_list}
    )


    if(BMAKE_USE_CTEST_SETUP_CATCH)
        include(Catch)
          catch_discover_tests(${test_name})
    endif()

    if(BMAKE_USE_AUTOEXE_TESTS)
       add_custom_command(TARGET ${test_name}
           POST_BUILD COMMAND ${test_name}
           COMMENT "Running ${test_name} Tests"
       )
    endif()
endfunction()
