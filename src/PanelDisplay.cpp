#include "PanelDisplay.h"

// Qt
#include <QImage>
#include <QLabel>
#include <QtMath>
#include <QPainter>
#include <QScrollArea>
#include <QVBoxLayout>

#include "Car.h"
#include "Circuit.h"

PanelDisplay::PanelDisplay(QWidget *parent) :
    QWidget(parent)
{
    // create a layout manager
    QGridLayout *layout = new QGridLayout();

    // load the image into a QPixmap
    m_pixmap = new QPixmap("../ressource/circuit.jpeg");

    // create a QLabel for display a QPixmap
    label = new QLabel();
    label->setPixmap(*m_pixmap);

    // create and configure the scroll area
    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(label);

    // add the scroll area to the layout
    layout->addWidget(scrollArea);

    // set the layout manager for this widget
    setLayout(layout);

    m_listCar = new std::vector<const Car*>(0);
}

PanelDisplay::~PanelDisplay()
{
    delete m_pixmap;
    delete m_listCar;
}

QSize PanelDisplay::sizeHint() const
{
    int width = m_pixmap->width() + 20;
    int height = m_pixmap->height() + 20;
    return QSize(width, height);
}

void PanelDisplay::paintEvent(QPaintEvent *)
{
    // create a QImage from m_pixmap
    QImage tmp(m_pixmap->toImage());

    // create a QPainter for drawing in tmp (QImage)
    QPainter painter(&tmp);

    // set properties for QPen
    QPen paintpen(Qt::red);
    paintpen.setWidth(2);
    painter.setPen(paintpen);

    /* Draw from here on QPainter */
    for (unsigned int i = 0; i < m_listCar->size(); ++i) {
        const Car *car = m_listCar->at(i);
        qreal x = car->x();
        qreal y = car->y();
        qreal teta = car->teta();
        QPointF p = m_circuit->toImage(x, y);
        painter.drawPoint(p);
        painter.save();
        painter.translate(p);
        painter.rotate(-(teta / M_PI) * 180.0);
        painter.drawRect(-10, -5, 20, 10);
        painter.drawLine(0, 0, 10, 0);
        painter.restore();
    }

    // set the new QPixmap from the tmp (QImage)
    label->setPixmap(QPixmap::fromImage(tmp));
}
