/*
 *  mafVisualPipeVTKSurfaceTest.cpp
 *  mafPipesLibrary
 *
 *  Created by Daniele Giunchi on 01/03/10.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafVisualPipeOSGSurface.h>
#include <mafContainer.h>
#include <mafDataSet.h>
#include <mafCoreSingletons.h>
#include <mafEventBusManager.h>
#include <mafPluginManager.h>

#ifdef WIN32
    #define TEST_LIBRARY_NAME "mafPluginOSG_d.dll"
#else
    #ifdef __APPLE__
        #define TEST_LIBRARY_NAME "libmafPluginOSG_debug.dylib"
    #else
        #define TEST_LIBRARY_NAME "libmafPluginOSG_debug.so"
    #endif
#endif


using namespace mafCore;
using namespace mafResources;
using namespace mafPluginsOSG;
using namespace mafEventBus;


/**
 Class name: mafVisualPipeOSGSurfaceTest
 This class creates a vtkPolyData and visualizes it trough the mafVisualPipeOSGSurface
 */

//! <title>
//mafVisualPipeOSGSurface
//! </title>
//! <description>
//mafVisualPipeOSGSurface is a visual pipe used to render VTK polydata.
//It takes a mafDataSet as input and returns a mafContainer<vtkActor>.
//! </description>

class mafVisualPipeOSGSurfaceTest : public QObject {
    Q_OBJECT

private slots:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        mafRegisterObjectAndAcceptBind(mafPluginsOSG::mafVisualPipeOSGSurface);



        // and give it to the mafDataSet.
        //! <title>
        /*m_VME = mafNEW(mafResources::mafVME);
        m_DataSet = mafNEW(mafResources::mafDataSet);
        m_DataSet->setDataValue(&??????CONTAINER???????);
        m_VME->dataSetCollection()->insertItem(m_DataSet, 0);*/
        //! </title>
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_DataSet);
        mafUnregisterObjectAndAcceptUnbind(mafPluginsOSG::mafVisualPipeOSGSurface);
        m_PluginManager->shutdown();
        mafEventBusManager::instance()->shutdown();
        mafCoreSingletons::mafSingletonsShutdown();
    }

    /// Test the creation of the vtkActor
    void updatePipeTestFromPlugIn();
    void updatePipeTest();

private:
    mafVME *m_VME; ///< Contain the only item mesh representing a surface.
    mafDataSet *m_DataSet; ///< mesh representing a surface.
    //mafContainer<irr::scene::IAnimatedMesh> m_OSGMesh; ///< Container of the IAnimatedMesh
    mafPluginManager *m_PluginManager; ///< Test var.
};

void mafVisualPipeOSGSurfaceTest::updatePipeTestFromPlugIn() {

    m_PluginManager = mafPluginManager::instance();
    mafString pluginName = TEST_LIBRARY_NAME;

    // Load the library containing the visual pipe that I want to plug-in.
    m_PluginManager->loadPlugin(pluginName);

    // Dump the plug-in information.
    mafPluginInfo info = m_PluginManager->pluginInformation(pluginName);
    mafMsgDebug() << "Plug-in Information:";
    mafMsgDebug() << "Varsion: " << info.m_Version;
    mafMsgDebug() << "Author: " << info.m_Author;
    mafMsgDebug() << "Vendor: " << info.m_Vendor;
    mafMsgDebug() << "Description: " << info.m_Description;

    mafStringList binding_class_list;
    binding_class_list = mafCoreRegistration::acceptObject(m_VME);
    int num = binding_class_list.count();

    QVERIFY(num == 1);

    mafString visualPipeType = binding_class_list.at(0);
    QCOMPARE(visualPipeType,mafString("mafPluginsOSG::mafVisualPipeOSGSurface"));

}


void mafVisualPipeOSGSurfaceTest::updatePipeTest() {

    //! <title>
    mafVisualPipeOSGSurface *pipe;
    pipe = mafNEW(mafPluginsOSG::mafVisualPipeOSGSurface);
    //! </title>
    pipe->setInput(m_VME);

    //ADD CODE HERE
}

MAF_REGISTER_TEST(mafVisualPipeOSGSurfaceTest);
#include "mafVisualPipeOSGSurfaceTest.moc"
