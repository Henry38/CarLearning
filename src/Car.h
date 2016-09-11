#ifndef CAR_H
#define CAR_H

// Qt
#include <QObject>
#include <QtGlobal>

// Eigen
#include <Eigen>

using Eigen::Vector3d;

class Car : public QObject
{
    Q_OBJECT

public:
    explicit Car(QObject *parent = 0);
    ~Car();

    qreal& x() { return m_x; }
    qreal& y() { return m_y; }
    qreal& theta() { return m_theta; }
    qreal& velocity() { return m_velocity; }

    bool& forward() { return m_moveForward; }
    bool& left() { return m_turnLeft; }
    bool& backward() { return m_moveBackward; }
    bool& right() { return m_turnRight; }

    void update();

    static const size_t nbRays;

private:
    qreal m_x;
    qreal m_y;
    qreal m_theta;
    qreal m_velocity;

    bool m_moveForward;
    bool m_turnLeft;
    bool m_moveBackward;
    bool m_turnRight;

public slots:
    void move(int, bool);

};

#endif // CAR_H
