/*
 *  mafVisualPipeIrrlichtSurface.h
 *  mafPipesLibrary
 *
 *  Created by Daniele Giunchi on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVISUALPIPEIRRLICHTSURFACE_H
#define MAFVISUALPIPEIRRLICHTSURFACE_H

// Includes list
#include "mafPluginsIrrlichtDefinitions.h"
#include <mafContainer.h>
#include <mafVisualPipe.h>

// Class forwarding list

namespace mafPluginsIrrlicht {

/**
 Class name: mafVisualPipeIrrlichtSurface
 This class represents visual pipe used to render VTK polydata.
 */

class MAFPLUGINSIRRLICHTSHARED_EXPORT mafVisualPipeIrrlichtSurface : public mafResources::mafVisualPipe {
    Q_OBJECT
    Q_PROPERTY(IrrlichtDeviceWrapperPointer IrrlichtDeviceWrapper READ irrlichtDeviceWrapper WRITE setIrrlichtDeviceWrapper)
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafVisualPipe);

public:
    /// Object constructor;
    mafVisualPipeIrrlichtSurface(const mafString code_location = "");

    /// Object destructor.
    /* virtual */ ~mafVisualPipeIrrlichtSurface();

    /// Accept function
    static bool acceptObject(mafCore::mafObjectBase *obj);


    /// Initialize ans create the pipeline.
    /*virtual*/ void createPipe();

    /// Temporry method to connect irrlicht device to visual pipe
    void setIrrlichtDeviceWrapper(IrrlichtDeviceWrapper *deviceWrapper);

    IrrlichtDeviceWrapper *irrlichtDeviceWrapper();

public slots:
    /// Allow to execute and update the pipeline when something change.
    /*virtual*/ void updatePipe(double t = -1);

private:
    IrrlichtDeviceWrapper *m_DeviceWrapper;
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////


} // namespace mafPluginsIrrlicht

#endif // MAFVISUALPIPEIRRLICHTSURFACE_H
