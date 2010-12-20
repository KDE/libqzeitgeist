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

#include "test-dsr.h"

#include <QSignalSpy>

void DataSourceRegistryTest::initTestCase()
{
    // Initialize QtZeitgeist types.
    QtZeitgeist::init();

    // Create the object to be tested.
    m_registry = new QtZeitgeist::DataSourceRegistry(this);
    m_testId = "registry-test";
};

void DataSourceRegistryTest::cleanupTestCase()
{
    // Clear m_registry;
    delete m_registry;
};

void DataSourceRegistryTest::registerSourceTest()
{
    QString name = "datasource registry test";
    QString description = "DataSource to test the datasource registry.";
    QtZeitgeist::DataModel::EventList events;

    QDBusPendingReply<bool> reply =
        m_registry->registerDataSource(m_testId, name, description, events);

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY(reply.isValid());
}

void DataSourceRegistryTest::getSourcesTest()
{
    // Get sources from Zeitgeist.
    QDBusPendingReply<QtZeitgeist::DataModel::DataSourceList> reply =
        m_registry->getDataSources();

    // Block and wait for reply.
    reply.waitForFinished();

    // Check if the return is valid.
    QVERIFY(reply.isValid());

    // Check if the return is not empty.
    QVERIFY(reply.value().size() > 0);

    // Check the ids are not blank.
    for (uint i = 0; i < reply.value().size(); ++i)
        QVERIFY(reply.value()[i].uniqueId().isEmpty() == false);
}

void DataSourceRegistryTest::enableSourceTest()
{
    QSignalSpy spy(m_registry, SIGNAL(dataSourceEnabled(const QString&, bool)));

    // First test we can disable our source.
    m_registry->setDataSourceEnabled(m_testId, false);

    while (spy.count() == 0)
        QTest::qWait(5);

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(1).type() == QVariant::Bool);
    QVERIFY(arguments.at(1).toBool() == false);

    // Then test that we can enable our source.
    m_registry->setDataSourceEnabled(m_testId, true);

    while (spy.count() == 0)
        QTest::qWait(5);

    arguments = spy.takeFirst();
    QVERIFY(arguments.at(1).type() == QVariant::Bool);
    QVERIFY(arguments.at(1).toBool() == true);
}

QTEST_MAIN(DataSourceRegistryTest)
