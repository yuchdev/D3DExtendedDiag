set(TARGET d3dcore)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    add_compile_definitions(_HAS_CXX17)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

file(GLOB SOURCES *.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/${TARGET}/*.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(SHARED)
    add_library(${TARGET} SHARED ${SOURCES})
else()
    add_library(${TARGET} ${SOURCES})
endif()

target_link_libraries(${TARGET} dxguid)
