function(bm_target_compile_stuff target_name)
  target_compile_features(${target_name} INTERFACE cxx_std_17)
endfunction(bm_target_compile_stuff target_name)

function(bm_target_compile target_name)
  bm_target_compile_stuff(${target_name})

  target_compile_options(${target_name} INTERFACE
	$<$<IN_LIST:${CMAKE_CXX_COMPILER_ID},GNU;AppleClang>:-Wall;-Wunused-parameter>
	$<$<NOT:$<BOOL:${WIN32}>>:$<$<IN_LIST:${CMAKE_CXX_COMPILER_ID},Clang>:-Wall>>
	$<$<BOOL:${WIN32}>:$<$<IN_LIST:${CMAKE_CXX_COMPILER_ID},Clang>:-Wall;-Wno-c++98-compat;-Wno-c++98-compat-pedantic>>
	$<$<IN_LIST:${CMAKE_CXX_COMPILER_ID},MSVC>:/permissive->
  )
endfunction(bm_target_compile target_name)

#set a function up that sets target_compile_definitions
#want to hook boost assert -D definitions in here.

