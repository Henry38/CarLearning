#ifndef RAY_H
#define RAY_H

#include <QtMath>
#include <Eigen>
#include <vector>

using namespace std;
using namespace Eigen;

class Ray
{
public:
    Ray(size_t p_discretization, Vector3d p_G, qreal p_angle, qreal p_L);
    qreal distanceFromOrigin(qreal p_x, qreal p_y)const;

    vector<Vector3d> line()const{return m_line;}

    void setLength(const qreal& p_length){this->m_length = p_length;}

private:
    Vector3d m_G;
    qreal m_theta;
    qreal m_L;
    size_t m_discretization;
    vector<Vector3d> m_line;
    qreal m_length;
};

#endif // RAY_H
