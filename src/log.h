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


#ifndef QZEITGEIST_LOG_H_
#define QZEITGEIST_LOG_H_

#include <QObject>
#include <QDBusPendingReply>

#include "DataModel/event.h"
#include "DataModel/timerange.h"

namespace QZeitgeist
{

class Monitor;
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
class QZEITGEIST_EXPORT Log : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Log)
    Q_ENUMS(StorageState)
    Q_ENUMS(ResultType)

public:

    enum StorageState
    {
        NotAvailable = 0,
        Available,
        Any
    };

    enum ResultType
    {
		MostRecentEvents = 0,
		LeastRecentEvents,
		MostRecentSubjects,
		LeastRecentSubjects,
		MostPopularSubjects,
		LeastPopularSubjects,
		MostPopularActor,
		LeastPopularActor,
		MostRecentActor,
		LeastRecentActor
    };

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
    QDBusPendingReply<QZeitgeist::DataModel::EventIdList> insertEvents(
            const QZeitgeist::DataModel::EventList events);

    /**
     * Delete the log file and all its content.
     *
     * Note: This is a dangerous method. Once it's called it will request
     * Zeitgeist to delete the entire log file and all its content in one go.
     * To delete specific subsets use @findEventIds combined with
     * @deleteEvents().
     *
     * @see findEventIds
     * @see deleteEvents
     */
    void deleteLog();

    /**
     * Get a list of URIs of subjects which frequently occur together with
     * events matching the event templates within time range.
     *
     * The resulting URIs must occur as subjects of events matching given
     * result event templates and have the given storage state.
     *
     * @param timeRange two timestamps defining the timerange for the query.
     * @param eventTemplateList a list of event templates which you want URIs
     * that relate to.
     * @param resultEventTemplateList a list of event templates which the
     * returned URIs must occur as subjects of.
     * @param state whether the item is currently known to be available.
     * @param maxEvents maximal amount of returned events.
     * @param type the Order in which the result should be made available.
     *
     * @returns A list of URI strings.
     */
    QDBusPendingReply<QStringList> findRelatedUris(
            QZeitgeist::DataModel::TimeRange timeRange,
            QZeitgeist::DataModel::EventList eventTemplateList,
            QZeitgeist::DataModel::EventList resultEventTemplateList,
            StorageState state, uint maxEvents, ResultType type);

    /**
     * Get events matching a given set of templates.
     *
     * The matching is done where unset fields in the templates are treated as
     * wildcards. If a template has more than one subject then events will
     * match the template if any one of their subjects match any one of the
     * subject templates.
     *
     * @param timeRange two timestamps defining the timerange for the query.
     * @param eventTemplateList a list of event templates which you want URIs
     * that relate to.
     * @param state whether the item is currently known to be available.
     * @param maxEvents maximal amount of returned events.
     * @param type the Order in which the result should be made available.
     *
     * @returns A list of Events.
     */
    QDBusPendingReply<QZeitgeist::DataModel::EventList> findEvents(
            QZeitgeist::DataModel::TimeRange timeRange,
            QZeitgeist::DataModel::EventList eventTemplateList,
            StorageState state, uint maxEvents, ResultType type);

    /**
     * Search for events matching a given set of templates and return the IDs
     * of matching events.
     *
     * The matching is done where unset fields in the templates are treated as
     * wildcards. If a template has more than one subject then events will
     * match the template if any one of their subjects match any one of the
     * subject templates.
     *
     * @param timeRange two timestamps defining the timerange for the query.
     * @param eventTemplateList a list of event templates which you want URIs
     * that relate to.
     * @param state whether the item is currently known to be available.
     * @param maxEvents maximal amount of returned events.
     * @param type the Order in which the result should be made available.
     *
     * @returns A list of Event Ids.
     */
    QDBusPendingReply<QZeitgeist::DataModel::EventIdList> findEventIds(
            QZeitgeist::DataModel::TimeRange timeRange,
            QZeitgeist::DataModel::EventList eventTemplateList,
            StorageState state, uint maxEvents, ResultType type);

    /**
     * Delete a set of events from the log given their IDs.
     *
     * @param ids list of event IDs.
     */
    void deleteEvents(QZeitgeist::DataModel::EventIdList ids);

    /**
     * Get full event data for a set of event IDs.
     *
     * @param ids a list of event IDs.
     *
     * @returns A list of Events.
     */
    QDBusPendingReply<QZeitgeist::DataModel::EventList> getEvents(
            QZeitgeist::DataModel::EventIdList ids);

    /**
     * Request the installation of a new monitor.
     *
     * Register a client side monitor object to receive callbacks when
     * events matching time range and event templates are inserted or deleted.
     *
     * @param timeRange a @TimeRange with the time range monitored events
     * must fall within.
     * @param eventTemplateList Event templates that events must match in
     * order to trigger the monitor.
     *
     * @return A const @Monitor instance.
     */
    QZeitgeist::Monitor *installMonitor(
            QZeitgeist::DataModel::TimeRange timeRange,
            QZeitgeist::DataModel::EventList eventTemplateList);

    /**
     * Request the removing of the given monitor.
     *
     * Remove from Zeitgeist daemon an installed @Monitor.
     * Note: Once the @Monitor is removed, the @Log class will automatically
     * delete the @Monitor instance and should not be used after it.
     *
     * @param monitor an installed  @Monitor instance to be removed.
     */
    void removeMonitor(QZeitgeist::Monitor *monitor);

private:

    // D Pointer.
    class LogPrivate * const d;
};

};

#endif // QZEITGEIST_LOG_H_
