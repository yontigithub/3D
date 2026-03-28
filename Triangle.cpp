//
// Created by Yonatan Rappoport on 08/06/2023.
//

#include "Triangle.h"
#include "Line.h"

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3) :
        m_p1(p1),
        m_p2(p2),
        m_p3(p3)
{

}

void Triangle::smartSweep(const std::function<void(const Point3D&)>& func) {
    Line edge(m_p1, m_p2);
    edge.smartSweep([&](const Point3D& p) {Line line(m_p3, p); line.smartSweep(func);});
}
