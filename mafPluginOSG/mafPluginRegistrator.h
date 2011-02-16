/*
 *  mafPluginRegistrator.h
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi - Paolo Quadrani on 15/02/11.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFPLUGINREGISTRATOR_H
#define MAFPLUGINREGISTRATOR_H

#include "mafPluginOSGDefinitions.h"

namespace mafPluginsOSG {

/**
 Class name: mafPluginRegistrator
 This class is the object that is in charge to register all the class contained into the library as plug-in
 by sending the message through the mafEventBus using the macro mafRegisterPluginEvent.
 @sa mafEventBusManager, mafPluginManager
 */
class MAFPLUGINSOSGSHARED_EXPORT mafPluginRegistrator {
public:
    /// Object costructor
    mafPluginRegistrator();

    /// Object destructor
    ~mafPluginRegistrator();

    /// Register all the objects present into the library.
    void registerObjects();

};

/** Retrieve the engine version we're going to expect*/
extern "C" MAFPLUGINSOSGSHARED_EXPORT mafResources::mafPluginInfo pluginInfo() {
    mafResources::mafPluginInfo info;
    info.m_Version = 1.0;
    info.m_PluginName = "Plugin for OpenSceneGraph";
    info.m_Author = "Daniele Giunchi";
    info.m_Vendor = "B3C";
    info.m_VendorHomepage = "http:///www.biomedtown.org/";
    info.m_Description = "Test plugin";

    return info;
}

// MAF required version function.
// XML file for the UI. Also with switch possibility between different levels of complexity.
mafPluginRegistrator registrator;

/** Tells us to register our functionality to an engine kernel*/
extern "C" MAFPLUGINSOSGSHARED_EXPORT void registerPlugin() {
    registrator.registerObjects();
}

} // namespace mafPluginOSG

#endif // MAFPLUGINREGISTRATOR_H
