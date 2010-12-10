find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

include_directories(
   ${QT_INCLUDES}
   ${KDE4_INCLUDES}
   ${CMAKE_SOURCE_DIR}
)

set(
   test-zeitgeist_SRCS
   test-zeitgeist.cpp
   types.cpp
   main.cpp
)

set(zeitgeist_xml org.gnome.zeitgeist.xml)
set_source_files_properties(
   ${zeitgeist_xml}
   PROPERTIES INCLUDE "types.h"
)

qt4_add_dbus_interface(test-zeitgeist_SRCS ${zeitgeist_xml} zeitgeist_interface)

kde4_add_executable(test-zeitgeist ${test-zeitgeist_SRCS})

target_link_libraries(
   test-zeitgeist
   ${QT_QTCORE_LIBRARIES}
   ${QT_QTDBUS_LIBRARIES}
)


