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
    explicit PanelDisplay(QWidget *parent = 0);
    ~PanelDisplay();

    void addCar(const Car *car);
    void setCircuit(const Circuit *circuit);

    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *);

private:
    QLabel *label;
    QScrollArea *scrollArea;
    QPixmap *m_pixmap;

    std::vector<const Car*> *m_listCar;
    const Circuit *m_circuit;

};

#endif // PANELDISPLAY_H
