#ifndef PANELINFO_H
#define PANELINFO_H

// Qt
#include <QWidget>

class QGridLayout;
class QGroupBox;
class QLCDNumber;
class Simulation;

class PanelInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PanelInfo(Simulation *simulation, QWidget *parent = 0);
    ~PanelInfo();

private:
    QGroupBox *createTopGroupBox();
    QGroupBox *createBottomGroupBox();

    QGridLayout *m_layout;
    QGroupBox *m_panelTop, *m_panelBottom;
    QLCDNumber *m_clock;
    Simulation *m_simulation;

public slots:
    void timeUpdate();

};

#endif // PANELINFO_H
