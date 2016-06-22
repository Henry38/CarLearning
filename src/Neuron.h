#ifndef NEURON_H
#define NEURON_H

// Qt
#include <QtGlobal>

// Eigen
#include <Eigen/Eigen>

class Neuron
{

public:
    explicit Neuron(size_t n);

    void init();
    qreal compute(Eigen::VectorXd entries);

private:
    Eigen::VectorXd m_weightVector;
    qreal w0;

};

#endif // NEURON_H
