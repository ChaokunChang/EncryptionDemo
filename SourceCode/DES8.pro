#-------------------------------------------------
#
# Project created by QtCreator 2018-10-07T18:13:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DES8
TEMPLATE = app

#INCLUDEPATH += D:/Program/MinGW/include
#LIBS += -lgmp

SOURCES += main.cpp\
        des8ui.cpp \
    DES8.cpp \
    rsa.cpp

HEADERS  += des8ui.h \
    C:/Users/70700/Desktop/MyTest/Info Security Project/PJ1.1/DES8.h \
    DES8.h \
    rsa.h

FORMS    += des8ui.ui





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmpd
else:unix: LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmp

INCLUDEPATH += $$PWD/../../../Program/gmp-6.1.2-2
DEPENDPATH += $$PWD/../../../Program/gmp-6.1.2-2


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmpxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmpxxd
else:unix: LIBS += -L$$PWD/../../../Program/gmp-6.1.2-2/.libs/ -lgmpxx

INCLUDEPATH += $$PWD/../../../Program/gmp-6.1.2-2
DEPENDPATH += $$PWD/../../../Program/gmp-6.1.2-2


