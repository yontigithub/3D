//
// Created by Yonatan Rappoport on 30/03/2026.
//

#include "Mesh.h"
#include <fstream>
#include <strstream>

Mesh::Mesh(const std::vector<Point3D>& vertices, const std::vector<std::vector<int>>& indices) : vtx(vertices), idx(indices){

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
                pixel(page, screen(Cam.project(point)), c);
            });
        }
    }
}

bool Mesh::loadMesh(const std::string& str) {
    std::ifstream f(str);
    if (!f.is_open()) return false;

    while(!f.eof()) {
        char line[128];
        f.getline(line, 128);
        std::strstream s;
        s << line;
        char junk;
        if (line[0] == 'v') {
            Point3D p;
            s >> junk >> p.x >> p.y >> p.z;
            vtx.push_back(p);
        } else if (line[0] == 'f') {
            int a,b,c;
            s >> junk >> a >> b >> c;
            idx.push_back({a-1,b-1,c-1});
        }
    }

    return true;
}