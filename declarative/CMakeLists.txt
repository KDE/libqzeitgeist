find_package(Automoc4)
include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})

set(declarative_SRCS
    declarativeevent.cpp
    declarativelogmodel.cpp
    declarativesubject.cpp
    plugin.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)
automoc4_add_library(QZeitgeistDeclarativePlugin MODULE ${declarative_SRCS})

target_link_libraries(QZeitgeistDeclarativePlugin ${QT_QTDECLARATIVE_LIBRARIES} qzeitgeist)

install(TARGETS QZeitgeistDeclarativePlugin DESTINATION ${QZEITGEIST_QT_IMPORTS_INSTALL_DIR}/org/gnome/zeitgeist)
install(FILES qmldir DESTINATION ${QZEITGEIST_QT_IMPORTS_INSTALL_DIR}/org/gnome/zeitgeist)
