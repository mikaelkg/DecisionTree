#----------------------------------------------------------------
# Generated CMake target import file for configuration "Coverage".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dectree" for configuration "Coverage"
set_property(TARGET dectree APPEND PROPERTY IMPORTED_CONFIGURATIONS COVERAGE)
set_target_properties(dectree PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_COVERAGE "CXX"
  IMPORTED_LOCATION_COVERAGE "${_IMPORT_PREFIX}/lib/libdectree.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dectree )
list(APPEND _IMPORT_CHECK_FILES_FOR_dectree "${_IMPORT_PREFIX}/lib/libdectree.a" )

# Import target "tui" for configuration "Coverage"
set_property(TARGET tui APPEND PROPERTY IMPORTED_CONFIGURATIONS COVERAGE)
set_target_properties(tui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_COVERAGE "CXX"
  IMPORTED_LOCATION_COVERAGE "${_IMPORT_PREFIX}/lib/libtui.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS tui )
list(APPEND _IMPORT_CHECK_FILES_FOR_tui "${_IMPORT_PREFIX}/lib/libtui.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
