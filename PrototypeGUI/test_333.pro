QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comment_1.cpp \
    communitiestab.cpp \
    main.cpp \
    mainwindow.cpp \
    makecommentorpost.cpp \
    post_1.cpp \
    profile.cpp \
    searchresults.cpp \
    secdialog.cpp

HEADERS += \
    comment_1.h \
    communitiestab.h \
    mainwindow.h \
    makecommentorpost.h \
    post_1.h \
    profile.h \
    searchresults.h \
    secdialog.h

FORMS += \
    comment_1.ui \
    communitiestab.ui \
    mainwindow.ui \
    makecommentorpost.ui \
    post_1.ui \
    profile.ui \
    searchresults.ui \
    secdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
