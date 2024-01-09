if(BMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS)
	message(STATUS " CMakeLists.txt: In directory = [${CMAKE_CURRENT_BINARY_DIR}]")
endif()

set(target SpecialFunctions)

add_library( ${target} INTERFACE )

target_link_libraries(${target} INTERFACE 
  Boost::boost
  Utilities
  Math 
)
target_include_directories( ${target} INTERFACE 
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

include(BMake/Target_Compile)
  bm_target_compile(${target})

if(BMAKE_ENABLE_BUILD_TESTING)
   add_subdirectory(unit_tests)
endif()

#unset(target)
