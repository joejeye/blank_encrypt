# This is an intermediate CMakeLists.txt. Its purpose is to
# make the code in the parent directory's CMakeLists.txt
# cleaner, specifically with less `add_subdirectory(...)`
# commands. Without this CMakeLists.txt, the parent directory's
# CMakeLists.txt would have to call `add_subdirectory` on each
# following subdirectories respectively.

add_subdirectory(BINARY_LAYER)
add_subdirectory(ENCODING_LAYER)
add_subdirectory(IO_INTERFACE)
