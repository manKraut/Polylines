#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <stdexcept>
using namespace std;
typedef std::pair<double, double> Point;

void RamerDouglasPeucker(const vector<Point> &pointList, double epsilon, vector<Point> &out);
