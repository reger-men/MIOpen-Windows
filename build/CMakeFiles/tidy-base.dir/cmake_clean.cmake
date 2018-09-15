file(REMOVE_RECURSE
  "fixits"
  "cppcheck-build"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/tidy-base.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
