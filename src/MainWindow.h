#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>

class QLabel;
class QPushButton;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //QGraphicsView* m_view;        // provide a widget for display a QGraphicsScene
    //QGraphicsScene* m_scene;      // provides a surface for managing 2D graphical items

    QWidget* myWidget;
    QHBoxLayout* myLayout;
    QPushButton* quit;
    QPushButton* start;
    QLabel* label;

signals:

public slots:

};

#endif // MAINWINDOW_H
