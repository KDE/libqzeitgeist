find_package(Doxygen REQUIRED)

configure_file(Doxyfile.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
                   COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   COMMENT "Generating doxygen docs")

add_custom_target(docs ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)

install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "${SHARE_INSTALL_PREFIX}/doc/libqzeitgeist/")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/qch/" DESTINATION "${SHARE_INSTALL_PREFIX}/doc/libqzeitgeist/")
