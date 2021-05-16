#include <iostream>
#include "glucose.hpp"
using namespace ::Glucose;

Solver s;

void populate(){
    vec<Lit> clause1;
    clause1.push(mkLit(2));
    clause1.push(~mkLit(4));
    s.addClause(clause1);
}

void populate1(){
    vec<Lit> clause1;
    clause1.push(~mkLit(1));
    clause1.push(~mkLit(3));
    clause1.push(~mkLit(4));
    s.addClause(clause1);
}

int main()
{
std::cout << "Test"<< std::endl;

while(4 >= s.nVars()) 
s.newVar();


populate();
populate1();




vec<Lit> clause3;
clause3.push(~mkLit(3));
clause3.push(mkLit(4));
s.addClause(clause3);

vec<Lit> clause4;
clause4.push(mkLit(1));
clause4.push(~mkLit(2));
clause4.push(~mkLit(3));
s.addClause(clause4);

vec<Lit> clause5;
clause5.push(~mkLit(1));
clause5.push(~mkLit(3));
clause5.push(mkLit(4));
s.addClause(clause5);

vec<Lit> clause6;
clause6.push(~mkLit(2));
clause6.push(~mkLit(3));
s.addClause(clause6);

// vec<Lit> clause7;
// clause7.push(mkLit(2));
// s.addClause(clause7);
// clause7.push(mkLit(3));

// vec<Lit> clause8;
// clause8.push(~mkLit(2));
//s.addClause(clause3);






bool ans = s.solve();
std::cout << "This is :" <<ans << std::endl;
return 0;
}