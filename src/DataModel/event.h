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


#ifndef QZEITGEIST_EVENT_H_
#define QZEITGEIST_EVENT_H_

#include <QList>
#include <QDateTime>
#include <QMetaType>
#include <QDBusArgument>
#include "../qzeitgeist.h"

#include "subject.h"

namespace QZeitgeist
{

namespace DataModel
{

class EventPrivate;

/**
 * @class Event event.h event.h
 * @brief The Event objects abstract events returned from Zeitgeist queries.
 *
 * The Event class is one of the primary elements for communicating  with the
 * Zeitgeist daemon. The Event serve two purposes:
 * Unsurprisingly they represent events that have happened, but they also
 * can act as templates.
 *
 * @see Subject.
 *
 * @author Abner Silva <abner@collabora.co.uk>
 */
class QZEITGEIST_EXPORT Event
{

public:

    /**
     * Default constructor.
     *
     * Initializes the timestamp to QDateTime::currentDateTime()
     */
    explicit Event();

    /**
     * Copy constructor.
     */
    Event(const Event &source);

    /**
     * Destructor.
     */
    virtual ~Event();

    /**
     * Get the event id as assigned by the Zeitgeist engine.
     *
     * @return The event id or 0 if it's unset. An event retrieved from the
     * Zeitgeist engine will always have an event id.
     */
    quint32 id() const;

    /**
     * Get the event timestamp.
     *
     * The timestamp is in milliseconds since the Unix epoch.
     *
     * @return The event timestamp. Note that 0 is ambiguous as it denotes both
     * an unset timestamp and the time of the Unix Epoch.
     */
    QDateTime timestamp() const;

    /**
     * Set the event timestamp.
     *
     * The timestamp is in milliseconds since the Unix epoch.
     *
     * @param timestamp the timestamp to set the event for.
     *
     * Note that the if you insert events into the Zeitgeist log without a
     * timestamp set the Zeiteist daemon will automatically assign the
     * timestamp of the logging time to the event.
     */
    void setTimestamp(const QDateTime &timestamp);

    /**
     * The event interpretation represents what happened.
     *
     * It is encoded as URI defined by the Zeitgeist Event Ontology.
     * Examples could be "something was opened" or "something was modified".
     *
     * @return The event interpretation as a URI or empty if unset.
     */
    QString interpretation() const;

    /**
     * Set the event interpretation.
     *
     * @param interpretation the URI designating the interpretation type of
     * the event.
     */
    void setInterpretation(const QString &interpretation);

    /**
     * The event manifestation represents how did it happen.
     *
     * It is encoded as URI defined by the Zeitgeist Event Ontology. Examples
     * could be "the user did it" or "the system send a notification".
     *
     * @return The event interpretation as a URI or empty if unset.
     */
    QString manifestation() const;

    /**
     * Set the event manifestation.
     *
     * @param manifestation the URI designating the manifestation type of
     * the event.
     */
    void setManifestation(const QString &manifestation);

    /**
     * Get the event actor.
     *
     * The actor represents the party responsible for triggering the event.
     * When the actor is an application (which it almost always is) the actor
     * is encoded in the app:// URI scheme with the base name of the .desktop
     * file for the application appended. Eg.app://firefox.desktop
     *
     * @return A URI designating the actor of the event.
     */
    QString actor() const;

    /**
     * Set the event actor.
     *
     * @param The URI designating the actor triggering the event.
     */
    void setActor(const QString &actor);

    /**
     * Get the subject list of this event.
     *
     * @return A list containing all event's subjects.
     */
    SubjectList subjects() const;

    /**
     * Set the event's subject list.
     *
     * @param subjects the list of subjects to set.
     */
    void setSubjects(const SubjectList &subjects);

    /**
     * Get the event's payload.
     *
     * Look up the free form binary payload of @Event.
     *
     * @return The event payload or NULL (empty) if unset.
     */
    QByteArray payload() const;

    /**
     * Set the event's payload.
     *
     * Attach a a free form binary payload to @Event. Payloads are application
     * specific and can not be assumed to have any particular format unless
     * you have other contextual information about the event.
     *
     * @param payload the payload to add to @Event.
     */
    void setPayload(const QByteArray &payload);

    /**
     * Append a @Subject to the list of subjects for @Event.
     *
     * @param subject the subject to be added to the event.
     */
    void addSubject(const Subject &subject);

    Event & operator = (const Event &source);
    bool operator==(const Event &source) const;

    void setOrigin(const QString &origin);
    QString origin() const;

private:

    // D Pointer.
    class EventPrivate * const d;

    // Marshalers operators.
    friend QDBusArgument & operator << (QDBusArgument &argument,
            const Event &event);
    friend const QDBusArgument & operator >> (const QDBusArgument &argument,
            Event &event);
};

QZEITGEIST_EXPORT QDBusArgument & operator << (QDBusArgument &argument,
               const Event &event);
QZEITGEIST_EXPORT const QDBusArgument & operator >> (const QDBusArgument &argument,
               Event &event);

// Create additional types.
typedef QList<Event> EventList;
typedef QList<quint32> EventIdList;

};

};

// Declare types as Qt Meta Type.
Q_DECLARE_METATYPE(QZeitgeist::DataModel::Event)
Q_DECLARE_METATYPE(QZeitgeist::DataModel::EventList)
Q_DECLARE_METATYPE(QZeitgeist::DataModel::EventIdList)

#endif // QZEITGEIST_EVENT_H_
