#include "Simulation.h"

// Qt
#include <QtMath>

// Standard Library
#include <iostream>

Simulation::Simulation(qreal L, QObject *parent) :
    QObject(parent),
    m_car(this),
    m_circuit(L, this),
    m_timer(this)
{
    m_car.setX(0);
    m_car.setY(225);
    m_car.setTeta(0);
    m_car.setVelocity(10);

    // connect timeout signal and timeUpdate slot
    // every x milliseconds, timeUpdate method is call by m_timer
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    m_timer.start(1000);
}

void Simulation::timeUpdate()
{
    std::cout << "Timer out" << std::endl;
    // 1- Recuperer le lancer de rayon a partir de la voiture
    //std::vector<qreal> rayCast = m_circuit.getRayCast(m_car);

    // 1.1 - Générer le vecteur des scores parfaits
    //std::vector<qreal> perfectScore(0);



    // 2- Balancer le vecteur de distance au réseau de neurone
    // 3- Recuperer le résultat du reseau de neurone
    // 4- Faire bouger la voiture
    // 5- Incrementer le temps de dt ?
}
