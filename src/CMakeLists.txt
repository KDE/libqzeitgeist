set(QT_DONT_USE_QTGUI "YES")
include(${QT_USE_FILE})

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

set(generated_SRCS
    _gen/blacklistinterface.cpp
    _gen/datasourceinterface.cpp
    _gen/loginterface.cpp
    _gen/monitoradaptor.cpp
)

set(generated_HDRS
    _gen/blacklistinterface.h
    _gen/datasourceinterface.h
    _gen/loginterface.h
    _gen/monitoradaptor.h
)

set(library_SRCS
    ${generated_SRCS}
    qtzeitgeist.cpp
    datasourceregistry.cpp
    log.cpp
    monitor.cpp
    datamodel/datasource.cpp
    datamodel/event.cpp
    datamodel/subject.cpp
    datamodel/timerange.cpp
)

set(library_MOC_HDRS
    ${generated_HDRS}
    ${INC_DIR}/QtZeitgeist/datasourceregistry.h
    ${INC_DIR}/QtZeitgeist/log.h
    ${INC_DIR}/QtZeitgeist/monitor.h
    ${INC_DIR}/QtZeitgeist/qtzeitgeist.h
    ${INC_DIR}/QtZeitgeist/DataModel/datasource.h
    ${INC_DIR}/QtZeitgeist/DataModel/event.h
    ${INC_DIR}/QtZeitgeist/DataModel/subject.h
    ${INC_DIR}/QtZeitgeist/DataModel/timerange.h
    monitor_p.h
)

qt4_wrap_cpp(library_MOC_SRCS ${library_MOC_HDRS})
add_library(qzeitgeist SHARED ${library_SRCS} ${library_MOC_SRCS})
target_link_libraries(qzeitgeist ${QT_LIBRARIES} ${QDBUS_LDFLAGS})
set_target_properties(qzeitgeist PROPERTIES VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}" SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR})
install(TARGETS qzeitgeist EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
install(EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/share/qzeitgeist/cmake NAMESPACE QZEITGEIST_)
