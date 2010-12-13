set(library_HDRS
    QtZeitgeist
    qtzeitgeist.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist)

add_subdirectory(DataModel)
