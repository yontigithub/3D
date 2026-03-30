//
// Created by Yonatan Rappoport on 15/06/2023.
//

#ifndef SPINNINGCUBE_UTILS_H
#define SPINNINGCUBE_UTILS_H

const long double add = 0.005;
const unsigned short PAGE_WIDTH = 160, PAGE_HEIGHT = 160;

typedef std::pair<long double, long double> Point2D;

static int to_pos(long double x, int Max) {
    return std::max(std::min((int)ceil(x),Max-1),0);
}
static std::pair<int, int> screen(Point2D p) {
    return {to_pos((1 - (p.second + 1)/2)*PAGE_HEIGHT, PAGE_HEIGHT), to_pos((p.first + 1)/2*PAGE_WIDTH, PAGE_WIDTH)};
}

const std::string light = ".,-~:;=!*#$@";

#endif //SPINNINGCUBE_UTILS_H
