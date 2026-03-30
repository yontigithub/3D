//
// Created by Yonatan Rappoport on 08/06/2023.
//

#include "Triangle.h"
#include "Line.h"
#include "Point3D.h"

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3) :
        p1(p1),
        p2(p2),
        p3(p3)
{
}

void Triangle::smartSweep(const std::function<void(const Point3D&)>& func) {
    Line edge(p1, p2);
    edge.smartSweep([&](const Point3D& p) {Line line(p3, p); line.smartSweep(func);});
}

Point3D Triangle::normal() const {
    return crossProduct(p2 - p1, p3 - p1).normalize();
}