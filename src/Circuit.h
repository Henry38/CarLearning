#ifndef CIRCUIT_H
#define CIRCUIT_H

// Qt
#include <QImage>
#include <QObject>
#include <QPointF>

// Eigen
#include <Eigen>

class Car;

class Circuit : public QObject
{

public:
    explicit Circuit(qreal L, QObject *parent = 0);

    const QString& getFilename() const { return filename; }

    Eigen::VectorXd getRayCast(const Car &car) const;
    QPointF toImage(qreal x, qreal y) const;

private:
    QString filename;
    QImage m_track;
    Eigen::Matrix3d m_projMatrix;
    Eigen::Matrix3d m_screenMatrix;

};

#endif // CIRCUIT_H
