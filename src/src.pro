
# Nom de l'executable
TARGET = Neuronal_Network

# Dans Qt5, QApplication fait parti du module widgets
QT += widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    PanelInfo.cpp \
    PanelDisplay.cpp \
    Car.cpp \
    Simulation.cpp \
    Circuit.cpp

HEADERS += \
    MainWindow.h \
    PanelInfo.h \
    PanelDisplay.h \
    Car.h \
    Simulation.h \
    Circuit.h

# Ajout du repertoire d'Eigen pour les fichers d'inclusion
INCLUDEPATH += ../lib/Eigen-3.2.8

OTHER_FILES += \
    ../ressource/circuit.jpeg
