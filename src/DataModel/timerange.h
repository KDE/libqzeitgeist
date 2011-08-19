/*
 * This file is part of QZeitgeist.
 *
 * Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef QZEITGEIST_TIMERANGE_H_
#define QZEITGEIST_TIMERANGE_H_

#include <QDateTime>
#include <QMetaType>
#include <QDBusArgument>

namespace QZeitgeist
{

namespace DataModel
{

class TimeRangePrivate;

/**
 * @class TimeRange timerange.h timerange.h
 * @brief The representation of an interval in time, marked by a
 * beginning and an end.
 *
 * The start and the end point are represented in number of milliseconds
 * since the Unix Epoch.

 * @author Abner Silva <abner@collabora.co.uk>
 */
class Q_DECL_EXPORT TimeRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 begin READ begin WRITE setBegin)
    Q_PROPERTY(qint64 end READ end WRITE setEnd)

public:

    /**
     * Default constructor.
     */
    explicit TimeRange(QObject *parent = 0);

    /**
     * Copy constructor.
     */
    TimeRange(const TimeRange &source, QObject *parent = 0);

    /**
     * Data initializing constructor.
     *
     * @param startTime the start point of the time range.
     * @param endTime the end point of the time range.
     */
    TimeRange(qint64 startTime, qint64 endTime);

    /**
     * Destructor.
     */
    virtual ~TimeRange();

    /**
     * Returns the start point of the time range.
     *
     * @returns the begin of the time range.
     */
    qint64 begin() const;

    /**
     * Set the start value/point of the time range.
     *
     * @param begin a value for the start point in milliseconds.
     */
    void setBegin(qint64 begin);

    /**
     * Returns the end point of the time range.
     *
     * @returns the end of the time range.
     */
    qint64 end() const;

    /**
     * Set the end value/point of the time range.
     *
     * @param end a value for the start point in milliseconds.
     */
    void setEnd(qint64 end);

    /**
     * Returns a new time range starting from the beginning of the Unix Epoch
     * and ending at the moment of the invocation.
     *
     * @returns a TimeRange starting from Epoch to the current time.
     */
    static TimeRange timeRangeToNow();

    /**
     * Returns a new time range starting from the moment of invocation to the
     * end of time.
     *
     * @returns a TimeRange starting from now to the end of time.
     */
    static TimeRange timeRangeFromNow();

    /**
     * Returns a new time range starting from the Unix Epoch and ending at the
     * end of time.
     *
     * @returns A TimeRange representing always.
     */
    static TimeRange always();

    TimeRange & operator = (const TimeRange &source);

private:

    // D Pointer.
    class TimeRangePrivate * const d;

    // Marshalers operators.
    friend QDBusArgument & operator << (QDBusArgument &argument,
            const TimeRange &event);
    friend const QDBusArgument & operator >> (const QDBusArgument &argument,
            TimeRange &event);
};

Q_DECL_EXPORT QDBusArgument & operator << (QDBusArgument &argument,
               const TimeRange &event);
Q_DECL_EXPORT const QDBusArgument & operator >> (const QDBusArgument &argument,
               TimeRange &event);

};

};

// Declare types as Qt Meta Type.
Q_DECLARE_METATYPE(QZeitgeist::DataModel::TimeRange)

#endif // QZEITGEIST_TIMERANGE_H_
