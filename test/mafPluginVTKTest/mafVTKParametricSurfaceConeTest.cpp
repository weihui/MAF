/*
 *  mafVTKParametricSurfaceConeTest.cpp
 *  mafPluginVTKTest
 *
 *  Created by Roberto Mucci on 20/01/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafResourcesRegistration.h>
#include <mafPipeVisualVTKSurface.h>
#include <mafVTKParametricSurfaceCone.h>
#include <mafVTKWidget.h>
#include <mafDataBoundaryAlgorithmVTK.h>
#include <mafProxy.h>
#include <mafVME.h>
#include <mafDataSet.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkAlgorithmOutput.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <QMainWindow>
#include <QDebug>

using namespace mafResources;
using namespace mafEventBus;
using namespace mafPluginVTK;

/**
 Class name: mafVTKParametricSurfaceConeTest
 This class implements the test suite for mafVTKParametricSurfaceCone.
 */

//! <title>
//mafVTKParametricSurfaceCone
//! </title>
//! <description>
//mafVTKParametricSurfaceCone represent a VTK cone surface with modificable parametrs.
//! </description>

class mafVTKParametricSurfaceConeTest : public QObject {
    Q_OBJECT
    //initialize all the graphic resources
    void initializeGraphicResources();

    //shutdown all the graphic resources
    void shutdownGraphicResources();

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        mafRegisterObjectAndAcceptBind(mafPluginVTK::mafPipeVisualVTKSurface);
        
        // Create the parametric sphere.
        m_ParametricCone = mafNEW(mafPluginVTK::mafVTKParametricSurfaceCone);

        //! <snippet>
        //// m_DataSourceContainer is the container of type vtkAlgorithmOutput
        //// to "wrap" the vtkPolyData just simply use the code below.
        m_DataSourceContainer.setClassTypeNameFunction(vtkClassTypeNameExtract);
        m_DataSourceContainer = m_ParametricCone->output();

        //Insert data into VME
        m_VME = mafNEW(mafResources::mafVME);
        m_DataSet = mafNEW(mafResources::mafDataSet);
        mafDataBoundaryAlgorithmVTK *boundaryAlgorithm;
        boundaryAlgorithm = mafNEW(mafDataBoundaryAlgorithmVTK);
        m_DataSet->setBoundaryAlgorithm(boundaryAlgorithm);
        m_DataSet->setDataValue(&m_DataSourceContainer);
        m_VME->dataSetCollection()->insertItem(m_DataSet, 0);
        //! </snippet>
        initializeGraphicResources();
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_DataSet);
        mafDEL(m_VME);
        mafDEL(m_ParametricCone);
        mafMessageHandler::instance()->shutdown();
        shutdownGraphicResources();
    }

    /// visualize parametric surface
    void visualizeTest();


private:
    mafVTKParametricSurfaceCone *m_ParametricCone; ///< Parametric sphere.
    mafVME *m_VME; ///< Contain the only item vtkPolydata representing a surface.
    mafResources::mafDataSet *m_DataSet;
    mafProxy<vtkAlgorithmOutput> m_DataSourceContainer; ///< Container of the Data Source
    QObject *m_RenderWidget; /// renderer widget
    vtkRenderer *m_Renderer; ///< Accessory renderer
    QMainWindow *w;
};

void mafVTKParametricSurfaceConeTest::initializeGraphicResources() {
    w = new QMainWindow();
    w->setMinimumSize(640,480);

    m_RenderWidget = new mafVTKWidget();
    ((mafVTKWidget*)m_RenderWidget)->setParent(w);

    m_Renderer = ((mafVTKWidget*)m_RenderWidget)->renderer();

    m_Renderer->SetBackground(0.1, 0.1, 0.1);
    ((mafVTKWidget*)m_RenderWidget)->update();
    w->show();
}

void mafVTKParametricSurfaceConeTest::shutdownGraphicResources() {
    w->close();
}

void mafVTKParametricSurfaceConeTest::visualizeTest() {
    mafPipeVisualVTKSurface *pipe;
    pipe = mafNEW(mafPluginVTK::mafPipeVisualVTKSurface);
    pipe->setInput(m_VME);
    pipe->setProperty("scalarVisibility", 0);
    pipe->setProperty("immediateRendering", 1);
    pipe->setGraphicObject(m_RenderWidget);
    pipe->updatePipe();

    // Get the vtkActor from the visual pipe
    // And assign to a mafProxy
    mafProxy<vtkActor> *actor = mafProxyPointerTypeCast(vtkActor, pipe->output());
    QVERIFY(actor != NULL);

    // Connect the actor (contained into the container) with the renderer.
    m_Renderer->AddActor(*actor);
    m_Renderer->ResetCamera();

    ((mafVTKWidget*)m_RenderWidget)->update();
    ((mafVTKWidget*)m_RenderWidget)->GetRenderWindow()->Render();

    //iren->Start();
    QTest::qSleep(1000);

    double newCenter[3];
    newCenter[0] = 10;
    newCenter[1] = 5;
    newCenter[2] = 20.5;

    //Change parameters of the sphere.
    m_ParametricCone->setCenter(newCenter);
    m_ParametricCone->setProperty("coneHeight", 20);
    m_ParametricCone->setProperty("coneRadius", 1);
    m_ParametricCone->setProperty("coneRes", 10);
    m_ParametricCone->setProperty("coneCapping", 0);
    m_ParametricCone->updateSurface();


    //Check if parameters had changed.
    QCOMPARE(m_ParametricCone->property("coneHeight").toDouble(), 20.0);
    QCOMPARE(m_ParametricCone->property("coneRadius").toDouble(), 1.0);
    QCOMPARE(m_ParametricCone->property("coneRes").toDouble(), 10.0);
    QCOMPARE(m_ParametricCone->property("coneCapping").toInt(), 0);

    QCOMPARE(m_ParametricCone->center()[0], 10.0);
    QCOMPARE(m_ParametricCone->center()[1], 5.0);
    QCOMPARE(m_ParametricCone->center()[2], 20.5);

    pipe->setGraphicObject(NULL);
    mafDEL(pipe);
}


MAF_REGISTER_TEST(mafVTKParametricSurfaceConeTest);
#include "mafVTKParametricSurfaceConeTest.moc"


