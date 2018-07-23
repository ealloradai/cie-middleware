#
# Middleware CIE
# Author: Fabio Petagna <fabio.petagna@etuitus.it>
#

include(CIEPKI.pri)

TEMPLATE = lib
TARGET = CIEPKI
CONFIG += staticlib

INCLUDEPATH += \
        $$OPENSSL_INC \
        $$_PRO_FILE_PWD_/../PKCS11

LIBS += \
        $$OPENSSL_LIB

win32: {
    DEFINES += _WINDOWS _USRDLL CSP_EXPORTS

    INCLUDEPATH += ../CacheLib

    HEADERS += ./StdAfx.h \
        ./CSP/CSP.h \
        ./CSP/CardMod.h \
        ./CSP/IAS.h \
        ./res/resource.h

    SOURCES += ./stdafx.cpp \
        ./CSP/abilitaCIE.cpp \
        ./CSP/ExtAuthKey.cpp \
        ./CSP/cambioPIN.cpp \
        ./CSP/CSP.cpp \
        ./CSP/update.cpp \
        ./CSP/IAS.cpp \
        ./CSP/NotImpl.cpp \
        ./CSP/sbloccoPIN.cpp \
        ./CSP/StoreProvider.cpp \
        \
        ./UI/Message.cpp \
        ./UI/Bitmap.cpp \
        ./UI/PIN.cpp \
        ./UI/safeDesktop.cpp \
        ./UI/SystemTray.cpp \
        ./UI/Verifica.cpp

    LIBS += \
        -lWinhttp \
        -lbcrypt \
        -lversion \
        -lComctl32 \
        -lCrypt32 \
        -lshlwapi \
        -lwinscard
}

macx-clang: {
    SOURCES += ./Util/Portable.cpp
    HEADERS += ./Util/Portable.h
}

HEADERS += \
    ./Crypto/AES.h \
    ./Crypto/ASNParser.h \
    ./Crypto/Base64.h \
    ./Crypto/DES3.h \
    ./Crypto/MAC.h \
    ./Crypto/MD5.h \
    ./Crypto/RSA.h \
    ./Crypto/SHA1.h \
    ./Crypto/sha256.h \
    ./Crypto/sha512.h \
    ./PKCS11/CardContext.h \
    ./PKCS11/CardTemplate.h \
    ./PKCS11/CIEP11Template.h \
    ./PKCS11/InitP11.h \
    ./PKCS11/Mechanism.h \
    ./PKCS11/P11Object.h \
    ./PKCS11/PKCS11Functions.h \
    ./PKCS11/session.h \
    ./PKCS11/Slot.h \
    ./Util/Array.h \
    ./Util/defines.h \
    ./Util/funccallinfo.h \
    ./Util/IniSettings.h \
    ./Util/log.h \
    ./Util/ModuleInfo.h \
    ./Util/SyncroEvent.h \
#    ./Util/SyncroMutex.h \
    ./Util/tinyxml2.h \
    ./Util/TLV.h \
    ./Util/util.h \
    ./Util/UtilException.h \
    ./UI/Message.h \
    ./UI/AtlBitmapSkinButton.h \
    ./UI/atlcontrols.h \
    ./UI/Bitmap.h \
    ./UI/PIN.h \
    ./UI/safeDesktop.h \
    ./UI/SystemTray.h \
    ./UI/VCEdit.h \
    ./UI/Verifica.h \
    ./PCSC/APDU.h \
    ./PCSC/CardLocker.h \
    ./PCSC/PCSC.h \
    ./PCSC/Token.h

SOURCES += \
    ./Crypto/MD5.cpp \
    ./Crypto/SHA512.cpp \
    ./crypto/AES.cpp \
    ./crypto/ASNParser.cpp \
    ./crypto/Base64.cpp \
    ./crypto/DES3.cpp \
    ./crypto/MAC.cpp \
    ./crypto/RSA.cpp \
    ./crypto/SHA1.cpp \
    ./crypto/SHA256.cpp \
    ./PKCS11/CardContext.cpp \
    ./PKCS11/CardTemplate.cpp \
    ./PKCS11/CIEP11Template.cpp \
    ./PKCS11/initP11.cpp \
    ./PKCS11/Mechanism.cpp \
    ./PKCS11/P11Object.cpp \
    ./PKCS11/PKCS11Functions.cpp \
    ./PKCS11/session.cpp \
    ./PKCS11/Slot.cpp \
    ./Util/Array.cpp \
    ./Util/funccallinfo.cpp \
    ./Util/IniSettings.cpp \
    ./Util/log.cpp \
    ./Util/ModuleInfo.cpp \
    ./Util/SyncroEvent.cpp \
#    ./Util/SyncroMutex.cpp \
    ./Util/tinyxml2.cpp \
    ./Util/TLV.cpp \
    ./Util/util.cpp \
    ./Util/UtilException.cpp \
    ./PCSC/APDU.cpp \
    ./PCSC/CardLocker.cpp \
    ./PCSC/PCSC.cpp \
    ./PCSC/Token.cpp
