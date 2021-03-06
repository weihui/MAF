/*
 *  mafExporterVTKTest.cpp
 *  mafResourcesTest
 *
 *  Created by Paolo Quadrani on 22/09/09.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafExporterVTK.h>
#include <mafVMEManager.h>
#include "mafDataBoundaryAlgorithmVTK.h"
#include <mafOperationManager.h>
#include <mafProxy.h>
#include <mafVME.h>
#include <mafDataSet.h>

#include <vtkSmartPointer.h>
#include <vtkDataSetReader.h>
#include <vtkSphereSource.h>
#include <vtkAlgorithmOutput.h>

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;
using namespace mafPluginVTK;

/**
 Class name: mafExporterVTKTest
 This class implements the test suite for mafImporterVTK.
 */
class mafExporterVTKTest: public QObject {
    Q_OBJECT

    /// Prepare the test data to be used into the test suite.
    void initializeTestData();
    
private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        m_EventBus = mafEventBusManager::instance();
        m_VMEManager = mafVMEManager::instance();
        
        m_EventBus->notifyEvent("maf.local.resources.hierarchy.request");
        
        m_OperationManager = mafOperationManager::instance();
        
        initializeTestData();
}

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        QFile::remove(m_VTKFile);
        mafDEL(m_VME);
        
        m_OperationManager->shutdown();
        m_VMEManager->shutdown();
        
        //restore vme manager status
        m_EventBus->notifyEvent("maf.local.resources.hierarchy.request");
        
        m_EventBus->shutdown();
        mafMessageHandler::instance()->shutdown();
    }
    
    /// Test the import of VTK file created.
    void exportVMEinVTKFile();

private:
    QString m_VTKFile; ///< VTK filename to import.
    
    mafEventBusManager *m_EventBus;
    mafVMEManager *m_VMEManager;
    mafOperationManager *m_OperationManager;
    mafVME *m_VME;
    
    vtkSmartPointer<vtkSphereSource> surfSphere;
};

void mafExporterVTKTest::initializeTestData() {
    m_VTKFile = QDir::tempPath();
    m_VTKFile.append("/maf3TestData");
    QDir log_dir(m_VTKFile);
    if(!log_dir.exists()) {
        log_dir.mkpath(m_VTKFile);
    }
    m_VTKFile.append("/vtkExportedVTKData.vtk");
    
    surfSphere = vtkSmartPointer<vtkSphereSource>::New();
    surfSphere->SetRadius(5);
    surfSphere->SetPhiResolution(10);
    surfSphere->SetThetaResolution(10);
    surfSphere->Update();
    
    m_VME = mafNEW(mafResources::mafVME);
    m_VME->setObjectName("VME to export");
    
    mafDataSet *data = mafNEW(mafResources::mafDataSet);
    mafProxy<vtkAlgorithmOutput> *vtkDataProxy = new mafProxy<vtkAlgorithmOutput>();
    vtkDataProxy->setClassTypeNameFunction(vtkClassTypeNameExtract);
    *vtkDataProxy = surfSphere->GetOutputPort();
    mafDataBoundaryAlgorithmVTK *boundaryAlgorithm;
    boundaryAlgorithm = mafNEW(mafDataBoundaryAlgorithmVTK);
    data->setBoundaryAlgorithm(boundaryAlgorithm);
    data->setDataValue(vtkDataProxy);
        
    m_VME->dataSetCollection()->insertItem(data);
    mafDEL(data);
    
    mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafObjectBase *, m_VME));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.add", mafEventTypeLocal, &argList);
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.select", mafEventTypeLocal, &argList);

}

void mafExporterVTKTest::exportVMEinVTKFile() {
    QVariantList op;
    op.append(QVariant("mafPluginVTK::mafExporterVTK"));
    QVariantMap params;
    params.insert("filename", QVariant(m_VTKFile));
    op.push_back(params); // Needs push_back to preserve the QVariantList structure as second element of the main variant list.

    mafEventArgumentsList listToSend;
    listToSend.append(mafEventArgument(QVariantList, op));
    m_EventBus->notifyEvent("maf.local.resources.operation.executeWithParameters", mafEventTypeLocal, &listToSend);

    QTime dieTime = QTime::currentTime().addSecs(10);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    }

    vtkSmartPointer<vtkDataSetReader> reader = vtkSmartPointer<vtkDataSetReader>::New();
    QByteArray ba = m_VTKFile.toAscii();
    reader->SetFileName(ba.constData());
    reader->Update();
    
    vtkDataSet *output = reader->GetOutput();
    QVERIFY(output != NULL);
    QVERIFY(output->IsA("vtkPolyData") == 1);
    
}




MAF_REGISTER_TEST(mafExporterVTKTest);
#include "mafExporterVTKTest.moc"
