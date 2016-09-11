#include "PanelInfo.h"

// Qt
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QResizeEvent>
#include <QVBoxLayout>

PanelInfo::PanelInfo(QWidget *parent) :
    QWidget(parent)
{
    // create the layout manager for this widget
    m_layout = new QGridLayout();

    m_panelTop = createTopGroupBox();
    m_layout->addWidget(m_panelTop, 0, 0);

    m_panelBottom = createBottomGroupBox();
    m_layout->addWidget(m_panelBottom, 1, 0);

    // set the layout of the widget
    setLayout(m_layout);
}

PanelInfo::~PanelInfo()
{
}

QGroupBox *PanelInfo::createTopGroupBox()
{
    QGroupBox *groupBox = new QGroupBox("Control");

    // connect m_quit button signal and close program slot
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

    QRadioButton *radio1 = new QRadioButton("Radio button 1");
    QRadioButton *radio2 = new QRadioButton("Radio button 2");
    QRadioButton *radio3 = new QRadioButton("Radio button 3");

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}
