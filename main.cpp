#include <iostream>
#include <google/dense_hash_map>
#include "glucose.hpp"

#include <fstream>
#include <string>
#include <hash_fun.h>

using namespace ::Glucose;
using  std::string;
using google::dense_hash_map; 

using __gnu_cxx::hash;
// using std::dense_hash_map;



struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
  }
};

int main()
{
    //Temp Data Structure
    char data[100];
    std::ifstream infile;
    infile.open("./testcase/testcase0.v");

     ;

    dense_hash_map<char*, int> keyValue;

    while (!infile.eof()){// find the end of the file

        infile.getline(data,100);
        string temp = data;

        //deal with input and output
        if(temp.find("module miter") != string::npos){
            infile.getline(data,100);
            int i=0;
            bool isContinue = false;
            
            int tempKeyLentgh = 0;
            string tempKeyChar;
            bool isBeforeCommenStr = false;
            while(data[i++] != '\0'){
                if(' ' == data[i] || ',' == data[i])
                {
                    if(isBeforeCommenStr){
                        
                    }
                    //string deal;
                    continue;
                }
                else
                {
                    isContinue = true;



                }
            }
            

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