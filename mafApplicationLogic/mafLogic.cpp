/*
 *  mafLogic.cpp
 *  mafApplicationLogic
 *
 *  Created by Daniele Giunchi on 28/06/10.
 *  Copyright 2009-2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafLogic.h"

#include <mafCoreSingletons.h>
#include <mafEventDefinitions.h>

using namespace mafEventBus;

#ifdef WIN32
    #define PLUGIN_EXTENSION_FILTER "*.dll"
    #ifdef QT_DEBUG
        #define RESOURCES_LIBRARY_NAME "mafResources_d.dll"
    #else
        #define RESOURCES_LIBRARY_NAME "mafResources.dll"
    #endif
#else
    #ifdef __APPLE__
        #define PLUGIN_EXTENSION_FILTER "*.dylib"
        #ifdef QT_DEBUG
            #define RESOURCES_LIBRARY_NAME "libmafResources_debug.dylib"
        #else
            #define RESOURCES_LIBRARY_NAME "libmafResources.dylib"
        #endif
    #else
        #define PLUGIN_EXTENSION_FILTER "*.so"
        #ifdef QT_DEBUG
            #define RESOURCES_LIBRARY_NAME "libmafResources_debug.so"
        #else
            #define RESOURCES_LIBRARY_NAME "libmafResources.so"
        #endif
    #endif
#endif


using namespace mafCore;
using namespace mafApplicationLogic;

mafLogic::mafLogic(const mafString code_location) : mafLogicLight(code_location), m_WorkingDirectory(""), m_ApplicationDirectory(QDir::currentPath()) {
}

mafLogic::~mafLogic() {
}

bool mafLogic::initialize() {
    // Call the ionitialization of the superclass.
    Superclass::initialize();

    mafIdProvider *provider = mafIdProvider::instance();
    provider->createNewId("maf.local.logic.settings.viewmanager.store");
    provider->createNewId("maf.local.logic.settings.viewmanager.restore");
    provider->createNewId("maf.local.logic.settings.vmemanager.store");
    provider->createNewId("maf.local.logic.settings.vmemanager.restore");

    // Signal registration.
    mafRegisterLocalSignal("maf.local.logic.settings.viewmanager.store", this, "settingsViewManagerStore()");
    mafRegisterLocalSignal("maf.local.logic.settings.vmemanager.store", this, "settingsVmeManagerStore()");
    mafRegisterLocalSignal("maf.local.logic.settings.viewmanager.restore", this, "settingsViewManagerRestore(mafCore::mafMemento *, bool)");
    mafRegisterLocalSignal("maf.local.logic.settings.vmemanager.restore", this, "settingsVmeManagerRestore(mafCore::mafMemento *, bool)");

    // Load the module related to the resources and managers and initialize it.
    bool module_initialized(false);
    module_initialized = mafInitializeModule(RESOURCES_LIBRARY_NAME);

    // load the plugins (if any)
    loadPlugins();

    // Perform design by contract check.
    ENSURE(module_initialized);
    return module_initialized;
}

void mafLogic::loadPlugins() {
    // Build the plugin absolute directory.
    mafString plugin_dir = m_ApplicationDirectory + QDir::toNativeSeparators("/plugins");
    plugin_dir = QDir::cleanPath(plugin_dir);

    // Check for plugins to load
    QDir dir(plugin_dir);
    mafStringList filters;
    filters << PLUGIN_EXTENSION_FILTER;
    mafStringList plugin_list = dir.entryList(filters);
    mafEventArgumentsList argList;

    // For each plugin file ask the plugin manager to load it through the event bus.
    foreach(mafString file, plugin_list) {
        argList.clear();
        file = dir.absoluteFilePath(file);
        argList.append(mafEventArgument(mafString, file));
        mafEventBusManager::instance()->notifyEvent("maf.local.resources.plugin.loadLibrary", mafEventTypeLocal, &argList);
    }
}
