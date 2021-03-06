/*
 *  mafMementoResourceTest.cpp
 *  mafResourcesTest
 *
 *  Created by Paolo Quadrani on 22/09/09.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafResourcesRegistration.h>
#include <mafMementoResource.h>

using namespace mafCore;
using namespace mafResources;

//! <title>
//mafMementoResource
//! </title>
//! <description>
//mafMementoResource defines the MAF3 base resource for storing
//a mafResource state. This can be used to restore a previous
//stored resource state (undo mechanism or serialization purposes).
//! </description>

/**
 Class name: mafMementoResourceTest
 This class implements the test suite for mafMementoResource.
 */
class mafMementoResourceTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        m_MementoResource = NULL;
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_MementoResource);
        mafMessageHandler::instance()->shutdown();
    }

    /// mafMementoResource allocation test case.
    void mafMementoResourceDefaultAllocationTest();
    /// mafMementoResource allocation test case.
    void mafMementoResourceCustomAllocationTest();

private:
    mafMementoResource *m_MementoResource; ///< Test var.
};

void mafMementoResourceTest::mafMementoResourceDefaultAllocationTest() {
    mafMemento *m = (mafMemento *)mafNEWFromString("mafResources::mafMementoResource");
    QVERIFY(m != NULL);
    m_MementoResource = qobject_cast<mafMementoResource*>(m);
    QVERIFY(m_MementoResource != NULL);
}

void mafMementoResourceTest::mafMementoResourceCustomAllocationTest() {
    mafDEL(m_MementoResource);

    mafObject *obj = mafNEW(mafCore::mafObject);
    mafResourceList inputList;

    //! <snippet>
    m_MementoResource = new mafMementoResource(obj, &inputList, mafCodeLocation);
    //! </snippet>
    QVERIFY(m_MementoResource != NULL);

    mafDEL(obj);
}

MAF_REGISTER_TEST(mafMementoResourceTest);
#include "mafMementoResourceTest.moc"

