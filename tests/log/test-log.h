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

#include <QTest>
#include <QDebug>

#include "QZeitgeist/QZeitgeist"
#include "QZeitgeist/Log"
#include "QZeitgeist/Monitor"

class LogTest : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase();
    void cleanupTestCase();

    void insertEventsTest();
    void getEventsTest();
    void findEventIdsTest();
    void findEventsTest();
    void deleteEventsTest();
    void installMonitor();
    void removeMonitor();

private:
    QZeitgeist::Log *m_log;
    const QZeitgeist::Monitor *m_monitor;
    QZeitgeist::DataModel::EventIdList m_ids;
};
