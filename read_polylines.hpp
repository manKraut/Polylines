#include <cstdlib>
#include <string>
#include <vector>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>

using namespace std;

typedef pair<double, double> Point;

vector< vector<Point> > read_polylines(string fileName);

void print_polylines(vector< vector<Point> > polylines);

void print_pline( vector<Point> pline);

vector<Point> simplifyLine(vector<Point> pline);