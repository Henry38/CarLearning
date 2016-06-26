#ifndef CAR_H
#define CAR_H

// Qt
#include <QObject>
#include <QtGlobal>

class Car : public QObject
{

public:
    explicit Car(QObject *parent = 0);

    qreal x() const { return m_x; }
    qreal y() const { return m_y; }
    qreal teta() const { return m_teta; }
    qreal velocity() const { return m_velocity; }

    void setX(qreal x);
    void setY(qreal y);
    void setTeta(qreal teta);
    void setVelocity(qreal velocity);

    static const size_t nbRays;

private:

    qreal m_x;
    qreal m_y;
    qreal m_teta;
    qreal m_velocity;

};

#endif // CAR_H
