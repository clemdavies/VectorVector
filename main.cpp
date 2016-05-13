#include <iostream>

#include "TestingTools.h"
#include "TestVector.h"

#include <vector>

using namespace std;

int main()
{


  TestingTools tools;
  TestVector test(tools);

  test.emptyConstructor();
  test.paramConstructor();
  test.copyConstructor();
  test.assignmentOperator();
  test.get();
  test.getSize();
  test.getMaxSize();
  test.insert();
  test.clear();
  test.empty();
  test.increaseSize();

  tools.outputTotals();
  cout << tools.getOutputStream().str() << endl;


    return 0;
}
