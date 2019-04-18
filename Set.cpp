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

  // YOUR CODE HERE

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

