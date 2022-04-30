/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test vector.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   
#endif
 //#undef DEBUG  // Remove this comment to disable unit tests

#include "testVector.h"     // for the vector unit tests
#include "testSpy.h"        // for the spy unit tests
int Spy::counters[] = {};

#include <vector>
#include <iostream>


/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{

   //std::vector<int> test =  {1,2,3,7};


   //std::vector<int> sec;
   //for (int i = 0; i < test.size(); i++)
   //   std::cout << test[i] << std::endl;

   //for (int i = 0; i < sec.size(); i++)
   //   std::cout << sec[i] << std::endl;

   //std::cout << "spacer" << std::endl;

   //sec = test;

   //for (int i = 0; i < test.size(); i++)
   //   std::cout << test[i] << std::endl;

   //for (int i = 0; i < sec.size(); i++)
   //   std::cout << sec[i] << std::endl;

#ifdef DEBUG
   // unit tests
   TestSpy().run();
   TestVector().run();
#endif // DEBUG
   
   return 0;
}

