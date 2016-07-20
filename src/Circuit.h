#ifndef CIRCUIT_H
#define CIRCUIT_H

//CarLearning Project
#include "Car.h"

// Qt
#include <QImage>
#include <QObject>
#include <QPointF>
#include <QPainter>

// Eigen
#include <Eigen>

// stl
#include <vector>

using std::vector;

class Car;

class Circuit : public QObject
{

public:
    explicit Circuit(qreal L, QObject *parent = 0);

    const QString& getFilename() const { return filename; }

    void getRayCast(const Car &car, vector<vector<QPoint> > &p_raysOnImage)const;

    QPointF toImage(qreal x, qreal y) const;
    void computeProjMatrix();
    void computeScreenMatrix();
//    vector<QPointF> rayOnImageProjection(const vector<Vector3d>& p_line)const;
//    int* imageToArray(QImage image)const;
//    qreal lengthComputation(const vector<QPointF>& p_rayOnImage)const;
//    vector<vector<QPointF> > raysOnImage()const{return m_raysOnImage;}
//    vector<qreal> raysLength()const{return m_raysLength;}
//    int positionOnImageToPixelValue(int x, int y) const;

    bool isCollision(int x, int y) const;
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
