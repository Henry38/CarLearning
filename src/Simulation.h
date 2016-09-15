#ifndef SIMULATION_H
#define SIMULATION_H

// Qt
#include <QObject>
#include <QTime>
#include <QTimer>

// Project
#include "Car.h"
#include "Circuit.h"
#include "NeuralNetwork.h"

using namespace std;

class Simulation : public QObject
{
    Q_OBJECT

public:
    explicit Simulation(qreal L, QObject *parent = 0);
    ~Simulation();

    Car* getCar() { return &m_car; }
    Circuit* getCircuit() { return &m_circuit; }
    int time() { return m_timeElapsed + m_time.elapsed(); }

private:
    Car m_car;
    Circuit m_circuit;
    NeuralNetwork *m_neuralNetwork;

    int m_timeElapsed;
    QTime m_time;
    QTimer m_timer;

signals:
    void needUpdate();

public slots:
    void toggleTimer(bool value);
    void timeUpdate();

};

#endif // SIMULATION_H
