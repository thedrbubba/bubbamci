if(BMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS)
  message(STATUS " CMakeLists.txt: In directory = [${CMAKE_CURRENT_BINARY_DIR}]")
endif()

add_subdirectory(Utilities)
