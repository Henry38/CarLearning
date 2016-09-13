#include "Car.h"

const size_t Car::nbRays = 7;
const size_t Car::widhtcar = 20;
const size_t Car::heightcar = 10;

Car::Car(QObject *parent) :
    QObject(parent),
    m_x(0),
    m_y(0),
    m_theta(0),
    m_velocity(0),
    m_moveForward(false),
    m_turnLeft(false),
    m_moveBackward(false),
    m_turnRight(false),
    m_color(Qt::green)
{
}

Car::~Car()
{
}

void Car::update()
{
    if (m_moveForward) {
        x() += m_velocity * cos( theta() * M_PI / 180.0 );
        y() += m_velocity * sin( theta() * M_PI / 180.0 );
    }

    if (m_moveBackward) {
        x() -= m_velocity * cos( theta() * M_PI / 180.0 );
        y() -= m_velocity * sin( theta() * M_PI / 180.0 );
    }

    if (m_turnLeft) {
        theta() += 3.0;
    }

    if (m_turnRight) {
        theta() -= 3.0;
    }
}

void Car::move(int key, bool isPressed)
{
    if (key == Qt::Key_Z) {
        m_moveForward = isPressed;
    }

    if (key == Qt::Key_Q) {
        m_turnLeft = isPressed;
    }

    if (key == Qt::Key_S) {
        m_moveBackward = isPressed;
    }

    if (key == Qt::Key_D) {
        m_turnRight = isPressed;
    }
}
