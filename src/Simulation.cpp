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
    // set 3 slices and define the number of neurons on each of them
    Eigen::VectorXi dimension(3);
    dimension << 3, 4, 3;

    // create a neural network
    m_neuralNetwork = new NeuralNetwork(dimension);

    // set properties of the car
    m_car.setX(100);
    m_car.setY(225);
    m_car.setTeta(0);
    m_car.setVelocity(10);

    // connect timeout signal and timeUpdate slot
    // every x milliseconds, timeUpdate method is call by m_timer
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    m_timer.start(1000);
}

Simulation::~Simulation()
{
    delete m_neuralNetwork;
}

void Simulation::timeUpdate()
{
    std::cout << "Timer out" << std::endl;
    // 1- Recuperer le lancer de rayon a partir de la voiture
    // Eigen::VectorXd rayCast = m_circuit.getRayCast(m_car);

    // 2- Générer le vecteur des scores parfaits
    // Eigen::VectorXd perfectScore = Eigen::VectorXd::Constant(Car::nbRays,1);

    // 3- Balancer le vecteur de distance au réseau de neurone
    // m_neuralNetwork->compute(rayCast, perfectScore);

    // 4- Recuperer le résultat du reseau de neurone
    // 5- Faire bouger la voiture
    // 6- Incrementer le temps de dt ?

    vector<vector<QPointF> > raysOnImage;
    vector<qreal> raysLength;

    m_circuit.getRayCast(m_car, p_raysOnImage, p_raysLength);
}
