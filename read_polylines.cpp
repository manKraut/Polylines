#include "read_polylines.hpp"

vector< vector<Point> > read_polylines(string fileName)
{
	string				line;
	vector<Point>			polyline;
	vector< vector<Point> >		AllPolylines;

	ifstream infile(fileName);

	/*
	 * Read input file line-by-line. Each line corresponds to a polyline and the format of each line is as follows:
	 *
	 * x_1,y_1 x_2,y_2 x_3,y_3 ... x_n,y_n
	 */
	while (getline(infile, line)) {

		/*
		 * Each point in the line read is separated from the next point by a space character.
		 * The following 4 lines split the line into tokens at each space character and
		 * create the vector 'vstrings' that contains all pairs x_i,y_i
		 */
		stringstream			ss(line);
		istream_iterator<string>	begin(ss);
		istream_iterator<string>	end;
		vector<string>			vstrings(begin, end);

		/*
		 * Every pair x_i,y_i in 'vstrings' is now split into its constituting coordinates at the comma character and
		 * inserted into the vector of points 'polyline'.
		 */
		polyline.clear();
		for (vector<string>::const_iterator it = vstrings.begin(); it != vstrings.end(); it++) {
			Point	p;
			string	token;
			istringstream tokenStream(*it);
			
			getline(tokenStream, token, ',');
			p.first = stod(token);
			getline(tokenStream, token, ',');
			p.second = stod(token);

			polyline.push_back(p);
		}

		/*
		 * A complete polyline has been created at this point and
		 * is inserted into the vector 'AllPolylines'
		 */
		AllPolylines.push_back(polyline);
	}
	return AllPolylines;
	
}
/*
 * Print out all polylines contained in 'AllPolylines' as a test.
 */

void print_polylines(vector< vector<Point> > polylines)
{
	for (vector< vector<Point> >::const_iterator it1 = polylines.begin(); it1 != polylines.end(); it1++) {
		vector<Point>	polyline = (*it1);;
		print_pline(polyline);
	}
	
}
void print_pline( vector<Point> pline)
{
	for (vector<Point>::const_iterator it2 = pline.begin(); it2 != pline.end(); it2++) {
		cout << "(" << (*it2).first << ", " << (*it2).second << ") ";
	}
	cout << endl;
}
