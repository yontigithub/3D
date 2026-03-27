//
// Created by Yonatan Rappoport on 06/12/2023.
//

#include <iostream>
#include "Object3D.h"
#include "Triangle.h"

Object3D::Object3D(Point3D** points) : m_points(points) {}

void Object3D::rotate(const Point3D& rotationPoint, const long double& x_phi, const long double& y_phi, const long double& z_phi) {
    for (int i = 0; m_points[i] != nullptr; ++i) {
        m_points[i]->rotateX(rotationPoint, x_phi);
        m_points[i]->rotateY(rotationPoint, y_phi);
        m_points[i]->rotateZ(rotationPoint, z_phi);
    }
}

void Object3D::rotate(const Point3D::Axis &axis, const long double& phi) {
    for (int i = 0; m_points[i] != nullptr; ++i) {
        m_points[i]->rotate(axis, phi);
        m_points[i]->rotate(axis, phi);
        m_points[i]->rotate(axis, phi);
    }
}

int Object3D::getLen() const {
    int ans = 0;
    for (; m_points[ans] != nullptr; ++ans);
    return ans;
}

void Object3D::Sweep(const std::function<void(const Point3D&)>& func) {
    int l = getLen();

    for (int k1 = 0; k1 < l - 2; ++k1) {
        for (int k2 = 0; k2 < l - 1; ++k2) {
            for (int k3 = 0; k3 < l; ++k3) {
                Triangle t(*m_points[k1], *m_points[k2], *m_points[k3]);
                t.smartSweep(func);
            }
        }
    }
}