#
# Middleware CIE
# Author: Fabio Petagna <fabio.petagna@etuitus.it>
#

include (MiddlewareCIE.pri)

TEMPLATE = subdirs

CONFIG += ordered

win32 {
    #SUBDIRS += CacheLib/CacheLib.pro
}

SUBDIRS += \
    CSP/CIEPKI.pro
    #EsempioPKCS11/EsempioPKCS11.pro \
    #EsempioPCSC/EsempioPCSC.pro
