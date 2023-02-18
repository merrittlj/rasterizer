#include <cstdlib>
#include <cmath>
#include <SDL2/SDL.h>
#include "line_renderer.h"
#include "point_controller.h"
#include "common.h"

void draw_line(SDL_Renderer* renderer, point_2d point_0, point_2d point_1)  // TODO: refactor and implement bresenham's algorithm
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int x0 = point_0.get_x();
    int y0 = point_0.get_y();
    int x1 = point_1.get_x();
    int y1 = point_1.get_y();
    // if the change in x is bigger than the change in y(line is more horizontal)
    if (abs(x1 - x0) > abs(y1 - y0)) {
        // ensure x0 < x1
        if (x0 > x1) {
            std::swap(x0, x1);
        }

        std::vector<int> ys = interpolate(x0, y0, x1, y1);
        for (auto x = x0; x < x1; x++) {
            // translate coordinates to proper system
            int ys_value = x - x0 < ys.size() ? ys.at(x - x0) : 0;
            int translated_x = (480/2) + x;
            int translated_y = (480/2) - ys_value;
            SDL_RenderDrawPoint(renderer, translated_x, translated_y);
        }
    } else {  // line is more vertical
        // ensure y0 < y1
        if (y0 > y1) {
            std::swap(y0, y1);
        }

        std::vector<int> xs = interpolate(y0, x0, y1, x1);
        for (auto y = y0; y < y1; y++) {
            // translate coordinates to proper system
            int xs_value = y - y0 < xs.size() ? xs.at(y - y0) : 0;
            int translated_x = (480/2) + xs_value;
            int translated_y = (480/2) - y;
            SDL_RenderDrawPoint(renderer, translated_x, translated_y);
        }
    }
}

void draw_wireframe_triangle(SDL_Renderer* renderer, point_2d point_0, point_2d point_1, point_2d point_2)
{
    draw_line(renderer, point_0, point_1);
    draw_line(renderer, point_1, point_2);
    draw_line(renderer, point_2, point_0);
}

void draw_filled_triangle(SDL_Renderer* renderer, point_2d point_0, point_2d point_1, point_2d point_2)
{
    // ensure y0 <= y1 <= y2
    if (point_1.get_y() < point_0.get_y()) {
        std::swap(point_1, point_0);
    }
    if (point_2.get_y() < point_0.get_y()) {
        std::swap(point_2, point_0);
    }
    if (point_2.get_y() < point_1.get_y()) {
        std::swap(point_2, point_1);
    }
    // proper value fetch
    int x0 = point_0.get_x();
    int y0 = point_0.get_y();
    int x1 = point_1.get_x();
    int y1 = point_1.get_y();
    int x2 = point_2.get_x();
    int y2 = point_2.get_y();

    // x values between two points
    std::vector<int> x_01 = interpolate(y0, x0, y1, x1);
    std::vector<int> x_12 = interpolate(y1, x1, y2, x2);
    std::vector<int> x_02 = interpolate(y0, x0, y2, x2);

    // concatenate x_01 and x_12(short sides)
    x_01.pop_back();
    x_01.insert(x_01.end(), x_12.begin(), x_12.end());

    int m = floor(x_01.size() / 2);  // middle horizontal line
    std::vector<int> x_left;  // left of horizontal line
    std::vector<int> x_right;  // right of horizontal line
    if (x_02.at(m) < x_01.at(m)) {
        x_left = x_02;
        x_right = x_01;
    } else {
        x_left = x_01;
        x_right = x_02;
    }

    for (int y = y0; y < y2; y++) {
        for (x = x_left.at(y - y0); x < x_right.at(y - y0); x++) {
            // canvas pixel placement
        }
    }
}
