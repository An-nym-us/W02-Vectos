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

   int x = 5, y = 8;
   if(x & y)
      std::cout << "reager" << (x&y) << std::endl;
   else
      std::cout << "not" << (x & y) << std::endl;

   int32_t nums[3] = { 2,4,3 };
   std::cout << ( nums[0] << nums[1] << nums [2]) << std::endl;

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

