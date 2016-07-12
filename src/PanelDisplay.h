#ifndef PANELDISPLAY_H
#define PANELDISPLAY_H

// Qt
#include <QWidget>

using namespace std;

class QLabel;
class QScrollArea;
class QPixmap;
class Simulation;

class PanelDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit PanelDisplay(Simulation *simulation, QWidget *parent = 0);
    ~PanelDisplay();

    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent*);
    virtual void keyPressEvent(QKeyEvent*);

    void displayRays(QPainter& p_painter, const vector<vector<QPointF> >& p_rays, const vector<qreal>& p_lengths);

    void displayOneRay(QPainter& p_painter, const vector<QPointF>& p_ray, qreal p_lengths);

private:
    QLabel *m_label;
    QScrollArea *m_scrollArea;
    QPixmap *m_pixmap;

    const Simulation *m_simulation;
};

#endif // PANELDISPLAY_H
