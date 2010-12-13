set(QT_DONT_USE_QTGUI "YES")
include(${QT_USE_FILE})

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

set(generated_SRCS
    _gen/blacklistinterface.cpp
)

set(generated_HDRS
    _gen/blacklistinterface.h
)

set(library_SRCS
    ${generated_SRCS}
    datamodel/event.cpp
    datamodel/timerange.cpp
)

set(library_MOC_HDRS
    ${generated_HDRS}
    ${INC_DIR}/QtZeitgeist/DataModel/event.h
    ${INC_DIR}/QtZeitgeist/DataModel/timerange.h
)

qt4_wrap_cpp(library_MOC_SRCS ${library_MOC_HDRS})
add_library(qzeitgeist SHARED ${library_SRCS} ${library_MOC_SRCS})
target_link_libraries(qzeitgeist ${QT_LIBRARIES} ${QDBUS_LDFLAGS})
install(TARGETS qzeitgeist DESTINATION lib)
