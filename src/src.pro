
# Nom de l'executable
TARGET = Neuronal_Network

# Dans Qt5, QApplication fait parti du module widgets
QT += widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    PanelInfo.cpp \
    PanelDisplay.cpp

HEADERS += \
    MainWindow.h \
    PanelInfo.h \
    PanelDisplay.h

OTHER_FILES += \
    ../ressource/circuit.jpeg
