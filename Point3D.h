//
// Created by Yonatan Rappoport on 06/06/2023.
//

#ifndef SPINNINGCUBE_POINT3D_H
#define SPINNINGCUBE_POINT3D_H

#include <iostream>
#include <vector>

class Point3D {
public:
    Point3D(long double x, long double y, long double z);
    Point3D(const Point3D& point) = default;
    ~Point3D() = default;

    [[nodiscard]] long double dis(const Point3D& point) const;

    class Axis;
    [[nodiscard]] Axis getAxis_X() const;
    [[nodiscard]] Axis getAxis_Y() const;
    [[nodiscard]] Axis getAxis_Z() const;

    void rotateX(const Point3D& rotationPoint, long double phi);
    void rotateY(const Point3D& rotationPoint, long double phi);
    void rotateZ(const Point3D& rotationPoint, long double phi);

    void rotate(const Axis& axis, long double phi);

    std::vector<long double> getCoords() const;

    Point3D operator+(const Point3D& p) const;
    Point3D operator-(const Point3D& p) const;
    Point3D operator-() const;
    long double operator*(const Point3D& p) const;
    Point3D operator*(const long double& c) const;
    Point3D& operator+=(const Point3D& p);
    Point3D& operator-=(const Point3D& p);
    Point3D& operator*=(const long double& c);


private:
    long double m_x, m_y, m_z;

    friend std::ostream& operator<<(std::ostream& os, const Point3D& point);

    friend Point3D crossProduct(const Point3D& p1, const Point3D& p2);
};

Point3D operator*(const long double& c, const Point3D& p);

class Point3D::Axis {
public:
    Axis(const Axis&) = default;

private:
    const Point3D m_org; // origin todo: shared-pointer
    const Point3D m_dir; // normal-vec

    Axis(const Point3D& org, const Point3D& dir);

    friend class Point3D;
};


long double dis(const Point3D&, const Point3D&);
Point3D rotateX(const Point3D& point, const Point3D& rotationPoint, long double phi);
Point3D rotateY(const Point3D& point, const Point3D& rotationPoint, long double phi);
Point3D rotateZ(const Point3D& point, const Point3D& rotationPoint, long double phi);
Point3D rotate(const Point3D& point, const Point3D::Axis& axis, long double phi);
#endif SPINNINGCUBE_POINT3D_H