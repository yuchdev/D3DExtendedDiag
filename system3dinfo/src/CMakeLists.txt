set(TARGET system3dinfo)

file(GLOB SOURCES *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/d3dcore/include 
)

if(SHARED)
    add_library(${TARGET} SHARED ${SOURCES})
else()
    add_library(${TARGET} ${SOURCES})
endif()

add_dependencies(${TARGET} d3dcore)  
target_link_libraries(${TARGET} ${Boost_LIBRARIES} d3dcore)
