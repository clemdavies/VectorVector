#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <vector>

const unsigned MINIMUM_SIZE = 10;

  /**
   * @class Vector
   * @brief Encapsulated array. Dynamically increases the size when needed.
   *
   * @author Clem Davies
   * @version 01
   * @date 27/04/2016
   *
   */
template <class T>
class Vector
{
  public:

      /**
       * @brief Creates a Vector with size starting at minimum_size of 10.
       */
    Vector()
		{
		  currentSize = 0;
		  maxSize = MINIMUM_SIZE;
      elements = new T[maxSize];
      usedIndices = new bool[maxSize];
      for(unsigned i = 0; i < maxSize; i++)usedIndices[i] = false;
      currentIndex = -1;
      lastIndex = -1;
		}

      /**
       * @brief Creates a Vector with starting maxSize as passed value.
       * @param The maximum size of the array.
       */
    Vector(unsigned size)
		{
		  currentSize = 0;
      maxSize = (size > MINIMUM_SIZE) ? size : MINIMUM_SIZE;
      elements = new T[maxSize];
      usedIndices = new bool[maxSize];
      for(unsigned i = 0; i < maxSize; i++) usedIndices[i] = false;
      currentIndex = -1;
      lastIndex = -1;
		}

      /**
       * @brief Constructs a copy of Vector.
       * @param The Vector object to copy from.
       * @return The newly created Vector object.
       */
    Vector( const Vector &srcVector)
		{
		  maxSize = srcVector.maxSize;
		  currentSize = srcVector.currentSize;

		  elements = new T[maxSize];
      usedIndices = new bool[maxSize];
      for(unsigned i = 0; i < maxSize; i++)
      {
        if(srcVector.usedIndices[i])
        {
          elements[i] = srcVector.elements[i];
          usedIndices[i] = true;
        }
        else
        {
          usedIndices[i] = false;
        }
      }
      currentIndex = srcVector.currentIndex;
      lastIndex = srcVector.lastIndex;
		}

      /**
       * @brief Constructs a copy of Vector using assignment operator.
       * @param The Vector object to copy from.
       * @return The newly created Vector object.
       */
    Vector& operator=(const Vector &srcVector)
		{
      // check for self-assignment
      if (this == &srcVector)
        return *this;

		  maxSize = srcVector.maxSize;
		  currentSize = srcVector.currentSize;

		  elements = new T[maxSize];
      usedIndices = new bool[maxSize];
      for(unsigned i = 0; i < maxSize; i++ )
      {
        if(srcVector.usedIndices[i])
        {
          elements[i] = srcVector.elements[i];
          usedIndices[i] = true;
        }
        else
        {
          usedIndices[i] = false;
        }
      }
      currentIndex = srcVector.currentIndex;
      lastIndex = srcVector.lastIndex;

      return *this;
		}

      /**
       * @brief Destroys the stored arrays.
       */
    virtual ~Vector()
		{
		  clear();
		  delete[] elements;
		  delete[] usedIndices;
		}

      /**
       * @brief Iterates the currentIndex up to the next element or resets back to -1.
       * @return True if the currentIndex succesfully found the next element.
       */
		bool next()
		{
		  if(currentSize == 0) return false;
		  for(currentIndex++;!usedIndices[currentIndex] && currentIndex < (int)maxSize;currentIndex++);
		  if(currentIndex == (int)maxSize)currentIndex = -1;
		  return currentIndex != -1;
		}


      /**
       * @brief Returns the element at passed index in array.
       * @param The index.
       * @return The element.
       */
    const T& get(unsigned index) const
		{
      return elements[index];
		}

      /**
       * @brief Returns the element currently being pointed to.
       * @return The element.
       */
    const T& getCurrent() const
		{
      return elements[currentIndex];
		}

      /**
       * @brief Inserts passed element at passed index in array. Resizes if neccessary.
       * @param Index to insert at.
       * @param Element to insert.
       */
    void insert(unsigned index, const T &element)
		{
      if(index >= maxSize)
      {
        // index out of bounds
        increaseMaxSize(index);
      }
      currentSize++;
      usedIndices[index] = true;
      currentIndex = index;
      elements[index] = element;
      lastIndex = ((int)index > lastIndex) ? (int)index : lastIndex;
		}

      /**
       * @brief Inserts passed element to the end of the array.
       * @param Element to insert
       */
    void insertEnd(const T &element)
		{
		  insert(lastIndex+1,element);
		}

      /**
       * @brief Removes all elements from array and calls delete on each element ptr.
       */
		void clearPtrs()
		{
		  for(unsigned i = 0;i < maxSize;i++)
      {
        if(usedIndices[i])
        {
          delete elements[i];
        }
      }
      clear();
		}

      /**
       * @brief Empties the arrays and resets member variables to initial state.
       */
    void clear()
		{
      delete[] elements;
      delete[] usedIndices;
		  maxSize = MINIMUM_SIZE;
      elements = new T[maxSize];
      usedIndices = new bool[maxSize];
      for(unsigned i = 0; i < maxSize; i++) usedIndices[i] = false;
      currentSize = 0;
      currentIndex = -1;
		}

      /**
       * @brief Removes the element at passed index from array.
       * @param The index of the element to remove.
       */
    void erase(unsigned index)
    {
      if(index < maxSize && usedIndices[index])
      {
        currentSize--;
        usedIndices[index] = false;
        resetIndex();
      }
		}

      /**
       * @brief Erases the ptr at index and the calls delete on the element it is pointing to.
       * @param The index to erase.
       */
		void erasePtr(unsigned index)
		{
      if(index < maxSize && usedIndices[index])
      {
        delete elements[index];
        elements[index] = nullptr;
        currentSize--;
        usedIndices[index] = false;
        resetIndex();
      }
		}

      /**
       * @brief Calculates the starting position for current index and last index.
       */
    void resetPtr()
    {
      resetIndex();
    }


      /**
       * @brief Checks to see if the array has an element stored at passed index.
       * @param The index to check.
       * @return True if there is an element at given index.
       */
    bool hasValue(unsigned index) const
    {
      return usedIndices[index];
    }

      /**
       * @brief Checks to see if the array has any elements.
       * @return True if there are no elements in the array.
       */
    bool empty() const
		{
		  return currentSize == 0;
		}

      /**
       * @brief Returns the current indexor -1 if array empty.
       * @return The current index.
       */
		int getCurrentIndex() const
		{
		  return currentIndex;
		}

      /**
       * @brief Returns the index of the last element in the array or -1 if array empty.
       * @return The last index.
       */
		int getLastIndex() const
		{
		  return lastIndex;
		}

      /**
       * @brief Returns the current number of elements in the array.
       * @return The size.
       */
    unsigned getSize() const
		{
      return currentSize;
		}

      /**
       * @brief Returns the current maximum size of the array.
       * @return The maximum size.
       */
    unsigned getMaxSize() const
		{
      return maxSize;
		}

  private:

      /**
       * @brief Calculates the starting position for current index and last index.
       */
    void resetIndex()
    {
      if(currentSize == 0)
      {
        currentIndex = -1;
        lastIndex = -1;
      }
      else
      {
        for(currentIndex = 0;!usedIndices[currentIndex];currentIndex++);
        for(lastIndex = maxSize-1;!usedIndices[lastIndex];lastIndex--);
      }
    }

      /**
       * @brief Increases maxSize of elements array by 1.5 until passed index fits and copies all values into larger array.
       * @param The index value that needs to fit into the new array.
       */
    void increaseMaxSize(unsigned toFitIndex)
		{
		  if(toFitIndex < maxSize)return;

      unsigned OLD_maxSize = maxSize;
		  while(toFitIndex >= maxSize) maxSize = ceil( maxSize * 1.5 );

      bool * LARGER_usedIndices = new bool[maxSize];
      T * LARGER_elements = new T[maxSize];

      for(unsigned i = 0; i < maxSize; i++)
      {
        if(i < OLD_maxSize && usedIndices[i])
        {
          LARGER_usedIndices[i] = true;
          LARGER_elements[i] = elements[i];
        }
        else
        {
          LARGER_usedIndices[i] = false;
        }
      }
      delete[] elements;
      delete[] usedIndices;
      elements = LARGER_elements;
      usedIndices = LARGER_usedIndices;
      currentIndex = -1;
		}

    /**
     * @brief The index of the currently pointed to element in the array.
     */
    int currentIndex;

    /**
     * @brief The index of the last element in the array.
     */
    int lastIndex;

    /**
     * @brief The current number of elements in the elements array.
     */
    unsigned currentSize;

    /**
     * @brief The maximum size of elements array.
     */
    unsigned maxSize;

    /**
     * @brief Array denoting if there is an element stored at the same index in elements array.
     */
    bool * usedIndices;

    /**
     * @brief The encapsulated vector.
     */
    T * elements;
};

#endif // VECTOR_H
