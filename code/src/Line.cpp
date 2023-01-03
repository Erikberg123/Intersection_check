/*Author: Erik Bergqvist*/
/*Date: 03/11/2022*/
/*Purpose: To define methods of line class defined in the header file
The methods that are added are constructors, a destructor getters and setters for the 
Two points in the line, a tostring method and a distance method
Methods for slope struct are also defined 
*/

#include "./../inc/Line.hpp"
#include <cmath>
namespace Erik
{
	namespace CAD
	{

		Line::Line() : p1(), p2()
		{
			//default Line construct
			slope.type = undef; // Points are same so cannot define a slope
			//This case can be ignored as these cases will be filtered out by LineContainer
		}


		Line::Line(const Point& new_start_point, const Point& new_end_point) : p1(new_start_point), p2(new_end_point)
		{
			//constructor with input points
			slope.make(new_start_point.X(), new_start_point.Y(), new_end_point.X(), new_end_point.Y());

		}


		Line::Line(const Line& source_line) : p1(source_line.p1), p2(source_line.p2)
		{
			//copy constructor given another line passed as reference
			slope.type = source_line.slope.type;
			if(slope.type == real)
				slope.gradient = source_line.slope.gradient;
		}


		Line::~Line()
		{
			// Line destructor
		}


		void Line::P1(const Point &new_start_point) 
		{
			//setter for start point
			p1 = new_start_point;
		}


		void Line::P2(const Point &new_end_point)  
		{
			// setter for end point
			p2 = new_end_point;
		}

		Point Line::P1(void) const
		{
			//getter for start point
			return p1;
		}

		Point Line::P2(void) const
		{
			//getter for end point
			return p2;
		}

		string Line::ToString() const
		{
			//tostring method to print out the coordinates in string format
			stringstream stream_output; // initialise string stream
			stream_output << "Line(" << p1.ToString()  << ", " << p2.ToString()  <<  ")"; //output string format
			
			return stream_output.str(); // return string output
		}

		double Line::Length(void) const
		{
			//Compute distance of Line by getting distance between the two points
			return p1.Distance(p2); 
		}

		// operators
		Line& Line::operator = (const Line& source_line)
		{
			// Assignment operator definition
			if (this == &source_line) //avoid assigning to self
			{
				cout << "Preclude self-assignment" << endl; // Alert of special case
				return *this; 
			}
			else
			{
				p1 = source_line.p1;
				p2 = source_line.p2;
				return *this; // return Line after fixing new coordinates
			}
		}

		Line Line::operator - () const
		{   
			// Negate the coordinates
			return Line(-p1, -p2);
		}

		Line Line::operator * (double factor) const
		{
			// Scale the coordinates
			return Line( p1 * factor,  p2 * factor);
		}

		Line Line::operator + (const Line& l) const
		{
			// Add to coordinates
			return Line(p1 + l.p1, p2 + l.p2);
		}

		bool Line::operator == (const Line& l) const
		{   
			// Equally compareon coordinates operator
			return ( p1 == l.p1) && (p2 == l.p2);
		}

		Line& Line::operator *= (double factor)
		{
			// Scale the coordinates & assign them
			p1 *= factor;
			p2 *= factor;
			return *this; //return reference to Line
		}

		
		// Overloaded os operator 
		ostream& operator << (ostream& os, const Line& source)
		{
			os << " Line( "<<source.p1 << " , " << source.p2 << " ) " ; //get Line content
			return os; //returned by reference
		}


		void Slope::make(const double& x0, const double& y0, const double& x1, const double&y1) 
		{
			//This method is for computing gradient of line 
			//It is used to compute gradient or classify cases where the slope cannot be defined
			if(x0 == x1)
				if(y0 < y1)
					type = pos_infty;
				else
					type = neg_infty;
			else {
				type = real;
				gradient = (y0 - y1) / (x0 - x1) ;
			}

			return;
		}

		bool Slope::operator==(const Slope& s) const 
		{
			//For cases where gradients exits or are infinity check if it's in same direction
			if(type == pos_infty && s.type == pos_infty)
				return true;
			else if(type == neg_infty && s.type == neg_infty)
				return true;
			else if(type == real && s.type == real){
				if(gradient==s.gradient){
					return true;
				}
			}
			return false; //These are the cases when the gradient are the same
		}
	}
}