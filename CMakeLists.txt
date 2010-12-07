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
   main.cpp
)

kde4_add_executable(test-zeitgeist ${test-zeitgeist_SRCS})

target_link_libraries(
   test-zeitgeist
   ${QT_QTCORE_LIBRARIES}
   ${QT_QTDBUS_LIBRARIES}
)


