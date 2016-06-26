#ifndef NEURALCLASSES_H
#define NEURALCLASSES_H

#include <iostream>

//Qt
#include <QtGlobal>

// stl
#include <vector>

using std::vector;
using namespace std;

class NeuralClasses
{
public:
    NeuralClasses(qreal p_minAngle, qreal p_maxAngle, size_t p_numberOfClasses);
    const vector<qreal> classes()const{return m_classes;}

private:
    qreal m_minAngle;
    qreal m_maxAngle;
    size_t m_numberOfClasses;
    vector<qreal> m_classes;
};

#endif // NEURALCLASSES_H
