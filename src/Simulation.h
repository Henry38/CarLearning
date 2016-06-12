#ifndef SIMULATION_H
#define SIMULATION_H

#include "Car.h"
#include "Circuit.h"

class Simulation
{
public:
    Simulation(const char *filename, qreal L);

    const Car* getCar() const { return &m_car; }
    const Circuit* getCircuit() const { return &m_circuit; }

    std::vector<qreal> getRayCast() const;

private:
    Car m_car;
    Circuit m_circuit;
};

#endif // SIMULATION_H
