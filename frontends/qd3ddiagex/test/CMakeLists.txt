set(TARGET qd3ddiagex_unit_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

enable_testing(true)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

# TODO: add testable *.cpp files
file(GLOB SOURCES *.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/frontends/qd3ddiagex/include)

add_executable(${TARGET} ${SOURCES})
add_dependencies(${TARGET} qd3ddiagex)

target_link_libraries(${TARGET}
    Qt5::Core
    Qt5::Test)

add_test(NAME ${TARGET} COMMAND ${TARGET})
SET_PROPERTY(TARGET ${TARGET} PROPERTY FOLDER "Tests")
