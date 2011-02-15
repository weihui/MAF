# -------------------------------------------------
# Project created by QtCreator 2010-03-01T14:14:10
# -------------------------------------------------
QT += xml
CONFIG += qtestlib
CONFIG += link_prl
SOURCES += main.cpp \
    mafVisualPipeIrrlichtSurfaceTest.cpp
include(../../mafInstallTest.pri)
include(../../mafImportVXL.pri)
include(../../mafImportIrrlicht.pri)
include(../../mafImportQXMLRPC.pri)
include(../../mafImportQtSoap.pri)

INCLUDEPATH += ../../mafResources \
    ../../mafEventBus \
    ../../mafCore
LIBS += -L$$DESTDIR \
    -lmafResources$$BUILD_EXT \
    -lmafEventBus$$BUILD_EXT \
    -lmafCore$$BUILD_EXT \
    -lmafPluginIrrlicht$$BUILD_EXT
