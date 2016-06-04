#include "PanelInfo.h"

// Qt
#include <QApplication>

PanelInfo::PanelInfo(QWidget *parent) :
    QWidget(parent)
{
    // create the layout manager for this widget
    m_layout = new QVBoxLayout();

    // create a QPushButton
    m_quit = new QPushButton("Quitter");

    // connect m_quit button signal and close program slot
    QObject::connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    // add the button to the layout
    m_layout->addWidget(m_quit);

    // set the layout of the widget
    setLayout(m_layout);
}

PanelInfo::~PanelInfo()
{
}
