#ifndef TESTINGTOOLS_H
#define TESTINGTOOLS_H

#include <vector>
#include <iostream>
#include <typeinfo>
#include <string.h>
#include <string>
#include <exception>

#include <sstream>

using namespace std;

  /**
   * @class TestingTools
   * @brief Class used for unit testing.
   *
   * @author Clem Davies
   * @version 01
   * @date 07/04/2016
   *
   * @update decouple testing logic, output logic, output values.
   * @update implement iostream as output instead of outputStream
   * @update use constants for cstrings, and booleans for ==  != strings.
   * @update REMOVE SINGLETON DESIGN PATTERN. DEPENDANCY INJECTION FTW.
   */
class TestingTools
{
  public:
      /**
       * Destructor
       */
    virtual ~TestingTools(){};

      /**
       * @brief Constructor sets properties are to initial state.
       */
    TestingTools()
    {
      resetValues();
    };

      /**
       * @brief returns reference to outputStream.
       */
    const std::stringstream & getOutputStream()
    {
      return outputStream;
    };


      /**
       * @brief Outputs the totals for all tests and list of failed functions
       *
       * @update better output decoupling.
       */
    void outputTotals()
    {
      outputStream << std::endl
                   << "TEST TOTALS" << std::endl
                   << "Ran: " << totalTestsRan << std::endl
                   << "Passed: " << totalTestsPassed << std::endl
                   << "Failed: " << totalTestsFailed << std::endl;
      outputFailedFunctions();
    };

      /**
       * @brief Outputs a description at user's discretion.
       * @param description - Description for output.
       */
    void description( const char * description )
    {
      outputClassName();
      outputFunctionName();
      outputStream << description << std::endl;
    };

      /**
       * @brief Sets the class name for the current test.
       * Set at the start of testing a class.
       * @param newClassName - The class name to be output.
       */
    void setClassName( const char * newClassName )
    {
      classNameOutput = false;
      className = newClassName;
    };

      /**
       * @brief Returns the currently set class name.
       */
    const char * getClassName()
    {
      return className;
    }
      /**
       * @brief Returns the currently set function name.
       */
    const char * getFunctionName()
    {
      return functionName;
    }

      /**
       * @brief Sets the function name for the current test.
       * Set at the start of testing a function.
       * @param newClassName - The function name to be output.
       */
    void setFunctionName( const char * newFunctionName )
    {
      functionNameOutput = false;
      functionName = newFunctionName;
    };

      /**************************************************
                        BOOLEAN TESTS
       **************************************************/
      /**
       * @brief Tests a boolean value against true.
       * @param trueValue - Value to be tested.
       */
    void assertTrue( bool trueValue )
    {
      output( trueValue == true,"True" );
    };
      /**
       * @brief Tests a boolean value against false.
       * @param falseValue - Value to be tested.
       */
    void assertFalse( bool falseValue )
    {
      output( falseValue == false,"False" );
    };


      /**************************************************
                        VALUE TESTS
       **************************************************/
      /**
       * @brief Does an equal comparison against two values.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       */
    template <class T>
    void assertEquals( T predicted, T actual )
    {
      output(equalTest(predicted,actual),getTypeName(predicted),"==",predicted,actual);
    };
      /**
       * @brief Does a not equal comparison against two values.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       */
    template <class T>
    void assertNotEquals( T predicted, T actual )
    {
      output(equalTest(predicted,actual,false),getTypeName(predicted),"!=",predicted,actual);
    };

      /**
       * @brief Tests parsed value for what type it is, returning a human readable type name.
       * @param test - value to be tested.
       * @return the type name of parsed value.
       */
    template <class T>
    const char * getTypeName(T test)
    {
      const char * testname = typeid(test).name();
      if( strcmp(testname,typeid(int).name()) == 0)
      {
        return "int";
      }
      else if( strcmp(testname,typeid(float).name()) == 0)
      {
        return "float";
      }
      else if( strcmp(testname,typeid(double).name()) == 0)
      {
        return "double";
      }
      else if( strcmp(testname,typeid(unsigned).name()) == 0)
      {
        return "unsigned";
      }
      else if( strcmp(testname,typeid(long).name()) == 0)
      {
        return "long";
      }
      else if( strcmp(testname,typeid(const char *).name()) == 0)
      {
        return "cstring";
      }
      else if( strcmp(testname,typeid(std::string).name()) == 0)
      {
        return "string";
      }
      else
      {
        return "object";
      }
    }

      /**************************************************
                        TYPE TESTS
       **************************************************/

      /**
       * @brief Uses typeid().name() to do equality test of params types.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       */
    template <class T1, class T2>
    void assertTypeEquals( T1 predicted, T2 actual )
    {
      output(typeTest(predicted,actual),"Type","==", typeid(predicted).name(), typeid(actual).name());
    };
      /**
       * @brief Uses typeid().name() to do not equality test of params types.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       */
    template <class T1, class T2>
    void assertTypeNotEquals( T1 predicted, T2 actual )
    {
      output(typeTest(predicted,actual,false),"Type","!=", typeid(predicted).name(), typeid(actual).name());
    };

  protected:
  private:

      /// Currently tested class name.
    const char * className;
      /// Currently tested function name.
    const char * functionName;
      /// State of whether className has been output.
    bool classNameOutput;
      /// State of whether functionName has been output.
    bool functionNameOutput;

      /// Formatting output for passed results.
    const char * PASS_SPACER;
      /// Formatting output for failed results.
    const char * FAIL_SPACER;

      /// Count of tests run.
    unsigned totalTestsRan;
      /// Count of tests passed.
    unsigned totalTestsPassed;
      /// Count of tests failed.
    unsigned totalTestsFailed;


      /// Iterates to ensure a unique id is assigned to each class.
    unsigned uniqueClassID;
      /// Iterates to ensure a unique id is assigned to each function.
    unsigned uniqueFunctionID;
      /// The previous unique class id.
    unsigned lastClassID;
      /// The previous unique function id.
    unsigned lastFunctionID;

      /// The current count of tests run for a function.
    unsigned testCount;

      /// Vector of classNames of failed tests without duplicates. No delimiters.
    vector<const char *> classNames;
      /// Vector of functionNames of failed tests without duplicates. Empty String delimiters.
    vector<const char *> functionNames;
      /// Vector of testNumbers of failed tests without duplicates. 0 delimiters.
    vector<unsigned> testNumbers;
      /// Buffer to store output string.
    std::stringstream outputStream;


      /**
       * @brief Resets properties to initial state.
       * Used between calls to TestingTools::getInstance() to ensure properties are set to their initial state.
       */
    void resetValues()
    {
      className = "";
      functionName = "";

      PASS_SPACER = "----------";
      FAIL_SPACER = "++++++++++";

      functionNameOutput = false;
      classNameOutput = false;

      totalTestsRan = 0;
      totalTestsPassed = 0;
      totalTestsFailed = 0;

      uniqueClassID = 0;
      uniqueFunctionID = 0;
      lastClassID = 0;
      lastFunctionID = 0;
      testCount = 0;

      outputStream.flush();
    };


      /**
       * @brief Iterates total values.
       * Adds 1 to totalTestsRan and 1 to either totalsTestsPassed or totalTestsFailed according to test result.
       * @param result - Passed or failed boolean value.
       */
    void iterateTotals(bool result)
    {
      totalTestsRan++;
      if(result)
        totalTestsPassed++;
      else
        totalTestsFailed++;
    };

      /**
       * @brief Template function for running equalTests.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       * @param boolSwitch - Changes this test from == to !=.
       */
    template <class T>
    bool equalTest(T predicted,T actual,bool boolSwitch = true)
    {
      bool result = false;
      if( (predicted == actual) == boolSwitch )
        result = true;
      return result;
    };
      /**
       * @brief Cstring function for running equalTests.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       * @param boolSwitch - Changes this test from == to !=.
       */
    bool equalTest(const char * predicted,const char * actual,bool boolSwitch = true)
    {
      bool result = false;
      if( (strcmp(predicted,actual) == 0) == boolSwitch )
        result = true;
      return result;
    };

      /**
       * @brief Template function for running typeTest.
       * Uses typeid to test if both values are equal or not equal in type.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       * @param boolSwitch - Changes this test from == to !=.
       */
    template <class T1, class T2>
    bool typeTest(T1 predicted,T2 actual,bool boolSwitch = true)
    {
      bool result = false;
      if ( (typeid(predicted).name() == typeid(actual).name()) == boolSwitch )
        result = true;
      return result;
    };
      /**
       * @brief Accepts template params for outputting result for this test.
       * Attempts to output class and function name. Outputs values for predicted and actual and the boolean result.
       * @param result - Passed or failed boolean value.
       * @param message - Any cstring message to output, usually name of test ran.
       * @param operation - Cstring of operation performed either == or !=.
       * @param predicted - Predicted value for this test.
       * @param actual - Actual value for this test.
       * @update operation should be a boolean true being == and false being !=.
       */
    template <class T>
    void output(bool result, const char *message, const char *operation, T predicted, T actual)
    {
      outputClassName();
      outputFunctionName();
      outputStream << message << ": " << predicted << " " << operation << " " << actual << std::endl;
      outputResult(result);
      outputStream << std::endl;
    };


      /**
       * @brief Outputs result for this test.
       * Attempts to output class and function name. Outputs values object A and object B as placeholders for large object outputs
       * or objects wihtout an output function. Outputs the result of the test.
       * @param result - Passed or failed boolean value.
       * @param message - Any cstring message to output, usually name of test ran.
       * @param operation - Cstring of operation performed either == or !=.
       * @update operation should be a boolean true being == and false being !=.
       */
    void output( bool result, const char * message, const char *operation)
    {
      outputClassName();
      outputFunctionName();
      outputStream << message << ": " << "object A " << operation <<  " object B"  << std::endl;
      outputResult(result);
      outputStream << std::endl;
    };

      /**
       * @brief Outputs result for this test.
       * Attempts to output class and function name. Outputs a message and the result of the test.
       * @param result - Passed or failed boolean value.
       * @param message - Any cstring message to output, usually name of test ran.
       */
    void output(bool result,const char * message)
    {
      outputClassName();
      outputFunctionName();
      outputStream << message << std::endl;
      outputResult(result);
      outputStream<<std::endl;
    };


      /**
       * @brief Adds current function names, class name, and test number to vectors.
       * Uses unique ids to ensure no duplicates are stored in vectors.
       * Stores empty strings and 0 as wildcards to trigger a shift in the next array on output.
       */
    void appendFailedFunctions()
    {
      if(testNumbers.size() == 0 || uniqueClassID != lastClassID){
        lastClassID = uniqueClassID;
        classNames.push_back(className);
        if(testNumbers.size() > 0){
          functionNames.push_back("");
        }
      }

      if(testNumbers.size() == 0 || uniqueFunctionID != lastFunctionID)
      {
        lastFunctionID = uniqueFunctionID;
        functionNames.push_back(functionName);
        if(testNumbers.size() > 0){
          testNumbers.push_back(0);
        }
      }
      testNumbers.push_back(testCount);
    };

      /**
       * @brief Outputs current test class name.
       * Ensures the class name is only output once for each unique class.
       * @update Logic should not be a part of this output function.
       */
    void outputClassName()
    {
      if(!classNameOutput){
        outputStream << std::endl << "CLASS:    "  << className << std::endl;
        classNameOutput = true;
        uniqueClassID++;
      }
    };
      /**
       * @brief Outputs current test function name.
       * Ensures the function name is only output once for each unique function.
       * @update Logic should not be a part of this output function.
       */
    void outputFunctionName()
    {
      if(!functionNameOutput){
        outputStream << std::endl << "FUNCTION: " << functionName << std::endl << std::endl;
        functionNameOutput = true;
        uniqueFunctionID++;
        testCount = 0;
      }
    };
      /**
       * @brief Outputs the result of current test.
       * Formatted output for current test result. Iterates testCount and totals by 1.
       * @param result - Passed or failed boolean value.
       * @update Logic should not be a part of this output function.
       */
    void outputResult(bool result)
    {
      testCount++;
      iterateTotals(result);
      if(result){
        outputStream << PASS_SPACER << "PASSED" << PASS_SPACER;
      }
      else
      {
        outputStream << FAIL_SPACER << "FAILED" << FAIL_SPACER;
        appendFailedFunctions();
      }
    };
      /**
       * @brief Outputs a simple list of classNames, functionNames and testNumbers of all failed tests.
       * Class name is only output once for each failed class. Function name is only output once for each failed function.
       * There can only be one number for a failed test.
       * When all the test numbers for this function is output, iterate the functions vector, if all functions
       * have been output for this class, iterate the classes vector.
       * output is finished when all vectors have reached their last member.
       */
    void outputFailedFunctions()
    {

      unsigned funct_i = 0;
      unsigned class_i = 0;
      bool classOut = false;
      bool functOut = false;
      bool newLine = false;
      unsigned spaceLength = 0;

      for(unsigned test_i = 0; test_i < testNumbers.size() ; test_i++)
      {
        if(testNumbers[test_i] == 0)
        {
          // new function
          functOut = false;
          newLine  = true;
          funct_i++;
          if( strlen(functionNames[funct_i]) == 0 )
          {
          // new class
            classOut = false;
            class_i++;
            funct_i++;
          }
          outputStream << std::endl;
          continue;
        }

        if(!classOut)
        {
          outputStream << classNames[class_i] << "::";
          classOut = true;
          newLine  = false;
          spaceLength = strlen(classNames[class_i]) + 2;
        }
        if(!functOut)
        {
          for(unsigned space_i = 0; newLine && space_i < spaceLength; space_i++)
          {
            outputStream << " ";
          }
          outputStream << functionNames[funct_i];
          functOut = true;
          newLine = false;
        }
        outputStream << ":" << testNumbers[test_i];
      }


    };
};




#endif // TESTTOOLS_H
