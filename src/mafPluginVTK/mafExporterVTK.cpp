/*
 *  mafExporterVTK.cpp
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi on 04/04/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include "mafExporterVTK.h"
#include <mafVME.h>
#include <mafDataSetCollection.h>
#include <mafDataSet.h>

#include <vtkDataSetWriter.h>
#include <vtkAlgorithmOutput.h>
#include <mafProxy.h>

using namespace mafPluginVTK;
using namespace mafResources;
using namespace mafCore;

mafExporterVTK::mafExporterVTK(const QString code_location) : mafOperation(code_location), m_ExportAllTimestamps(false) {
    m_Writer = vtkDataSetWriter::New();
    setProperty("wildcard", mafTr("VTK Files (*.vtk)"));
}

mafExporterVTK::~mafExporterVTK() {
    m_Writer->Delete();
}

void mafExporterVTK::execute() {
    m_Status = mafOperationStatusExecuting;
    
    if (!filename().isEmpty()) {
        if (m_Status == mafOperationStatusAborted) {
            cleanup();
            return;
        }
    }
    mafResource *res = input();
    mafVME *vme = qobject_cast<mafResources::mafVME *>(res);
    
    mafDataSetCollection *dc = vme->dataSetCollection();
    mafDataSet *data = dc->itemAt(-1);
    mafProxyInterface *dv = data->dataValue();
    mafProxy<vtkAlgorithmOutput> *value = mafProxyPointerTypeCast(vtkAlgorithmOutput, dv);
    m_Writer->SetInputConnection(0, *value);
    QByteArray ba = filename().toAscii();
    const char *f = ba.constData();
    m_Writer->SetFileName(f);
    
    int result = m_Writer->Write();
    if(result == 0) {
        ba = mafTr("Unable to export the data in VTK format.").toAscii();
        qCritical(ba.constData());
    }
    
    Q_EMIT executionEnded();
}

bool mafExporterVTK::acceptObject(mafCore::mafObjectBase *obj) {
    mafVME *vme = qobject_cast<mafResources::mafVME *>(obj);
    bool result(false);
    if (vme == NULL) {
        QByteArray ba = mafTr("Missing VME!!").toAscii();
        qCritical(ba.constData());
        return result;
    }
    mafDataSetCollection *dc = vme->dataSetCollection();
    int elements = dc->collectionMap()->count();
    
    if(elements == 0) {
        return result;
    }
    
    mafDataSet *ds = (*dc)[0];
    if(ds == NULL) {
        return result;
    }
   
    result = ds->externalDataType().contains(QRegExp("^vtk.*"));
    return result;
}

void mafExporterVTK::terminated() {
    
}

void mafExporterVTK::cleanup() {
    // Cleanup memory and unregister callback.
    mafDEL(m_Output);
}

void mafExporterVTK::unDo() {
}

void mafExporterVTK::reDo() {
}

