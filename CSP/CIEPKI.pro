# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = CIEPKI
DESTDIR = ../Win32/Debug
CONFIG += debug
DEFINES += _WINDOWS _USRDLL CSP_EXPORTS
INCLUDEPATH += $(SolutionDir)PKCS11 \
    $(NOINHERIT)
LIBS += -L"$(NOINHERIT)" \
    -lWinhttp \
    -lbcrypt \
    -lversion \
    -lComctl32 \
    -lCrypt32 \
    -lshlwapi \
    -lwinscard
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(CIEPKI.pri)
