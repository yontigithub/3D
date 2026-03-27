//
// Created by Yonatan Rappoport on 06/06/2023.
//

#include "Point3D.h"
#include "Utils.h"
#include <cmath>


Point3D::Point3D(long double x, long double y, long double z) :
    m_x(x),
    m_y(y),
    m_z(z)
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
    return sqrtl((m_x - point.m_x)*(m_x - point.m_x) +
                 (m_y - point.m_y)*(m_y - point.m_y) +
                 (m_z - point.m_z)*(m_z - point.m_z));
}

void Point3D::rotateX(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.m_x = m_x;

    long double radius = this->dis(centerOfRotation);
    long double theta = atanl((centerOfRotation.m_y - m_y) / (centerOfRotation.m_z - m_z));
    long double newAngle = theta + phi;

    long double newY = radius * sinl(newAngle);
    long double newZ = radius * cosl(newAngle);

    m_y = newY;
    m_z = newZ;
}
void Point3D::rotateY(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.m_y = m_y;

    long double radius = this->dis(centerOfRotation);
    long double theta = atanl((centerOfRotation.m_x - m_x) / (centerOfRotation.m_z - m_z));
    long double newAngle = theta + phi;

    long double newX = radius * sinl(newAngle);
    long double newZ = radius * cosl(newAngle);

    m_x = newX;
    m_z = newZ;
}
void Point3D::rotateZ(const Point3D& rotationPoint, long double phi) {
    Point3D centerOfRotation(rotationPoint);
    centerOfRotation.m_z = m_z;

    long double radius = this->dis(centerOfRotation);
    long double theta = atanl((centerOfRotation.m_y - m_y) / (centerOfRotation.m_x - m_x));
    long double newAngle = theta + phi;

    long double newY = radius * sinl(newAngle);
    long double newX = radius * cosl(newAngle);

    m_y = newY;
    m_x = newX;
}

Point3D Point3D::rotate(const Axis& axis, long double phi) const {
    Point3D v = *this - axis.m_org; // Translate to origin
    Point3D k = axis.m_dir;        // Assume axisDir is already normalized

    Point3D k_cross_v = crossProduct(k, v);

    long double k_dot_v = k * v;

    Point3D v_rot = (v * cos(phi)) + (k_cross_v * sin(phi)) + (k * k_dot_v * (1 - cos(phi)));

    return v_rot + axis.m_org;
}

Point3D::Axis::Axis(const Point3D& org, const Point3D& dir) :
    m_org(org), m_dir(dir)
{
}



long double dis(const Point3D& point1, const Point3D& point2) {
    return point1.dis(point2);
}

Point3D rotateX(const Point3D& point, const Point3D& rotationPoint, long double phi) {
    Point3D pointCopy(point);
    pointCopy.rotateX(rotationPoint, phi);
    return pointCopy;
}
Point3D rotateY(const Point3D& point, const Point3D& rotationPoint, long double phi) {
    Point3D pointCopy(point);
    pointCopy.rotateY(rotationPoint, phi);
    return pointCopy;
}
Point3D rotateZ(const Point3D& point, const Point3D& rotationPoint, long double phi) {
    Point3D pointCopy(point);
    pointCopy.rotateZ(rotationPoint, phi);
    return pointCopy;
}

long double* Point3D::getCoords() const {
    long double* coordinates = new long double[3];
    coordinates[0] = m_x;
    coordinates[1] = m_y;
    coordinates[2] = m_z;

    return coordinates;
}

Point3D Point3D::operator+(const Point3D &p) const {
    return {m_x + p.m_x, m_y + p.m_y, m_z + p.m_z};
}
Point3D Point3D::operator-(const Point3D &p) const {
    return {m_x - p.m_x, m_y - p.m_y, m_z - p.m_z};
}
Point3D Point3D::operator-() const {
    return {-m_x, -m_y, -m_z};
}
long double Point3D::operator*(const Point3D& p) const {
    return m_x*p.m_x + m_y*p.m_y + m_z*p.m_z;
}
Point3D Point3D::operator*(const long double& c) const {
    return {c*m_x,c*m_y,c*m_z};
}

Point3D operator*(const long double& c, const Point3D& p) {
    return p*c;
}

std::ostream& operator<<(std::ostream& os, const Point3D& point) {
    os << '(' << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
    return os;
}
Point3D crossProduct(const Point3D& p1, const Point3D& p2) {
    return {p1.m_y*p2.m_z-p1.m_z*p2.m_y,
            p1.m_z*p2.m_x-p1.m_x*p2.m_z,
            p1.m_x*p2.m_y-p1.m_x*p2.m_y};
}