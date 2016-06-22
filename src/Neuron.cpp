#include "Neuron.h"

// Standard Library
#include <stdlib.h>
#include <time.h>

Neuron::Neuron(unsigned int n) :
    size(n),
    m_weightVector(n+1)
{
    init();
}

void Neuron::init()
{
    // initialise la graine aleatoire
    std::srand(time(0));

    // le poids w0 est vaut toujours -1
    m_weightVector[0] = -1;

    // initialise des poids aleatoire entre 0 et 1
    for (unsigned int i = 1; i < size; ++i) {
        m_weightVector[i] = (rand() % 100) / 100.0;
    }
}
