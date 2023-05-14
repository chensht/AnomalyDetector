/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "minCircle.h"

// Function to return the euclidean distance
// between two points
float dist(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle& c, const Point& p) {
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
Point get_circle_center(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return { (cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D) };
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point& A, const Point& B, const Point& C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return { I, dist(I, A) };
}

Circle circle_from(const Point& A, const Point& B) {
    float x = (A.x + B.x) / 2;
    float y = (A.y + B.y) / 2;
    Point p = Point(x,y);
    return { p, dist(A, B) / 2 };
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle& c, const vector<Point>& P) {
    // Iterating through all the points
    // to check  whether the points
    // lie inside the circle or not
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point>& P) {
    assert(P.size() <= 3);
    if (P.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (P.size() == 1) {
        return { P[0], 0 };
    }
    else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }
    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(vector<Point>& P, vector<Point> R, int n) {
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }
    // Pick a random point randomly
    int idx = rand() % n;
    Point p = P[idx];
    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);
    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = welzl_helper(P, R, n - 1);
    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }
    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);
    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(P, R, n - 1);
}

Circle findMinCircle(Point** points,size_t size) {
    vector<Point> P_copy;
    for ( int i = 0; i < size; ++i) {
        float &xP = points[i]->x;
        float &yP = points[i]->y;
        Point tempPoint = Point(xP, yP);
        P_copy.push_back(tempPoint);
    }
    random_shuffle(P_copy.begin(), P_copy.end());
    return welzl_helper(P_copy, {}, P_copy.size());
}