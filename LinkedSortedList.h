/** ADT sorted list: Link-based implementation.
 @file LinkedSortedList.h */
#ifndef _LINKED_SORTED_LIST
#define _LINKED_SORTED_LIST
#include "SortedListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
template < class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
    private :
    Node<ItemType>* headPtr; // Pointer to first node in the chain
    int itemCount; // Current count of list items
    // Locates the node that is before the node that should or does
    // contain the given entry.
    // @param anEntry The entry to find.
    // @return Either a pointer to the node before the node that contains
    // or should contain the given entry, or nullptr if no prior node exists.
    Node<ItemType>* getNodeBefore( const ItemType& anEntry) const ;
    // Locates the node at a given position within the chain.
    Node<ItemType>* getNodeAt( int position) const ;
    // Returns a pointer to a copy of the chain to which origChainPtr points.
    Node<ItemType>* copyChain( const Node<ItemType>* origChainPtr);
    public :
    LinkedSortedList();
    LinkedSortedList(const LinkedSortedList<ItemType>& aList);
    virtual ~LinkedSortedList();
    void insertSorted( const ItemType& newEntry);
    bool removeSorted( const ItemType& anEntry);
    int getPosition( const ItemType& newEntry) const ;
    // The following methods are the same as given in ListInterface:
    bool isEmpty() const ;
    int getLength() const ;
    bool remove( int position);
    void clear();
    ItemType getEntry( int position) const throw (PrecondViolatedExcep);
}; // end LinkedSortedList


template < class ItemType>
LinkedSortedList<ItemType>::
LinkedSortedList( const LinkedSortedList<ItemType>& aList)
{
    headPtr = copyChain(aList.headPtr);
} // end copy constructor

template < class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::
copyChain( const Node<ItemType>* origChainPtr)
{
    Node<ItemType>* copiedChainPtr;
    if (origChainPtr == nullptr)
    {
        copiedChainPtr = nullptr ;
        itemCount = 0;
    }
    else
    {
        // Build new chain from given one
        Node<ItemType>* copiedChainPtr =
        new Node<ItemType>(origChainPtr->getItem());
        copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
        itemCount++;
    } // end if
    return copiedChainPtr;
} // end copyChain

template < class ItemType>
void LinkedSortedList<ItemType>::insertSorted( const ItemType& newEntry)
{
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
    Node<ItemType>* prevPtr = getNodeBefore(newEntry);
    if (isEmpty() || (prevPtr == nullptr )) // Add at beginning
    {
        newNodePtr->setNext(headPtr);
        headPtr = newNodePtr;
    }
    else // Add after node before
    {
        Node<ItemType>* aftPtr = prevPtr->getNext();
        newNodePtr->setNext(aftPtr);
        prevPtr->setNext(newNodePtr);
    } // end if
    itemCount++;
} // end insertSorted

template < class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::
getNodeBefore( const ItemType& anEntry) const
{
    Node<ItemType>* curPtr = headPtr;
    Node<ItemType>* prevPtr = nullptr;
    while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
    {
        prevPtr = curPtr;
        curPtr = curPtr->getNext();
    } // end while
    return prevPtr;
} // end getNodeBefore
#endif
