#include "project2_first.h" //include the first file's header so you can access the calls to the objects 


int main (int argc, char* argv[]){
    //in here we'll take care of getting the info 
    Dictionary::readFromFile(argv[1]);
    return 0; 
}