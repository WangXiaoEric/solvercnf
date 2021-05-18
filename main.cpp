#include <iostream>
#include <fstream>

#include "glucose.hpp"

using namespace ::Glucose;

#include <google/dense_hash_map>

#include <fstream>
#include <string>
#include <string.h>   
#include <hash_fun.h>
#include <vector>

#include <cstdio>
#include<ctime>



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
    result[length] = '\0';
    // delete target;
    //std::cout << result << std::endl;   
}

void getStringFromCharArrayAdvancedStr(string target, int begin, int end, string result)
{
    int length = end - begin;
    for (int i = 0; i < length; i++)
    {
        result[i] = target[i + begin];
    }
    // delete target;
    std::cout << result << std::endl;
    
}

Solver s;

int main(int argc, char* argv[]) {
    
    clock_t startTime,endTime;
    startTime = clock();//计时开始
    //delete the log result file.
    remove(argv[2]);

    // std::cout << "argv0  " << argv[0] << std::endl;
    // std::cout << "argv1  " << argv[1] << std::endl;
    // std::cout << "argv2  " << argv[2] << std::endl;

    //myTestFunctionAdvanced();

    //Store varibale and its index;
    dense_hash_map<const char*, int, __gnu_cxx::hash<const char*>, eqstr> varibleMap;
    varibleMap.set_empty_key(NULL);

    //Temp Data Structure
    //char data[100];
    string data;
    std::ifstream infile;

    string tempargv = argv[1];
    string inputPath = "./" + tempargv;
    // infile.open("./testcase/testcase1.v");
    infile.open(inputPath);

    char *result = NULL;

    int clauseCount = 0;
    std::vector<string> inputVector;
    

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
                            result = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            varibleMap[result] = index;
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;
                            //std::cout << "key -> \\A[2][9]" <<  " value -> "  << varibleMap["\\A[2][9]"] << std::endl;
                            
                            //std::cout << "varibleMap size  " << varibleMap.size()<< std::endl;

                            inputVector.push_back(result);
                            isBeforeCommenStr = false;
                            index++;
                            //delete result;
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
            if(data.find("eq  );") != string::npos)
            {
                varibleMap["eq"] = index;
                inputVector.push_back("eq");
                index++;
                //when reach eq, jump out continue to run outer loop
                continue;
            }
        }

        if(data.find(" wire ") != string::npos){
            while(data.find(");") == string::npos)
            {
                bool isBeforeCommenStr = false;
                int lastCharIndex = 0;

                for (int i = 0; i < data.length(); i++)
                {
                    if(' ' == data[i] || ',' == data[i] || ';' == data[i])
                    {
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("wire", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }

                            
                            varibleMap[result] = index;
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            

                            //std::cout << "varibleMap size  " << varibleMap.size()<< std::endl;
                            inputVector.push_back(result);

                            isBeforeCommenStr = false;
                            index++;
                            //delete result;
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
                std::getline(infile, data);
            }

        }
        // initialize newVar
        while(varibleMap.size() + 1 >= s.nVars()) s.newVar();

        // deal with not
        if(data.find("not  (") != string::npos){
            int y = 0;
            int x = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("not", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //(-y+-x)(y +x )
            vec<Lit> clause;
            clause.push(~mkLit(y));
            clause.push(~mkLit(x));

            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(mkLit(x));
            s.addClause(clause1);
            clauseCount++;

        }

        // deal with buf
        if(data.find("buf ") != string::npos){
            int y = 0;
            int x = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("buf", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //(-y+x)(y + -x )
            vec<Lit> clause;
            clause.push(~mkLit(y));
            clause.push(mkLit(x));
            s.addClause(clause);

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(~mkLit(x));
            s.addClause(clause1);

        }

        // deal with or  (y+-x1)(y+-r2)(-y +x1 + x2)
        if(data.find("or   (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("or", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //(y+-x1)(y+-r2)(-y +x1 + x2)
            vec<Lit> clause;
            clause.push(mkLit(y));
            clause.push(~mkLit(x1));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
            clauseCount++;
        }

        // deal with and  (-y+x1)(-y+x2)(y+-x1+-x2)
        if(data.find("and  (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("and", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            // deal with and  (-y+x1)(-y+x2)(y+-x1+-x2)
            vec<Lit> clause;
            clause.push(~mkLit(y));
            clause.push(mkLit(x1));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(~mkLit(x2));
            s.addClause(clause2);
            clauseCount++;
        }

        // deal nand (y+x1)(y+x2)(-y+-x1 +-x2)
        if(data.find("nand (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("nand", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //deal nand (y+x1)(y+x2)(-y+-x1 +-x2)
            vec<Lit> clause;
            clause.push(mkLit(y));
            clause.push(mkLit(x1));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(~mkLit(x2));
            s.addClause(clause2);
            clauseCount++;
        }

        // deal nor (-y+-x1))(-y+-x2)(y +x1 +x2)
        if(data.find("nor  (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("nor", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //deal nor (-y+-x1))(-y+-x2)(y +x1 +x2)
            vec<Lit> clause;
            clause.push(~mkLit(y));
            clause.push(~mkLit(x1));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
            clauseCount++;
        }

        // deal xor (-y+x1+x2)(-y+-x1+-x2)(y+-x1+x2)(y +x1+-x2)
        if(data.find("xor  (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("xor", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //deal xor (-y+x1+x2)(-y+-x1+-x2)(y+-x1+x2)(y +x1+-x2)
            vec<Lit> clause;
            clause.push(~mkLit(y));
            clause.push(mkLit(x1));
            clause.push(mkLit(x2));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(~mkLit(x1));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
            clauseCount++;

            vec<Lit> clause3;
            clause3.push(mkLit(y));
            clause3.push(mkLit(x1));
            clause3.push(~mkLit(x2));
            s.addClause(clause3);
            clauseCount++;
        }

        // deal xnor (y+x1+x2)(y +-x1 +-x2)(-y+-x1+x2)(-y +x1 +-x2)
        if(data.find("xnor (") != string::npos){
            int y = 0;
            int x1 = 0;
            int x2 = 0;
            int parameterCount = 1;
            bool isBeforeCommenStr = false;
            int lastCharIndex = 0;
            for (int i = 0; i < data.length(); i++)
            {
                if(' ' == data[i] || ',' == data[i] || ';' == data[i] || '(' == data[i] || ')' == data[i])
                    {
                        
                        //then should store one parameter
                        if(isBeforeCommenStr){
                            result = new char [i - lastCharIndex + 1];
                            //resultWire = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("xnor", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }
                            //std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
                            if(parameterCount == 1){
                                y = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 2)
                            {
                                x1 = varibleMap[result];
                                parameterCount++;
                            }
                            else if (parameterCount == 3)
                            {
                                x2 = varibleMap[result];
                                parameterCount++;
                            }
                            
                            isBeforeCommenStr = false;
                            //delete result;
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
            //deal  xnor (y+x1+x2)(y +-x1 +-x2)(-y+-x1+x2)(-y +x1 +-x2)
            vec<Lit> clause;
            clause.push(mkLit(y));
            clause.push(mkLit(x1));
            clause.push(mkLit(x2));
            s.addClause(clause);
            clauseCount++;

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(~mkLit(x1));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);
            clauseCount++;

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
            clauseCount++;

            vec<Lit> clause3;
            clause3.push(~mkLit(y));
            clause3.push(mkLit(x1));
            clause3.push(~mkLit(x2));
            s.addClause(clause3);
            clauseCount++;
        }
    }

    // add the primary output clause;
    int eqindex = varibleMap["eq"];
    //std::cout << "eqindex is :" <<eqindex << std::endl;
    vec<Lit> clauseeq;
    clauseeq.push(mkLit(eqindex));
    s.addClause(clauseeq);

	
    infile.close();
    
    // vec<Lit> clause;
    // clause.push(mkLit(100));
    // std::cout << s.nVars()<< std::endl;
    // clause.push(mkLit(101));
    // clause.push(~mkLit(102));
    // while(4 >= s.nVars()) 
    // s.newVar();
    // s.addClause(clause);
    
    //std::cout << "clauseCount is :" <<clauseCount << std::endl;

    // s.printClause(1000);
    // s.printInitialClause(1);



    bool ans = s.solve();
    //std::cout << "This is :" <<ans << std::endl;
    //ht::iterator it = varibleMap.begin();

    // for (dense_hash_map<int*, int>::iterator it = varibleMap.begin(); it != varibleMap.end(); ++it) {

    //     std::cout << "EQ" << std::endl;
    // }

    //std::cout << "inputVector size is :" << inputVector.size() << std::endl;
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::ofstream of(argv[2]);
    std::streambuf* fileBuf = of.rdbuf();
    std::cout.rdbuf(fileBuf);

    if(ans){
        std::cout << "EQ" << std::endl;
    }else{
        std::cout << "NEQ" << std::endl;
        // for(int i = 0; i <= 1008; i ++){
        //     s.printLit(mkLit(i));
        //     std::cout << std::endl;
        // }

        for (int i = 0; i < inputVector.size();i++)
        {
            const char *abc = inputVector[i].c_str();
            int tempVaribale = varibleMap[abc];
            //std::cout << s.getLitValue(mkLit(9)) << std::endl;
            std::cout << "<" << inputVector[i] << "><"  << s.getLitValue(mkLit(tempVaribale)) << ">"   << std::endl;
        }
    }

    endTime = clock();//计时结束
    std::cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;

    of.flush();
    of.close();
    // 恢复cout原来的流缓冲区指针
    std::cout.rdbuf(coutBuf);
    
    return 0;
}