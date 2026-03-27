#include <iostream>

#include "Point3D.h"
#include "Utils.h"
#include "Triangle.h"
#include "Object3D.h"
#include <cmath>


long double C[8][3] = { {10,20,10},{30,20,10},{10,40,10},{30,40,10},{10,20,30},{30,20,30},{10,40,30},{30,40,30} };
//const long double O[3] = { 20,30,20 };

void filll_zis(long double zis[PAGE_HEIGHT][PAGE_WIDTH], int d) {
    for (int i = 0; i < PAGE_HEIGHT; ++i) {
        for (int j = 0; j < PAGE_WIDTH; ++j) {
            zis[i][j] = d;
        }
    }
}

void clear_page(char page[PAGE_HEIGHT][PAGE_WIDTH]) {
    for (int i = 0; i < PAGE_HEIGHT; ++i) {
        for (int j = 0; j < PAGE_WIDTH; ++j) {
            page[i][j] = ' ';
        }
    }
}
void print_page(char page[PAGE_HEIGHT][PAGE_WIDTH]) {
    for (int i = 0; i < PAGE_HEIGHT; ++i) {
        for (int j = 0; j < PAGE_WIDTH; ++j) {
            std::cout << page[i][j];
        }
        std::cout << '\n';
    }
}

int main() {
    char page[PAGE_HEIGHT][PAGE_WIDTH];
    long double zis[PAGE_HEIGHT][PAGE_WIDTH];
    clear_page(page);
    filll_zis(zis, -10000);

    Point3D p1(5, 5, 0), p2(15, 14, 0), p3(3, 12, 0), p4(5, 5, 2);

    Triangle T(p1, p2, p3);


    Point3D** P = new Point3D*[5];

    P[0] = &p1; P[1] = &p2; P[2] = &p3; P[3] = &p4; P[4] = nullptr;

    Object3D O(P);

    O.Sweep([&page, &zis](const Point3D& point) {
        if (point.getCoords()[2] > zis[(int)ceil(point.getCoords()[0])][(int)ceil(point.getCoords()[1])]) {
            page[(int)ceil(point.getCoords()[0])][(int)ceil(point.getCoords()[1])] = 'a';
        }
    });

    char c = 'a';
    /*T.smartSweep([c, &page](const Point3D& point){
        page[(int)ceil(point.getCoords()[0])][(int)ceil(point.getCoords()[1])] = c;
    });
*/



    print_page(page);
    return 0;
}
