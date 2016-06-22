#include "Circuit.h"

#include "Car.h"

Circuit::Circuit(qreal L, QObject *parent) :
    QObject(parent),
    filename("../ressource/circuit.jpeg"),
    m_track(filename),
    m_projMatrix(),
    m_screenMatrix()
{
    int width = m_track.width();
    int height = m_track.height();
    qreal ratio = qreal(width) / qreal(height);
    qreal r = 0.5 * L;
    qreal t = 0.5 * L * (1.0 / ratio);

    m_projMatrix = Eigen::Matrix3d::Constant(0);
    m_projMatrix(0,0) = 1 / r;
    m_projMatrix(1,1) = 1 / t;
    m_projMatrix(2,2) = 1;

    m_screenMatrix = Eigen::Matrix3d::Constant(0);
    m_screenMatrix(0,0) = width / 2.0;
    m_screenMatrix(1,1) = -height / 2.0;
    m_screenMatrix(0,2) = width / 2.0;
    m_screenMatrix(1,2) = height / 2.0;
    m_screenMatrix(2,2) = 1;
}

std::vector<qreal> Circuit::getRayCast(const Car &car) const
{
    std::vector<qreal> vector(0);
    // TODO : implements ray cast algorithm from a continuous space ?
    for (unsigned int i = 0; i < 7; ++i) {
        vector.push_back(20);
    }
    return vector;
}

QPointF Circuit::toImage(qreal x, qreal y) const
{
    // Homogeneous coordinate
    Eigen::Vector3d p(x, y, 1);

    // Projection space
    Eigen::Vector3d p_proj = m_projMatrix * p;

    // Normale coordinate space
    qreal x_ndc = p_proj(0) / p_proj(2);
    qreal y_ndc = p_proj(1) / p_proj(2);
    Eigen::Vector3d p_ndc = Eigen::Vector3d(x_ndc, y_ndc, 1);

    // Image space
    Eigen::Vector3d p_image = m_screenMatrix * p_ndc;

    return QPointF(p_image(0), p_image(1));
}
