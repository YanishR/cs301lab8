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

  // get previous and index
  int prev, index;

  for (int i = 0; i < myAssociativty; i++)
  {
      if(myBlocks[i].getTag() == tag &&
              myBlocks[i].getValid())
      {
          hit = true;
          index = i;
          prev = myBlokcs[i].getLRU(); 
          myBlocks[i].setLRU(0);
      }
  }

  // increment indeces LRU's if smaller than previous
  // and not index
  if (hit)
  {
      for (int i = 0; i < myAssociativity; i++)
          if ( myBlocks[i].getLRU() != -1 &&
               myBlocks[i].getLRU() < prev &&
               i != index )
              myBlocks[i].setLRU(myBlocks[i].getLRU() + 1);
  }
  else
  {
      // index to find k
      int k = -1;

      for (int i = 0; i < myAssociativty; i++)
      {
          if (myBlocks[i].getLRU() == -1)
          {
              prev = myBlocks[i].getLRU();
              k = i; 
              break;
          }
          if (myBlocks[i].getLRU() > k)
          {
              prev = myBlocks[i].getLRU();
              k = i;
          }
      }

      // Set myBlocks[k]'s values
      myBlocks[k].setTag(tag);
      myBlocks[k].setValid(true);
      myBlocks[k].setLRU(0);

      // increment LRU in all blocks if not empty and at index k
      for(int i = 0; i < myAssociativity; i++)
          if(myBlocks[i].getLRU() != -1 && j != k)
              myBlocks[i].setLRU(myBlocks[i].getLRU() + 1);
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

