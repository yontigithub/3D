//
// Created by Yonatan Rappoport on 08/06/2023.
//


#include "Line.h"
#include "Utils.h"

Line::Line(const Point3D& point1, const Point3D& point2) :
        p1(point1),
        p2(point2)
{
}

void Line::smartSweep(const std::function<void(const Point3D&)>& func) {

    long double distance = p1.dis(p2);

    if (distance <= 0.0) {
        func(p1);
        return;
    }

    long double physicalStep = 0.02;
    long double dt = physicalStep / distance;

    for (long double t = 0.0; t <= 1.0; t += dt) {
        Point3D currentPoint = (t * p2) + ((1.0 - t) * p1);
        func(currentPoint);
    }
}
