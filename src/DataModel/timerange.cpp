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


#include "timerange.h"

#include <limits>

namespace QZeitgeist
{

namespace DataModel
{

class TimeRangePrivate
{
public :
    TimeRangePrivate(qint64 _begin = 0, qint64 _end = 0)
        : begin(_begin),
        end(_end)
    {
    }

    qint64 begin;
    qint64 end;
};

TimeRange::TimeRange()
    : d(new TimeRangePrivate())
{
    Q_ASSERT(d);
}

TimeRange::TimeRange(const TimeRange & source)
    : d(new TimeRangePrivate())
{
    Q_ASSERT(d);

    // Copy the source attribute's value.
    d->begin = source.d->begin;
    d->end = source.d->end;
}

TimeRange::TimeRange(qint64 begin, qint64 end)
    : d(new TimeRangePrivate(begin, end))
{
}

TimeRange::~TimeRange()
{
    delete d;
}

qint64 TimeRange::begin() const
{
    return d->begin;
}

void TimeRange::setBegin(qint64 begin)
{
    d->begin = begin;
}

qint64 TimeRange::end() const
{
    return d->end;
}


void TimeRange::setEnd(qint64 end)
{
    d->end = end;
}

TimeRange TimeRange::timeRangeToNow()
{
    return TimeRange(0, QDateTime::currentDateTime().toMSecsSinceEpoch());
}

TimeRange TimeRange::timeRangeFromNow()
{
    return TimeRange(QDateTime::currentDateTime().toMSecsSinceEpoch(),
            std::numeric_limits<qint64>::max());
}

TimeRange TimeRange::always()
{
    return TimeRange(0, std::numeric_limits<qint64>::max());
}

TimeRange &TimeRange::operator = (const TimeRange &source)
{
    // Copy the source attribute's value.
    if (this != &source) {
        d->begin = source.d->begin;
        d->end = source.d->end;
    }

    return *this;
}

QDBusArgument & operator << (QDBusArgument &argument,
        const TimeRange &timeRange)
{
    argument.beginStructure();

    argument
        << timeRange.d->begin
        << timeRange.d->end;

    argument.endStructure();

    return argument;
}

const QDBusArgument & operator >> (const QDBusArgument &argument,
        TimeRange &timeRange)
{
    argument.beginStructure();

    argument
        >> timeRange.d->begin
        >> timeRange.d->end;

    argument.endStructure();

    return argument;
}

};

};
