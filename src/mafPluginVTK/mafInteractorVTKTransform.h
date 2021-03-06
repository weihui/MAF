/*
 *  mafInteractorVTKTransform.h
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi - Paolo Quadrani on 7/7/11.
 *  Copyright 2011 B3C.s All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFINTERACTORVTKTRANSFORM_H
#define MAFINTERACTORVTKTRANSFORM_H

// Includes list
#include "mafPluginVTKDefinitions.h"
#include <mafInteractor.h>

// Foundation Class forwarding list
class vtkRenderer;
class vtkInteractorObserver;
class vtkMAFInteractorStyleTrackballActor;

namespace mafPluginVTK {

/**
Class name: mafInteractorVTKTransform
This class represent an interactor implementing a picking operation.
*/

class MAFPLUGINVTKSHARED_EXPORT mafInteractorVTKTransform : public mafResources::mafInteractor {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafInteractor);

public:
    /// Object constructor.
    mafInteractorVTKTransform(const QString code_location = "");

public Q_SLOTS:
    /// Called when the any mouse button is pressed
    /*virtual*/ void mousePress(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

    /// Called when the any mouse button is released
    /*virtual*/ void mouseRelease(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

    /// Called when mouse is moved
    /*virtual*/ void mouseMove(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

protected:
    /// Object destructor.
    /* virtual */~mafInteractorVTKTransform();

private:    
    bool m_DragObject; ///< flag put to true when the mouse button is pressed and to false when it is released.
    vtkInteractorObserver *m_PreviousVTKInteractor; ///< represents the old interactor.
    vtkMAFInteractorStyleTrackballActor *m_CurrentVTKInteractor; ///< represents the interactor currently attached
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

} // namespace mafPluginVTK

#endif // MAFINTERACTORVTKTRANSFORM_H
