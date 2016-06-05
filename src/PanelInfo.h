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

    //virtual void resizeEvent(QResizeEvent *event);

private:
    QGridLayout *m_layout;
    QGroupBox *m_panelTop, *m_panelBottom;
    QPushButton *m_quit;
    QPushButton *m_start;

    QGroupBox *createTopGroupBox();
    QGroupBox *createBottomGroupBox();
};

#endif // PANELINFO_H
