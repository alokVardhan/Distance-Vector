/* 
 * File:   main.cpp
 * Author: alok vardhan
 *
 * Created on September 14, 2014, 11:51 AM
 */
#include <cstdlib>

#include <cctype>
#include <iostream>
#include <string>
#include<cstdlib>
#include <vector>
#include<sstream>
//#include "Server.h"
//#include "Client.h"
#include <cstdlib>
#include "Common.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int PORT;
    Common common;
    int routing_update_interval;
    if (argc != 5) {
        cout << "Invalid input 1...usage : -t <file path> -i <routing table update>"<<endl;
        exit(1);
    }
    if ( string(argv[1]) != "-t"  || string(argv[3]) != "-i"   ) {
        cout << "Invalid input...usage : -t <file path> -i <routing table update>"<<endl;
        exit(1);
    }
    
    istringstream(string(argv[4])) >> routing_update_interval;
    
    if (routing_update_interval==0) {
        cout << "invalid update interval" << endl;
        exit(1);
    }
    
    string filepath = string(argv[2]);
    common.populate(filepath);
    
    return 0;
}

