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

#include "testVector.h"  
#include "vector.h"// for the vector unit tests
#include <vector>
using namespace std;


/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{

  /* vector < int> myvector = { 1, 2, 3, 4, 5 };
   cout << myvector.capacity() << endl;
   cout << myvector.size() << endl;

   for (auto it = myvector.begin(); it != myvector.end(); ++it)
      cout << ' ' << *it;
   cout << "\n";
   myvector.pop_back();


   cout << myvector.capacity() << endl;
   cout << myvector.size() << endl;
   for (auto it = myvector.begin(); it != myvector.end(); ++it)
      cout << ' ' << *it;*/

#ifdef DEBUG
   // unit tests
   TestVector().run();
#endif // DEBUG
   
   return 0;
}

