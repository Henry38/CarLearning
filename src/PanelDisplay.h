#ifndef PANELDISPLAY_H
#define PANELDISPLAY_H

// Qt
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class PanelDisplay : public QWidget
{
    Q_OBJECT

public:
    PanelDisplay(QWidget *parent = 0);
    ~PanelDisplay();

private:
    QVBoxLayout *m_layout;
    QLabel *m_label;
};

#endif // PANELDISPLAY_H
