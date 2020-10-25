#include "project2_first.h" //include the first file's header so you can access the calls to the objects 
#include "hash24.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <utility>

using namespace std; 

//  //readFrom
// static Dictionary readFromFile(string fName){
//        // Object to read from file
//     ifstream dictionary_object;
 
//     // Opening file in input mode
//     dictionary_object.open(fName, ios::in);
    
//     dictionary_object.seekg(0);
//     // Object of class contestant to input data in file
    
//     Dictionary read_dictionary;

//     dictionary_object.read((char*)&read_dictionary, sizeof(read_dictionary));

//     return read_dictionary; 
//  }


int main (int argc, char* argv[]){
    string argument = argv[2]; 
    string token = ", ";
    vector<string> result;
        while(argument.length()){
            int index = argument.find(token);
            if(index!=string::npos){
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
        (Dictionary::readFromFile(argv[1])).find(s); 
    }


    return 0; 
}