#include <iostream>
#include <fstream>
#include <ctime>
#include "graph.h"
#include <iomanip>

using namespace std;
Graph G;

int main(int argc, char** argv)
{
    if(argc != 3){
        cerr<< "Number of Input Arguments Mismatch!" <<endl;
        cerr<< "./bezier [test.in] [test.out]" <<endl;
        return 1;
    }    
    clock_t start, end;
    start = clock();
    
    if(G.parser(argv)) return 1;
    
    G.segmentation();

    if(G.smooth(argv)) return 1;
    
    end = clock();
    
    cout << "Execution time: " << (end-start)/(double)(CLOCKS_PER_SEC) << endl;
    
    return 0;
}
