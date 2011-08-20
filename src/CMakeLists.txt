find_package(Automoc4)
set(QT_DONT_USE_QTGUI "YES")
include(${QT_USE_FILE})
include(QZeitgeistMacros)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(qzeitgeist_HEADERS
    datasourceregistry.h
    interpretation.h
    log.h
    manifestation.h
    monitor.h
    qzeitgeist.h
)

set(qzeitgeist_MODEL_HEADERS
    DataModel/datasource.h
    DataModel/event.h
    DataModel/subject.h
    DataModel/timerange.h
)

set(qzeitgeist_SRCS
    qzeitgeist.cpp
    datasourceregistry.cpp
    log.cpp
    monitor.cpp
    DataModel/datasource.cpp
    DataModel/event.cpp
    DataModel/subject.cpp
    DataModel/timerange.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/DataModel ${CMAKE_CURRENT_BINARY_DIR}/DataModel)

set(zeitgeist_DBUS_XML
    dbus-xml/org.gnome.zeitgeist.Log.xml
    dbus-xml/org.gnome.zeitgeist.Blacklist.xml
    dbus-xml/org.gnome.zeitgeist.DataSourceRegistry.xml
)

set_source_files_properties(${zeitgeist_DBUS_XML} PROPERTIES INCLUDE QZeitgeist/QZeitgeist)
zg_add_dbus_interface(qzeitgeist_SRCS dbus-xml/org.gnome.zeitgeist.Log.xml loginterface)
zg_add_dbus_interface(qzeitgeist_SRCS dbus-xml/org.gnome.zeitgeist.Blacklist.xml blacklistinterface)
zg_add_dbus_interface(qzeitgeist_SRCS dbus-xml/org.gnome.zeitgeist.DataSourceRegistry.xml datasourceregistryinterface)

qt4_add_dbus_adaptor(qzeitgeist_SRCS dbus-xml/org.gnome.zeitgeist.Monitor.xml monitor_p.h QZeitgeist::MonitorPrivate)

automoc4_add_library(qzeitgeist SHARED ${qzeitgeist_SRCS})

target_link_libraries(qzeitgeist ${QT_LIBRARIES} ${QDBUS_LDFLAGS})
set_target_properties(qzeitgeist PROPERTIES VERSION "${QZEITGEIST_VERSION}" SOVERSION ${QZEITGEIST_VERSION_MAJOR})

install(TARGETS qzeitgeist EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

install(FILES ${qzeitgeist_HEADERS} DESTINATION include/QZeitgeist)
install(FILES ${qzeitgeist_MODEL_HEADERS} DESTINATION include/QZeitgeist/DataModel)
