QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClassManager.cpp \
    ClassTime.cpp \
    main.cpp

HEADERS += \
    ClassManager.h \
    ClassTime.h \
    Header.h
INCLUDEPATH+= $$PWD
FORMS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
DISTFILES += \
    Eidolon.ico \
    myapp.rc \
    src.txt
copydata.commands = $(COPY_FILE) \"$$shell_path($$PWD\\src.txt)\" \"$$shell_path($$OUT_PWD)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
RC_FILE = myapp.rc
