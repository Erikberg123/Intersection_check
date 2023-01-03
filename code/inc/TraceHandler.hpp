
/*Author: Erik Bergqvist*/
/*Creation Date: 10/12/2022*/
/*
Purpose: To define TraceHandler class
*/

#ifndef TraceHandler_HPP
#define TraceHandler_HPP

#include<vector> // get vector
#include<map> // get map
#include "./../inc/Trace.hpp" //get trace point and line classes

using namespace Erik::CAD; // For working with point and line classes 

class TraceHandler
{
    /*
    The purpose of this class is to append Traces and append points to the traces
    It checks for intersections inbetween traces as well
    */
    private:
        int num_traces; // Number of current traces 
        std::map<int,Trace> trace_map; // Map to traces

    public:
        TraceHandler(): num_traces(0) {}; // For default constructor at start there are 0 traces
        void add_trace(Line input_line); // Takes line as input for new trace
        void add_to_trace(Point new_point, int trace_id, bool right_side); // Add point to trace given the trace id
        int get_num_traces(){return num_traces;}; //getter for num_traces
        void display_all_traces();// Print content of all traces with ids
};

#endif // TraceHandler_HPP