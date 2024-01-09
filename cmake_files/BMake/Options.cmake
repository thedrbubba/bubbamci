
# A central place for placing Bubbamake Developer created Option Variables. 
#   For example: -DBMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS=ON
#    Users of Bubbamake can set their own defaults as needed.
#
function(bm_options_general)
    # See the top of the top CMakeLists.txt file for option BMAKE_ENABLE_BUILD_TESTING initialization.

    option(BMAKE_ENABLE_AUTOEXE_TESTS
	   "Enables the execution of tests automatically post build of their targets." OFF)
    include(CMakeDependentOption)
    cmake_dependent_option(BMAKE_USE_AUTOEXE_TESTS
	    "Use the AutoExe of tests" ON
	    "BMAKE_ENABLE_AUTOEXE_TESTS;BMAKE_ENABLE_BUILD_TESTING" OFF)


    # These are for control of the examples of each .... for demonstration purposes 	   
    option(BMAKE_ENABLE_DEPENDENCY_MPARK_VARIANT
	    "Enables Use of mpark variant library." OFF)
    option(BMAKE_ENABLE_DEPENDENCY_BOOST
	    "Enables Use of Boost library." ON)    
    option(BMAKE_ENABLE_DEPENDENCY_CATCH
	   "Enables Use of Catch library." ON)

	# Just for debugging cmake traceback logic of entering a file.
	option(BMAKE_ENABLE_CMAKELISTS_DIAGNOSTICS
	   "Enables CmakeLists.txt output for debugging." ON)

endfunction()

# Functions that gets a list of possible dependency's options for each dependency
#
function(bm_options_dependencies)
	include(BMake/Dep/MParkV_Funcs)
	 bm_options_mpark_variant()

	include(BMake/Dep/Catch_Funcs)
	 bm_options_catch()

	include(BMake/Dep/Boost_Funcs)
	 bm_options_boost()
endfunction()

