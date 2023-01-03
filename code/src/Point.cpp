/*Author: Erik Bergqvist*/
/*Date: 7/12/2022*/
/*Purpose: To add methods to point class*/

#include "./../inc/Point.hpp"
#include <cmath>

namespace Erik
{
	namespace CAD
	{
		Point::Point():  m_x(0.0), m_y(0.0) 
        {
            //default point constructor
            
        }

        Point::Point(double newx, double newy) : m_x(newx), m_y(newy)
        {
            //constructor with input coordinates
        }

        Point::Point(const Point &source): m_x(source.m_x),m_y(source.m_y)
        {
            //copy constructor initialised based on another class
        }

        Point::Point(double value_for_both) : m_x(value_for_both), m_y(value_for_both)
        {
            //constructor using one value as input
        } 

		Point::~Point()// point destructor
		{
		}

		void Point::X(double newX)
		{
			//setter for x
			m_x = newX; 
		}

		void Point::Y(double newY)
		{
			//setter for y
			m_y = newY;
		}

		double Point::X(void) const
		{
			//getter for x
			return m_x;
		}

		double Point::Y(void) const
		{
			//getter for y
			return m_y;
		}

		string Point::ToString() const
		{
			//tostring method to print out the coordinates in string format
			stringstream stream_output; // initialise string stream
			stream_output << "Point(" << m_x << ", " << m_y << ")"; //output string format
			
			return stream_output.str(); //string output
		}

		double  Point::Distance(void) const
		{
			//Compute distance of point from origin and return it
			return sqrt( pow(m_y , 2) + pow(m_x , 2 ));// compute distance
		}


		double Point::Distance(const Point& pt) const		
		{
			//compute distance from point to point pt
			// passing point pt bm_y reference as const returning const value
			return sqrt(pow((m_x - pt.m_x), 2) + pow((m_y - pt.m_y), 2));// compute distance
		}

		// operators
		Point& Point::operator = (const Point& source_point)
		{
			// Assignment operator definition
			if (this == &source_point) //avoid assigning to self
			{
				cout << "Preclude self-assignment" << endl; // Alert of special case
				return *this; 
			}
			else
			{
				m_x = source_point.m_x;
				m_y = source_point.m_y;
				return *this; // return point after fixing new coordinates
			}
		}

		Point Point::operator - () const
		{   
			// Negate the coordinates
			return Point(-m_x, -m_y);
		}

		Point Point::operator * (double factor) const
		{
			// Scale the coordinates
			return Point(factor * m_x, factor* m_y);
		}

		Point Point::operator + (const Point& p) const
		{
			// Add to coordinates
			return Point(m_x + p.m_x, m_y + p.m_y);
		}

		bool Point::operator == (const Point& p) const
		{   
			// Equally compare on coordinates operator
			return (m_x == p.m_x) && (m_y == p.m_y);
		}

		Point& Point::operator *= (double factor)
		{
			// Scale the coordinates & assign them
			m_x *= factor;
			m_y *= factor;
			return *this; //return reference to point
		}

		// Overloaded os operator 
		
		ostream& operator << (ostream& os, const Point& source)
		{
			os <<"Point(" <<source.m_x << " , " << source.m_y << ")"; //get Line content directly thanks to being frined

			return os; //returned by reference
		}
		
	}
}
