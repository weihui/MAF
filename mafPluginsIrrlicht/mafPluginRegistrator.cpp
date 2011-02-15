#include "mafPluginRegistrator.h"
#include "mafVisualPipeIrrlichtSurface.h"

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;
using namespace mafPluginsIrrlicht;

mafPluginRegistrator::mafPluginRegistrator() {
    // Register to the mafObjectFactory the plug-in object's types.
    mafRegisterObjectAndAcceptBind(mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface);
}

mafPluginRegistrator::~mafPluginRegistrator() {
    // When the library is Un-Loaded it has to remove from the mafObjectFactory its object's types.
    mafUnregisterObjectAndAcceptUnbind(mafPluginsIrrlicht::mafVisualPipeIrrlichtSurface);
}

void mafPluginRegistrator::registerObjects() {
    mafPluggedObjectsHash pluginHash;

    mafPluggedObjectInformation visualPipeIrrlichtSurface("Visual pipe Irrlicht Surface", "mafPluginIrrlicht::mafVisualPipeIrrlichtSurface");
    pluginHash.insertMulti("mafResources::mafVisualPipe", visualPipeIrrlichtSurface);

    mafEventBus::mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafPluggedObjectsHash, pluginHash));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.plugin.registerLibrary", mafEventTypeLocal, &argList);

}
