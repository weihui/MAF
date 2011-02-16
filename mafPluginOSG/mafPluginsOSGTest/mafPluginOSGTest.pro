# -------------------------------------------------
# Project created by QtCreator 2010-03-01T14:14:10
# -------------------------------------------------
QT += xml
QT += opengl
CONFIG += qtestlib
CONFIG += link_prl
SOURCES += main.cpp \
    mafVisualPipeOSGSurfaceTest.cpp
include(../../mafInstallTest.pri)
include(../../mafImportVXL.pri)
include(../../mafImportOSG.pri)
include(../../mafImportQXMLRPC.pri)
include(../../mafImportQtSoap.pri)

INCLUDEPATH += ../../mafResources \
    ../../mafEventBus \
    ../../mafCore
LIBS += -L$$DESTDIR \
    -lmafResources$$BUILD_EXT \
    -lmafEventBus$$BUILD_EXT \
    -lmafCore$$BUILD_EXT \
    -lmafPluginOSG$$BUILD_EXT

