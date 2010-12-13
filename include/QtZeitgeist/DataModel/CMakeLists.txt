set(library_HDRS
    Event
    event.h
    TimeRange
    timerange.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist/DataModel)
