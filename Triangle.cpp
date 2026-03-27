//
// Created by Yonatan Rappoport on 08/06/2023.
//

#include "Triangle.h"
#include "Line.h"

Triangle::Triangle(const Point3D &point1, const Point3D &point2, const Point3D &point3) :
        m_vertex1(point1),
        m_vertex2(point2),
        m_vertex3(point3)
{

}

void Triangle::smartSweep(const std::function<void(const Point3D&)>& func) {
    Line edge(m_vertex1, m_vertex2);
    edge.smartSweep([&](const Point3D& point) {Line line(m_vertex3, point); line.smartSweep(func);});
}
