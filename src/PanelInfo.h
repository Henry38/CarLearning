#ifndef PANELINFO_H
#define PANELINFO_H

// Qt
#include <QWidget>

class QGridLayout;
class QGroupBox;
class QPushButton;

class PanelInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PanelInfo(QWidget *parent = 0);
    ~PanelInfo();

private:
    QGridLayout *m_layout;
    QGroupBox *m_panelTop, *m_panelBottom;

    QGroupBox *createTopGroupBox();
    QGroupBox *createBottomGroupBox();

};

#endif // PANELINFO_H
