cmake_minimum_required(VERSION 3.10)

# Set the project name
project(exif-decorator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the executable
add_executable(exif-decorator 
    src/main.cpp
)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set OpenSSL paths
set(OPENSSL_INCLUDE_DIR "C:/Program Files/FireDaemon OpenSSL 3/include")
set(OPENSSL_LIB_DIR "C:/Program Files/FireDaemon OpenSSL 3/lib")

# Include OpenSSL directories
include_directories(${OPENSSL_INCLUDE_DIR})

# Link OpenSSL libraries
target_link_libraries(exif-decorator 
    ${OPENSSL_LIB_DIR}/libssl.lib 
    ${OPENSSL_LIB_DIR}/libcrypto.lib
)

# Include cpp-httplib
set(CPPHTTPLIB_DIR "./deps/cpp-httplib")

include_directories(${CPPHTTPLIB_DIR})