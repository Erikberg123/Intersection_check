README
This folder contains code written for the Leica task it is written in C++ and uses STL 


To compile:
On my machine with the g++ compiler I run:
g++ ./src/Point.cpp ./src/Line.cpp ./src/Trace.cpp ./src/TraceHandler.cpp  main.cpp -o runtests

in the code directore
To execute:
./runtests "./short_test_no_intersection.txt" 
Remaining work that should be done:
Add notes on algorithmic complexity, make it so that one adds to traces not only by adding to most recent point. Currently test script forces you to input a file which is a bit bulky.