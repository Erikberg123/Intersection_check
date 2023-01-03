/*
Creator: Erik Bergqvist
Date of creation: 8/12/2022
Purpose: This file contains code for testing calls to the class
*/

#include <iostream> // get cout
#include <fstream> // for stream operations
#include <sstream>
#include "./inc/TraceHandler.hpp" //Get tracehandler class definition along with trace,point, and line classes
using namespace std;

template<typename T>
std::vector<T> split(const std::string& line) {
    //This method is used to split string lines and convert it to vector of type T
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}


int main(int argc, char** argv)
{

    
    fstream newfile; //file object for reading input
    TraceHandler test_drawing; //Initialise handler for storing all the traces
    Point left_point, right_point; //Points read input with

    if (argc < 2) {
        cout << "Need input file for " << argv[0] << "to run" << endl;
        return EXIT_FAILURE; //raise problem if there is no input file
    }

    char *s1 = argv[1]; //read argument input
    const char *filename = argv[1];


    //intersection checks
    cout << "Test intersection check:" << endl; //Check for intersections
    cout << "Point(0)-> Point(1,0) vs Point(1,2)-> Point(1,1)" << endl;
    string is_intersecting = CheckIntersect(Point(0),Point(1,0), Point(1,2), Point(1,1),false) ? "Intersects": "Doesnt intersect"; 
    cout<< is_intersecting <<endl;
    cout << "Point(0)-> Point(1,0) vs Point(1,0)-> Point(1,1)" << endl;
    is_intersecting =  CheckIntersect(Point(0),Point(1,0), Point(1,0), Point(1,1),false)? "Intersects": "Doesnt intersect"; 
    cout<< is_intersecting <<endl;
    cout << "Point(0)-> Point(1,0) vs Point(1,0)-> Point(1,1) treated as extension" << endl;
    is_intersecting =  CheckIntersect(Point(0),Point(1,0), Point(1,0), Point(1,1),true)? "Intersects": "Doesnt intersect"; 
    cout<< is_intersecting <<endl;
    cout << "Point(0)-> Point(0,1) vs Point(0,1)-> Point(0,0.5) treated as extension" << endl;
    is_intersecting =  CheckIntersect(Point(0),Point(0,1), Point(0,1), Point(0,0.5),true)? "Intersects": "Doesnt intersect"; 
    // This is false cause line intersects with previous one
    cout<< is_intersecting <<endl;


    //Run tests on Trace
    Trace manual_input_container(Line(Point(0,0),Point(1,0))); // container objects for adding points and lines into
    manual_input_container.display_all_lines();
    
    
    cout << "Test adding to container:" << endl;  // test different ways of adding points to the right and left
    cout << "Try adding (1,0) to right hand side" << endl;
    manual_input_container.add_to_right(Point(1,0));
    cout << "Try adding (1,0) to left hand side" << endl;
    manual_input_container.add_to_left(Point(1,0));
    manual_input_container.display_all_lines();
    
    cout << "Add new trace (2,2),(3,3)" << endl;

    try{
        manual_input_container.add_trace(Line(Point(2,2),Point(3,3))); //Try adding new trace
    }
    catch (const std::exception& e) {cout << e.what() << endl; };
    
    cout << "Print all lines" << endl;
    manual_input_container.display_all_lines();
    

    //Test add_to_trace some more
    cout << "Test adding more points" << endl; 
    cout << "add (6,6) to right of trace" << endl;
    manual_input_container.add_to_right(Point(6,6));
    manual_input_container.display_all_lines();
    cout << "add (0,7) to left of trace" << endl;
    manual_input_container.add_to_left(Point(0,7));
    manual_input_container.display_all_lines();
    cout << "add (6,6) to left of trace" << endl;
    manual_input_container.add_to_left(Point(6,6));
    manual_input_container.display_all_lines();
    
    cout << "\n\n\nTest the trace handler using file input" << endl;//start file read
    newfile.open(filename,ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){   //checking whether the file is open
      string tp;
      int line_num = 1;
      while(getline(newfile, tp))
      {  //read data from file object and put it into string.
            
            std::vector<double> double_vec = split<double>(tp); //vector to split values with
            if( double_vec.size() ==3){
                cout << "Attempt to add (" << double_vec[0] << "," << double_vec[1] << ") to right of trace: " << (int) double_vec[2] <<endl;
                try{test_drawing.add_to_trace(Point(double_vec[0],double_vec[1]), (int) double_vec[2] , true);}  //always add to the right hand side
                catch (const std::exception& e) {cout << e.what() << endl; };
                cout << "current trace is " <<endl;
                test_drawing.display_all_traces();//print current set of traces
            }
            else if( double_vec.size() ==4){
                left_point = Point( double_vec[0], double_vec[1]); //overwrite point values
                right_point =Point(double_vec[2], double_vec[3]);
                cout << "Attempt to create trace with " << left_point << "->" << right_point << endl;
                try{test_drawing.add_trace(Line(left_point , right_point));} //Try adding trace
                catch (const std::exception& e) {cout << e.what() << endl; };
                cout << "current trace is " <<endl;
                test_drawing.display_all_traces(); //print current set of traces
            }
            
            else{
                cout << "Invalid input line: "<< tp << " " <<endl;   //print the data of the string that is not recognised
            }
      }  
   }
   
}