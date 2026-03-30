//
// Created by Yonatan Rappoport on 30/03/2026.
//

#include "Camera.h"
Camera::Camera(const Point3D& c, const Point3D& f, const Point3D& u, const Point3D& r, const long double& d) :
        cam(c), forward(f), up(u), right(r), dis(d)
{
}

bool Camera::visible(const Point3D& p) const {
    Point3D v = p - cam;
    return (v*forward  >= -0.0001);
}

Point2D Camera::project(const Point3D& p) const {
    Point3D v = p - cam;
    Point3D c(v*right, v*up, v*forward);
    if(c.z == 0) return {0,0};

    return {dis*c.x/c.z, dis*c.y/c.z};
}