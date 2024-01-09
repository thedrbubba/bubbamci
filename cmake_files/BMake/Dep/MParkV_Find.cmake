set(DPend mpark_variant)
set(DPend_Version 1.4.0)
string(TOLOWER ${DPend} DPend_Lower)   


if(BMAKE_ENABLE_FINDPACKAGE_MPARK)
   set(FindPackage_Option QUIET)
   if(BMAKE_FINDPACKAGE_MPARK_REQUIRED)
      set(FindPackage_Option REQUIRED)
   endif()

   set(FP_ARGS
     "FINDPACKAGE_ARGS"
        "${DPend_Version}"
        "${FindPackage_Option}"
   )
   message(STATUS " BM DEPENDENCY: [${DPend_Lower}] maybe found by find_package")
endif()

if(BMAKE_ENABLE_FETCH_GITHUB_MPARK)
   set(FC_ARGS
     "FETCHCONTENT_ARGS"
        "GIT_REPOSITORY" "https://github.com/mpark/variant.git"
        "GIT_SHALLOW"    "TRUE"
        "GIT_TAG"        "v${DPend_Version}"
   )
   message(STATUS " BM DEPENDENCY: [${DPend_Lower}] maybe fetched from Github")
else()
   include(FetchContent)
   set(FC_ARGS
     "FETCHCONTENT_ARGS"
        "SUBBUILD_DIR" "${FETCHCONTENT_BASE_DIR}/${DPend_Lower}-subbuild"
        "BINARY_DIR"   "${FETCHCONTENT_BASE_DIR}/${DPend_Lower}-build"
        "SOURCE_DIR"   "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${DPend}"
   )
   message(STATUS " BM DEPENDENCY: [${DPend_Lower}] maybe populated from a source directory")
endif()


include(BMake/FindOrFetch)
find_or_fetch(${DPend}
   ${FP_ARGS}
   ${FC_ARGS}
)
