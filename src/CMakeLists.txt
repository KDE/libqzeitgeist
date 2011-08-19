find_package(Automoc4)
set(QT_DONT_USE_QTGUI "YES")
include(${QT_USE_FILE})

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

set(qzeitgeist_HEADERS
    datasourceregistry.h
    interpretation.h
    log.h
    manifestation.h
    monitor.h
    qtzeitgeist.h
    DataModel/datasource.h
    DataModel/event.h
    DataModel/subject.h
    DataModel/timerange.h
)

set(generated_SRCS
    _gen/blacklistinterface.cpp
    _gen/datasourceinterface.cpp
    _gen/loginterface.cpp
    _gen/monitoradaptor.cpp
)

set(library_SRCS
    ${generated_SRCS}
    qtzeitgeist.cpp
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

automoc4_add_library(qzeitgeist SHARED ${library_SRCS})

target_link_libraries(qzeitgeist ${QT_LIBRARIES} ${QDBUS_LDFLAGS})
set_target_properties(qzeitgeist PROPERTIES VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}" SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR})
install(TARGETS qzeitgeist EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
install(EXPORT QZeitgeistExport DESTINATION ${CMAKE_INSTALL_PREFIX}/share/qzeitgeist/cmake NAMESPACE QZEITGEIST_)
install(FILES ${qzeitgeist_HEADERS} DESTINATION include/QtZeitgeist)
