#include <iostream>
#include "glucose.hpp"
using namespace ::Glucose;

int main()
{
std::cout << "Test"<< std::endl;
Solver s;

vec<Lit> clause;
clause.push(mkLit(1));
// std::cout << s.nVars()<< std::endl;
clause.push(mkLit(2));
clause.push(~mkLit(3));

while(3 >= s.nVars()) 
s.newVar();

s.addClause(clause);
bool ans = s.solve();
std::cout << "This is :" <<ans << std::endl;
return 0;
}