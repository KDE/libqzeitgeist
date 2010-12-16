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

#include "test-log.h"

void LogTest::initTestCase()
{
    // Initialize QtZeitgeist types.
    QtZeitgeist::init();

    // Create the object to be tested.
    m_log = new QtZeitgeist::Log(this);

    // Initialize the monitor.
    m_monitor = 0;
};

void LogTest::cleanupTestCase()
{
    // Clear m_log;
    delete m_log;

    // Clear the id list.
    m_ids.clear();
};

void LogTest::insertEventsTest()
{
    // Event list to be inserted.
    QtZeitgeist::DataModel::EventList events;

    // Event item 1.
    QtZeitgeist::DataModel::Event event1;

    event1.setInterpretation("foo://Interp");
    event1.setManifestation("foo://Manif");
    event1.setActor("app://firefox.desktop");

    QtZeitgeist::DataModel::Subject subject1;

    subject1.setUri("file:///tmp/bar.txt");
    subject1.setInterpretation("foo://TextDoc");
    subject1.setManifestation("foo://File");
    subject1.setOrigin("file:///tmp");
    subject1.setMimeType("text/plain");
    subject1.setText("bar.txt");
    subject1.setStorage("bfb486f6-f5f8-4296-8871-0cc749cf8ef7");

    QtZeitgeist::DataModel::SubjectList subjects1;
    subjects1 << subject1;

    event1.setSubjects(subjects1);

    events.append(event1);

    // Event item 2.
    QtZeitgeist::DataModel::Event event2;

    event2.setInterpretation("foo://Interp2");
    event2.setManifestation("foo://Manif2");
    event2.setActor("app://firefox.desktop");

    QtZeitgeist::DataModel::Subject subject2;

    subject2.setUri("file:///tmp/bar.txt2");
    subject2.setInterpretation("foo://TextDoc");
    subject2.setManifestation("foo://File");
    subject2.setOrigin("file:///tmp");
    subject2.setMimeType("text/plain");
    subject2.setText("bar.txt");
    subject2.setStorage("bfb486f6-f5f8-4296-8871-0cc749cf8ef7");

    QtZeitgeist::DataModel::SubjectList subjects2;
    subjects2 << subject2;

    event2.setSubjects(subjects2);

    events.append(event2);


    // Insert events into Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::EventIdList> reply =
        m_log->insertEvents(events);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY (reply.isValid() == true);

    // Check if the return is not empty
    QVERIFY (reply.value().size() > 0);

    // Check if the id is not 0;
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i] != 0);

    // Assign to our id list.
    m_ids = reply.value();
};

void LogTest::getEventsTest()
{
    QVERIFY(m_ids.size() > 0);

    // Get events from Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::EventList> reply =
        m_log->getEvents(m_ids);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY (reply.isValid() == true);

    // Check if the return is not empty
    QVERIFY (reply.value().size() > 0);

    // Check if the id is not 0;
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i].id() != 0);
};

void LogTest::findEventIdsTest()
{
    QtZeitgeist::DataModel::Event event;
    QtZeitgeist::DataModel::EventList events;

    // Set the template to search for.
    event.setActor("app://firefox.desktop");
    event.setSubjects(QtZeitgeist::DataModel::SubjectList());

    // Add to the event list.
    events << event;

    // Query for all events since Epoch.
    QtZeitgeist::DataModel::TimeRange timeRange =
        QtZeitgeist::DataModel::TimeRange::timeRangeToNow();

    // Search on Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::EventIdList> reply =
        m_log->findEventIds(timeRange, events,
                QtZeitgeist::Log::Any, 10,
                QtZeitgeist::Log::MostRecentEvents);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY (reply.isValid() == true);

    // Check if the return is not empty
    QVERIFY (reply.value().size() > 0);

    // Check if the id is 0;
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i] != 0);
}

void LogTest::findEventsTest()
{
    QtZeitgeist::DataModel::Event event;
    QtZeitgeist::DataModel::EventList events;

    // Set the template to search for.
    event.setActor("app://firefox.desktop");
    event.setSubjects(QtZeitgeist::DataModel::SubjectList());

    // Add to the event list.
    events << event;

    // Query for all events since Epoch.
    QtZeitgeist::DataModel::TimeRange timeRange =
        QtZeitgeist::DataModel::TimeRange::timeRangeToNow();

    // Search on Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::EventList> reply =
        m_log->findEvents(timeRange, events,
                QtZeitgeist::Log::Any, 10,
                QtZeitgeist::Log::MostRecentEvents);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY (reply.isValid() == true);

    // Check if the return is not empty
    QVERIFY (reply.value().size() > 0);

    // Check if the id is 0;
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i].id() != 0);
}

void LogTest::deleteEventsTest()
{
    QVERIFY(m_ids.size() > 0);

    // Get events from Zeitgeist.
    m_log->deleteEvents(m_ids);

    // Get the supposed deleted events from Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::EventList> reply =
        m_log->getEvents(m_ids);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY (reply.isValid() == true);

    // Check if the return is not empty
    QVERIFY (reply.value().size() > 0);

    // Check if the id is 0;
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i].id() == 0);
};


void LogTest::installMonitor()
{
    QtZeitgeist::DataModel::Event event;
    QtZeitgeist::DataModel::EventList events;

    // Set the template to search for.
    event.setActor("app://firefox.desktop");

    // Add to the event list.
    events << event;

    // Query for all events since Epoch.
    QtZeitgeist::DataModel::TimeRange timeRange =
        QtZeitgeist::DataModel::TimeRange::timeRangeToNow();

    // Ask to register a monitor.
    m_monitor = m_log->installMonitor(timeRange, events);

    // Check if it was created.
    QVERIFY(m_monitor != 0);
}

void LogTest::removeMonitor()
{
    QVERIFY(m_monitor != 0);

    // Ask to remove the monitor.
    m_log->removeMonitor(const_cast<QtZeitgeist::Monitor *>(m_monitor));
}

QTEST_MAIN(LogTest)
