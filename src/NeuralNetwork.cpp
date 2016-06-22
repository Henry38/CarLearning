#include "NeuralNetwork.h"

#include "Car.h"

NeuralNetwork::NeuralNetwork(const Eigen::VectorXi &dimension) :
    neuronSlices(0)
{
    // fetch the number of ray cast from a car
    size_t nbEntries = Car::nbRay;

    // create for each slices, the number of neurons given
    for (unsigned int i = 0; i < dimension.rows(); ++i)
    {
        unsigned int nbNeurons = dimension[i];
        std::vector<Neuron*> vector(nbNeurons);
        for (unsigned int n = 0; n < nbNeurons; ++n)
        {
            vector[n] = new Neuron(nbEntries);
        }
        neuronSlices.push_back(vector);
        nbEntries = nbNeurons;
    }
}

NeuralNetwork::~NeuralNetwork()
{
    for (unsigned int i = 0; i < neuronSlices.size(); ++i)
    {
        std::vector<Neuron*> &slice = neuronSlices[i];
        for (unsigned int n = 0; n < slice.size(); ++n) {
            delete slice[n];
        }
    }
}

void NeuralNetwork::compute(const Eigen::VectorXd &rayCast)
{

}
