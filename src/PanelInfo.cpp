#include "PanelInfo.h"

// Qt
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QVBoxLayout>

#include <QRadioButton>
#include <iostream>

PanelInfo::PanelInfo(QWidget *parent) :
    QWidget(parent)
{
    // create the layout manager for this widget
    m_layout = new QGridLayout();

    m_panelTop = createTopGroupBox();
    m_layout->addWidget(m_panelTop, 0, 0);

    m_panelBottom = createBottomGroupBox();
    m_layout->addWidget(m_panelBottom, 1, 0);

//    // create a QPushButton
//    m_quit = new QPushButton("Quitter");

//    // connect m_quit button signal and close program slot
//    // close the application when the button is hit
//    QObject::connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

//    // add the button to the layout
//    m_layout->addWidget(m_quit, 0, 0);

    // set the layout of the widget
    setLayout(m_layout);
}

PanelInfo::~PanelInfo()
{
}

//void PanelInfo::resizeEvent(QResizeEvent *event)
//{
//    //QSize size = event->size();
//    //std::cout << size.width() << ", " << size.height() << std::endl;
//    //m_panelBottom->setMaximumHeight(size.height() / 2);
//}

QGroupBox *PanelInfo::createTopGroupBox()
{
    QGroupBox *groupBox = new QGroupBox("Control");

    QPushButton *quit = new QPushButton("Quitter");

    // connect m_quit button signal and close program slot
    // close the application when the button is hit
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(quit);
//    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QGroupBox *PanelInfo::createBottomGroupBox()
{
    QGroupBox *groupBox = new QGroupBox("Simulation");

    QRadioButton *radio1 = new QRadioButton("Radio button 1");
    QRadioButton *radio2 = new QRadioButton("Radio button 2");
    QRadioButton *radio3 = new QRadioButton("Radio button 3");

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    //vbox->setAlignment(radio3, Qt::AlignRight);
    // place la groupBox sur la droite, useless
    //groupBox->setAlignment(Qt::AlignRight);

    return groupBox;

//    QGroupBox *groupBox = new QGroupBox("Simualtion");
//    QVBoxLayout *vbox = new QVBoxLayout();

//    QPushButton *start = new QPushButton("Start");
//    vbox->addWidget(start);
//    //vbox->addStretch(1);
//    groupBox->setLayout(vbox);

//    return groupBox;
}
