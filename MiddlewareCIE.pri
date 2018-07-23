#
# Middleware CIE
# Author: Fabio Petagna <fabio.petagna@etuitus.it>
#

CONFIG += c++11

CONFIG(release, debug|release): {
    CONFIG_TYPE=release
    DEFINES -= DEBUG
    DEFINES -= _DEBUG
}
CONFIG(debug, debug|release): {
    CONFIG_TYPE=debug
    DEFINES += DEBUG
    DEFINES += _DEBUG
}

contains(QMAKE_HOST.arch, x86_64):{
    MYARCH = x86_64
}
else{
    MYARCH = i386
}

macx-clang: {
    # app using this lib may define a DESTDIR suitable for app build
    isEmpty(DESTDIR) {
        DESTDIR = $$PWD/../MidCIE_bin/mac_$${MYARCH}_$$CONFIG_TYPE
    }

    OPENSSL_INC = /opt/local/include
    OPENSSL_LIB = -L/opt/local/lib -lcrypto
}

linux-g++: {
    # app using this lib may define a DESTDIR suitable for app build
    isEmpty(DESTDIR) {
        DESTDIR = $$PWD/../MidCIE_bin/mac_$${MYARCH}_$$CONFIG_TYPE
    }
}
