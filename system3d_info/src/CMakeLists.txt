set(TARGET system3d_info)

file(GLOB SOURCES *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(SHARED)
    add_library(${TARGET} SHARED ${SOURCES})
else()
    add_library(${TARGET} ${SOURCES})
endif()


