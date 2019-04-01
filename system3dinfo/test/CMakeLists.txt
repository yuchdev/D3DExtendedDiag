project(system3dinfo_unit_test CXX)
set(TARGET system3dinfo_unit_test)

cmake_policy(SET CMP0015 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS unit_test_framework date_time REQUIRED) 

file(GLOB SOURCES *.cpp) 
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    d3dcore
    system3dinfo)

add_dependencies(${TARGET} d3dcore system3dinfo)
add_test(NAME system3dinfo_unit_test COMMAND ${TARGET})
SET_PROPERTY(TARGET system3dinfo_unit_test PROPERTY FOLDER "Tests")
