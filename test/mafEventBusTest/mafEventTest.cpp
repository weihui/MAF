
/*
 *  mafEventTest.cpp
 *  mafEventBusTest
 *
 *  Created by Daniele Giunchi on 20/04/10.
 *  Copyright 2009-2011 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafEvent.h>

using namespace mafEventBus;

/**
 Class name: mafEventTest
 This class implements the test suite for mafEvent.
 */

//! <title>
//mafEvent
//! </title>
//! <description>
//mafEvent is the object which contain information in a dictionary structure,
//regarding message between classes through mafEventBus
//! </description>

class mafEventTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        m_Event = new mafEvent();
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        delete m_Event;
    }

    /// mafEventDispatcherRemote allocation test case.
    void mafEventAllocationTest();

    /// test all the accessors of a mafEvent
    void mafEventAccessorsTest();

private:
    mafEvent *m_Event; ///< Test var.
};

void mafEventTest::mafEventAllocationTest() {
    QVERIFY(m_Event != NULL);
}

void mafEventTest::mafEventAccessorsTest() {
    m_Event->setEventType(mafEventTypeRemote);
    QVERIFY(m_Event->eventType() == mafEventTypeRemote);
    QVERIFY(m_Event->isEventLocal() != true);

    QString topic = "maf.level1.level2.level3";
    m_Event->setEventTopic(topic);
    QCOMPARE(m_Event->eventTopic(), topic);

    const QVariantHash *cdict = m_Event->entries(); //const metod
    QVERIFY(cdict != NULL);

    QVariantHash *dict = m_Event->entries();
    QVERIFY(dict != NULL);

    QVariant var = (*m_Event)[TOPIC];
    QString check = var.toString();
    QCOMPARE(check, topic);

    delete m_Event;
    topic = "maf.lev1.lev2.lev3";
    m_Event = new mafEvent(topic, mafEventTypeLocal, mafSignatureTypeSignal, this, "testmethod");
    QCOMPARE(m_Event->eventTopic(), topic);
}


MAF_REGISTER_TEST(mafEventTest);
#include "mafEventTest.moc"



