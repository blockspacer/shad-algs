#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include <algorithm>


/* INPUT
 5
 1 3
 3 1
 5 8
 8 19
 10 15
 */

const double EPS = 1e-12;

struct Point {
    
    
    double x_axis;
    double y_axis;
};

struct x_axis_intersections {
    
    
    double value;
    bool is_left;
    bool is_right;
    bool operator<(const struct x_axis_intersections& other) {
        
        
        return value < other.value;
    }
};

bool operator< (const struct x_axis_intersections& other,
                const struct x_axis_intersections& another) {
    
    
    return other.value < another.value;
}

bool get_intersections(const struct Point pt, double radius,
                       struct x_axis_intersections* left,
                       struct x_axis_intersections* right) {
    
    
    double help = radius * radius - pt.y_axis * pt.y_axis;
    if (help < 0) {
        return false;
    } else {
        left->is_left = true;
        left->is_right = false;
        right->is_right = true;
        right->is_left = false;
        left->value = pt.x_axis - sqrt(help);
        right->value = pt.x_axis + sqrt(help);
    }
    return true;
}


bool check_if_such_radius_is_possible(const std::vector<Point>& points,
                                      double radius, size_t num_to_cover) {
    
    
    size_t counter = 0;
    std::vector<struct x_axis_intersections> intersections;
    x_axis_intersections left, right;
    for (auto elem : points) {
        if (get_intersections(elem, radius, &left, &right)) {
            intersections.push_back(left);
            intersections.push_back(right);
        }
    }
    // std::cout << "radius is " << radius << '\n';
    std::sort(intersections.begin(), intersections.end());
//    for (auto elem : intersections) {
//        std::cout << elem.value << (elem.is_left ? " is_left " : " is_right ");
//    }
//    std::cout << '\n';
    for (auto elem : intersections) {
        if ((elem.is_left) && (!elem.is_right)) {
            ++counter;
        } else if ((elem.is_right) && (!elem.is_left)) {
            --counter;
        }
        if (counter == num_to_cover) {
            return true;
        }
    }
    return false;
}


void read_points(std::vector<Point>* points, size_t* num_to_cover) {
    size_t num_of_points;
    std::cin >> num_of_points >> *num_to_cover;
    points->resize(num_of_points);
    for (size_t i = 0; i < num_of_points; ++i) {
        std::cin >> (*points)[i].x_axis >> (*points)[i].y_axis;
    }
}


void TaskFunc() {
    
    
    std::vector<Point> points;
    size_t num_to_cover;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    read_points(&points, &num_to_cover);
    double radius_l = 0.0;
    double radius_r = 1500.0;
    double middle = 0.0;
    while (!(fabs(radius_l - radius_r) < EPS)) {
        middle = radius_l + (radius_r - radius_l) / 2.0;
        if (check_if_such_radius_is_possible(points, middle, num_to_cover)) {
            radius_r = middle;
        } else {
            radius_l = middle;
        }
    }
    std::cout.precision(6);
    std::cout << std::fixed;
    std::cout << radius_l << '\n';
}


int main() {
    
    
    TaskFunc();
    return 0;
}
