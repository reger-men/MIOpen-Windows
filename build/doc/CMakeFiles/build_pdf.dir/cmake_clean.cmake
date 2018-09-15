file(REMOVE_RECURSE
  "doxygen/output"
  "../../doc/html"
  "sphinx/_doctrees"
  "sphinx/_build"
  "../../doc/pdf"
  "sphinx/_doctrees"
  "sphinx/_build"
  "CMakeFiles/build_pdf"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/build_pdf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
