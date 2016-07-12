#include "PanelDisplay.h"

// Standard Library
#include <iostream>

// Qt
#include <QImage>
#include <QLabel>
#include <QtMath>
#include <QPainter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QKeyEvent>

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
    const Car *car = m_simulation->getCar();
    const Circuit *circuit = m_simulation->getCircuit();

    qreal x = car->X();
    qreal y = car->Y();
    qreal theta = car->theta();
    QPointF p = circuit->toImage(x, y);
    painter.drawPoint(p);
    painter.save();
    painter.translate(p);
    painter.rotate(-theta);
    painter.drawRect(-10, -5, 20, 10);
    painter.drawLine(0, 0, 10, 0);
    painter.restore();
    vector<vector<QPointF> > raysOnImage;
    vector<qreal> raysLength;
    circuit->getRayCast( *car, raysOnImage, raysLength );
    displayRays(painter, raysOnImage, raysLength);

    // set the new QPixmap from the tmp (QImage)
    m_label->setPixmap(QPixmap::fromImage(tmp));
}

void PanelDisplay::keyPressEvent(QKeyEvent* event)
{
    // A changer !
    if(event->key() == Qt::Key_Z){
        Car *car = (Car*) m_simulation->getCar();
        car->forward(1.0);
        repaint();
    }

    if(event->key() == Qt::Key_Q){
        Car *car = (Car*) m_simulation->getCar();
        car->turn(1.0);
        repaint();
    }

    if(event->key() == Qt::Key_S){
        Car *car = (Car*) m_simulation->getCar();
        car->forward(-1.0);
        repaint();
    }

    if(event->key() == Qt::Key_D){
        Car *car = (Car*) m_simulation->getCar();
        car->turn(-1.0);
        repaint();
    }
}

void PanelDisplay::displayRays(QPainter& p_painter, const vector<vector<QPointF> >& p_rays, const vector<qreal>& p_lengths){
    for(size_t i=0; i<p_rays.size(); ++i){
        displayOneRay(p_painter, p_rays[i], p_lengths[i]);
    }
}

void PanelDisplay::displayOneRay(QPainter& p_painter, const vector<QPointF>& p_ray, qreal p_length){
    //cout << p_ray.size() << endl;
    for(size_t i=0; i<p_ray.size(); ++i){
        QPointF dif = p_ray[i]-p_ray[0];
        qreal dist =  sqrt( QPointF::dotProduct(dif,dif) );
        //cout << i << " " << p_length << " " << dist << endl;
        if(dist<p_length){
            p_painter.drawPoint(p_ray[i]);
        }
    }
}
