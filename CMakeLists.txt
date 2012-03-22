project(QZeitgeist)

# Minimal CMAKE version
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

find_package(Qt4 4.7.0 COMPONENTS QtCore QtDBus QtTest QtDeclarative REQUIRED)


set(QZEITGEIST_VERSION_MAJOR 0)
set(QZEITGEIST_VERSION_MINOR 8)
set(QZEITGEIST_VERSION_PATCH 0)
set(QZEITGEIST_LIB_SOVERSION 1)
set(QZEITGEIST_VERSION "${QZEITGEIST_VERSION_MAJOR}.${QZEITGEIST_VERSION_MINOR}.${QZEITGEIST_VERSION_PATCH}")
set(SHARE_INSTALL_PREFIX "share")

option(QZEITGEIST_BUILD_DOC "Build API documentation" OFF)

if(QZEITGEIST_BUILD_DOC)
    add_subdirectory(doc)
endif()

# Provide a cmake option, which, if set, force the Qt stuff to be installed into the
# system Qt directories, which may be outside CMAKE_INSTALL_PREFIX.
# By default always install inside CMAKE_INSTALL_PREFIX.
option(QZEITGEIST_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT "Install Qt designer plugins, QML plugins and mkspecs into the system Qt install directory or not" FALSE)
if(QZEITGEIST_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT)
    # in this case, the values have to be FORCED into the cache
    set(QZEITGEIST_QT_IMPORTS_INSTALL_DIR ${QT_IMPORTS_DIR} CACHE PATH "The directory where QZeitgeist Qt imports (QML) will be installed to." FORCE)
else(QZEITGEIST_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT)
    # in this case, the values can be adjusted by the user e.g. via cmake-gui, so no FORCE
    set(QZEITGEIST_QT_IMPORTS_INSTALL_DIR lib${LIB_SUFFIX}/qt4/imports CACHE PATH "The directory where QZeitgeist Qt imports (QML) will be installed to.")
endif(QZEITGEIST_INSTALL_QT_EXTENSIONS_INTO_SYSTEM_QT)

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

option(BUILD_DECLARATIVE "Build Declarative bindings" TRUE)

if (BUILD_DECLARATIVE)
   add_subdirectory(declarative)
endif()

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

