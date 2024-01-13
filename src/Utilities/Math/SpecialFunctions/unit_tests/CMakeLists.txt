if(BMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS)
	message(STATUS " CMakeLists.txt: In directory = [${CMAKE_CURRENT_BINARY_DIR}]")
endif()

set(source_list 
	Broadening_tests.cc
    negExp_tests.cc
    Erf_tests.cc
)
set(library_list
   ${target}
)
set(include_list
    ${CMAKE_CURRENT_LIST_DIR}
)

include(BMake/Dep/Catch_Funcs)
 bm_setup_catch(Unit${target})

 unset(target)
