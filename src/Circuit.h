#ifndef CIRCUIT_H
#define CIRCUIT_H

//CarLearning Project
#include "Car.h"
#include "NeuralClasses.h"
#include "Ray.h"

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

    void getRayCast(const Car &car, vector<vector<QPointF> >& p_raysOnImage, vector<qreal>& p_raysLength)const;

    QPointF toImage(qreal x, qreal y) const;
    void computeProjMatrix();
    void computeScreenMatrix();
    vector<QPointF> rayOnImageProjection(const vector<Vector3d>& p_line)const;
    int* imageToArray(QImage image)const;
    qreal lengthComputation(const vector<QPointF>& p_rayOnImage)const;
    int positionOnImageToPixelValue(const QPointF& p_position)const;
    vector<vector<QPointF> > raysOnImage()const{return m_raysOnImage;}
    vector<qreal> raysLength()const{return m_raysLength;}


private:
    QString filename;
    QImage m_track;
    Eigen::Matrix3d m_projMatrix;
    Eigen::Matrix3d m_screenMatrix;
    qreal m_L;
    vector<qreal> m_raysLength;
    vector<vector<QPointF> > m_raysOnImage;

};

#endif // CIRCUIT_H
