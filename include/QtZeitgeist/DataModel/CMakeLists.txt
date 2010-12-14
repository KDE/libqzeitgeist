set(library_HDRS
    Event
    event.h
    Subject
    subject.h
    TimeRange
    timerange.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist/DataModel)
