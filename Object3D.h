//
// Created by Yonatan Rappoport on 17/06/2023.
//

#ifndef SPINNINGCUBE_OBJECT3D_H
#define SPINNINGCUBE_OBJECT3D_H

#include "Point3D.h"
#include <functional>

class Object3D {
public:
    explicit Object3D(Point3D** points);

    void rotate(const Point3D& rotationPoint, const long double& x_phi, const long double& y_phi, const long double& z_phi);
    void rotate(const Point3D::Axis& axis, const long double& phi);
    void Sweep(const std::function<void(const Point3D&)>& func);
    [[nodiscard]] int getLen() const;

private:
    Point3D** m_points;
};

#endif //SPINNINGCUBE_OBJECT3D_H
