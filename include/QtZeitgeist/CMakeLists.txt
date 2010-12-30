set(library_HDRS
    DataSourceRegistry
    datasourceregistry.h
    Log
    log.h
    Monitor
    monitor.h
    QtZeitgeist
    qtzeitgeist.h
    Interpretation
    interpretation.h
    Manifestation
    manifestation.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist)

add_subdirectory(DataModel)
