#ifndef TESTVECTOR_H
#define TESTVECTOR_H

#include "TestingTools.h"
#include "Vector.h"

class TestVector
{
  public:
    TestVector(TestingTools &toolsRef);
    virtual ~TestVector();

    void emptyConstructor();
    void paramConstructor();
    void copyConstructor();
    void assignmentOperator();

    void next();

    void get();
    void getCurrent();
    void getCurrentIndex();
    void getSize();
    void getMaxSize();

    void insert();
    void insertEnd();
    void clear();
    void clearPtrs();
    void erase();
    void erasePtr();
    void empty();

    void increaseSize();
    void resetIndex();

  protected:
  private:
    TestingTools * tools;
};

#endif // TESTVECTOR_H
