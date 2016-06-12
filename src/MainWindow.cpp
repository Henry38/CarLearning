#include "MainWindow.h"

// Qt
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

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

    // Create a simulation
    simulation = new Simulation("../ressource/circuit.jpeg", 1000);

    // Set element for m_panelDisplay
    m_panelDisplay->addCar(simulation->getCar());
    m_panelDisplay->setCircuit(simulation->getCircuit());
}

MainWindow::~MainWindow()
{
    // m_centralWidget is automaticaly deleted by MainWindow
    // so is m_layout from m_centralWidget (parenting)
    // so are m_panelInfo and m_panelDisplay from m_layout (parenting)
    delete simulation;
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
    // 1- Recuperer le lancer de rayon a partir de la voiture
    // 1.1 - Générer le vecteur des scores parfaits
    // 2- Balancer le vecteur de distance au réseau de neurone
    // 3- Recuperer le résultat du reseau de neurone
    // 4- Faire bouger la voiture
    // 5- Incrementer le temps de dt ?
}
