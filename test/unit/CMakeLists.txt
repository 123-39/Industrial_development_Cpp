project(tests)

set(EXE_SOURCES XMLreaderTest.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${EXE_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE funcs_lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE funcs_lib GTest::Main)