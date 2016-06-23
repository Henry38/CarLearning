#include "Neuron.h"

// Standard Library
#include <math.h>
#include <stdlib.h>
#include <time.h>

Neuron::Neuron(size_t n) :
    m_weightVector(n),
    m_w0(0)
{
    init();
}

void Neuron::init()
{
    // initialise la graine aleatoire
    std::srand(time(0));

    // ???
    m_w0 = 0;

    // initialise des poids aleatoire entre 0 et 1
    size_t size = m_weightVector.rows();
    for (size_t i = 0; i < size; ++i) {
        m_weightVector[i] = (rand() % 100) / 100.0;
    }
}

qreal Neuron::compute(Eigen::VectorXd entries)
{
    qreal result = m_weightVector.dot(entries);
    // Fonction Heaviside
    return (result < m_w0 ? 0 : 1);
}
