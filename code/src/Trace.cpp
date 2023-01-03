
/*Author: Erik Bergqvist*/
/*Date: 7/12/2022*/
/*
Purpose: To define and add methods to Trace class
It also contains functions for checking if there is intersection between lines 
*/

#include "./../inc/Trace.hpp" //Get Trace class

bool onSegment(Point a, Point b, Point c)
{
    //For collinear points a, b,c  checks if
    // a lies on line b->c
    if (a.X() <= max(b.X(), c.X()) && a.X() >= min(b.X(), c.X()) &&
        a.Y() <= max(b.Y(), c.Y()) && a.Y() >= min(b.Y(), c.Y()))
        return true;

    return false;
}


int orientation(Point a, Point b, Point c)
{
    // Find  a-> b -> c orientation
    // 0 --> a, b and c are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    double val = (b.Y() - a.Y()) * (c.X() - b.X()) -
        (b.X() - a.X()) * (c.Y() - b.Y());

    if (val == 0) return 0;  // collinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}


bool CheckIntersect(Point a_left, Point a_right, Point b_left, Point b_right, bool added_to_trace)
{ /*
    Check if there is an intersection between (a_left,a_right) and (b_left,b_right)
    */
    
    if(added_to_trace){ //If a_right==b_left and added_to_trace is true then one doesn't want an intersection
                        //as long as b_right doesnt intersect with a_left->a_right
                        //This is sufficient because there is at most one point with a_right == b_left
        if( (a_right==b_left )){
            Slope a_seg_slope, reverse_b_seg_slope;
            a_seg_slope.make(a_left.X(), a_left.Y(), a_right.X(), a_right.Y());
            reverse_b_seg_slope.make( b_right.X(), b_right.Y(),b_left.X(), b_left.Y());
            if(a_seg_slope == reverse_b_seg_slope) {return true;}
            else return false;
        }
        else return false;
    }
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(a_left, a_right, b_left);
    int o2 = orientation(a_left, a_right, b_right);
    int o3 = orientation(b_left, b_right, a_left);
    int o4 = orientation(b_left, b_right, a_right);
    // General case
    if (o1 != o2 && o3 != o4){
        cout << "general case intersection" << endl;
        return true;
        }
    // Special Cases
    // a_left, a_right and b_left are collinear and b_left lies on segment a_left -> a_right
    else if (o1 == 0 && onSegment(b_left, a_left, a_right)){
        cout << "Intersection with o1 = 0"<<endl;
        return true;
    }
    // a_left, a_right and b_right are collinear and b_right lies on segment a_left -> a_right
    else if (o2 == 0 && onSegment(b_right,a_left, a_right)) {
        cout << "Intersection with o2 = 0"<<endl;
        return true;
    }

    // b_left, b_right and a_left are collinear and a_left lies on segment b_left -> b_right
    else if (o3 == 0 && onSegment( a_left,b_left, b_right)) {
        cout << "Intersection with o3 = 0"<<endl;
        return true;
    }
    // b_left, b_right and a_right are collinear and a_right lies on segment b_left -> b_right
    else if (o4 == 0 && onSegment( a_right,b_left, b_right)) {
        cout <<b_left<< a_right<< b_right<< endl;
        cout << "Intersection with o4 = 0"<<endl;
        return true;
    }
    else
    {
    return false; // Doesn't fall in any of the above cases
    }
}


Trace::Trace(Line input_line){
    /*
    Default constructor checks that it's a valid line  and adds it to the 
    m_lines queue 
    */
    if ((input_line.P1() == input_line.P2())){
        throw std::invalid_argument(  "Line cannot have the same start and end point" );
    }
    cout << "Adding new trace" << endl; //Inform that new line has been added
    m_lines.push_back(input_line);//add new line
    most_recent_left_point =input_line.P1(); //update point to the right
    most_recent_right_point =input_line.P2(); //update point to the right
}

void Trace::add_trace(Line input_line)
{
    /*
    Function for adding trace this is in case Trace was generated without input line
    */

    if(m_lines.size()==0)
    {
        cout << "Adding new trace" << endl;
        m_lines.push_back(input_line);//add new line
        most_recent_left_point =input_line.P1(); //update point to the right
        most_recent_right_point =input_line.P2(); //update point to the right
    }
    else{
        throw std::logic_error( "Cannot add new traces"); //Throw error if there already is a trace
    }
}

Point Trace::right_point()
{ return most_recent_right_point;}; // getter for most recent right point


Point Trace::left_point()
{ return most_recent_left_point;};// getter for most recent left point


bool Trace::check_intersect(const Line comparison_line)
{
    /*
    Iterate over current lines and check if given line intersects with any point
    */
    
    if(m_lines.size()==0) //No trace has been added no check required
    {
        throw std::invalid_argument(  "No lines in trace to compare with" );
    }

    else
    {
        //Check if there is intersection with other lines by iterating thorugh the traces deque
        bool intersect_w_other;
        for(auto it : m_lines) 
        {
            intersect_w_other= CheckIntersect(it.P1(),it.P2(),comparison_line.P1(),comparison_line.P2(),false); 
            if(intersect_w_other)
            {
                cout << "Intersection with" << it << endl; 
                break;
            }
        }
        return intersect_w_other;
    }
}


void Trace::add_to_left(Point new_point){
    /*
     Add line by drawing line from most recent point to given point 
    */
    bool intersect_w_other; // used to check for intersection

    if(m_lines.size()==0)
    {
        cout << "No trace to add to, point not added" << endl;
    }

    if(most_recent_left_point==new_point)
    {
        cout << "Cannot add line with same points" << endl;
    }
    else
    {
        
        for(auto it : m_lines) // iterate over traces to check if there is an intersection
        {
            
            if(!(it.P1()==most_recent_left_point))
            {
                intersect_w_other= CheckIntersect(it.P1(), it.P2(),new_point,most_recent_left_point,false);//Will ignore intersection with most recent point
            }
            else
            {
                intersect_w_other= CheckIntersect(it.P1(), it.P2(),new_point,most_recent_left_point,true);//Will ignore intersection with most recent point
            }
            if(intersect_w_other){cout << "Intersection with" << it<< "segment not added" << endl; break;}
                       
        }
        if(!intersect_w_other) //no intersection found proceed to add new line
        {
            Line new_line(new_point,most_recent_left_point);
            m_lines.push_front(new_line);//add new line  to deque of values 
            most_recent_left_point = new_point;// update most recent point 
        }
    }
}


void Trace::add_to_right(Point new_point){
    /*
     Add line by drawing line from most recent point to given point 
    */
    bool intersect_w_other; // used to check for intersection

    if(m_lines.size()==0)
    {
        cout << "No trace to add to, point not added" << endl;
    }

    if(most_recent_right_point==new_point)
    {
        cout << "Cannot add line with same points" << endl;
    }
    else
    {
        
        for(auto it : m_lines) // iterate over traces to check if there is an intersection
        {
            
            if(it.P2()==most_recent_right_point)
            {
            
                intersect_w_other= CheckIntersect(it.P1(), it.P2(),most_recent_right_point,new_point,true);//Will ignore intersection with most recent point
            }
            else
            {
                intersect_w_other= CheckIntersect(it.P1(), it.P2(),most_recent_right_point,new_point,false); //normal intersection check
            }
            if(intersect_w_other){cout << "Intersection with" << it<< "segment not added" << endl; break;}
            
                       
        }
        if(!intersect_w_other) //no intersection found proceed to add new line
        {
            m_lines.push_back(Line(most_recent_right_point,new_point));//add new line  to deque of values 
            most_recent_right_point = new_point;// update most recent point 
        }
    }
}

void Trace::display_all_lines(void){
    /*
    Prints all  the traces that have been drawn
    */
    if(m_lines.size()==0)
    {
        cout << "No lines to display" << endl; 
    }
    else
    {
        cout << "Trace:" << endl;
        for(auto it : m_lines) //Iterate over all lines in trace and print their content
        {
            cout << it << endl;            
        }
    }
}