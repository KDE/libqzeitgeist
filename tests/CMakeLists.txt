include(${QT_USE_FILE})

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

add_subdirectory(datasourceregistry)
add_subdirectory(log)
