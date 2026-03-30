//
// Created by Yonatan Rappoport on 06/06/2023.
//

#include "Point3D.h"
#include "Utils.h"
#include <cmath>


Point3D::Point3D(long double X, long double Y, long double Z) :
        x(X),
        y(Y),
        z(Z)
{
}

Point3D::Axis Point3D::getAxis_X() const {
    Axis result(*this, Point3D(1, 0, 0));
    return result;
}
Point3D::Axis Point3D::getAxis_Y() const  {
    Axis result(*this, Point3D(0, 1, 0));
    return result;
}
Point3D::Axis Point3D::getAxis_Z() const {
    Axis result(*this, Point3D(0, 0, 1));
    return result;
}

long double Point3D::dis(const Point3D& point) const {
    return sqrtl((x - point.x) * (x - point.x) +
                 (y - point.y) * (y - point.y) +
                 (z - point.z) * (z - point.z));
}

// todo: check rotation functions for translation to and from rotationPoint
void Point3D::rotateX(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.x = x;

    long double radius = this->dis(centerOfRotation);
    long double theta = atan2l(centerOfRotation.y - y, centerOfRotation.z - z);
    long double newAngle = theta + phi;

    long double newY = radius * sinl(newAngle);
    long double newZ = radius * cosl(newAngle); // might need to add centerOfRotation

    y = newY;
    z = newZ;
}
void Point3D::rotateY(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.y = y;

    long double radius = this->dis(centerOfRotation);
    long double theta = atan2l(centerOfRotation.x - x, centerOfRotation.z - z);
    long double newAngle = theta + phi;

    long double newX = radius * sinl(newAngle);
    long double newZ = radius * cosl(newAngle);

    x = newX;
    z = newZ;
}
void Point3D::rotateZ(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.z = z;

    long double radius = this->dis(centerOfRotation);
    long double theta = atan2l(centerOfRotation.y - y, centerOfRotation.x - x);
    long double newAngle = theta + phi;

    long double newY = radius * sinl(newAngle);
    long double newX = radius * cosl(newAngle);

    y = newY;
    x = newX;
}

void Point3D::rotate(const Axis& axis, long double phi) {
    Point3D v = *this - axis.m_org; // Translate to origin
    Point3D k = axis.m_dir;        // Assume axisDir is already normalized

    Point3D k_cross_v = crossProduct(k, v);

    long double k_dot_v = k * v;

    Point3D v_rot = (v * cosl(phi)) + (k_cross_v * sinl(phi)) + (k * k_dot_v * (1 - cosl(phi)));

    Point3D newPoint = v_rot + axis.m_org;
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
}

Point3D::Axis::Axis(const Point3D &org, const Point3D& dir) :
    m_org(org), m_dir(dir)
{
}



long double dis(const Point3D& p1, const Point3D& p2) {
    return p1.dis(p2);
}

Point3D rotateX(const Point3D& p, const Point3D& rot, long double phi) {
    Point3D pointCopy(p);
    pointCopy.rotateX(rot, phi);
    return pointCopy;
}
Point3D rotateY(const Point3D& p, const Point3D& rot, long double phi) {
    Point3D pointCopy(p);
    pointCopy.rotateY(rot, phi);
    return pointCopy;
}
Point3D rotateZ(const Point3D& p, const Point3D& rot, long double phi) {
    Point3D pointCopy(p);
    pointCopy.rotateZ(rot, phi);
    return pointCopy;
}
Point3D rotate(const Point3D& p, const Point3D::Axis& axis, long double phi) {
    Point3D pointCopy(p);
    pointCopy.rotate(axis, phi);
    return pointCopy;
}

Point3D Point3D::operator+(const Point3D &p) const {
    return {x + p.x, y + p.y, z + p.z};
}
Point3D Point3D::operator-(const Point3D &p) const {
    return {x - p.x, y - p.y, z - p.z};
}
Point3D Point3D::operator-() const {
    return {-x, -y, -z};
}
long double Point3D::operator*(const Point3D& p) const {
    return x * p.x + y * p.y + z * p.z;
}
Point3D Point3D::operator*(const long double& c) const {
    return {c * x, c * y, c * z};
}
Point3D& Point3D::operator+=(const Point3D& p) {
    Point3D newPoint = *this + p;
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
    return *this;
}
Point3D& Point3D::operator-=(const Point3D& p) {
    Point3D newPoint = *this - p;
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
    return *this;
}
Point3D& Point3D::operator*=(const long double& c) {
    Point3D newPoint = *this * c;
    x = newPoint.x;
    y = newPoint.y;
    z = newPoint.z;
    return *this;
}


Point3D operator*(const long double& c, const Point3D& p) {
    return p*c;
}

std::ostream& operator<<(std::ostream& os, const Point3D& p) {
    os << '(' << p.x << ", " << p.y << ", " << p.z << ')';
    return os;
}
Point3D crossProduct(const Point3D& p1, const Point3D& p2) {
    return {p1.y * p2.z - p1.z * p2.y,
            p1.z * p2.x - p1.x * p2.z,
            p1.x * p2.y - p1.y * p2.x};
}


Point2D Point3D::project() const {
    if(z == 0.0) return {10000, 10000};
    return {x / z, y / z};
}

Point3D& Point3D::normalize() {
    long double d = this->dis({0,0,0});
    if (d == 0) return *this;
    x/=d;
    y/=d;
    z/=d;
    return *this;
}
Point3D normalize(const Point3D& p) {
    Point3D pointCopy(p);
    pointCopy.normalize();
    return pointCopy;
}