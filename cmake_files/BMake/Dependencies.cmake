include(BMake/Options)
 bm_options_dependencies()


if(BMAKE_ENABLE_DEPENDENCY_CATCH)
  if(BMAKE_ENABLE_BUILD_TESTING)
	 include(BMake/Dep/Catch_Find)
  endif()
endif()


if(BMAKE_ENABLE_DEPENDENCY_BOOST) 
	include(BMake/Dep/Boost_Find)	
	
	include(BMake/Dep/Boost_Funcs)
	 bm_setting_boostassert()
endif()

if(BMAKE_ENABLE_DEPENDENCY_MPARK_VARIANT) 
	include(BMake/Dep/MParkV_Find)
endif()


