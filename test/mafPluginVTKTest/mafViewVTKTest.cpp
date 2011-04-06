/*
 *  mafViewVTKTest.cpp
 *  mafPluginVTKTest
 *
 *  Created by Roberto Mucci on 26/03/10.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafVisitorFindSceneNodeByVMEHash.h>
#include <mafResourcesRegistration.h>
#include <mafVMEManager.h>
#include <mafView.h>
#include <mafViewVTK.h>
#include <mafPipeVisualVTKSurface.h>
#include <mafSceneNode.h>
#include <mafVME.h>
#include <mafContainer.h>
#include <mafDataSet.h>

#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkRenderWindow.h>
#include <vtkAlgorithmOutput.h>

#include <vtkSphereSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;
using namespace mafPluginVTK;

/**
 Class name: mafViewTest
 This class implements the test suite for mafViewVTK.
 */

//! <title>
//mafViewVTK
//! </title>
//! <description>
//mafViewVTK defines the VTK view in MAF3.
//! </description>

class mafViewVTKTest : public QObject {
    Q_OBJECT

private slots:

    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        mafRegisterObjectAndAcceptBind(mafPluginVTK::mafPipeVisualVTKSurface);
        mafVMEManager::instance();

        /// Create the view...
        m_View = mafNEW(mafPluginVTK::mafViewVTK);

        // Create a polydata.
        m_DataSource = vtkCubeSource::New();
        m_DataSource->SetXLength(5);
        m_DataSource->SetYLength(3);
        m_DataSource->SetZLength(8);

        m_DataSourceContainer.setExternalCodecType("mafPluginVTK::mafExternalDataCodecVTK");
        m_DataSourceContainer.setExternalDataType("vtkAlgorithmOutput");
        m_DataSourceContainer = m_DataSource->GetOutputPort(0);

        //Insert data into VME
        m_VmeCube = mafNEW(mafResources::mafVME);
        m_VmeCube->setObjectName("VME Cube");
        m_DataSetCube = mafNEW(mafResources::mafDataSet);
        m_DataSetCube->setDataValue(&m_DataSourceContainer);
        m_VmeCube->dataSetCollection()->insertItem(m_DataSetCube, 0);

        // Second test VME
        m_DataSourceMoved = vtkCubeSource::New();
        m_DataSourceMoved->SetXLength(5);
        m_DataSourceMoved->SetYLength(3);
        m_DataSourceMoved->SetZLength(8);

        vtkTransform *t = vtkTransform::New();
        t->RotateZ(50);
        t->RotateX(50);
        t->Update();

        m_PDataFilter = vtkTransformPolyDataFilter::New();
        m_PDataFilter->SetTransform(t);
        m_PDataFilter->SetInputConnection(m_DataSourceMoved->GetOutputPort(0));
        m_PDataFilter->Update();
        t->Delete();

        m_DataSourceContainerMoved.setExternalCodecType("mafPluginVTK::mafExternalDataCodecVTK");
        m_DataSourceContainerMoved.setExternalDataType("vtkAlgorithmOutput");
        m_DataSourceContainerMoved = m_PDataFilter->GetOutputPort(0);
        m_DataSetCubeMoved = mafNEW(mafResources::mafDataSet);
        m_DataSetCubeMoved->setDataValue(&m_DataSourceContainerMoved);

        m_VmeCubeMoved = mafNEW(mafResources::mafVME);
        m_VmeCubeMoved->setObjectName("Moved VME Cube");
        m_VmeCubeMoved->dataSetCollection()->insertItem(m_DataSetCubeMoved, 0);
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        //To close widget window
        mafContainerInterfacePointer widgetContainer;
        widgetContainer = m_View->property("renderWidget").value<mafCore::mafContainerInterfacePointer>();
        QWidget *widget = mafContainerPointerTypeCast(QWidget, widgetContainer)->externalData();
        widget->close();

        mafDEL(m_View);
        mafDEL(m_VmeCube);
        mafDEL(m_VmeCubeMoved);
        m_PDataFilter->Delete();
        m_DataSource->Delete();
        m_DataSourceMoved->Delete();
        mafVMEManager::instance()->shutdown();
        mafMessageHandler::instance()->shutdown();
    }

    /// mafViewVTK allocation test case.
    void mafViewVTKAllocationTest();

    /// mafViewVTK 2 VME visualization test case.
    void mafViewVTKCreateView2VMETest();

private:
    mafViewVTK *m_View; ///< Test var.
    mafVME *m_VmeCube; ///< Test var.
    mafVME *m_VmeCubeMoved; ///< Test var.
    vtkCubeSource *m_DataSource;
    vtkCubeSource *m_DataSourceMoved;
    vtkTransformPolyDataFilter *m_PDataFilter; ///< Filter used to transform the bounding box.
    mafContainer<vtkAlgorithmOutput> m_DataSourceContainer; ///< Container of the Data Source
    mafContainer<vtkAlgorithmOutput> m_DataSourceContainerMoved; ///< Container of the Data S
    mafResources::mafDataSet *m_DataSetCube;
    mafResources::mafDataSet *m_DataSetCubeMoved;
};

void mafViewVTKTest::mafViewVTKAllocationTest() {
    QVERIFY(m_View != NULL);
}

void mafViewVTKTest::mafViewVTKCreateView2VMETest() {
    //! <snippet>
    m_View->create();

    // Ask for the inner widget.
    mafContainerInterfacePointer resultWidget;
    resultWidget = m_View->property("renderWidget").value<mafCore::mafContainerInterfacePointer>();

    QWidget *resultObject = mafContainerPointerTypeCast(QWidget, resultWidget)->externalData();
    resultObject->resize(QSize(400, 400));
    resultObject->show();

    QString name_result = resultObject->objectName();
    QCOMPARE(name_result, QString("VTKWidget"));

    mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafObjectBase *, m_VmeCube));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.add", mafEventTypeLocal, &argList);

    m_View->plugVisualPipe("vtkAlgorithmOutput","mafPluginVTK::mafPipeVisualVTKSurface");
    //! </snippet>

    // Visualize first cube
    QString h = m_VmeCube->objectHash();
    mafVisitorFindSceneNodeByVMEHash *v = new mafVisitorFindSceneNodeByVMEHash(h, mafCodeLocation);
    mafObjectRegistry::instance()->findObjectsThreaded(v);
    mafSceneNode *cubeNode = v->sceneNode();
    m_View->showSceneNode(cubeNode, true);
    mafDEL(v);

    QTest::qSleep(2000);
    // Visualize also second cube (I could cutomize visualPipe)
    argList.clear();
    argList.append(mafEventArgument(mafCore::mafObjectBase *, m_VmeCubeMoved));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.add", mafEventTypeLocal, &argList);

    v = new mafVisitorFindSceneNodeByVMEHash(m_VmeCubeMoved->objectHash(), mafCodeLocation);
    mafObjectRegistry::instance()->findObjectsThreaded(v);
    mafSceneNode *cubeMovedNode = v->sceneNode();
    mafDEL(v);
    m_View->showSceneNode(cubeMovedNode, true,  "mafPluginVTK::mafPipeVisualVTKSurface");
    QTest::qSleep(2000);

    // Show off first cube
    m_View->showSceneNode(cubeNode, false);
    QTest::qSleep(2000);    
}

MAF_REGISTER_TEST(mafViewVTKTest);
#include "mafViewVTKTest.moc"