#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>

class PanelDisplay;
class PanelInfo;
class QHBoxLayout;
class QTimer;

class Simulation;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void timerStart();
    void timerStop();

private:
    // IHM
    // on met le m_layout dans le m_centralWidget
    // puis on met le m_panelInfo et le m_panelDisplay dans le m_layout
    QWidget *m_centralWidget;
    QHBoxLayout *m_layout;
    PanelInfo *m_panelInfo;
    PanelDisplay *m_panelDisplay;

    // Simulation
    Simulation *m_simulation;

};

#endif // MAINWINDOW_H
