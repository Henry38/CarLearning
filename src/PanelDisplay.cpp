#include "PanelDisplay.h"

// Qt
#include <QImage>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QScrollArea>
#include <QtMath>
#include <QVBoxLayout>

// Project
#include "Car.h"
#include "Circuit.h"
#include "Simulation.h"

PanelDisplay::PanelDisplay(Simulation *simulation, QWidget *parent) :
    QWidget(parent),
    m_simulation(simulation)
{
    // create a layout manager
    QGridLayout *layout = new QGridLayout();

    // create a QPixmap
    m_pixmap = new QPixmap();
    m_pixmap->load(simulation->getCircuit()->getFilename());

    // create a QLabel for display a QPixmap
    m_label = new QLabel();
    m_label->setPixmap(*m_pixmap);

    // create and configure the scroll area
    m_scrollArea = new QScrollArea();
    m_scrollArea->setBackgroundRole(QPalette::Light);
    m_scrollArea->setAlignment(Qt::AlignCenter);
    m_scrollArea->setWidget(m_label);

    // add the scroll area to the layout
    layout->addWidget(m_scrollArea);

    // set the layout manager for this widget
    setLayout(layout);
}

PanelDisplay::~PanelDisplay()
{
    delete m_pixmap;
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
    Car *car = m_simulation->getCar();
    const Circuit *circuit = m_simulation->getCircuit();

    paintpen.setColor(car->color());
    painter.setPen(paintpen);

    qreal x = car->x();
    qreal y = car->y();
    qreal theta = car->theta();
    QPointF p = circuit->toImage(x, y);
    painter.drawPoint(p);
    painter.save();
    painter.translate(p);
    painter.rotate(-theta);

    QPointF p1 = circuit->toImage(x+Car::widhtcar, y+Car::heightcar) - p;
    painter.drawRect(-p1.x()/2.0, -p1.y()/2.0, p1.x(), p1.y());
    painter.drawRect(0, 0, p1.x()/2.0, 0);
    painter.restore();

    paintpen.setColor(Qt::red);
    paintpen.setWidth(1);
    painter.setPen(paintpen);

    vector<vector<QPoint> > raysOnImage;
    circuit->getRayCast(*car, raysOnImage);
    if (raysOnImage.size() > 0) {
        displayRays(painter, raysOnImage);
    }

    // set the new QPixmap from the tmp (QImage)
    m_label->setPixmap(QPixmap::fromImage(tmp));
}

void PanelDisplay::displayRays(QPainter& p_painter, const vector<vector<QPoint> >& p_rays)
{
    for(size_t i = 0; i < p_rays.size(); ++i) {
        p_painter.drawLine(p_rays[i][0], p_rays[i][1]);
    }
}
