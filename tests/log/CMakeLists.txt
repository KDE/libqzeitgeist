include(${QT_USE_FILE})

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

set(test-log_SRCS
    test-log.cpp
)

set(test-log_HDRS
    test-log.h
)

QT4_WRAP_CPP(test-log_MOC_SRCS ${test-log_HDRS})
QT4_AUTOMOC(${test-log_SRCS})

add_executable(test-log ${test-log_SRCS} ${test-log_MOC_SRCS})
target_link_libraries(test-log qzeitgeist ${QT_LIBRARIES})

