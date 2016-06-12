#ifndef PANELDISPLAY_H
#define PANELDISPLAY_H

// Qt
#include <QWidget>

class Car;
class Circuit;
class QLabel;
class QScrollArea;
class QPixmap;

class PanelDisplay : public QWidget
{
    Q_OBJECT

public:
    PanelDisplay(QWidget *parent = 0);
    ~PanelDisplay();

    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *);

    void addCar(const Car *car) { m_listCar->push_back(car); }
    void setCircuit(const Circuit *circuit) { m_circuit = circuit; }

private:
    QLabel *label;
    QScrollArea *scrollArea;
    QPixmap *m_pixmap;

    std::vector<const Car*> *m_listCar;
    const Circuit *m_circuit;

};

#endif // PANELDISPLAY_H
