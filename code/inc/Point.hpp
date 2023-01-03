/*Author: Erik Bergqvist*/
/*Date: 7/12/2022*/
/*Purpose: To define 2d point class  used for line class*/

#ifndef Point_HPP
#define Point_HPP

#include <iostream> //get cout
#include <sstream> // to store stream
using namespace std;


namespace Erik
{
	namespace CAD
	{
		class Point //define Point class
		{
		private:
			double m_x; //private member coordinates x and y
			double m_y;

		public:
			Point();//default constructor
			Point(double xval, double yval);//constructor with given x and y values
			Point(const Point& source);// constructor by copying another point
			explicit Point(double value_for_both); // explicit to prevent implicit conversion 
			~Point(); //class destructor

			//Selectors
			double X() const; // Access the x value
			double Y() const; // Access the y value

			//Modifiers
			void X(double newX); //Set the x value
			void Y(double newY); //Set the y value

			string ToString() const; //initialize to string method

			double Distance(void) const; // distance from origin initialiser 
			double Distance(const Point& pt) const;// distance from another point initialiser 

			//Operator overloading
			Point& operator = (const Point& );// Assignment operator   
			Point operator - () const; // Negate the coordinates
			Point operator * (double factor) const; // Scale the coordinates
			Point operator + (const Point& p) const; // Add coordinates
			bool operator == (const Point& p) const; // Equally compare operator
			Point& operator *= (double factor);// Scale the coordinates & assign
			friend ostream& operator << (ostream& os, const Point& p);// os operator
		};
	}
}
#endif // Point_HPP