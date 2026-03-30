#include <iostream>
#include "Point3D.h"
#include "Utils.h"
#include "Triangle.h"
#include "Camera.h"
#include "Line.h"
#include <cmath>
#include <thread>
#include <chrono>

void clear_page(char page[PAGE_HEIGHT][PAGE_WIDTH+1]) {
    for (int i = 0; i < PAGE_HEIGHT; ++i)
        for (int j = 0; j < PAGE_WIDTH; ++j)
            page[i][j] = ' ';
}

void print_page(char page[PAGE_HEIGHT][PAGE_WIDTH+1]) {
    std::cout << &page[0][0];
}

void init(char page[PAGE_HEIGHT][PAGE_WIDTH+1]) {
    clear_page(page);
    for (int i = 0; i < PAGE_HEIGHT - 1; ++i) page[i][PAGE_WIDTH] = '\n';
    page[PAGE_HEIGHT - 1][PAGE_WIDTH] = '\0';
}

int to_pos(long double x, int Max) {
    return std::max(std::min((int)ceil(x),Max-1),0);
}

std::pair<int, int> screen(Point2D p) {
    return {to_pos((1 - (p.second + 1)/2)*PAGE_HEIGHT, PAGE_HEIGHT), to_pos((p.first + 1)/2*PAGE_WIDTH, PAGE_WIDTH)};
}

std::vector<std::vector<int>> triangulate_dodecahedron(const std::vector<std::vector<int>> &faces) {
    std::vector<std::vector<int>> ans;
    for (auto& v : faces) {
        ans.push_back({v[0],v[1],v[2]});
        ans.push_back({v[2],v[3],v[0]});
        ans.push_back({v[3],v[4],v[0]});
    }
    return ans;
}

int main() {
    char page[PAGE_HEIGHT][PAGE_WIDTH+1];
    init(page);

    // definitions
    std::string light = ".,-~:;=!*#$@";

    Point3D light_source(-1,-1,-1); light_source.normalize();
    Camera Cam({0,0,0});

    std::vector<Point3D> dodeca({{-1.00000000,-1.00000000,-1.00000000},{-1.00000000,-1.00000000,1.00000000},{-1.00000000,1.00000000,-1.00000000},{-1.00000000,1.00000000,1.00000000},{1.00000000,-1.00000000,-1.00000000},{1.00000000,-1.00000000,1.00000000},{1.00000000,1.00000000,-1.00000000},{1.00000000,1.00000000,1.00000000},{0.00000000,-1.61803399,-0.61803399},{0.00000000,-1.61803399,0.61803399},{0.00000000,1.61803399,-0.61803399},{0.00000000,1.61803399,0.61803399},{-0.61803399,0.00000000,-1.61803399},{-0.61803399,0.00000000,1.61803399},{0.61803399,0.00000000,-1.61803399},{0.61803399,0.00000000,1.61803399},{-1.61803399,-0.61803399,0.00000000},{-1.61803399,0.61803399,0.00000000},{1.61803399,-0.61803399,0.00000000},{1.61803399,0.61803399,0.00000000}});
    std::vector<std::vector<int>> faces({{0,8,9,1,16},{0,12,14,4,8},{0,16,17,2,12},{12,2,10,6,14},
                                         {10,11,7,19,6},{14,6,19,18,4},{17,3,11,10,2},{11,3,13,15,7},
                                         {19,7,15,5,18},{4,18,5,9,8},{1,9,5,15,13},{17,16,1,13,3}});



    std::vector<std::vector<int>> triangles = triangulate_dodecahedron(faces);


    long double dz = 4.0;
    while(true) {
       /* for (auto &v: faces) {
            for (int i = 0; i < v.size(); ++i) {
                Line a(dodeca[v[i]], dodeca[v[(i + 1) % ((int) v.size())]]);

                a.smartSweep([&Cam, &dz, &page](const Point3D &point) {
                   if (Cam.visible(point)) {
                        auto a = screen(Cam.project(point + Point3D(0, 0, dz)));
                        page[a.first][a.second] = '#';
                   }
                });
            }
            //Cam.cam.x -= 0.001;
            //dz += 0.0001;
        }*/

        for (int i = 0; i < (int)triangles.size(); ++i) {
            Point3D a(0,0,dz);
            Triangle tri(dodeca[triangles[i][0]]+a, dodeca[triangles[i][1]]+a, dodeca[triangles[i][2]]+a);
            Point3D n = tri.normal();
            if (n*(tri.p1 - Cam.cam) < 0.0) {
                //char c = light[std::min((int)ceil(((n * light_source) + 1.0)/2.0 * 11.0), 11)];
                char c = light[i/3];
                tri.smartSweep([&Cam, c, &page](const Point3D& point){
                    auto a = screen(Cam.project(point));

                    page[(int)ceil(a.second)][(int)ceil(a.first)] = c;
                });

                /*Line lines[3] = {{tri.p1, tri.p2}, {tri.p2, tri.p3}, {tri.p3, tri.p1}};
                for (auto & line : lines) {
                    line.smartSweep([&Cam, &dz, &page](const Point3D &point) {
                        auto a = screen(Cam.project(point));
                        page[a.first][a.second] = '#';
                    });
                }*/
            }
        }


        std::cout << "\x1b[0;0H";
        print_page(page);
        clear_page(page);

        for (auto& p : dodeca) p.rotate(Point3D::Axis({0,0,0},{0,1,0}), 0.01);
        for (auto& p : dodeca) p.rotate(Point3D::Axis({0,0,0},{1,0,0}), 0.005);

        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return 0;
}
