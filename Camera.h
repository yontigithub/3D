//
// Created by Yonatan Rappoport on 30/03/2026.
//

#ifndef SPINNINGCUBERENDER_CAMERA_H
#define SPINNINGCUBERENDER_CAMERA_H

#include "Point3D.h"
#include "Utils.h"

class Camera {
public:
    Camera(const Point3D& c, const Point3D& f = {0,0,1}, const Point3D& u = {0,1,0}, const Point3D& r = {1,0,0}, const long double& d = 1);
    Camera(const Camera&) = default;
    ~Camera() = default;

    [[nodiscard]] bool visible(const Point3D& p) const;
    Point2D project(const Point3D& p) const;

    Point3D cam;
    Point3D forward, up, right;
    long double dis;
};


#endif //SPINNINGCUBERENDER_CAMERA_H
