# Add more folders to ship with the application, here
qqc.source = qml/qqc
qqc.target = qml
DEPLOYMENTFOLDERS = qqc

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += bluetooth dbus

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    btconnector.cpp \
    settingsadapter.cpp \
    uinputadapter.cpp \
    btdataprocessor.cpp \
    bluez5btadapter.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    btconnector.h \
    settingsadapter.h \
    uinputadapter.h \
    btdataprocessor.h \
    bluez5btadapter.h

OTHER_FILES += \
    qml/qqc/main.qml \
    qml/qqc/BtSelectDialog.qml \
    qml/qqc/ZeeControlTab.qml
