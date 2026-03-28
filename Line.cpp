//
// Created by Yonatan Rappoport on 08/06/2023.
//


#include "Line.h"
#include "Utils.h"

Line::Line(const Point3D& point1, const Point3D& point2) :
        m_point1(point1),
        m_point2(point2)
{
}

void Line::smartSweep(const std::function<void(const Point3D&)>& func) {
    /*
    std::vector<long double> p = m_point1.getCoords(), q = m_point2.getCoords();

    long double sep;

    if (p[0] != q[0]) {
        if ((p[1] - q[1]) / (p[0] - q[0]) >= -1 && (p[1] - q[1]) / (p[0] - q[0]) <= 1) sep = 0.5;
        else sep = std::max(add, 1 / (3 * (abs((p[1] - q[1]) / (p[0] - q[0])))));

        for (long double x = std::min(q[0], p[0]); x <= std::max(p[0], q[0]);) {
            long double z = ((p[2] - q[2]) / (p[0] - q[0])) * (x - p[0]) + p[2];
            long double y = ((p[1] - q[1]) / (p[0] - q[0])) * (x - p[0]) + p[1];

            Point3D tmp(x, y, z);
            func(tmp);

            x += sep;
        }
    }
    else if (p[1] != q[1]) {
        if ((p[1] - q[1]) / (p[2] - q[2]) >= -1 && (p[1] - q[1]) / (p[2] - q[2]) <= 1) sep = 0.5;
        else sep = std::max(add, 1 / (3 * (abs((p[1] - q[1]) / (p[2] - q[2])))));

        long double x = p[0];

        for (long double y = std::min(p[1], q[1]); y <= std::max(p[1], q[1]);) {
            long double z = ((p[2] - q[2]) / (p[1] - q[1])) * (y - p[1]) + p[2];

            Point3D tmp(x,y,z);
            func(tmp);

            y += sep;
        }
    }
    else {
        sep = 0.5;
        long double x = p[0];
        long double y = p[1];

        for(long double z = std::min(p[0], q[0]); z < std::max(p[0], p[1]);) {
            Point3D tmp(x,y,z);
            func(tmp);

            z += sep;
        }
    }
     */

    long double distance = m_point1.dis(m_point2);

    if (distance <= 0.0) {
        func(m_point1);
        return;
    }

    long double physicalStep = 0.5;
    long double dt = physicalStep / distance;

    for (long double t = 0.0; t <= 1.0; t += dt) {
        Point3D currentPoint = (t * m_point2) + ((1.0 - t) * m_point1);
        func(currentPoint);
    }
}
