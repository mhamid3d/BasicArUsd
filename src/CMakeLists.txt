cmake_minimum_required(VERSION "3.7.1")

project("BasicResolver")

set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}")

set(USD_ROOT "" CACHE STRING "Root location of USD installation")


find_package(Python 3.9 COMPONENTS Interpreter Development REQUIRED EXACT)

execute_process(COMMAND "${Python_EXECUTABLE}" "-c"
    "from distutils import sysconfig as s;import sys;import struct;
print(sys.prefix);
print(s.get_python_inc(plat_specific=True));
"
    RESULT_VARIABLE _PYTHON_SUCCESS
    OUTPUT_VARIABLE _PYTHON_VALUES
    ERROR_VARIABLE _PYTHON_ERROR_VALUE)

string(REGEX REPLACE ";" "\\\\;" _PYTHON_VALUES ${_PYTHON_VALUES})
string(REGEX REPLACE "\n" ";" _PYTHON_VALUES ${_PYTHON_VALUES})
list(GET _PYTHON_VALUES 0 PYTHON_PREFIX)
list(GET _PYTHON_VALUES 1 PYTHON_INCLUDE_DIR)
string(REGEX REPLACE "\\\\" "/" PYTHON_PREFIX ${PYTHON_PREFIX})
string(REGEX REPLACE "\\\\" "/" PYTHON_INCLUDE_DIR ${PYTHON_INCLUDE_DIR})

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    string(APPEND CMAKE_C_FLAGS " /Zc:inline-")
    string(APPEND CMAKE_CXX_FLAGS " /Zc:inline-")
endif()

include_directories(
    .
    ${PYTHON_INCLUDE_DIR}
    ${PYTHON_PREFIX}/Library/include
)

link_directories(
    ${USD_ROOT}/lib
    ${Python_LIBRARY_DIRS}
)

link_libraries(
    ${CURL_LIBRARY}
)

add_library(BasicResolver SHARED basicResolver.cpp)

set_target_properties(BasicResolver PROPERTIES PREFIX "")

target_include_directories(BasicResolver PUBLIC
    ${USD_ROOT}/include
    ${USD_ROOT}/include/boost-1_70
)

target_link_libraries(BasicResolver
    usd_arch
    usd_ar
    usd_tf
    usd_plug
    usd_js
    usd_vt
)


set(PLUG_INFO_LIBRARY_NAME "BasicResolver${CMAKE_SHARED_LIBRARY_SUFFIX}")
configure_file(plugInfo.json.in ${CMAKE_BINARY_DIR}/base/plugInfo.json @ONLY)

install(TARGETS BasicResolver DESTINATION lib)
install(FILES basicResolver.h DESTINATION include)
install(FILES ${CMAKE_BINARY_DIR}/base/plugInfo.json DESTINATION plugin/base)