#ifndef NEURON_H
#define NEURON_H

// Qt
#include <QtGlobal>

// Eigen
#include <Eigen>

class Neuron
{

public:
    explicit Neuron(size_t n);

    size_t getNbEntries() { return m_weightVector.rows(); }

    void init();
    qreal compute(Eigen::VectorXd entries);

private:
    Eigen::VectorXd m_weightVector;
    qreal m_w0;

};

#endif // NEURON_H
