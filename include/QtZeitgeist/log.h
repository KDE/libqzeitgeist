/*
 * This file is part of QtZeitgeist.
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


#ifndef QTZEITGEIST_LOG_H_
#define QTZEITGEIST_LOG_H_

#include <QObject>
#include <QDBusPendingReply>

#include "QtZeitgeist/DataModel/Event"

namespace QtZeitgeist
{

class LogPrivate;

/**
 * @class Log log.h log.h
 * @brief Primary access point for talking to the Zeitgeist daemon.
 *
 * @Log encapsulates the low level access to the Zeitgeist daemon.
 * You can use it to manage the log by inserting and deleting entries as well
 * as do queries on the logged data.
 *
 * It's important to realize that the @Log class does not expose
 * any API that does synchronous communications with the message bus -
 * everything is asynchronous. Thus, instead of the real result, each
 * asynchronous operation will return a DBus pending reply object, that can
 * be used to watch and fetch the real operation return/result.
 *
 * Example:
 *
 * QDBusPendingCall async = log->asyncCall(value1, value2);
 * QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(async, this);
 *
 * QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
 *                  this, SLOT(callFinishedSlot(QDBusPendingCallWatcher*)));
 *
 *
 * @see Event
 *
 * @author Abner Silva <abner@collabora.co.uk>
 */
class Q_DECL_EXPORT Log : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Log)

public:

    /**
     * Default constructor.
     */
    explicit Log(QObject *parent = 0);

    /**
     * Destructor.
     */
    virtual ~Log();

    /**
     * Asynchronously send a set of events to the Zeitgeist daemon, requesting
     * they be inserted into the log.
     *
     * @param events the list of events to be inserted.
     *
     * returns The Id list of the inserted events.
     */
    QDBusPendingReply<QtZeitgeist::DataModel::EventIdList> insertEvents(
            const QtZeitgeist::DataModel::EventList events);
private:

    // D Pointer.
    class LogPrivate * const d;
};

};

#endif // QTZEITGEIST_LOG_H_
