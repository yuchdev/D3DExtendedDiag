project(d3dcore_example_app CXX)
set(TARGET d3dcore_example_app)

cmake_policy(SET CMP0015 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCES *.cpp) 
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET}
    ${Boost_LIBRARIES}
    d3dcore)

add_dependencies(${TARGET} d3dcore) 
set_property(TARGET d3dcore_example_app PROPERTY FOLDER "Tests")
