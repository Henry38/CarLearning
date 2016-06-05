#include "MainWindow.h"

// Qt
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

#include "PanelInfo.h"
#include "PanelDisplay.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // create an empty widget with 'this' as parent
    m_centralWidget = new QWidget(this);

    // create the layout manager for m_centralWidget
    m_layout = new QHBoxLayout();

    // set the layout manager for m_centralWidget
    // MainWindow takes the ownership of m_layout (parenting)
    m_centralWidget->setLayout(m_layout);

    // create the two graphicals panels
    m_panelInfo = new PanelInfo();
    m_panelDisplay = new PanelDisplay();

    // add panels to m_layout
    // MainWindow takes ownership of them (parenting)
    m_layout->addWidget(m_panelInfo);
    m_layout->addWidget(m_panelDisplay);

    // set the central widget of the window
    setCentralWidget(m_centralWidget);

    // create a timer for time simulation
    m_timer = new QTimer(this);

    // connect timeout signal and timeUpdate slot
    // every x milliseconds, timeUpdate method is call by m_timer
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
}

MainWindow::~MainWindow()
{
    // m_centralWidget is automaticaly delete by MainWindow
    // so m_layout is from m_centralWidget (parenting)
    // so m_panelInfo and m_panelDisplay are from m_layout (parenting)
}

void MainWindow::timerStart()
{
    m_timer->start(1000);
}

void MainWindow::timerStop()
{
    m_timer->stop();
}

void MainWindow::timeUpdate()
{
    std::cout << "Timer out" << std::endl;
}
