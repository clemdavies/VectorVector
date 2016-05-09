#include "TestVector.h"

TestVector::TestVector(TestingTools &toolsRef)
{
  tools = &toolsRef;
  tools->setClassName("Vector");
}

TestVector::~TestVector()
{
  //dtor
}


void TestVector::emptyConstructor()
{
	tools->setFunctionName("emptyConstructor");
	{
		Vector<int> instance1;
		Vector<float> instance2;
		Vector<int> instance3;
    tools->assertTypeNotEquals(instance1,instance2);
    tools->assertTypeEquals(instance1,instance3);
	}
	{
		Vector<int*> instance1;
		Vector<float*> instance2;
		Vector<int*> instance3;
    tools->assertTypeNotEquals(instance1,instance2);
    tools->assertTypeEquals(instance1,instance3);
    instance1.clearPtrs();
    instance2.clearPtrs();
    instance3.clearPtrs();
	}
}

void TestVector::paramConstructor()
{
	tools->setFunctionName("paramConstructor");
	{
		Vector<int> instance(3);
		tools->assertEquals(instance.getMaxSize(),(unsigned)10);
	}
	{
		Vector<int> instance(100);
		tools->assertEquals(instance.getMaxSize(),(unsigned)100);
	}
	{
		Vector<const char *> instance(100);
		tools->assertEquals(instance.getMaxSize(),(unsigned)100);
	}
	{
	  tools->description("Vector of Vectors");
		Vector<Vector<int>> instance;
		Vector<int> inner;
		instance.insert(0,inner);
		tools->assertEquals(instance.getSize(),(unsigned)1);
		tools->assertEquals(instance.get(0).getSize(),(unsigned)0);
		tools->assertEquals(instance.getMaxSize(),(unsigned)10);
		tools->assertEquals(instance.get(0).getMaxSize(),(unsigned)10);
	}
}

void TestVector::copyConstructor()
{
	tools->setFunctionName("copyConstructor");
	{
		Vector<int> copyFrom;
		copyFrom.insert(0,5);
		copyFrom.insert(1,6);
		copyFrom.insert(2,7);
		tools->assertEquals( copyFrom.get(0), 5);
		tools->assertEquals( copyFrom.get(1), 6);
		tools->assertEquals( copyFrom.get(2), 7);
		Vector<int> copyTo( copyFrom );
		tools->assertEquals(copyTo.get(0),5);
		tools->assertEquals(copyTo.get(1),6);
		tools->assertEquals(copyTo.get(2),7);
		tools->assertEquals(copyFrom.getSize(),copyTo.getSize());
		tools->assertEquals(copyFrom.getMaxSize(),copyTo.getMaxSize());
	}
	{
		Vector<const char *> copyFrom;
		copyFrom.insert(0,"Clem");
		copyFrom.insert(1,"W");
		copyFrom.insert(2,"Davies");
		tools->assertEquals( copyFrom.get(0), "Clem");
		tools->assertEquals( copyFrom.get(1), "W");
		tools->assertEquals( copyFrom.get(2), "Davies");
		Vector<const char *> copyTo( copyFrom );
		tools->assertEquals(copyTo.get(2),"Davies");
		tools->assertEquals(copyTo.get(1),"W");
		tools->assertEquals(copyTo.get(0),"Clem");
	}
}

void TestVector::assignmentOperator()
{
	tools->setFunctionName("assignementOperator");
	{
	  Vector<int> copyFrom;
		Vector<int> instance = copyFrom;
    tools->assertTypeEquals(instance,copyFrom);
    tools->assertEquals(instance.getMaxSize(),(unsigned)10);
    tools->assertEquals(instance.getSize(),(unsigned)0);
	}
	{
	  Vector<int> copyFrom(5);
	  copyFrom.insert(0,2);
	  copyFrom.insert(1,4);
	  copyFrom.insert(2,8);
	  copyFrom.insert(3,16);
	  copyFrom.insert(4,32);
		Vector<int> instance = copyFrom;
    tools->assertEquals(instance.getMaxSize(),(unsigned)10);
    tools->assertEquals(copyFrom.getSize(),(unsigned)5);
    tools->assertEquals(instance.getSize(),(unsigned)5);
    tools->assertEquals(instance.get(4),32);
    tools->assertEquals(instance.get(3),16);
    tools->assertEquals(instance.get(2),8);
    tools->assertEquals(instance.get(1),4);
    tools->assertEquals(instance.get(0),2);
	}
}

void TestVector::next()
{
	tools->setFunctionName("next");
	{
		Vector<int> instance;
		instance.insert(0,5);
		instance.insert(1,6);
		instance.insert(2,7);
		instance.insert(3,8);
    instance.resetPtr();
		tools->assertEquals(instance.getCurrent(),5);
		tools->assertTrue(instance.next());
		tools->assertEquals(instance.getCurrent(),6);
		tools->assertTrue(instance.next());
		tools->assertEquals(instance.getCurrent(),7);
		tools->assertTrue(instance.next());
		tools->assertEquals(instance.getCurrent(),8);
		tools->assertFalse(instance.next());
    instance.resetPtr();
		tools->assertEquals(instance.getCurrent(),5);
		instance.next();
		tools->assertEquals(instance.getCurrent(),6);
	}
}

void TestVector::get()
{
	tools->setFunctionName("at");
	{
		Vector<int> instance;
		instance.insert(0,1);
		instance.insert(1,2);
		instance.insert(2,3);
    tools->assertEquals(instance.get(0),1);
    tools->assertEquals(instance.get(1),2);
    tools->assertEquals(instance.get(2),3);
	}
}

void TestVector::getCurrent()
{
	tools->setFunctionName("getCurrent");
	{
		Vector<int> instance;
		instance.insert(0,5);
		instance.insert(1,6);
		tools->assertEquals(instance.getCurrent(),6);
		instance.insert(2,7);
		tools->assertEquals(instance.getCurrent(),7);
		instance.insert(3,8);
		tools->assertEquals(instance.getCurrent(),8);
		instance.resetPtr();
		tools->assertEquals(instance.getCurrent(),5);
    instance.insert(4,25);
		tools->assertEquals(instance.getCurrent(),25);
    instance.insert(6,30);
		instance.resetPtr();
		for(unsigned i = 0;i<5;i++)instance.next();
		tools->assertEquals(instance.getCurrent(),30);
	}
}


void TestVector::getCurrentIndex()
{
	tools->setFunctionName("getCurrentIndex");
	{
		Vector<int> instance;
		tools->assertEquals(instance.getCurrentIndex(),-1);
		instance.insert(0,5);
		instance.insert(1,6);
		tools->assertEquals(instance.getCurrentIndex(),1);
		instance.insert(2,7);
		tools->assertEquals(instance.getCurrentIndex(),2);
		instance.insert(3,8);
		tools->assertEquals(instance.getCurrentIndex(),3);
		instance.resetPtr();
		tools->assertEquals(instance.getCurrentIndex(),0);
    instance.insert(4,25);
		tools->assertEquals(instance.getCurrentIndex(),4);
    instance.insert(6,30);
		instance.resetPtr();
		for(unsigned i = 0;i<5;i++)instance.next();
		tools->assertEquals(instance.getCurrentIndex(),6);
	}
}


void TestVector::getSize()
{
	tools->setFunctionName("getSize");
	{
		Vector<int> instance;
		instance.insert(0,1);
		instance.insert(1,2);
		instance.insert(2,3);
    tools->assertEquals(instance.getSize(),(unsigned)3);
    instance.insert(3,4);
    instance.insert(4,5);
    tools->assertEquals(instance.getSize(),(unsigned)5);
	}
}

void TestVector::getMaxSize()
{
	tools->setFunctionName("getMaxSize");
	{
		Vector<int> instance;
    tools->assertEquals(instance.getMaxSize(),(unsigned)10);
		instance.insert(0,1);
		instance.insert(1,2);
		instance.insert(2,3);
    tools->assertEquals(instance.getMaxSize(),(unsigned)10);
	}
	{
		Vector<int> instance(110);
    tools->assertEquals(instance.getMaxSize(),(unsigned)110);
		instance.insert(0,1);
		instance.insert(1,2);
		instance.insert(2,3);
    tools->assertEquals(instance.getMaxSize(),(unsigned)110);
	}
}

void TestVector::insert()
{
	tools->setFunctionName("insert");
	{
		Vector<int> instance;
		instance.insert(0,5);
		tools->assertEquals(instance.get(0),5);
		instance.insert(2,3);
		tools->assertEquals(instance.get(2),3);
	}
	{
		Vector<const char *> instance;
		instance.insert(0,"Clem");
		tools->assertEquals(instance.get(0),"Clem");
		instance.insert(2,"Davies");
		tools->assertEquals(instance.get(2),"Davies");
		tools->assertEquals(instance.getSize(),(unsigned)2);
	}
}

void TestVector::insertEnd()
{
  tools->setFunctionName("insertEnd");
  {
    Vector<int> instance;
    instance.insertEnd(10);
    instance.insertEnd(20);
    instance.insertEnd(30);
    tools->assertEquals(instance.get(0),10);
    tools->assertEquals(instance.get(1),20);
    tools->assertEquals(instance.get(2),30);
  }
}

void TestVector::clear()
{
	tools->setFunctionName("clear");
	{
		Vector<int> instance;
		instance.insert(0,5);
		instance.insert(1,6);
		instance.insert(2,8);
		instance.clear();
		tools->assertTrue(instance.empty());
	}
	{
		Vector<const char *> instance;
		instance.insert(0,"Clem");
		instance.insert(1,"W");
		instance.insert(2,"Davies");
		instance.clear();
		tools->assertTrue(instance.empty());
	}
}

void TestVector::clearPtrs()
{
  tools->setFunctionName("clearPtrs");
  {
    Vector<int*> instance;
    int *i1 = new int(5),
        *i2 = new int(10),
        *i3 = new int(15);
    instance.insertEnd(i1);
    instance.insertEnd(i2);
    instance.insertEnd(i3);
    tools->assertFalse( instance.empty() );
    tools->assertEquals(i1,instance.get(0));
    instance.clearPtrs();
    tools->assertTrue( instance.empty() );
  }
}

void TestVector::erase()
{
	tools->setFunctionName("erase");
	{
		Vector<int> instance;
		instance.insert(0,5);
		instance.insert(1,6);
		instance.insert(2,8);
		instance.erase(0);
		tools->assertEquals(instance.getSize(),(unsigned)2);
		instance.erase(0);
		tools->assertEquals(instance.getSize(),(unsigned)2);
		instance.erase(1);
		tools->assertEquals(instance.getSize(),(unsigned)1);
		instance.erase(1);
		tools->assertEquals(instance.getSize(),(unsigned)1);
		instance.erase(2);
		tools->assertEquals(instance.getSize(),(unsigned)0);
	}
	{
		Vector<const char *> instance;
		instance.insert(0,"Clem");
		instance.insert(1,"W");
		instance.insert(2,"Davies");
		instance.erase(0);
		tools->assertEquals(instance.getSize(),(unsigned)2);
		instance.erase(0);
		tools->assertEquals(instance.getSize(),(unsigned)2);
		instance.erase(1);
		tools->assertEquals(instance.getSize(),(unsigned)1);
		instance.erase(1);
		tools->assertEquals(instance.getSize(),(unsigned)1);
		instance.erase(2);
		tools->assertEquals(instance.getSize(),(unsigned)0);
	}
}

void TestVector::erasePtr()
{
  tools->setFunctionName("erasePtr");
  {
    Vector<int*> instance;
    int *i1 = new int(5),
        *i2 = new int(10),
        *i3 = new int(15);
    instance.insertEnd(i1);
    instance.insertEnd(i2);
    instance.insertEnd(i3);
    tools->assertTrue( instance.hasValue(0) );
    tools->assertEquals(instance.get(0),i1);
    instance.erasePtr(0);
    tools->assertFalse( instance.hasValue(0) );
    tools->assertNotEquals(instance.get(0),i1);
    tools->assertEquals(*i2,10);
    instance.erasePtr(1);
    instance.erasePtr(2);
  }
}

void TestVector::empty()
{
	tools->setFunctionName("empty");
	{
		Vector<const char *> instance;
		tools->assertTrue(instance.empty());
		instance.insert(0,"Clem");
		instance.insert(1,"W");
		instance.insert(2,"Davies");
		tools->assertFalse(instance.empty());
	}
}

void TestVector::increaseSize()
{
	tools->setFunctionName("increaseSize");
	{
		Vector<int> instance;
    tools->assertEquals( instance.getMaxSize(),(unsigned)10 );
		instance.insert(1,2);
    instance.insert(10,25);
		tools->assertEquals( instance.getSize(),(unsigned)2 );
		tools->assertEquals( instance.get(1),2 );
		tools->assertEquals( instance.get(10),25 );
		tools->assertEquals( instance.getSize(),(unsigned)2 );
		tools->assertEquals( instance.getMaxSize(),(unsigned)15 );
    instance.insert(15,35);
		tools->assertEquals( instance.getSize(),(unsigned)3 );
		tools->assertEquals( instance.get(10),25 );
		tools->assertEquals( instance.getSize(),(unsigned)3 );
		tools->assertEquals( instance.get(15),35 );
		tools->assertEquals( instance.getSize(),(unsigned)3 );
		tools->assertEquals( instance.getMaxSize(),(unsigned)23 );
		instance.insert(100,55);
		/*
      new = ceil(old * 1.5)
      23 * 1.5 = 23 + 11.5 = 34.5 = 35
      35 * 1.5 = 35 + 17.5 = 52.5 = 53
      53 * 1.5 = 53 + 26.5 = 79.5 = 80
      80 * 1.5 = 80 + 40 = 120 = 120
		*/
		tools->assertEquals( instance.getSize(),(unsigned)4 );
		tools->assertEquals( instance.getMaxSize(),(unsigned)120 );
		tools->assertEquals( instance.get(100) ,55 );
		instance.erase(15);
		tools->assertEquals( instance.getSize(),(unsigned)3 );
		tools->assertEquals( instance.getMaxSize(),(unsigned)120 );
		instance.clear();
		tools->assertTrue( instance.empty() );
		tools->assertEquals( instance.getSize(),(unsigned)0 );
		tools->assertEquals( instance.getMaxSize(),(unsigned)10 );
	}
}


void TestVector::resetIndex()
{
  tools->setFunctionName("resetIndex");
  {
    Vector<int> instance;
    instance.insert(5,20);
    instance.insert(10,25);
    instance.insert(20,35);
    tools->assertEquals(instance.getCurrentIndex(),20);
    instance.erase(20);
    tools->assertEquals(instance.getCurrentIndex(),5);
    instance.resetPtr();
    instance.erase(5);
    tools->assertEquals(instance.getCurrentIndex(),10);
  }
}
