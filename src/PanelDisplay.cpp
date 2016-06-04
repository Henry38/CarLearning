#include "PanelDisplay.h"

// Qt
#include <QPixmap>

PanelDisplay::PanelDisplay(QWidget *parent) :
    QWidget(parent)
{
    // create the layout manager for this widget
    m_layout = new QVBoxLayout();

    // create a QLabel and load an image
    m_label = new QLabel();
    m_label->setPixmap(QPixmap("../ressource/circuit.jpeg"));

    // add label to m_layout
    m_layout->addWidget(m_label);

    // set the layout manager for this widget
    setLayout(m_layout);
}

PanelDisplay::~PanelDisplay()
{
}
