#ifndef QUATERNION_H
#define QUATERNION_H

#include <QVector3D>
#include "math.h"

class Quaternion
{
private:
    float w,x,y,z;
public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion operator*(const Quaternion& q);
    QVector3D operator*(const QVector3D& v);
    Quaternion operator*(float f);
    Quaternion operator+(const Quaternion& q);
    Quaternion& operator*=(const Quaternion& q);
    float dot(const Quaternion& q) const;
    void set(float w, float x, float y, float z);
    void setFromAxis(float angle, float ax, float ay, float az);
    Quaternion conjugate();
    Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
    float norm();
    void normalize();
    void setRotationMatrix(float mat);
};

#endif // QUATERNION_H
