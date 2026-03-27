//
// Created by Yonatan Rappoport on 08/06/2023.
//

#ifndef SPINNINGCUBE_LINE_H
#define SPINNINGCUBE_LINE_H

#include <iostream>
#include "Point3D.h"
#include <functional>

class Line {
public:
    Line(const Point3D&, const Point3D&);
    Line(const Line&) = default;
    ~Line();

    void smartSweep(const std::function<void(const Point3D&)>& func);

private:
    Point3D m_point1, m_point2;
};

#endif //SPINNINGCUBE_LINE_H
