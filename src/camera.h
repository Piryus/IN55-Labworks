#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix>
#include "quaternion.h"

class Camera
{
private:
    QVector3D m_Position;
    Quaternion m_Orientation;
    QMatrix m_ViewMatrix;
    QMatrix m_ProjectionMatrix;
public:
    Camera();
    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);
    void rotate(float angle, float ax, float ay, float az);
    void rotateX(float angle);
    void roatateY(float angle);
    void rotateZ(float angle);
    const QMatrix& getViewMatrix();
    void setAspectRatio(float ar);
    void setPlanes(float np, float fp);
    void setFOV(float angle);
    const QMatrix& getProjectionMatrix();
protected:
    void buildViewMatrix();
    void buildProjectionMatrix();
};

#endif // CAMERA_H
