QT       += printsupport

DEFINES += QCUSTOMPLOT_USE_OPENGL

LIBS += -lopengl32 -lglu32

SOURCES += \
    $$PWD/multicurvesplot.cpp \
    $$PWD/qcustomplot.cpp

HEADERS += \
    $$PWD/multicurvesplot.h \
    $$PWD/qcustomplot.h

FORMS +=
