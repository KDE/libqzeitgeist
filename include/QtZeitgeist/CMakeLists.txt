set(library_HDRS
    DataSourceRegistry
    datasourceregistry.h
    Log
    log.h
    Monitor
    monitor.h
    QtZeitgeist
    qtzeitgeist.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist)

add_subdirectory(DataModel)
