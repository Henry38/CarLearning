#ifndef CIRCUIT_H
#define CIRCUIT_H

// Qt
#include <QImage>
#include <QObject>
#include <QPointF>
#include <QPainter>

// Eigen
#include <Eigen>

//Project
#include "Car.h"

using std::vector;

class Car;

class Circuit : public QObject
{

public:
    explicit Circuit(qreal L, QObject *parent = 0);

    const QString& getFilename() const { return filename; }

    void getRayCast(Car &car, vector<vector<QPoint> > &p_raysOnImage)const;

    QPointF toImage(qreal x, qreal y) const;
    void computeProjMatrix();
    void computeScreenMatrix();

    bool isCollision(int x, int y) const;
    bool isCollision(Car &car) const;
    void Bresenham2D(int x1, int y1, int x2, int y2, std::vector<QPoint> &ray) const;

private:
    QString filename;
    QImage m_track;
    Eigen::Matrix3d m_projMatrix;
    Eigen::Matrix3d m_screenMatrix;
    qreal m_L;
    vector<vector<QPointF> > m_raysOnImage;

};

#endif // CIRCUIT_H
