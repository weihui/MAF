/*
 *  mafVisualPipeIrrlichtSurface.cpp
 *  mafPipesLibrary
 *
 *  Created by Roberto Mucci - Paolo Quadrani on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafVisualPipeIrrlichtSurface.h"
#include <mafDataSet.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace mafCore;
using namespace mafResources;
using namespace mafPluginsIrrlicht;

mafVisualPipeIrrlichtSurface::mafVisualPipeIrrlichtSurface(const mafString code_location) : mafVisualPipe(code_location) {
}

mafVisualPipeIrrlichtSurface::~mafVisualPipeIrrlichtSurface() {

}

bool mafVisualPipeIrrlichtSurface::acceptObject(mafCore::mafObjectBase *obj) {
    mafVME *vme = qobject_cast<mafVME*>(obj);
    if(vme != NULL) {
        mafCore::mafContainerInterface *data = vme->dataSetCollection()->itemAtCurrentTime()->dataValue();
        if(data != NULL) {
            mafString dataType = data->externalDataType();
            if(1 || dataType == "") {
                return true;
            }
        }
    }
    return false;
}

void mafVisualPipeIrrlichtSurface::createPipe() {
        //m_Output = &m_Actor;
}

void mafVisualPipeIrrlichtSurface::updatePipe(double t) {
    mafVME *inputVME = this->inputList()->at(0);
    mafDataSet *inputDataSet = inputVME->dataSetCollection()->itemAtCurrentTime();

    if(inputDataSet == NULL) {
        return;
    }

    mafContainer<irr::scene::IAnimatedMesh> *mesh = mafContainerPointerTypeCast(irr::scene::IAnimatedMesh, inputDataSet->dataValue());
    irr::scene::IAnimatedMeshSceneNode* node = m_DeviceWrapper->m_Device->getSceneManager()->addAnimatedMeshSceneNode( *mesh );
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, m_DeviceWrapper->m_Device->getVideoDriver()->getTexture("sydney.bmp") );
    }

    //Get data contained in the mafContainer
    //mafContainer<irrqualcosa> *nodo = mafContainerPointerTypeCast(irrqualcosa, inputDataSet->dataValue());
}

void mafVisualPipeIrrlichtSurface::setIrrlichtDeviceWrapper(IrrlichtDeviceWrapper *deviceWrapper) {
     m_DeviceWrapper = deviceWrapper;
}


IrrlichtDeviceWrapper *mafVisualPipeIrrlichtSurface::irrlichtDeviceWrapper() {
     return m_DeviceWrapper;
}
