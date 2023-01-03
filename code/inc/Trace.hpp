/*Author: Erik Bergqvist*/
/*Date: 7/12/2022*/
/*
Purpose: To methods for Trace class
It also contains functions for checking if there is intersection between lines 
*/

#ifndef Trace_HPP
#define Trace_HPP

#include <stdexcept>
#include "./../inc/Point.hpp" // get point class
#include "./../inc/Line.hpp" // get line class 
#include<deque> // get deque
using namespace Erik::CAD;

typedef std::deque<Line> deque_seg; // define deque line type

bool onSegment(Point a, Point b, Point c);
int orientation(Point a, Point b, Point c);
bool CheckIntersect(Point a_left, Point a_right, Point b_left, Point b_right, bool added_to_trace);

class Trace
{
    /*
   This class contains a deque of lines which can be added to
   It allows for adding a line either by adding a point which will
   attempt to add a line from the most recent point or a line 
   this will add a new segment 
    */
    private:
        deque_seg m_lines; // vetor of traces
        Point most_recent_right_point; // most recent point on trace to the right
        Point most_recent_left_point; // most recent point on trace to the left
    public:
        Trace(){};
        Trace(Line input_line);
        
        void add_trace(Line input_line);
        bool check_intersect(const Line comparison_line); //check for intersections
        void add_to_left(Point new_point); //Make line by drawing line between input point and most recent point to the left
        void add_to_right(Point new_point); //Make line by drawing line between input point and most recent point to the right
        Point right_point(); //Show content of most recent point to the right
        Point left_point(); //Show content of most recent point to the left
        void display_all_lines(); //Display all the content of the containers
        
};
#endif // Trace_HPP