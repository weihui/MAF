/*
 *  mafPipeVisualTest.cpp
 *  mafResourcesTest
 *
 *  Created by Daniele Giunchi on 22/09/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafPipeVisual.h>
#include <mafVME.h>
#include <mafContainer.h>

using namespace mafCore;
using namespace mafResources;

//------------------------------------------------------------------------------------------
/**
 Class name: mafPipeVisualCustom
 This class implements the data pipe to be tested.
 */
class  testVisualPipeCustomForVisualPipe : public  mafPipeVisual {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafPipeVisual);

public:
    /// Object constructor.
    testVisualPipeCustomForVisualPipe(const QString code_location = "");

    /// Initialize and create the pipeline
    /*virtual*/ void createPipe();

    /// Return the string variable initializated and updated from the data pipe.
    QString pipeline() {return m_PipeLine;}

    bool m_RecivedPickEvent; /// True if maf.local.resources.interaction.vmePicked has been catched.

public slots:
    /// Allow to execute and update the pipeline when something change
    /*virtual*/ void updatePipe(double t = -1);

    /// Called when if maf.local.resources.interaction.vmePicked has been catched
    void vmePicked(double *pos, unsigned long modifiers, mafCore::mafObjectBase *vme);

private:
    QString m_PipeLine; ///< Test var.
    mafCore::mafContainer<QString> m_Container; ///< Test var.

};

testVisualPipeCustomForVisualPipe::testVisualPipeCustomForVisualPipe(const QString code_location) : mafPipeVisual(code_location), m_PipeLine("") {
    mafRegisterLocalSignal("maf.local.resources.interaction.vmePicked", this, "vmePickedSignal(double *, unsigned long, mafCore::mafObjectBase *)");
    mafRegisterLocalCallback("maf.local.resources.interaction.vmePicked", this, "vmePicked(double *, unsigned long, mafCore::mafObjectBase *)");
    m_RecivedPickEvent = false;
}

void testVisualPipeCustomForVisualPipe::createPipe() {
    m_PipeLine = "Created";
    m_Output = &m_Container;
}

void testVisualPipeCustomForVisualPipe::updatePipe(double t) {
    m_PipeLine = "Updated";
    m_PipeLine.append(QString::number(t));

    m_Container = new QString;
    m_Container.externalData()->append(m_PipeLine);
}

void testVisualPipeCustomForVisualPipe::vmePicked(double *pos, unsigned long modifiers, mafCore::mafObjectBase *vme){
    Q_UNUSED(pos);
    Q_UNUSED(modifiers);
    Q_UNUSED(vme);
    m_RecivedPickEvent = true;
}

//------------------------------------------------------------------------------------------

/**
 Class name: mafPipeVisualTest
 This class implements the test suite for mafPipeVisual.
 */
class mafPipeVisualTest : public QObject {
    Q_OBJECT

private slots:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        m_VisualPipe = mafNEW(testVisualPipeCustomForVisualPipe);
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_VisualPipe);
        mafMessageHandler::instance()->shutdown();
        mafEventBus::mafEventBusManager::instance()->shutdown();
    }

    /// mafPipeVisual allocation test case.
    void mafPipeVisualAllocationTest();
    /// Test the creation and update methods..
    void mafPipeVisualCreationAndUpdateTest();
    /// Test the vmePick method.
    void mafPipeVisualVmePickTest();

private:
    testVisualPipeCustomForVisualPipe *m_VisualPipe; ///< Test var.
};

void mafPipeVisualTest::mafPipeVisualAllocationTest() {
    QVERIFY(m_VisualPipe != NULL);
}

void mafPipeVisualTest::mafPipeVisualCreationAndUpdateTest() {
    QString res("Created");
    m_VisualPipe->createPipe();

    QCOMPARE(m_VisualPipe->pipeline(), res);

    res = "Updated1";
    m_VisualPipe->updatePipe(1);
    QCOMPARE(m_VisualPipe->pipeline(), res);
}

void mafPipeVisualTest::mafPipeVisualVmePickTest() {
    double posPicked[3];
    unsigned long modifiers;
    QEvent *e;

    mafVME *vme = mafNEW(mafResources::mafVME);
    mafCore::mafContainerInterface *stringContainer = m_VisualPipe->output();

    m_VisualPipe->setInput(vme);

    mafEventBus::mafEventArgumentsList argList;
    argList.append(mafEventArgument(double *, (double *)posPicked));
    argList.append(mafEventArgument(unsigned long, modifiers));
    argList.append(mafEventArgument(mafCore::mafContainerInterface *, stringContainer));
    argList.append(mafEventArgument(QEvent *, e));
    mafEventBus::mafEventBusManager::instance()->notifyEvent("maf.local.resources.interaction.vmePick", mafEventBus::mafEventTypeLocal, &argList);
    QVERIFY(m_VisualPipe->m_RecivedPickEvent == true);


    mafDEL(vme);
}

MAF_REGISTER_TEST(mafPipeVisualTest);
#include "mafPipeVisualTest.moc"