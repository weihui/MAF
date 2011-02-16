/*
 *  mafPipesLibrary_Global.h
 *  mafpipesLibrary
 *
 *  Created by Roberto Mucci on 30/12/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFPLUGINSOSG_GLOBAL_H
#define MAFPLUGINSOSG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAFPLUGIN_IRRLICHT)
#  define MAFPLUGINSOSGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAFPLUGINSOSGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MAFPLUGINSOSG_GLOBAL_H
