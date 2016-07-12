#include "Circuit.h"

#include "Car.h"

Circuit::Circuit(qreal L, QObject *parent) :
    QObject(parent),
    filename("../ressource/circuit.jpeg"),
    m_track(filename),
    m_projMatrix(),
    m_screenMatrix(),
    m_L(L)
{
    computeProjMatrix();
    computeScreenMatrix();
}

void Circuit::computeProjMatrix(){
    int width = m_track.width();
    int height = m_track.height();
    qreal ratio = qreal(width) / qreal(height);
    qreal r = 0.5 * m_L;
    qreal t = 0.5 * m_L * (1.0 / ratio);

    m_projMatrix = Eigen::Matrix3d::Constant(0);
    m_projMatrix(0,0) = 1. / r;
    m_projMatrix(1,1) = 1. / t;
    m_projMatrix(2,2) = 1.;
}

void Circuit::computeScreenMatrix(){
    int width = m_track.width(); // p_w
    int height = m_track.height(); // p_h
    m_screenMatrix = Eigen::Matrix3d::Constant(0);
    m_screenMatrix(0,0) = width / 2.0;
    m_screenMatrix(1,1) = -height / 2.0;
    m_screenMatrix(0,2) = width / 2.0;
    m_screenMatrix(1,2) = height / 2.0;
    m_screenMatrix(2,2) = 1;
}

void Circuit::getRayCast(const Car &car, vector<vector<QPoint> >& p_raysOnImage) const
{
    // angle of the rays thrown by the car wrt the direction of the car
    qreal minAngle = -90.;
    qreal maxAngle = 90.;
    size_t numberOfAngles = Car::nbRays;
    qreal step_angle = (maxAngle - minAngle) / (numberOfAngles - 1);

    QPointF p1 = toImage(car.X(), car.Y());
    int x1 = std::floor(p1.x());
    int y1 = std::floor(p1.y());

    // for each ray (each ray is caracterized by its angle wrt the direction of the car)
    for(size_t i = 0; i < numberOfAngles; ++i) {
        qreal angle = car.theta() + minAngle + (i * step_angle);
        qreal radian = angle * (M_PI / 180.0);
        QPointF p2 = toImage(car.X() + m_L * cos(radian), car.Y() + m_L * sin(radian));
        int x2 = p2.x();
        int y2 = p2.y();

        std::vector<QPoint> ray;
        Bresenham2D(x1, y1, x2, y2, ray);
        if (ray.size() > 0) {
            p_raysOnImage.push_back(ray);
        }
    }
}

// this function maps a 2D point taken in the continuous real space
// (the space where the circuit lives, with reallistic distance, for example: x= 500 m, y 200 m)
// into the pixel space of the image
//   (x_g)   (a_g)              (a_g)   (u_g)
// P*(y_g) = (b_g)   and  (M|t)*(b_g) = (v_g)
//   ( 1 )   ( 1 )              ( 1 )
//
//           (2/L*p_h/p_w     0     0)
// where P = (0               2/L   0)  <----- m_projMatrix
//           (0               0     1)
//
//         (p_w/2   0      p_w/2)
// and M = (0     -p_h/2    p_h/2)       <----- m_screenMatrix
QPointF Circuit::toImage(qreal x, qreal y) const
{
    // Homogeneous coordinate
    Eigen::Vector3d p(x, y, 1);

    // Projection space
    Eigen::Vector3d p_proj = m_projMatrix * p;

    // Normal coordinate space
    qreal x_ndc = p_proj(0) / p_proj(2);
    qreal y_ndc = p_proj(1) / p_proj(2);
    Eigen::Vector3d p_ndc = Eigen::Vector3d(x_ndc, y_ndc, 1);

    // Image space
    Eigen::Vector3d p_image = m_screenMatrix * p_ndc;

    return QPointF(p_image(0), p_image(1));
}

bool Circuit::isCollision(int x, int y) const
{
    if (x < 0 || y < 0 || x > m_track.width() || y > m_track.height()) {
        return true;
    }
    return (qGray(m_track.pixel(x,y)) == 0);
}

void Circuit::Bresenham2D(int x1, int y1, int x2, int y2, std::vector<QPoint> &ray) const
{
    int point[2];
    point[0] = x1;
    point[1] = y1;

    if (isCollision(point[0], point[1])) {
        return;
    }

    ray.push_back(QPoint(point[0], point[1]));

    int dx = x2 - x1;
    int dy = y2 - y1;
    int x_inc = (dx < 0) ? -1 : 1;
    int y_inc = (dy < 0) ? -1 : 1;
    int abs_dx = abs(dx);
    int abs_dy = abs(dy);

    int dx2 = abs_dx << 1;
    int dy2 = abs_dy << 1;

    if (abs_dx >= abs_dy) {
        int err = -abs_dx;
        bool collision = false;
        // iteration sur x
        for (int i = 0; i <= abs_dx && !collision; ++i) {
            //ray.push_back(QPoint(point[0], point[1]));
            err += dy2;
            if (err > 0) {
                point[1] += y_inc;
                err -= dx2;
            }
            point[0] += x_inc;
            collision = (isCollision(point[0], point[1]));
        }
    } else if (abs_dy >= abs_dx) {
        int err = -abs_dy;
        bool collision = false;
        // iteration sur y
        for (int i = 0; i <= abs_dy && !collision; ++i) {
            //ray.push_back(QPoint(point[0], point[1]));
            err += dx2;
            if (err > 0) {
                point[0] += x_inc;
                err -= dy2;
            }
            point[1] += y_inc;
            collision = (isCollision(point[0], point[1]));
        }
    }

    ray.push_back(QPoint(point[0], point[1]));
}




//vector<QPointF> Circuit::rayOnImageProjection(const vector<Vector3d>& p_line)const{
//    vector<QPointF> rayOnImage;
//    // for each point in a ray
//    for(size_t i=0; i<p_line.size(); i++){
//        qreal x = p_line[i](0);
//        qreal y = p_line[i](1);
//        // filling a vector that contains the coordinates in the "pixel space" of the points of a ray
//        rayOnImage.push_back(toImage(x,y));
//    }
//    return rayOnImage;
//}

//int* Circuit::imageToArray(QImage image)const{
//    int width = image.width();
//    int height = image.height();
//    int* matrix = new int[width*height];
//    for(int j = 0; j < height; j++)
//    {
//      for(int i = 0; i < width; i++)
//      {
//        matrix[j*width+i] = qGray(image.pixel(i,j));
//      }
//    }
//    return matrix;
//}

//qreal Circuit::lengthComputation(const vector<QPointF>& p_rayOnImage)const{
//    qreal length = 0.;
//    // for each point of the ray in the "pixel space"
//    for(size_t i=0; i<p_rayOnImage.size(); ++i){
//        // recover the value of the pixel associated to the ray current point
//        int pixel = positionOnImageToPixelValue(p_rayOnImage[i]);
//        if(pixel == 0){
//            QPointF dif = p_rayOnImage[i]-p_rayOnImage[0];
//            length = sqrt( QPointF::dotProduct(dif,dif) );
//            return length;
//        }
//    }
//    return length; // aie!! me renvoie 0
//}

//int Circuit::positionOnImageToPixelValue(int x, int y) const
//{
//    return qGray(m_track.pixel(x,y));
//}
