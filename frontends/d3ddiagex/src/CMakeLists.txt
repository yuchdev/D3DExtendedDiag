set(TARGET d3ddiagex)

find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS program_options REQUIRED) 
file(GLOB SOURCES *.cpp ../include/${TARGET}/*.h)
 
include_directories(${Boost_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/d3dcore/include 
)

add_executable(${TARGET} ${SOURCES})

if(SHARED)
target_link_libraries(${TARGET} 
    ${Boost_LIBRARIES})

else()
target_link_libraries(${TARGET} 
    ${Boost_LIBRARIES} 
    d3dcore)

endif()

add_dependencies(${TARGET} d3dcore)
