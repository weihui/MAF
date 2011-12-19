/*
 *  mafPipe.cpp
 *  mafResources
 *
 *  Created by Roberto Mucci - Paolo Quadrani on 30/12/09.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include "mafPipe.h"
#include "mafDataSet.h"
#include "mafDataSetCollection.h"
#include "mafVME.h"

using namespace mafCore;
using namespace mafResources;

mafPipe::mafPipe(const QString code_location) : mafObject(code_location), m_InputList(NULL) {
    m_InputList = new mafVMEList();
    connect(this, SIGNAL(modifiedObject()), this, SLOT(updatePipe()));
}

mafPipe::~mafPipe() {
    m_InputList->clear();
    m_ParametersHash.clear();
    
    delete m_InputList;
    m_InputList = NULL;
}

void mafPipe::setInput(mafVME *vme) {
    bool needsUpdate(false);
    if(!m_InputList->isEmpty()) {
        const mafVME *input_vme = m_InputList->at(0);
        if (input_vme->isEqual(vme)) {
            return;
        }
        removeInput(0);
        needsUpdate = true;
    }
    
    if(vme != NULL) {
        m_InputList->append(vme);

        mafDataSetCollection *datSetCollection = vme->dataSetCollection();
        if (datSetCollection) {
            //connect the data collection modified to the updatePipe slot
            connect(datSetCollection, SIGNAL(modifiedObject()), this, SLOT(updatePipe()));
        }
    }
    
    // Don't send modifyObject notification the first time you set the input
    if (needsUpdate) {
        setModified();
    }
}

mafVME *mafPipe::input(int idx) const {
    if (idx < 0 || idx >= m_InputList->count()) {
        return NULL;
    }
    
    return m_InputList->at(idx);
}

mafDataSet *mafPipe::dataSetForInput(int input_idx, double t) {
    mafVME *vme = input(input_idx);
    if (vme == NULL) {
        return NULL;
    }
    
    return vme->dataSetCollection()->itemAt(t);
}

void mafPipe::removeInput(mafVME *vme) {
    REQUIRE(vme != NULL);

    int idx = m_InputList->indexOf(vme);
    if(idx != -1) {
        m_InputList->removeAt(idx);
    } else {
        QByteArray ba = mafTr("Object %1 not present in input list").arg(vme->objectName()).toAscii();
        qWarning("%s", ba.data());
    }
}

void mafPipe::removeInput(const int idx) {
    REQUIRE(idx >= 0);

    if(idx < m_InputList->count()) {
        mafVME *vme = m_InputList->at(idx);
        m_InputList->removeAt(idx);
    } else {
        QByteArray ba = mafTr("Index %1 outside input list range.").arg(idx).toAscii();
        qWarning("%s", ba.data());
    }
}

void mafPipe::setParametersHash(const QVariantHash hash) {
    m_ParametersHash.unite(hash);
    QVariantHash::iterator iter = m_ParametersHash.begin();
    while (iter != m_ParametersHash.end()) {
        QByteArray ba = iter.key().toAscii();
        QVariant val(iter.value());
        setProperty(ba.constData(), val);
        ++iter;
    }
}
