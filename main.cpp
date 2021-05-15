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
    result[length] = '\0';
    // delete target;
    std::cout << result << std::endl;   
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
    string result = "123";
    getStringFromCharArrayAdvancedStr(target, begin, end, result);
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
    char *result = NULL;
    Solver s;

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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;
                            std::cout << "key -> \\A[2][9]" <<  " value -> "  << varibleMap["\\A[2][9]"] << std::endl;
                            
                            std::cout << "varibleMap size  " << varibleMap.size()<< std::endl;
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
                            if (index == 65)
                            {
                                int abc = 100;
                            }
                            if (index == 66)
                            {
                                int abc = 100;
                            }

                            result = new char [i - lastCharIndex + 1];
                            getStringFromCharArrayAdvanced(data, lastCharIndex, i, result);
                            // string tempSt(result);
                            // string tempSt = result;
                            if(strcmp("wire", result) == 0){
                                isBeforeCommenStr = false;
                                continue;
                            }

                            
                            varibleMap[result] = index;
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            

                            std::cout << "varibleMap size  " << varibleMap.size()<< std::endl;   ;
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
        // deal with not
        if(data.find("not ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap["new_n50_"] << std::endl;                            
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(mkLit(x));
            s.addClause(clause1);

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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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
        if(data.find("or ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
        }

        // deal with and  (-y+x1)(-y+x2)(y+-x1+-x2)
        if(data.find("and ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(~mkLit(x2));
            s.addClause(clause2);
        }

        // deal nand (y+x1)(y+x2)(-y+-x1 +-x2)
        if(data.find("nand ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(~mkLit(x2));
            s.addClause(clause2);
        }

        // deal nor (-y+-x1))(-y+-x2)(y +x1 +x2)
        if(data.find("nor ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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
            clause.push(mkLit(x1));
            s.addClause(clause);

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);
        }

        // deal xor (-y+x1+x2)(-y+-x1+-x2)(y+-x1+x2)(y +x1+-x2)
        if(data.find("xor ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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

            vec<Lit> clause1;
            clause1.push(~mkLit(y));
            clause1.push(~mkLit(x1));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);

            vec<Lit> clause3;
            clause3.push(mkLit(y));
            clause3.push(mkLit(x1));
            clause3.push(~mkLit(x2));
            s.addClause(clause3);
        }

        // deal xnor (y+x1+x2)(y +-x1 +-x2)(-y+-x1+x2)(-y +x1 +-x2)
        if(data.find("xnor ") != string::npos){
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
                            std::cout << "key  " << result <<  " value -> " << varibleMap[result] << std::endl;                            
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
            //deal xor (y+x1+x2)(y +-x1 +-x2)(-y+-x1+x2)(-y +x1 +-x2)
            vec<Lit> clause;
            clause.push(mkLit(y));
            clause.push(mkLit(x1));
            clause.push(mkLit(x2));
            s.addClause(clause);

            vec<Lit> clause1;
            clause1.push(mkLit(y));
            clause1.push(~mkLit(x1));
            clause1.push(~mkLit(x2));
            s.addClause(clause1);

            vec<Lit> clause2;
            clause2.push(~mkLit(y));
            clause2.push(~mkLit(x1));
            clause2.push(mkLit(x2));
            s.addClause(clause2);

            vec<Lit> clause3;
            clause3.push(~mkLit(y));
            clause3.push(mkLit(x1));
            clause3.push(~mkLit(x2));
            s.addClause(clause3);
        }

    }


	infile.close();

    bool ans = s.solve();
    std::cout << "This is :" <<ans << std::endl;
    return 0;
}