#include "NeuralClasses.h"

NeuralClasses::NeuralClasses(qreal p_minAngle, qreal p_maxAngle, size_t p_numberOfClasses /*must be an ode number*/):
    m_minAngle(p_minAngle),
    m_maxAngle(p_maxAngle),
    m_numberOfClasses(p_numberOfClasses)
{
    qreal d_angle = (m_maxAngle-m_minAngle)/(qreal)(m_numberOfClasses-1);

    qreal theta = m_minAngle;
    for(size_t i=0; i<m_numberOfClasses; ++i){
        //cout << theta << endl;
        m_classes.push_back(theta);
        theta += d_angle;
    }
}
