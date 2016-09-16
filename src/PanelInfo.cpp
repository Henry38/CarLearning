#include "PanelInfo.h"

// Qt
#include <QApplication>
#include <QGroupBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QTime>
#include <QVBoxLayout>

// Project
#include "Simulation.h"

#include <QIcon>

PanelInfo::PanelInfo(Simulation *simulation, QWidget *parent) :
    QWidget(parent),
    m_simulation(simulation)
{
    // create the layout manager for this widget
    m_layout = new QGridLayout();

    m_play = new QIcon("../ressource/play.png");
    m_pause = new QIcon("../ressource/pause.png");

    m_panelTop = createTopGroupBox();
    m_layout->addWidget(m_panelTop, 0, 0);

    m_panelBottom = createBottomGroupBox();
    m_layout->addWidget(m_panelBottom, 1, 0);

    m_clock = new QLCDNumber();
    m_clock->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
    m_clock->display("00:00");
    m_layout->addWidget(m_clock, 2, 0);

    // set the layout of the widget
    setLayout(m_layout);
}

PanelInfo::~PanelInfo()
{
    delete m_play;
    delete m_pause;
}

QGroupBox *PanelInfo::createTopGroupBox()
{
    QGroupBox *groupBox = new QGroupBox("Control");

    // connect quit button signal and close program slot
    // close the application when the button is hit
    QPushButton *quit = new QPushButton("Quitter");
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(quit);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *PanelInfo::createBottomGroupBox()
{
    QGroupBox *groupBox = new QGroupBox("Simulation");

    // connect play button signal and start simulation slot
    // start and pause the simulation when the button is toggled
    buttonplay = new QPushButton(*m_play, "");
    QObject::connect(buttonplay, SIGNAL(clicked(bool)), m_simulation, SLOT(toggleTimer(bool)));
    QObject::connect(buttonplay, SIGNAL(toggled(bool)), this, SLOT(toggledButton(bool)));
    buttonplay->setCheckable(true);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(buttonplay);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

void PanelInfo::toggledButton(bool value)
{
    if (value) {
        buttonplay->setIcon(*m_pause);
    } else {
        buttonplay->setIcon(*m_play);
    }
}

void PanelInfo::timeUpdate()
{
    int timeElapsed = m_simulation->time();
    int sec = (timeElapsed / 1000) % 60;
    int min = (timeElapsed / 60000);
    QTime t(0, min, sec, 0);
    QString h = t.toString("mm:ss");
    m_clock->display(h);
}
