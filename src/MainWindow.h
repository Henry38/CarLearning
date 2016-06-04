#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

#include "PanelInfo.h"
#include "PanelDisplay.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //QGraphicsView* m_view;        // provide a widget for display a QGraphicsScene
    //QGraphicsScene* m_scene;      // provides a surface for managing 2D graphical items

    QWidget *m_centralWidget;
    QHBoxLayout *m_layout;
    PanelInfo *m_panelInfo;
    PanelDisplay *m_panelDisplay;

signals:

public slots:

};

#endif // MAINWINDOW_H
