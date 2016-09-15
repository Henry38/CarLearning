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

PanelInfo::PanelInfo(Simulation *simulation, QWidget *parent) :
    QWidget(parent),
    m_simulation(simulation)
{
    // create the layout manager for this widget
    m_layout = new QGridLayout();

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
    QPushButton *play = new QPushButton("play");
    QObject::connect(play, SIGNAL(clicked(bool)), m_simulation, SLOT(toggleTimer(bool)));
    play->setCheckable(true);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(play);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
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
