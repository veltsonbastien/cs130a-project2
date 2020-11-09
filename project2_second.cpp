#include "dictionary.h"
#include "hash24.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <utility>
using namespace std; 


int main (int argc, char* argv[]){
    string argument = argv[2]; 
    string token = ", ";

 

     Dictionary d = Dictionary::readFromFile(argv[1]);


    //for testing purposes
    //Dictionary d ("PA2_dataset_10000.txt", 10000);

    vector<string> result;
        while(argument.length()){
            int index = argument.find(token);
            if((index!=string::npos) ){
                result.push_back(argument.substr(0,index));
                argument = argument.substr(index+token.size());
                if(argument.size()==0)result.push_back(argument);
            }else{
                result.push_back(argument);
                argument = "";
            }
        }

       
    //find each word 
    for(string s: result){
     
        d.find(s); 
    }


    return 0; 
}