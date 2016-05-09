#include <iostream>

#include "TestingTools.h"
#include "TestVector.h"

using namespace std;

int main()
{
  TestingTools tools;
  TestVector test(tools);

  test.emptyConstructor();
  test.paramConstructor();
  test.copyConstructor();
  test.assignmentOperator();
  test.next();
  test.get();
  test.getCurrent();
  test.getCurrentIndex();
  test.getSize();
  test.getMaxSize();
  test.insert();
  test.insertEnd();
  test.clear();
  test.clearPtrs();
  test.erase();
  test.erasePtr();
  test.empty();
  test.increaseSize();
  test.resetIndex();

  tools.outputTotals();
  cout << tools.getOutputStream().str() << endl;


    return 0;
}
