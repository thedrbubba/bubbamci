# MPark-Variant Handling Script
#  function( bm_options_mpark_variant )
#

function(bm_options_mpark_variant)
    option(BMAKE_ENABLE_FINDPACKAGE_MPARK
       "Enables Find_Package for MPark-Variant." ON )
    option(BMAKE_FINDPACKAGE_MPARK_REQUIRED
       "Makes MPark-Variant Find_Package Option [REQUIRED]. Default: OFF [QUIET]." OFF)
    option(BMAKE_ENABLE_FETCH_GITHUB_MPARK
       "FetchContent for MPark-Variant from Github." OFF )
endfunction(bm_options_mpark_variant)

