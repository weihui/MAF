# -------------------------------------------------
# Project created by QtCreator 2010-02-15T12:35:58
# -------------------------------------------------
#QT -= gui
TARGET = mafPluginOSG
TEMPLATE = lib
CONFIG += create_prl
CONFIG += link_prl
win32:CONFIG += dll
DEFINES += MAFPLUGIN_OSG

SOURCES += mafPluginRegistrator.cpp \
    mafVisualPipeOSGSurface.cpp
HEADERS += mafPluginOSG_global.h \
    mafPluginOSGDefinitions.h \
    mafPluginRegistrator.h \
    mafVisualPipeOSGSurface.h

include(../mafInstallModule.pri)
include(../mafImportVXL.pri)
include(../mafImportOSG.pri)
include(../mafImportQXMLRPC.pri)
include(../mafImportQtSoap.pri)

INCLUDEPATH += ../mafResources \
    ../mafEventBus \
    ../mafCore
LIBS += -L$$DESTDIR \
    -lmafResources$$BUILD_EXT \
    -lmafEventBus$$BUILD_EXT \
    -lmafCore$$BUILD_EXT

# install the mafplugin library (but leaving the generated library for test suite linking pourposes)
win32:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR\\$${LIB_PREFIX}$${TARGET}.dll \
    $$DESTDIR\\$${LIB_PREFIX}$${TARGET}.mafplugin
!macx:unix:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.so.1.0.0 \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.mafplugin
macx:QMAKE_POST_LINK += $$CP_CMD \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.1.0.0.dylib \
    $$DESTDIR/$${LIB_PREFIX}$${TARGET}.mafplugin
