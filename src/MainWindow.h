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
    QWidget *m_centralWidget;
    QHBoxLayout *m_layout;
    PanelInfo *m_panelInfo;
    PanelDisplay *m_panelDisplay;

    // Simulation
    Simulation *simulation;

    QTimer *m_timer;

signals:

public slots:
    void timeUpdate();

};

#endif // MAINWINDOW_H
