//
// Created by Yonatan Rappoport on 30/03/2026.
//

#include "Mesh.h"

Mesh::Mesh(const std::vector<Point3D>& vertices, const std::vector<std::vector<int>>& indices) :
vtx(vertices), idx(indices)
{
}

void Mesh::rotate(const Point3D::Axis& axis, long double phi) {
    for (auto& v : vtx)
        v.rotate(axis, phi);
}

void Mesh::translate(const Point3D& p) {
    for (auto& v : vtx)
        v += p;
}

void Mesh::render(char page[PAGE_HEIGHT][PAGE_WIDTH + 1], const Camera& Cam, const Point3D& light_source, const Point3D& trans) const {
    for (auto& t : idx) {
        Triangle tri(vtx[t[0]]+trans, vtx[t[1]]+trans, vtx[t[2]]+trans);
        Point3D n = tri.normal();
        if (n*(tri.p1 - Cam.cam) < 0.0) {
            char c = light[std::min((int)ceil(((n * light_source) + 1.0)/2.0 * 11.0), 11)];

            tri.smartSweep([&Cam, c, &page](const Point3D& point){
                auto a = screen(Cam.project(point));
                page[(int)ceil(a.second)][(int)ceil(a.first)] = c;
            });
        }
    }
}