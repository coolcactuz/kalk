######################################################################
# Automatically generated by qmake (3.1) Wed Aug 22 18:12:58 2018
######################################################################

TEMPLATE = app
TARGET = View
INCLUDEPATH += .
QT+=widgets

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += startup_view.h \
           items/KalkButton.h \
           specialized_view_hierarchy/specialized_view.h \
           specialized_view_hierarchy/VCircuito.h \
           specialized_view_hierarchy/VComplesso.h \
           specialized_view_hierarchy/VRazionale.h \
           specialized_view_hierarchy/VTupla.h
SOURCES += main.cpp \
           startup_view.cpp \
           specialized_view_hierarchy/specialized_view.cpp \
           specialized_view_hierarchy/VCircuito.cpp \
           specialized_view_hierarchy/VComplesso.cpp \
           specialized_view_hierarchy/VRazionale.cpp \
           specialized_view_hierarchy/VTupla.cpp
