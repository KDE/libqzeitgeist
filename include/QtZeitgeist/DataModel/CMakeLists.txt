set(library_HDRS
    DataSource
    datasource.h
    Event
    event.h
    Subject
    subject.h
    TimeRange
    timerange.h
)

install(FILES ${library_HDRS} DESTINATION include/QtZeitgeist/DataModel)
