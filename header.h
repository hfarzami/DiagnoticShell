#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <sys/resource.h>

using namespace std;

/* function prototypes*/
void PidFromString(string input);
void StringFromPid(string input);
void Systat();
void Usage();
string GetParam(string input);
void print_cpu_time();
