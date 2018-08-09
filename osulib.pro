QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    primitives/bounded/boundedint.cpp \
    primitives/bounded/boundeddouble.cpp \
    dbug.cpp \
    osu_primitives/hitobject.cpp \
    osu_primitives/timingpoint.cpp \
    osu_primitives/hitobjectlist.cpp \
    osu_primitives/timingpointlist.cpp \
    osu_algorithms/osualgorithm.cpp \
    osu_primitives/osuobject.cpp \
    osu_primitives/osuobjectlist.cpp \
    osustream.cpp

HEADERS += \
    primitives/bounded/boundedint.h \
    primitives/bounded/boundeddouble.h \
    dbug.h \
    primitives/sampleset.h \
    osu_primitives/hitobject.h \
    osu_primitives/timingpoint.h \
    osu_primitives/hitobjectlist.h \
    osu_primitives/timingpointlist.h \
    osu_algorithms/osualgorithm.h \
    osu_primitives/osuobject.h \
    osu_primitives/osuobjectlist.h \
    osustream.h

DISTFILES += \
    eg_hitObjectList.txt \
    eg_timingPointList.txt
