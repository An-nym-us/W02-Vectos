/***********************************************************************
 * Header:
 *    VECTOR
 * Summary:
 *    Our custom implementation of std::vector
 *
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        vector                 : A class that represents a Vector
 *        vector::iterator       : An interator through Vector
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
#include <new>      // std::bad_alloc
#include <memory> // for std::allocator
#include <iostream>

class TestVector; // forward declaration for unit tests
class TestStack;
class TestPQueue;
class TestHash;


/*
* Add note in submission report for what i am assuming to be an easter egg with thee context of Theme from "0xBAADF00D" by Slugbug Located in teh test cases
*/




namespace custom
{

/*****************************************
 * VECTOR
 * Just like the std :: vector <T> class
 ****************************************/
template <typename T>
class vector
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   
   // 
   // Construct
   //

   vector();
   vector(size_t numElements                );
   vector(size_t numElements, const T & t   );
   vector(const std::initializer_list<T>& l );
   vector(const vector &  rhs);
   vector(      vector && rhs);
   ~vector();

   //
   // Assign
   //

   void swap(vector& rhs)
   {
      // swap if same size;
      if (numCapacity == rhs.numCapacity)
      {     
         T& temp = *data;
         data = rhs.data;
         rhs.data = &temp;
      }
      else if (numCapacity > rhs.numCapacity)
      { 
         T& temp = *data;
         int tempCap = numCapacity;
         int tempEle = numElements;


         data = rhs.data;
         numCapacity = rhs.numCapacity;
         numElements = rhs.numElements;


         rhs.data = &temp;
         rhs.numCapacity = tempCap;
         rhs.numElements = tempEle;
         
      }
      else if (numCapacity < rhs.numCapacity)
      {
         T& temp = *data;
         int tempCap = numCapacity;
         int tempEle = numElements;


         data = rhs.data;
         numCapacity = rhs.numCapacity;
         numElements = rhs.numElements;


         rhs.data = &temp;
         rhs.numCapacity = tempCap;
         rhs.numElements = tempEle;
      }
      



   }
   vector & operator = (const vector & rhs);
   vector& operator = (vector&& rhs);

   //
   // Iterator
   //

   class iterator;
   iterator       begin() { return iterator(&data[0]); }
   iterator       end() { return iterator(&data[numCapacity]); }

   //
   // Access
   //

         T& operator [] (size_t index);
   const T& operator [] (size_t index) const;
         T& front();
   const T& front() const;
         T& back();
   const T& back() const;

   //
   // Insert
   //

   void push_back(const T& t);
   void push_back(T&& t);
   void reserve(size_t newCapacity);
   void resize(size_t newElements);
   void resize(size_t newElements, const T& t);

   //
   // Remove
   //

   // Works
   void clear()   
   {
      numElements = 0;
      for (int i = 0; i < numElements; i++)
         data[i] = 0;
   }

   void pop_back()
   {      
      if (data == nullptr)
      {
         return;
      }
      else
      {
         data[numElements - 1] = 0;
         numElements -= 1;
      }
   }
   void shrink_to_fit();

   //
   // Status
   //
   



   // Works
   size_t  size() const 
   { 
      return numCapacity;  
   }
   // Works
   size_t  capacity() const 
   { 
      return numCapacity;  
   }
   // Works
   bool empty() const// Works
   { 
      if (data == nullptr)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   
   // adjust the size of the buffer
   
   // vector-specific interfaces
   
private:
   
   T *  data;                 // user data, a dynamically-allocated array
   size_t  numCapacity;       // the capacity of the array
   size_t  numElements;       // the number of items currently used
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <typename T>
class vector <T> ::iterator
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   // constructors, destructors, and assignment operator
   iterator()                           { this->p = nullptr; }
   iterator(T* p)                       { this->p = p; }
   iterator(const iterator& rhs)        { this->p = rhs.p; }
   iterator(size_t index, vector<T>& v) { this->p = v.data + index;    }
   iterator& operator = (const iterator& rhs)
   {
      this->p = new T;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator& rhs) const 
   { 
      if (rhs.p != p)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool operator == (const iterator& rhs) const 
   { 
      if (rhs.p == p)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   // dereference operator
   T& operator * ()
   {
      return *p;
   }

   // prefix increment
   iterator& operator ++ ()
   {
      *p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      return iterator(p++);
   }

   // prefix decrement
   iterator& operator -- ()
   {
      *p--;
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      *p--;
      return *this;
   }

private:
   T* p;
};

/*****************************************
 * VECTOR :: DEFAULT constructors
 * Default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector()
{
   data = nullptr;
   numCapacity = 0;
   numElements = 0;
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num, const T & t) 
{
   data = new T[num];
   for (int i = 0; i < num; i++)
   {
      data[i] = t;
   }
   numCapacity = num;
   numElements = num;
}

/*****************************************
 * VECTOR :: INITIALIZATION LIST constructors
 * Create a vector with an initialization list.
 ****************************************/
template <typename T>
vector <T> :: vector(const std::initializer_list<T> & l) 
{
   data = new T[l.size()];
   int count = 0;
   for (auto it = l.begin(); it != l.end(); ++it) {
      data[count] = *it;
      count++;
   };

   numElements = l.size();
   numCapacity = l.size();
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num) 
{
   if (num == 0)
   {
      data = nullptr;
      numCapacity = num;
      numElements = num;
   }
   else
   {
      data = new T[num];
      for (int i = 0; i < num; i++)
      {
         data[i] = 0;
      }
      numCapacity = num;
      numElements = num;
   }

}

/*****************************************
 * VECTOR :: COPY CONSTRUCTOR
 * Allocate the space for numElements and
 * call the copy constructor on each element
 ****************************************/
template <typename T>
vector <T> :: vector (const vector & rhs) 
{
   
   
   // Allocate space
   if (!rhs.data)
   {
      data = nullptr;
   }
   else {
      data = new T[rhs.numElements];
      // Make a copy
      for (int i = 0; i < rhs.numElements; i++) {
         data[i] = rhs.data[i];
      }
   }
   numElements = rhs.numElements;
   numCapacity = rhs.numElements;
}

/*****************************************
 * VECTOR :: MOVE CONSTRUCTOR
 * Steal the values from the RHS and set it to zero.
 ****************************************/
template <typename T>
vector <T> :: vector (vector && rhs)
{
    // Steal the values
    data = rhs.data;
    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;
    
    // Set it to Zero or Null
    rhs.data = nullptr;
    rhs.numElements = 0;
    rhs.numCapacity = 0;
}

/*****************************************
 * VECTOR :: DESTRUCTOR
 * Call the destructor for each element from 0..numElements
 * and then free the memory
 ****************************************/
template <typename T>
vector <T> :: ~vector()
{
   delete[] data;
}

/***************************************
 * VECTOR :: RESIZE
 * This method will adjust the size to newElements.
 * This will either grow or shrink newElements.
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: resize(size_t newElements)
{
   if (newElements < this->numElements)
   {
      this->numElements = newElements;
   }
   else if (newElements > this->numElements)
   {
      T* temp = new T[newElements];
      
      for (int i = 0; i < this->numElements; i++)
      {
         temp[i] =data[i] ;
      }
      for (int i = this->numElements; i < newElements; i++)
      {
         temp[i] = 0;
      }
      data = temp;
      this->numElements = newElements;
      this->numCapacity = newElements;
   }



}

template <typename T>
void vector <T> :: resize(size_t newElements, const T & t)
{

   if (newElements < this->numElements)
   {
      this->numElements = newElements;
   }
   else if (newElements > this->numElements)
   {
      T* temp = new T[newElements];

      for (int i = 0; i < this->numElements; i++)
      {
         temp[i] = data[i];
      }
      for (int i = this->numElements; i < newElements; i++)
      {
         temp[i] = t;
      }
      data = temp;
      this->numElements = newElements;
      this->numCapacity = newElements;
   }


}

/***************************************
 * VECTOR :: RESERVE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: reserve(size_t newCapacity)
{   
   if (this->numCapacity >= newCapacity)
      return;
   else
      this->numCapacity = newCapacity;
}

/***************************************
 * VECTOR :: SHRINK TO FIT
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: shrink_to_fit()
{
   numCapacity = numElements;
   if (numElements == 0)
      data = nullptr;
}



/*****************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: operator [] (size_t index)
{
   return data[index];
}

/******************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: operator [] (size_t index) const
{
   return data[index];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: front ()
{
   
   return data[0];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: front () const
{
   return data[0];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: back()
{ 
   return data[numElements - 1];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: back() const
{
   return data[numElements - 1];
}

/***************************************
 * VECTOR :: PUSH BACK
 * This method will add the element 't' to the
 * end of the current buffer.  It will also grow
 * the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 **************************************/
template <typename T>
void vector <T> :: push_back (const T & t)
{
   



}

template <typename T>
void vector <T> ::push_back(T && t)
{
   
   
}

/***************************************
 * VECTOR :: ASSIGNMENT
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the vector to copy from
 *     OUTPUT : *this
 **************************************/
template <typename T>
vector <T> & vector <T> :: operator = (const vector & rhs)
{
   
   if (numElements == rhs.numElements)
   {
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
   }
   else if (numElements < rhs.numElements)
   {
      numElements = rhs.numElements;
      numCapacity = rhs.numCapacity;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }  
   }
   else if (numElements > rhs.numElements)
   {
      numElements = rhs.numElements;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
   }
   



   return *this;
}
template <typename T>
vector <T>& vector <T> :: operator = (vector&& rhs)
{

   if (numElements == rhs.numElements)
   {
      rhs.numElements = 0;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
   }
   else if (numElements < rhs.numElements)
   {
      numElements = rhs.numElements;
      numCapacity = rhs.numCapacity;    
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
      rhs.numElements = 0;
   }
   else if (numElements > rhs.numElements)
   {
      numElements = rhs.numElements;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
      rhs.numElements = 0;
   }

   return *this;
   


}




} // namespace custom

