#include "PanelDisplay.h"

//std
#include <iostream>

// Qt
#include <QImage>
#include <QLabel>
#include <QtMath>
#include <QPainter>
#include <QScrollArea>
#include <QVBoxLayout>

//project
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
    scrollArea->setBackgroundRole(QPalette::Light);
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

void PanelDisplay::addCar(const Car *car)
{
    m_listCar->push_back(car);
}

void PanelDisplay::setCircuit(const Circuit *circuit)
{
    m_circuit = circuit;
    m_pixmap->load(circuit->getFilename());
}

QSize PanelDisplay::sizeHint() const
{
    int width = m_pixmap->width() + 20;
    int height = m_pixmap->height() + 20;
    return QSize(width, height);
}

void PanelDisplay::paintEvent(QPaintEvent *)
{
    cout << "PAINT EVENT" << endl;
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
        //cout << i << endl;
        const Car *car = m_listCar->at(i);
        qreal x = car->X();
        qreal y = car->Y();
        qreal theta = car->theta();
        //x+=100.; y+=100;
        QPointF p = m_circuit->toImage(x, y);
        painter.drawPoint(p);
        painter.save();
        painter.translate(p);
        painter.rotate(-theta);//-(theta / M_PI) * 180.0);
        painter.drawRect(-10, -5, 20, 10);
        painter.drawLine(0, 0, 10, 0);
        painter.restore();
        vector<vector<QPointF> > raysOnImage;
        vector<qreal> raysLength;
        m_circuit->getRayCast( *car, raysOnImage, raysLength );
        displayRays(painter, raysOnImage, raysLength);
    }

    // set the new QPixmap from the tmp (QImage)
    label->setPixmap(QPixmap::fromImage(tmp));
}


void PanelDisplay::displayRays(QPainter& p_painter, const vector<vector<QPointF> >& p_rays, const vector<qreal>& p_lengths){
    for(size_t i=0; i<p_rays.size(); ++i){
        //cout << p_rays.size() << endl;
        displayOneRay(p_painter, p_rays[i], p_lengths[i]);
    }
}

void PanelDisplay::displayOneRay(QPainter& p_painter, const vector<QPointF>& p_ray, qreal p_length){
    //cout << p_ray.size() << endl;
    for(size_t i=0; i<p_ray.size(); ++i){
        QPointF dif = p_ray[i]-p_ray[0];
        //qreal dist =  sqrt( QPointF::dotProduct(dif,dif) );
        //cout << i << " " << p_length << " " << dist << endl;
        //if(dist<p_length){
            p_painter.drawPoint(p_ray[i]);
        //}
    }
}
