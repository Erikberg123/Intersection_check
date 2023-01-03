/*Author: Erik Bergqvist*/
/*Date: 7/12/2022*/
/*Purpose: To define line consisting of two points using the point classes the slope struct is also defined*/


#ifndef Line_HPP
#define Line_HPP

#include "Point.hpp" // get point class from header file defined from previous exercises 
#include <iostream> // get cout 
#include <sstream> // string stream
using namespace std;

namespace Erik
{
	namespace CAD
	{
		enum slope_type {undef, real, pos_infty, neg_infty}; // four cases to look out for

		//Define slope struct for line 
		struct Slope {
		slope_type type; 
		double gradient; 
		void make(const double&,const double&,const double&,const double&);
		bool operator==(const Slope&) const;
		};
		
		class Line 
		{
		//define Line class
		private:
			Point p1; //private member start point p1 and end point p2, this is composition
			Point p2;
			Slope slope; // Slope struct for determining type of slope this is needed to handle infty cases

		public:
			Line();//default constructor
			Line(const Point& new_start_point, const Point& new_end_point);//constructor with given points
			Line(const Line& source);// constructor by copying another Line
			
			~Line(); //class destructor

			//initialize getters and setters for line points
			Point P1() const; // default point constructor for first point
			void P1(const Point& new_start_point); // copy constructor for first point, call by reference
			Point P2() const; // default point constructor for second point
			void P2(const Point& new_end_point); //copy constructor for first point, call by reference


			string ToString() const; //initialize to string method
			double Length(void) const; // distance between end and start point

			//Assignment operator makes sense since operations on a point naturally extends to a line, can be thought of as a point of points
			Line& operator =(const Line& source); 
			Line operator - () const;					// Negate the coordinates
			Line operator * (double factor) const;		// Scale the coordinates
			Line operator + (const Line& l) const;	// Add coordinates
			bool operator == (const Line& l) const;	// Equally compare operator
			Line& operator *= (double factor);			// Scale the coordinates & assign
			
			friend ostream& operator << (ostream& os, const Line& source); // print line content operator
		};
		
		
	}
}
#endif 