#include "NeuralNetwork.h"

#include "Car.h"

NeuralNetwork::NeuralNetwork(const Eigen::VectorXi &dimension) :
    m_neuronLayers(0)
{
    // fetch the number of ray cast from a car
    size_t nbEntries = Car::nbRays;

    // create for each slices, the number of neurons given by dimension
    for (int i = 0; i < dimension.rows(); ++i)
    {
        size_t nbNeurons = dimension[i];
        std::vector<Neuron*> vector(nbNeurons);
        for (size_t n = 0; n < nbNeurons; ++n)
        {
            vector[n] = new Neuron(nbEntries);
        }
        m_neuronLayers.push_back(vector);
        nbEntries = nbNeurons;
    }
}

NeuralNetwork::~NeuralNetwork()
{
    for (size_t i = 0; i < m_neuronLayers.size(); ++i)
    {
        std::vector<Neuron*> &layers = m_neuronLayers[i];
        for (size_t n = 0; n < layers.size(); ++n) {
            delete layers[n];
        }
        layers.clear();
    }
}

qreal NeuralNetwork::compute(const Eigen::VectorXd &rayCast, const Eigen::VectorXd &perfectScore)
{
    size_t nbLayers = m_neuronLayers.size();
    Eigen::VectorXd entries = rayCast;
    Eigen::VectorXd result;

    // calcul de la sortie du reseau de neurones
    for (size_t i = 0; i < nbLayers; ++i)
    {
        std::vector<Neuron*> &layers = m_neuronLayers[i];
        result.resize(layers.size());

        for (size_t n = 0; n < layers.size(); ++n) {
            Neuron *neuron = layers[n];
            result[n] = neuron->compute(entries);
        }

        entries = result;
    }

    // result = sortie du reseau de neurones
    // TODO : correction des poids

    return 0;
//    // calcul de l'angle equivalent a la reponse du RDN
//    size_t nbOut = result.rows();
//    qreal sum = 0;
//    qreal angle = -45;
//    qreal angle_inc = 90 / (nbOut - 1);
//    int accum = 0;
//    for (int i = 0; i < nbOut; ++i) {
//        sum += angle * result[i];
//        angle += angle_inc;
//        accum += (result[i] > 0 ? 1 : 0);
//    }

//    return (sum / accum);
}
