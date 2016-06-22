#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// Qt
//#include <QObject>

// Standard Library
#include <vector>

// Eigen
#include <Eigen/Eigen>

#include "Neuron.h"

class NeuralNetwork
{

public:
    explicit NeuralNetwork(const Eigen::VectorXi &dimension);
    ~NeuralNetwork();

    void compute(const Eigen::VectorXd &rayCast);

private:
    std::vector< std::vector<Neuron*> > neuronSlices;

};

#endif // NEURALNETWORK_H
