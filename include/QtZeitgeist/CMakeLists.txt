set(library_HDRS
    QtZeitgeist
    qtzeitgeist.h
    Log
    log.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist)

add_subdirectory(DataModel)
