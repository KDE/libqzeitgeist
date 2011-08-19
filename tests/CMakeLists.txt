include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/DataModel)

add_subdirectory(datasourceregistry)
add_subdirectory(log)
