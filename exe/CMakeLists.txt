project(main)

set(EXE_SOURCES main.cpp)

add_executable(main ${EXE_SOURCES})

target_link_libraries(main PRIVATE funcs_lib)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/lib)