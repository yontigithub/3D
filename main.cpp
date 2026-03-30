#include <iostream>
#include "Point3D.h"
#include "Utils.h"
#include "Triangle.h"
#include "Camera.h"
#include "Line.h"
#include "Mesh.h"
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

    Point3D light_source(1,1,-1); light_source.normalize();
    Camera Cam(Point3D(0,0,0));

    std::vector<Point3D> dodeca({{-1.00000000,-1.00000000,-1.00000000},{-1.00000000,-1.00000000,1.00000000},{-1.00000000,1.00000000,-1.00000000},{-1.00000000,1.00000000,1.00000000},{1.00000000,-1.00000000,-1.00000000},{1.00000000,-1.00000000,1.00000000},{1.00000000,1.00000000,-1.00000000},{1.00000000,1.00000000,1.00000000},{0.00000000,-1.61803399,-0.61803399},{0.00000000,-1.61803399,0.61803399},{0.00000000,1.61803399,-0.61803399},{0.00000000,1.61803399,0.61803399},{-0.61803399,0.00000000,-1.61803399},{-0.61803399,0.00000000,1.61803399},{0.61803399,0.00000000,-1.61803399},{0.61803399,0.00000000,1.61803399},{-1.61803399,-0.61803399,0.00000000},{-1.61803399,0.61803399,0.00000000},{1.61803399,-0.61803399,0.00000000},{1.61803399,0.61803399,0.00000000}});
    std::vector<std::vector<int>> faces({{0,8,9,1,16},{0,12,14,4,8},{0,16,17,2,12},{12,2,10,6,14},
                                         {10,11,7,19,6},{14,6,19,18,4},{17,3,11,10,2},{11,3,13,15,7},
                                         {19,7,15,5,18},{4,18,5,9,8},{1,9,5,15,13},{17,16,1,13,3}});
    std::vector<std::vector<int>> triangles = triangulate_dodecahedron(faces);

    //Mesh mesh(dodeca, triangles);
    Mesh mesh;
    if(!mesh.loadMesh("../VideoShip.obj")) {
        std::cout << "no file found" <<'\n';
        exit(0);
    }



    long double dx = 0.0;
    while(true) {

        mesh.render(page, Cam, light_source, {dx,0,6});
        dx += 0.005;

        std::cout << "\x1b[0;0H";
        print_page(page);
        clear_page(page);

        mesh.rotate(Point3D::Axis({0,0,0},{0,1,0}), 0.01);
        mesh.rotate(Point3D::Axis({0,0,0},{1,0,0}), 0.003);
       // mesh.rotate(Point3D::Axis({0,0,0},{0,0,1}), 0.015);

        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return 0;
}
