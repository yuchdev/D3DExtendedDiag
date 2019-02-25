set(TARGET qd3ddiagex)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(QT_DEPENDENCIES Core Widgets)
find_package(Qt5 REQUIRED ${QT_DEPENDENCIES})

file(GLOB SOURCE *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)

add_executable(${TARGET} WIN32 ${SOURCE})
set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::XmlPatterns)

target_link_libraries(${TARGET} ${QT_LIBRARIES})
