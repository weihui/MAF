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
#include <mafVisualPipeIrrlichtSurface.h>
#include <mafContainer.h>
#include <mafDataSet.h>
#include <mafCoreSingletons.h>
#include <mafEventBusManager.h>
#include <mafPluginManager.h>

#ifdef WIN32
    #define TEST_LIBRARY_NAME "mafPluginIrrlicht_d.dll"
#else
    #ifdef __APPLE__
        #define TEST_LIBRARY_NAME "libmafPluginIrrlicht_debug.dylib"
    #else
        #define TEST_LIBRARY_NAME "libmafPluginIrrlicht_debug.so"
    #endif
#endif

#include <irrlicht.h>
using namespace mafCore;
using namespace mafResources;
using namespace mafPluginsIrrlicht;
using namespace mafEventBus;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/**
 Class name: mafVisualPipeIrrlichtSurfaceTest
 This class creates a vtkPolyData and visualizes it trough the mafVisualPipeIrrlichtSurface
 */

//! <title>
//mafVisualPipeIrrlichtSurface
//! </title>
//! <description>
//mafVisualPipeIrrlichtSurface is a visual pipe used to render VTK polydata.
//It takes a mafDataSet as input and returns a mafContainer<vtkActor>.
//! </description>

class mafVisualPipeIrrlichtSurfaceTest : public QObject {
    Q_OBJECT

private slots:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafResourcesRegistration::registerResourcesObjects();
        mafRegisterObjectAndAcceptBind(mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface);

        m_Device =
            createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
                false, false, false, 0);

        if (!m_Device)
            return;

        m_Device->setWindowCaption(L"Irrlicht in MAF3 Framework");

        IVideoDriver* driver = m_Device->getVideoDriver();
        ISceneManager* smgr = m_Device->getSceneManager();
        IGUIEnvironment* guienv = m_Device->getGUIEnvironment();


        guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
            rect<s32>(10,10,260,22), true);

        m_IrrlichtMesh = smgr->getMesh("sydney.md2");

        /*scene::IAnimatedMeshSceneNode* node=smgr->addAnimatedMeshSceneNode(m_IrrlichtMesh);
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") );*/

        // and give it to the mafDataSet.
        //! <title>
        m_VME = mafNEW(mafResources::mafVME);
        m_DataSet = mafNEW(mafResources::mafDataSet);
        m_DataSet->setDataValue(&m_IrrlichtMesh);
        m_VME->dataSetCollection()->insertItem(m_DataSet, 0);
        //! </title>
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafDEL(m_DataSet);
        mafUnregisterObjectAndAcceptUnbind(mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface);
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
    mafContainer<irr::scene::IAnimatedMesh> m_IrrlichtMesh; ///< Container of the IAnimatedMesh
    IrrlichtDevice *m_Device;
    mafPluginManager *m_PluginManager; ///< Test var.
};

void mafVisualPipeIrrlichtSurfaceTest::updatePipeTestFromPlugIn() {

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
    QCOMPARE(visualPipeType,mafString("mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface"));

}


void mafVisualPipeIrrlichtSurfaceTest::updatePipeTest() {

    //! <title>
    mafVisualPipeIrrlichtSurface *pipe;
    pipe = mafNEW(mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface);
    //! </title>
    pipe->setInput(m_VME);
    IrrlichtDeviceWrapper *idw = new IrrlichtDeviceWrapper(m_Device);
    //pipe->setIrrlichtDeviceWrapper(idw);
    mafVariant v = mafVariant::fromValue(idw);
    pipe->setProperty("IrrlichtDeviceWrapper", v);
//    pipe->setProperty("immediateRendering", 1);
    pipe->createPipe();
    pipe->updatePipe();

    m_Device->getSceneManager()->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));


    while(m_Device->run())
    {
        m_Device->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));
        m_Device->getSceneManager()->drawAll();
        m_Device->getGUIEnvironment()->drawAll();
        m_Device->getVideoDriver()->endScene();
    }
    m_Device->drop();
    mafDEL(pipe);
}

MAF_REGISTER_TEST(mafVisualPipeIrrlichtSurfaceTest);
#include "mafVisualPipeIrrlichtSurfaceTest.moc"
