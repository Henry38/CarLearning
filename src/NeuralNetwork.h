#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// Standard Library
#include <vector>

// Eigen
#include <Eigen>

#include "Neuron.h"

class NeuralNetwork
{

public:
    explicit NeuralNetwork(const Eigen::VectorXi &dimension);
    ~NeuralNetwork();

    qreal compute(const Eigen::VectorXd &rayCast, const Eigen::VectorXd &perfectScore);

private:
    std::vector< std::vector<Neuron*> > m_neuronLayers;

};

#endif // NEURALNETWORK_H
