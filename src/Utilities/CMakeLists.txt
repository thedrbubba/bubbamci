if(BMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS)
	message(STATUS " CMakeLists.txt: In directory = [${CMAKE_CURRENT_BINARY_DIR}]")
endif()

set(target Utilities)


add_library( ${target}
  AssertFailure.cc
)
target_link_libraries(${target} PUBLIC 
   Boost::boost
)
target_include_directories( ${target} INTERFACE 
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_subdirectory(Math)

include(BMake/Target_Compile)
 bm_target_compile(${target})

 unset(target)