//
// Created by Yonatan Rappoport on 30/03/2026.
//

#ifndef SPINNINGCUBERENDER_MESH_H
#define SPINNINGCUBERENDER_MESH_H

#include "Point3D.h"
#include "Utils.h"
#include "Triangle.h"
#include "Camera.h"
#include "Line.h"
#include <vector>

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Point3D>& vertices, const std::vector<std::vector<int>>& indices);
    Mesh(const Mesh&) = default;
    ~Mesh() = default;

    void rotate(const Point3D::Axis& axis, long double phi);
    void translate(const Point3D& p);
    void render(char page[PAGE_HEIGHT][PAGE_WIDTH + 1], const Camera& Cam, const Point3D& light_source = {-1,-1,-1}, const Point3D& trans = {0,0,0}) const;

    bool loadMesh(const std::string& str);

    std::vector<Point3D> vtx;
    std::vector<std::vector<int>> idx;
};


#endif //SPINNINGCUBERENDER_MESH_H
