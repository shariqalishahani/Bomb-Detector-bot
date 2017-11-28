#include <stdio.h>
#include <string>
#include <cstdlib>
using std::string;
int main(){
    string command;
    command  = "raspistill -o ";
    command.append("cam18.jpg");
    system(command.c_str());
   
    return 0;
}
