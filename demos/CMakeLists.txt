find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src ${QT_INCLUDES})

add_subdirectory(simple-list)
