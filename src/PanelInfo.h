#ifndef PANELINFO_H
#define PANELINFO_H

#include <QWidget>

#include <QVBoxLayout>
#include <QPushButton>

class PanelInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PanelInfo(QWidget *parent = 0);
    ~PanelInfo();

private:
    QVBoxLayout *m_layout;
    QPushButton *m_quit;
};

#endif // PANELINFO_H
