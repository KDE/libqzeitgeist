project(QtZeitgeist)

# Minimal CMAKE version
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(Qt4 4.7.0 COMPONENTS QtCore QtDBus REQUIRED)

#use CPack for packaging code up
include(CPack)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")


if(QT4_FOUND)
	include_directories(${QT_INCLUDE_DIR})
	include_directories(${QT_QT_INCLUDE_DIR})
	include_directories(${QT_QTCORE_INCLUDE_DIR})
	include_directories(${QT_QTDBUS_INCLUDE_DIR})
endif(QT4_FOUND)

set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/modules/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

# Generate pkg-config file
configure_file(${CMAKE_SOURCE_DIR}/QtZeitgeist.pc.in ${CMAKE_BINARY_DIR}/QtZeitgeist.pc)
install(FILES ${CMAKE_BINARY_DIR}/QtZeitgeist.pc DESTINATION lib/pkgconfig)

add_subdirectory(include)
add_subdirectory(src)
