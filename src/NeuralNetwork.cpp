#include "NeuralNetwork.h"

#include "Car.h"
#include <iostream>
NeuralNetwork::NeuralNetwork(const Eigen::VectorXi &dimension) :
    neuronSlices(0)
{
    // fetch the number of ray cast from a car
    size_t nbEntries = Car::nbRay;

    // create for each slices, the number of neurons given by dimension
    for (int i = 0; i < dimension.rows(); ++i)
    {
        size_t nbNeurons = dimension[i];
        std::vector<Neuron*> vector(nbNeurons);
        for (size_t n = 0; n < nbNeurons; ++n)
        {
            vector[n] = new Neuron(nbEntries);
        }
        neuronSlices.push_back(vector);
        nbEntries = nbNeurons;
    }
}

NeuralNetwork::~NeuralNetwork()
{
    for (size_t i = 0; i < neuronSlices.size(); ++i)
    {
        std::vector<Neuron*> &slice = neuronSlices[i];
        for (size_t n = 0; n < slice.size(); ++n) {
            delete slice[n];
        }
        slice.clear();
    }
}

qreal NeuralNetwork::compute(const Eigen::VectorXd &rayCast, const Eigen::VectorXd &perfectScore)
{
    size_t nbSlice = neuronSlices.size();
    Eigen::VectorXd entries = rayCast;
    Eigen::VectorXd result;

    // calcul de la sortie du reseau de neurones
    for (size_t i = 0; i < nbSlice; ++i)
    {
        std::vector<Neuron*> &slice = neuronSlices[i];
        result.resize(slice.size());

        for (size_t n = 0; n < slice.size(); ++n) {
            Neuron *neuron = slice[n];
            result[n] = neuron->compute(entries);
        }

        entries = result;
    }

    // result = sortie du reseau de neurones
    // TODO : correction des poids

    // calcul de l'angle equivalent a la reponse du RDN
    size_t nbOut = result.rows();
    qreal sum = 0;
    qreal angle = -45;
    qreal angle_inc = 90 / (nbOut - 1);
    int accum = 0;
    for (int i = 0; i < nbOut; ++i) {
        sum += angle * result[i];
        angle += angle_inc;
        accum += (result[i] > 0 ? 1 : 0);
    }

    return (sum / accum);
}
