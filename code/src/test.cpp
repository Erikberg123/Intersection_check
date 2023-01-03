
#include <iostream> // get cout
#include <fstream> // for stream operations
#include <sstream>
using namespace std;
#include <string>

template<typename T>
std::vector<T> split(const std::string& line) {
    //This method is used to split string lines and convert it to vector of type T
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}


int main()
{
    // Input string
    string a("1 2 3");
 
    // Object class of istringstream
    istringstream my_stream(a);
 
    // Variable to store number n
    int n;
    int m;
    // Stream a number till white space
    // is encountered
    my_stream >> n;
    my_stream >> m;
    // Print the number
    cout << n << m<< "\n";
}