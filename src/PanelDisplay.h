#ifndef PANELDISPLAY_H
#define PANELDISPLAY_H

// Qt
#include <QWidget>

//class QVBoxLayout;
class QScrollArea;
class QLabel;
class QPixmap;

class PanelDisplay : public QWidget
{
    Q_OBJECT

public:
    PanelDisplay(QWidget *parent = 0);
    ~PanelDisplay();

    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *);

private:
    //QVBoxLayout *m_layout;
    QLabel *label;
    QScrollArea *scrollArea;
    QPixmap *m_pixmap;

};

#endif // PANELDISPLAY_H
