#include <iostream>
#include <google/dense_hash_map>
#include "glucose.hpp"

#include <fstream>
#include <string>
#include <string.h>   
#include <hash_fun.h>

using namespace ::Glucose;
using  std::string;
using google::dense_hash_map; 

using __gnu_cxx::hash;



struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};


void getStringFromCharArray(char target[], int begin, int end, char result[])
{
    int length = end - begin;
    for (int i = 0; i < length; i++)
    {
        result[i] = target[i + begin];
    }
    // delete target;
    std::cout << result << std::endl;
    
}

void getStringFromCharArrayAdvanced(string target, int begin, int end, char result[])
{
    int length = end - begin;
    for (int i = 0; i < length; i++)
    {
        result[i] = target[i + begin];
    }
    // delete target;
    std::cout << result << std::endl;
    
}


void myTestFunction(){
    char * target = new char [7];
    target[0] = 'a';
    target[1] = 'b';
    target[2] = 'c';
    target[3] = 'd';
    target[4] = 'e';
    target[6] = 'g';

    int begin = 3;
    int end = 5;
    char * result = new char [end - begin + 1];
    getStringFromCharArray(target, begin, end, result);
    std::cout << result << std::endl;
}

void myTestFunctionAdvanced(){
    string target = "abcdefg";
    int begin = 3;
    int end = 5;
    char * result = new char [end - begin + 1];
    getStringFromCharArrayAdvanced(target, begin, end, result);
    std::cout << result << std::endl;
}


int main()
{
    //myTestFunctionAdvanced();

    //Store varibale and its index;
    dense_hash_map<const char*, int, __gnu_cxx::hash<const char*>, eqstr> varibleMap;
    varibleMap.set_empty_key(NULL);

    //Temp Data Structure
    //char data[100];
    string data;
    std::ifstream infile;
    infile.open("./testcase/testcase0.v");
    //test
    //std::getline(infile, test);

    int index = 1;
    while (!infile.eof()){// find the end of the filetarget
        std::getline(infile, data);
        //infile.getline(data,100);
        //string temp = data;

        //deal with input and output
        if(data.find("module miter") != string::npos){


            while(std::getline(infile, data) && data.find(");") == string::npos){
                //read one more line
                //int i=0;
                
                bool isBeforeCommenStr = false;            // 
                int lastCharIndex = 0;

                for (int i = 0; i < data.length(); i++)
                {
                    if(' ' == data[i] || ',' == data[i])
                    {
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            char * result = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            varibleMap[result] = index;
                            
                            std::cout << "key -> " << result <<  " value -> " << varibleMap[result] << std::endl;
                            std::cout << "key -> \\A[2][9]" <<  " value -> "  << varibleMap["\\A[2][9]"] << std::endl;
                            
                            std::cout << "====================";
                            isBeforeCommenStr = false;
                            index++;
                        }else{
                            //string deal;
                            continue;
                        }
                        
                    }
                    // If read the real characteristic
                    else
                    {
                        if(!isBeforeCommenStr){
                            isBeforeCommenStr =true;
                            lastCharIndex = i;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            if(eq  );)
        }

        std::cout << data << std::endl;
    }

 
	// infile >> data;
	// std::cout << "second read data from file1.dat == " << data << std::endl;
	infile.close();


    // std::cout << "Test"<< std::endl;
    // Solver s;

    // vec<Lit> clause1;
    // clause1.push(mkLit(2));
    // clause1.push(~mkLit(4));

    // vec<Lit> clause2;
    // clause2.push(~mkLit(1));
    // clause2.push(~mkLit(3));
    // clause2.push(~mkLit(4));

    // vec<Lit> clause3;
    // clause3.push(~mkLit(3));
    // clause3.push(mkLit(4));

    // vec<Lit> clause4;
    // clause4.push(mkLit(1));
    // clause4.push(~mkLit(2));
    // clause4.push(~mkLit(3));

    // vec<Lit> clause5;
    // clause5.push(~mkLit(1));
    // clause5.push(~mkLit(3));
    // clause5.push(mkLit(4));

    // vec<Lit> clause6;
    // clause6.push(~mkLit(2));
    // clause6.push(~mkLit(3));

    // vec<Lit> clause7;
    // clause7.push(mkLit(2));
    // // clause7.push(mkLit(3));

    // vec<Lit> clause8;
    // clause8.push(~mkLit(2));



    // while(4 >= s.nVars()) 
    //     s.newVar();

    // s.addClause(clause1);
    // s.addClause(clause2);
    // s.addClause(clause3);
    // s.addClause(clause4);
    // s.addClause(clause5);
    // s.addClause(clause6);
    // s.addClause(clause7);
    // s.addClause(clause7);


    // bool ans = s.solve();
    // std::cout << "This is :" <<ans << std::endl;
    return 0;
}