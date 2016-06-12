#ifndef CIRCUIT_H
#define CIRCUIT_H

// Qt
#include <QImage>
#include <QPointF>

// Eigen
#include <Eigen>

class Car;

class Circuit
{
public:
    explicit Circuit(const char *filename, qreal L);

    std::vector<qreal> getRayCast(const Car &car) const;
    QPointF toImage(qreal x, qreal y) const;

private:
    QImage m_track;
    Eigen::Matrix3d m_projMatrix;
    Eigen::Matrix3d m_screenMatrix;

};

#endif // CIRCUIT_H
