#include "Car.h"

const size_t Car::nbRays = 7;

Car::Car(QObject *parent) :
    QObject(parent)
{
    this->m_x = 0;
    this->m_y = 0;
    this->m_theta = 0;
    this->m_velocity = 0;
}

void Car::setX(qreal x)
{
    this->m_x = x;
}

void Car::setY(qreal y)
{
    this->m_y = y;
}

void Car::setTeta(qreal theta)
{
    this->m_theta = theta;
}

void Car::setVelocity(qreal velocity)
{
    this->m_velocity = velocity;
}
