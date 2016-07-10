#include "Ray.h"

Ray::Ray(const Car* p_car, size_t p_discretization, qreal p_theta, qreal p_L):
    m_theta(p_theta),
    m_L(p_L/2.),
    m_discretization(p_discretization)
{
    m_G(0) = p_car->X();
    m_G(1) = p_car->Y();
//    m_theta *= M_PI/180.;
    m_theta = ( m_theta + p_car->theta()) * M_PI/180.;
    qreal x = m_G(0);
    qreal y = m_G(1);
    qreal step = m_L/(qreal)m_discretization;

    qreal length = 0.;


    while(length <= m_L){
        m_line.push_back(Vector3d(x,y,1.));
        x += step*cos(m_theta);
        y += step*sin(m_theta);
        length = distanceFromOrigin(x,y);
    }
}

qreal Ray::distanceFromOrigin(qreal p_x, qreal p_y)const{
    qreal deltaX = p_x-m_G(0);
    qreal deltaY = p_y-m_G(1);
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}
