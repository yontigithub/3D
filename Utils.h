//
// Created by Yonatan Rappoport on 15/06/2023.
//

#ifndef SPINNINGCUBE_UTILS_H
#define SPINNINGCUBE_UTILS_H

const long double add = 0.005;
const unsigned short PAGE_WIDTH = 260, PAGE_HEIGHT = 260;

typedef std::pair<long double, long double> Point2D;

static std::pair<int, int> screen(const Point2D& p) {
    return {(int)ceil((1 - (p.second + 1)/2)*PAGE_HEIGHT), (int)ceil((p.first + 1)/2*PAGE_WIDTH)};
}

static void pixel(char page[PAGE_HEIGHT][PAGE_WIDTH + 1], const std::pair<int, int>& p, const char& c) {
    if (p.first < 0 || p.first >= PAGE_HEIGHT || p.second < 0 || p.second >= PAGE_WIDTH) return;
    page[p.first][p.second] = c;
}


const std::string light = ".,-~:;=!*#$@";

#endif //SPINNINGCUBE_UTILS_H
