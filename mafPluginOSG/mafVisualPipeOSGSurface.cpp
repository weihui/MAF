/*
 *  mafVisualPipeOSGSurface.cpp
 *  mafPipesLibrary
 *
 *  Created by Roberto Mucci - Paolo Quadrani on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafVisualPipeOSGSurface.h"
#include <mafDataSet.h>

using namespace mafCore;
using namespace mafResources;
using namespace mafPluginsOSG;

mafVisualPipeOSGSurface::mafVisualPipeOSGSurface(const mafString code_location) : mafVisualPipe(code_location) {
}

mafVisualPipeOSGSurface::~mafVisualPipeOSGSurface() {

}

bool mafVisualPipeOSGSurface::acceptObject(mafCore::mafObjectBase *obj) {
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

void mafVisualPipeOSGSurface::createPipe() {
        //m_Output = &m_Actor;
}

void mafVisualPipeOSGSurface::updatePipe(double t) {
    Q_UNUSED(t);

    mafVME *inputVME = this->inputList()->at(0);
    mafDataSet *inputDataSet = inputVME->dataSetCollection()->itemAtCurrentTime();

    if(inputDataSet == NULL) {
        return;
    }

    /*mafContainer<irr::scene::IAnimatedMesh> *mesh = mafContainerPointerTypeCast(irr::scene::IAnimatedMesh, inputDataSet->dataValue());
    irr::scene::IAnimatedMeshSceneNode* node = m_DeviceWrapper->m_Device->getSceneManager()->addAnimatedMeshSceneNode( *mesh );
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, m_DeviceWrapper->m_Device->getVideoDriver()->getTexture("sydney.bmp") );
    }*/

    //Get data contained in the mafContainer
    //mafContainer<irrqualcosa> *nodo = mafContainerPointerTypeCast(irrqualcosa, inputDataSet->dataValue());
}

/*void mafVisualPipeOSGSurface::setIrrlichtDeviceWrapper(IrrlichtDeviceWrapper *deviceWrapper) {
     m_DeviceWrapper = deviceWrapper;
}*/


/*IrrlichtDeviceWrapper *mafVisualPipeOSGSurface::irrlichtDeviceWrapper() {
     return m_DeviceWrapper;
}*/
