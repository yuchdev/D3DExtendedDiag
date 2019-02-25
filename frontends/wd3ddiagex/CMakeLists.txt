cmake_minimum_required(VERSION 3.12)
project(wd3ddiagex CXX)
set(TARGET wd3ddiagex)

if("UNIX" )
  message( FATAL_ERROR "POSIX configuration is not supported for that project")
elseif("WIN32")
  set(CMAKE_CXX_FLAGS "/EHsc")
endif()


cmake_policy(SET CMP0015 NEW)
file(GLOB SOURCES *.cpp ../include/${TARGET}/*.h)
add_executable(${TARGET} WIN32 ${SOURCES})