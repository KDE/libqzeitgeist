project(QZeitgeist)

# Minimal CMAKE version
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(Qt4 4.7.0 COMPONENTS QtCore QtDBus QtTest REQUIRED)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-fvisibility=hidden __HAVE_GCC_VISIBILITY)
if (__HAVE_GCC_VISIBILITY AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif (__HAVE_GCC_VISIBILITY AND NOT WIN32)

set(QZEITGEIST_VERSION_MAJOR 0)
set(QZEITGEIST_VERSION_MINOR 7)
set(QZEITGEIST_VERSION_PATCH 90)
set(QZEITGEIST_VERSION "${QZEITGEIST_VERSION_MAJOR}.${QZEITGEIST_VERSION_MINOR}.${QZEITGEIST_VERSION_PATCH}")


set(CPACK_PACKAGE_VERSION_MAJOR ${QZEITGEIST_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${QZEITGEIST_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${QZEITGEIST_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "QZeitgeist-${CPACK_PACKAGE_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")

#use CPack for packaging code up
include(CPack)

set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/modules/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

add_subdirectory(include)
add_subdirectory(src)

option(BUILD_TESTS "Build Tests" FALSE)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Generate cmake file
get_target_property(QZEITGEIST_LIBRARY qzeitgeist LOCATION)
configure_file(QZeitgeistConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/QZeitgeistConfig.cmake @ONLY)
configure_file(QZeitgeistConfigVersion.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/QZeitgeistConfigVersion.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QZeitgeistConfigVersion.cmake ${CMAKE_CURRENT_BINARY_DIR}/QZeitgeistConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/QZeitgeist/)
install(EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/QZeitgeist)

# Generate pkg-config file
configure_file(${CMAKE_SOURCE_DIR}/QZeitgeist.pc.in ${CMAKE_BINARY_DIR}/QZeitgeist.pc)
install(FILES ${CMAKE_BINARY_DIR}/QZeitgeist.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)

