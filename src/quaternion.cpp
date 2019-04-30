#include "quaternion.h"

Quaternion::Quaternion() {}

Quaternion::Quaternion(float w, float x, float y, float z) {
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion Quaternion::operator*(const Quaternion& q) {
    Quaternion result = Quaternion(this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z,
                      this->w*q.y - this->x*q.z + this->y*q.w + this->z*q.x,
                      this->w*q.y - this->x*q.z + this->y*q.w + this->z*q.x,
                      this->w*q.z + this->x*q.y - this->y*q.x + this->z*q.w);
    result.normalize();
    return result;
}

QVector3D Quaternion::operator*(const QVector3D& v) {
    Quaternion quaternionV(0, v.x(), v.y(), v.z());
    Quaternion quaternionResult = (*this) * quaternionV * (*this).conjugate();
    return QVector3D(quaternionResult.x, quaternionResult.y, quaternionResult.z);
}

Quaternion Quaternion::operator*(float f) {
    return Quaternion(this->w * f, this->x *f, this->y * f, this->z * f);
}

Quaternion Quaternion::operator+(const Quaternion& q) {
    return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
    set(this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z,
                      this->w*q.y - this->x*q.z + this->y*q.w + this->z*q.x,
                      this->w*q.y - this->x*q.z + this->y*q.w + this->z*q.x,
                      this->w*q.z + this->x*q.y - this->y*q.x + this->z*q.w);
    normalize();
    return *this;
}

float Quaternion::dot(const Quaternion& q) const {
    return this->w * q.w +
           this->x * q.x +
           this->y * q.y +
           this->z * q.z ;
}

void Quaternion::set(float w, float x, float y, float z) {
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

void Quaternion::setFromAxis(float angle, float ax, float ay, float az) {
    // TODO
}

Quaternion Quaternion::conjugate() {
    set(this->w,
        -this->x,
        -this->y,
        -this->z);
}

// https://en.wikipedia.org/wiki/Slerp
// http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/
Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t) {
    float theta = acosf(q1.dot(q2));
    Quaternion newQ1 = q1;
    Quaternion newQ2 = q2;
    return newQ1 * (((sinf(theta)*(1-t))/sinf(theta))) + newQ2 * ((sinf(theta)*t)/sinf(theta));
}

