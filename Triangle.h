//
// Created by Yonatan Rappoport on 08/06/2023.
//

#ifndef SPINNINGCUBE_TRIANGLE_H
#define SPINNINGCUBE_TRIANGLE_H

#include "Point3D.h"
#include <iostream>

class Triangle {
public:

    Triangle(const Point3D& point1, const Point3D& point2, const Point3D& point3);
    Triangle(const Triangle&) = default;
    ~Triangle() = default;

    void smartSweep(const std::function<void(const Point3D&)>& func);

private:
    Point3D m_vertex1, m_vertex2, m_vertex3;
};



#endif //SPINNINGCUBE_TRIANGLE_H
