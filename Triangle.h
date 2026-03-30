//
// Created by Yonatan Rappoport on 08/06/2023.
//

#ifndef SPINNINGCUBE_TRIANGLE_H
#define SPINNINGCUBE_TRIANGLE_H

#include "Point3D.h"
#include <iostream>

class Triangle {
public:

    Triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3);
    Triangle(const Triangle&) = default;
    ~Triangle() = default;

    void smartSweep(const std::function<void(const Point3D&)>& func);

    [[nodiscard]] Point3D normal() const;

    Point3D p1, p2, p3;
};



#endif //SPINNINGCUBE_TRIANGLE_H
