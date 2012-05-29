include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(mainwindow.cpp)
add_executable(browser main.cpp mainwindow.cpp)
target_link_libraries(browser qzeitgeist ${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARY})
