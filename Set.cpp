#include "Set.h"

/* Create a set with no blocks */
Set::Set()
{
  myBlocks = 0;
}

/* Deallocate any dynamically allocated memory */
Set::~Set()
{
  if(myBlocks != 0){
    delete [] myBlocks;
  }
}

/* Specify the number of blocks in a set (i.e. the set associativity) and
 * initialize the set with that number of blocks.
 */
void Set::initialize(int numBlocks)
{
  myAssociativity = numBlocks;
  myBlocks = new Block[myAssociativity];

}

/* Add an access to this tag to the set.  If the tag is not already in the
 * set, add it and return false to indicate a miss.  If the tag is already
 * in the set, access it and return true to indicate a hit.  In both
 * cases, update the information for the Block accordingly.
 */
bool Set::addAccess(long long tag)
{

  bool hit = false;

  // integers to store previous and index
  int previous, index;

  for (int i = 0; i < myAssociativity; i++)
  {
      if(myBlocks[i].getTag() == tag &&
              myBlocks[i].getValid())
      {
          hit = true;
          index = i;
          previous = myBlocks[i].getLRU(); 
          myBlocks[i].setLRU(0);
      }
  }

  // If hit
  // increment LRU's if smaller than previous
  // and not index
  if (hit)
  {
      for (int i = 0; i < myAssociativity; i++)

          if ( myBlocks[i].getLRU() != -1 &&
               myBlocks[i].getLRU() < previous &&
               i != index )

              myBlocks[i].setLRU(myBlocks[i].getLRU() + 1);

  }
  // else find -1 LRUs 
  else
  {
      // find index 
      int i = 0;

      for (; i < myAssociativity; i++)
      {
          if (myBlocks[i].getLRU() == -1)
          {
              previous = myBlocks[i].getLRU();
              break;
          }
          if (myBlocks[i].getLRU() > i)
              previous = myBlocks[i].getLRU();

      }

      // Set myBlocks[i]'s values
      myBlocks[i].setTag(tag);
      myBlocks[i].setValid(true);
      myBlocks[i].setLRU(0);

      // increment LRU in all blocks if not empty and at index k
      for(int j = 0; j < myAssociativity; j++)
          if(myBlocks[j].getLRU() != -1 && j != i)
              myBlocks[j].setLRU(myBlocks[j].getLRU() + 1);
  }

  return hit;
  
}

/* Print the contents of the set to stdout.  The argument specifies which
 * set this is in the cache.
 */
void Set::printSet(int set)
{
  cout << "****** SET " << set << "****** " << endl;
  for(int i = 0; i < myAssociativity; i++){
    cout << "Index " << i << ": tag " << hex << myBlocks[i].getTag()
	 << " valid "<< dec << myBlocks[i].getValid()
	 << " lru " << myBlocks[i].getLRU()
	 << endl;
  }
  cout << "***************** " << endl;

}
