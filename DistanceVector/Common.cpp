/* 
 * File:   Common.cpp
 * Author: alok vardhan
 * this file controls all the operations common to both client and server
 * Created on September 14, 2014, 12:16 PM
 */
#include "Common.h"
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <cstring>
#include <arpa/inet.h>
#include<iostream>
#include <time.h>
#include <sys/time.h>
#include<assert.h>
#include<cstdlib>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<iostream>
#include<sstream>
#include<cstring>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

Common::Common() {
}

/**
 * notostring function
 *this function returns string representation of a int
 * @param n : int no.
 * @return st :string
 */
string Common::notostring(int n) {
    stringstream s1;
    string st;
    s1 << n;
    st = s1.str();
    return st;
}

/** no known conversion for argument 1 from ‘std::string {aka std::basic_string<char>}’ to ‘const std::basic_ifstream<char
 * splitstring function
 *this function intakes a string and a delimeter and splits the string based on the 
 * delimeter and returns a vector of string containing tokens
 * @param  input_string
 * @param  delim :delimeter
 * @return tokens : vector containing all the tokens
 */
vector<string> Common::splitstring(string input_string, string delim) {
    vector<string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = input_string.find(delim)) != std::string::npos) {
        token = input_string.substr(0, pos);
        tokens.push_back(token);
        input_string.erase(0, pos + delim.length());
    }
    tokens.push_back(input_string);
    return tokens;
}

/**
 * gettime function
 *this function returns the current time
 * @return t1 : current time
 */
double Common::gettime() {
    struct timeval tim;
    gettimeofday(&tim, NULL);
    double t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);
    return t1;
}

/**
 * main function
 *this funct. does a case insensitive comparison of two strings and returns boolean value depending on comparison
 * @param  a first string
 * @param  b  second string
 * @return boolean value 
 */
bool Common::iequals_ignorecase(string a, string b) {
    int size_a = a.size();
    int size_b = b.size();
    if (size_a != size_b)
        return false;
    for (int i = 0; i < size_a; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

/**
 * stringtoint function
 *this function returns the int format of a no. in string format
 * @param no :no in string format
 * @return numb integer format of the no. in string format
 */
int Common::stringtoint(string no) {

    int numb;
    istringstream(no) >> numb;
    return numb;
}

void Common::populate(string filename) {
    

    ifstream infile(filename.c_str());
    string str;
    int i = 1;
    while (std::getline(infile, str)) {
        cout << str<<endl;
        if(i == 1){
            no_of_servers = stringtoint(str);
            i++;
            continue;
        }
        if(i == 2){
            no_of_neighbors = stringtoint(str);
            i++;
            continue;
        }
        if(i > 2 && i<= 2 + no_of_servers){
            vector<string> tokens = splitstring(str , " ");
            cout<<"displaying tokens ::"<<endl;
            for(int ind = 0 ;ind<tokens.size() ;ind++){
                cout<< tokens.at(ind)<<endl;
            }
            serverid_to_ip.insert(map<int, string>::value_type(stringtoint(tokens.at(0) ), tokens.at(1) + tokens.at(2)));
            i++;
            continue;
        }
        else{
            serverid_cost.push_back(str);
            i++;
            continue;
        }
    }
    cout<<"done"<<endl;
    cout<<"size of map" << serverid_to_ip.size()<<" :: "<<serverid_to_ip.at(1)<<endl;
    cout<<"size of vector :"<<serverid_cost.size() << "::"<<serverid_cost.at(0)<<endl;
    
    

}
/**
 * creator function
 * this function displays the creator info with policy acknowledgement
 */
void Common::creator() {
    cout << endl << "Name         	  : Alok Vardhan" << endl;
    cout << "UBIT NAME    	  : alokvard" << endl;
    cout << "UB email address   : alokvard@buffalo.edu" << endl;
    printf("I  have  read  and  understood  the   course   academic  integrity  policy  located  at http://www.cse.buffalo.edu/faculty/dimitrio/courses/cse4589_f14/index.html#integrity\n");
}

/**
 * help function
 *this function displays help
 */
void Common::help() {
    cout << endl << "1.CREATOR :" << endl;
    cout << "Display  your  full  name,  your  UBIT  name,  and  your  UB  email  address,  followed  by  the" << endl
            << "sentence  “I  have  read  and  understood  the   course   academic  integrity  policy  located  at" << endl
            << "http://www.cse.buffalo.edu/faculty/dimitrio/courses/cse4589_f14/index.html#integrity”." << endl;

}/**
 * gethostname function
 *This function returns hostname corresponding to its ip
 * @param  ip ip to be converted
 * @return ser_name :name of host corresponding to ip
 * ref:beejs guide
 */

string Common::gethostname(string ip) {
    struct hostent *he, *he1;
    struct in_addr ipv4addr;
    struct in_addr **addr_list;
    inet_pton(AF_INET, ip.c_str(), &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
    if (he == NULL) {
        return "invalid";
    }
    char *name = he->h_name;
    string ser_name = (string) name;
    return ser_name;
}

/**
 * longtostring function
 *This function returns string format of corresponding long no
 * @param  no long no to be converted to string
 * @return string format of no 
 */
string Common::longtostring(long no) {
    stringstream s1;
    string st;
    s1 << no;
    st = s1.str();
    return st;
}

/**
 * gethostip function
 *This function returns hostip corresponding to its name
 * @param  name :name of the host
 * @return IP of host corresponding to its name
 * reference beejs guide
 */
string Common::gethostip(string name) {
    struct hostent *he, *he1;
    struct in_addr ipv4addr;
    struct in6_addr ipv6addr;
    struct in_addr **addr_list;
    if ((he = gethostbyname(name.c_str())) == NULL) { // get the host info
        herror("gethostbyname");
        return "invalid";
    }
    addr_list = (struct in_addr **) he->h_addr_list;
    char *ip;
    string name_ip;
    for (int i = 0; addr_list[i] != NULL; i++) {
        ip = inet_ntoa(*addr_list[i]);
        name_ip = (string) ip;
        //        printf("%s ", name_ip);
        break;
    }
    return name_ip;
}

/**
 * myIp function
 *This function returns the actual ip of local machine
 * reference :http://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine
 * @return IP 
 */
string Common::myIp() {
    char buffer[200];
    memset(buffer, 0, 200);
    size_t buflen = 50;
    assert(buflen >= 16);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock != -1);

    const char* kGoogleDnsIp = "8.8.8.8";
    uint16_t kDnsPort = 53;
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof (serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
    serv.sin_port = htons(kDnsPort);

    int err = connect(sock, (const sockaddr*) &serv, sizeof (serv));
    assert(err != -1);

    sockaddr_in name;
    socklen_t namelen = sizeof (name);
    err = getsockname(sock, (sockaddr*) & name, &namelen);
    assert(err != -1);

    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, buflen);
    assert(p);
    string ip = (string) p;
    //      close(sock);
    return ip;

}