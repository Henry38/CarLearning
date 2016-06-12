#include "Simulation.h"

// Qt
#include <QtMath>

Simulation::Simulation(const char *filename, qreal L) :
    m_car(),
    m_circuit(filename, L)
{
    m_car.setX(0);
    m_car.setY(225);
    m_car.setTeta(0);
    m_car.setVelocity(10);

    //QPointF p = m_circuit.toImage(0, 0);  // Works !
    //std::cout << p.x() << ", " << p.y() << std::endl;
}

std::vector<qreal> Simulation::getRayCast() const
{
    return m_circuit.getRayCast(m_car);
}
