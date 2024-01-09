# BMake Boost find script.
#   This is purposely NOT in a function, since certain variables lose scope after being apended.
#   For example: CMAKE_MODULES_PATH appending when used with find_package. 
#
    set(DPend Boost)
    string(TOLOWER ${DPend} DPend_Lower)   


    if(BMAKE_ENABLE_FINDPACKAGE_BOOST)
        set(FindPackage_Option QUIET)
        if(BMAKE_FINDPACKAGE_BOOST_REQUIRED)
           set(FindPackage_Option REQUIRED)
        endif()

        set( Boost_USE_STATIC_LIBS ON)
        set( Boost_COMPONENTS filesystem system serialization program_options )
        find_package(${DPend} ${FindPackage_Option} ${Boost_COMPONENTS})
    endif()


    if(${DPend}_FOUND)
           message(STATUS " BM DEPENDENCY: [${DPend_Lower}] found")
           
           list(PREPEND Boost_COMPONENTS headers)
           foreach(Boost_Target ${Boost_COMPONENTS})
              if(NOT (TARGET Boost::${Boost_Target}))
                 message(FATAL_ERROR " BM DEPENDENCY Boost_Target = [${Boost_Target}] was NOT Found!")
              endif()
           endforeach()
           if( Boost_COMPONENTS)
              message(STATUS " BM DEPENDENCY: Found targets Boost::${Boost_COMPONENTS}")
           endif()
           
    elseif(BMAKE_ENABLE_FETCH_GITHUB_BOOST)
       # This will fail. Boost-CMake project is not ready at github, at least not as easy as this.
       include(BMake/Boost_Funcs.cmake)
        bm_fetch_github_boost(${DPend_Lower})
    else()
        message(FATAL_ERROR " BM DEPENDENCY: [${DPend}] was not FOUND!")     
    endif()    
