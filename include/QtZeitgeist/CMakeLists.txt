set(library_HDRS
    QtZeitgeist
    qtzeitgeist.h
    Log
    log.h
    DataSourceRegistry
    datasourceregistry.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist)

add_subdirectory(DataModel)
