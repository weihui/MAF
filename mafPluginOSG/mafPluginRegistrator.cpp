#include "mafPluginRegistrator.h"
#include "mafVisualPipeOSGSurface.h"

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;
using namespace mafPluginsOSG;

mafPluginRegistrator::mafPluginRegistrator() {
    // Register to the mafObjectFactory the plug-in object's types.
    mafRegisterObjectAndAcceptBind(mafPluginsOSG::mafVisualPipeOSGSurface);
}

mafPluginRegistrator::~mafPluginRegistrator() {
    // When the library is Un-Loaded it has to remove from the mafObjectFactory its object's types.
    mafUnregisterObjectAndAcceptUnbind(mafPluginsOSG::mafVisualPipeOSGSurface);
}

void mafPluginRegistrator::registerObjects() {
    mafPluggedObjectsHash pluginHash;

    mafPluggedObjectInformation visualPipeOSGSurface("Visual pipe Irrlicht Surface", "mafPluginsOSG::mafVisualPipeOSGSurface");
    pluginHash.insertMulti("mafResources::mafVisualPipe", visualPipeOSGSurface);

    mafEventBus::mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafPluggedObjectsHash, pluginHash));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.plugin.registerLibrary", mafEventTypeLocal, &argList);

}
