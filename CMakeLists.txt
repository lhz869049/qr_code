cmake_minimum_required (VERSION 3.2.0)
project (detect_qrcode)

add_definitions(-std=c++11)
add_definitions( -g -o2)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/share/OpenCV") 
find_package(OpenCV)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/share/Zbar")  
find_package (ZBar0)

#headers
include_directories(${PROJECT_SOURCE_DIR}/inc)
#sources
set(SRC
${PROJECT_SOURCE_DIR}/src/main.cpp
${PROJECT_SOURCE_DIR}/src/detect_qrcode.cpp
)

add_executable (main ${SRC})

target_link_libraries (main ${OpenCV_LIBRARIES} ${ZBAR_LIBRARIES}zbar)
