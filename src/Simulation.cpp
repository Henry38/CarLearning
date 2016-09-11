#include "Simulation.h"

// Qt
#include <QtMath>

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
    m_car.x() = 100;
    m_car.y() = 225;
    m_car.theta() = 0;
    m_car.velocity() = 3.0;

    // connect timeout signal and timeUpdate slot
    // every x milliseconds, timeUpdate method is call by m_timer
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    m_timer.start(25);
}

Simulation::~Simulation()
{
    delete m_neuralNetwork;
}

void Simulation::timeUpdate()
{
    // 1- Recuperer le lancer de rayon a partir de la voiture
    vector<vector<QPoint> > raysOnImage;
    m_circuit.getRayCast(m_car, raysOnImage);

    // 1.1 Generer le vecteur d'entree pour le reseau de neurone
    unsigned int nbRays = raysOnImage.size();
    Eigen::VectorXd rayCast(nbRays);
    for (unsigned int i = 0; i < nbRays; ++i) {
        QPoint p = raysOnImage[i][1] - raysOnImage[i][0];
        rayCast[i] = sqrt( QPoint::dotProduct(p,p) );
    }

    // 2- Generer le vecteur des scores parfaits
    unsigned int nbOut = 5; // ???
    // Eigen::VectorXd perfectScore = Eigen::VectorXd::Constant(Car::nbRays,1);

    // 3- Balancer les vecteurs au reseau de neurone
    // m_neuralNetwork->compute(rayCast, perfectScore);

    // 4- Recuperer le résultat du reseau de neurone
    // 5- Faire bouger la voiture
    m_car.update();

    // 6- Incrementer le temps de dt ?

    // 7- Mise a jour graphique
    emit needUpdate();
}
