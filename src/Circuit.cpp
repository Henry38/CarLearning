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
    int width = m_track.width(); // p_w
    int height = m_track.height(); // p_h
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

void Circuit::getRayCast(const Car &car, vector<vector<QPointF> >& p_raysOnImage, vector<qreal>& p_raysLength)const
{

    // recover the coordinate of the car in the physical space
    Vector3d G(car.X(), car.Y(), 1);

    // project those above coordinates in the pixel space of the image.
    QPointF G_on_image = toImage(G(0), G(1));

    // angle of the rays thrown by the car wrt the direction of the car
    qreal minAngle = -90.;
    qreal maxAngle = 90.;
    size_t numberOfAngles = 7;  // Attribut static a mettre de la classe Car
    size_t discretization = 100;

    NeuralClasses angleClasses(minAngle, maxAngle, numberOfAngles);
    vector<qreal> classes = angleClasses.classes();

    //int* matrix = imageToArray(m_track);

    // for each ray (each ray is caracterized by its angle wrt the direction of the car)
    for(size_t i = 0; i<classes.size(); ++i){

        Ray ray(discretization, G, classes[i], m_L);

        // projecion of a ray in the "pixel space"
        p_raysOnImage.push_back(rayOnImageProjection(ray.line()));

        // computing the length of the ray in the "pixel space"
        qreal length = lengthComputation(p_raysOnImage[i]);

        p_raysLength.push_back(length);
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

vector<QPointF> Circuit::rayOnImageProjection(const vector<Vector3d>& p_line)const{
    vector<QPointF> rayOnImage;
    // for each point in a ray
    for(size_t i=0; i<p_line.size(); i++){
        qreal x = p_line[i](0);
        qreal y = p_line[i](1);
        // filling a vector that contains the coordinates in the "pixel space" of the points of a ray
        rayOnImage.push_back(toImage(x,y));
    }
    return rayOnImage;
}

int* Circuit::imageToArray(QImage image)const{
    int width = image.width();
    int height = image.height();
    int* matrix = new int[width*height];
    for(int j = 0; j < height; j++)
    {
      for(int i = 0; i < width; i++)
      {
        matrix[j*width+i] = qGray(image.pixel(i,j));
      }
    }
    return matrix;
}

qreal Circuit::lengthComputation(const vector<QPointF>& p_rayOnImage)const{
    qreal length = 0.;
    // for each point of the ray in the "pixel space"
    for(size_t i=0; i<p_rayOnImage.size(); ++i){
        // recover the value of the pixel associated to the ray current point
        int pixel = positionOnImageToPixelValue(p_rayOnImage[i]);
        if(pixel == 0){
            QPointF dif = p_rayOnImage[i]-p_rayOnImage[0];
            length = sqrt( QPointF::dotProduct(dif,dif) );
            return length;
        }
    }
    return length; // aie!! me renvoie 0
}

int Circuit::positionOnImageToPixelValue(const QPointF& p_position)const{
    int i = floor(p_position.x());
    int j = floor(p_position.y());

    return qGray(m_track.pixel(i,j));
}
