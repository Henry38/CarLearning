#include "MainWindow.h"

// Qt
#include <QHBoxLayout>
#include <QPushButton>

// Project
#include "PanelInfo.h"
#include "PanelDisplay.h"
#include "Simulation.h"

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

    // create a simulation
    m_simulation = new Simulation(1000, this);

    // create the two graphicals panels
    m_panelInfo = new PanelInfo();
    m_panelDisplay = new PanelDisplay(m_simulation);

    // add panels to m_layout
    // MainWindow takes ownership of them (parenting)
    m_layout->addWidget(m_panelInfo);
    m_layout->addWidget(m_panelDisplay);

    // set the central widget of the window
    setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow()
{
    // m_centralWidget is automaticaly deleted by MainWindow
    // so is m_layout from m_centralWidget (parenting)
    // so are m_panelInfo and m_panelDisplay from m_layout (parenting)
}

void MainWindow::timerStart()
{
    //m_timer->start(1000);
}

void MainWindow::timerStop()
{
    //m_timer->stop();
}


