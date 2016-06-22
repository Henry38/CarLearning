#ifndef NEURON_H
#define NEURON_H

#include <Eigen/Eigen>

class Neuron
{
public:
    explicit Neuron(unsigned int n);

    void init();

private:
    unsigned int size;
    Eigen::VectorXd m_weightVector;
};

#endif // NEURON_H
