/*
 *  mafViewVTKButtons.h
 *  VTKButtons
 *
 *  Created by Roberto Mucci on 20/03/10.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFVIEWVTKBUTTONS_H
#define MAFVIEWVTKBUTTONS_H

// Includes list
#include <mafViewVTK.h>


class mafVTKWidget;

/**
 Class name: mafViewVTKButtons
 This is the VTK MAF3 views.
 */
class mafViewVTKButtons : public mafPluginVTK::mafViewVTK {
    Q_OBJECT

    /// typedef macro.
    mafSuperclassMacro(mafPluginVTK::mafViewVTK);

public:
    /// Object constructor.
    mafViewVTKButtons(const QString code_location = "");

    /// Crete view.
    /*virtual*/ bool initialize();


protected:
    /// Object destructor.
    /* virtual */ ~mafViewVTKButtons();

};

#endif // MAFVIEWVTKBUTTONS_H
