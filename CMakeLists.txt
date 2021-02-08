cmake_minimum_required (VERSION 3.3)
project (keyboardIOExample)



set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable (main main.cpp keyboard.cpp)
target_link_libraries(main
    ${CMAKE_THREAD_LIBS_INIT}
)