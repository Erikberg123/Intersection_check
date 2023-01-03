
/*Author: Erik Bergqvist*/
/*Creation Date: 10/12/2022*/
/*
Purpose: To define and add methods to TraceHandler class
*/
#include "./../inc/TraceHandler.hpp" //Get tracehandler class

void TraceHandler::add_trace(Line input_line){

    /*
    Start a new trace this function accepts a line pointer and adds it to
    the queue of segments if there is no intersecton with other traces
    */
    
    bool does_intersect; //For checking for intersection
    
    for(auto & x : trace_map)
    {
        does_intersect = x.second.check_intersect(input_line);
        if (does_intersect){cout << "Line causing intersection is in "<< x.first << endl ;break;} 
    }

    if(!does_intersect)
    {
        Trace new_trace(input_line);
        
        trace_map.insert(std::pair<int,Trace>(num_traces++, new_trace) ); //add to map and increment num_traces afterwards
    }
    
}


void TraceHandler::add_to_trace(Point new_point, int trace_id, bool right_side){
    /*
    Given a trace id this function adds a point in the right or left direction
    if one wishes to add to left side one sets right side to false
    */
    
    Line candidate_line;
    bool does_intersect = false;

    if(trace_id> num_traces-1){throw std::invalid_argument(  "trace id exceeds max number of traces" );};
    if(right_side){ //Construct line based on input point
        candidate_line = Line(trace_map[trace_id].right_point(), new_point);
    }
    else{
        candidate_line = Line(new_point, trace_map[trace_id].left_point());
    }
    for(auto & x : trace_map) //Iterate over all the traces
    {
        if(x.first != trace_id){
            does_intersect = x.second.check_intersect(candidate_line);
            if (does_intersect){cout << "Line causing intersection is in "<< x.first << endl ;break;} 
        }

    }
    if(!does_intersect){ //No intersection found add point to correct trace
        if(right_side){
            trace_map[trace_id].add_to_right(new_point) ;
        }
        else{
            trace_map[trace_id].add_to_left(new_point) ;
        }
    }
}


void TraceHandler::display_all_traces(void){
    /*
    Function to print content of tracehandler
    So prints each trace with it id
    */
    for(auto & x : trace_map)
    {
        cout << x.first << ":" << endl;
        x.second.display_all_lines();

    }
}