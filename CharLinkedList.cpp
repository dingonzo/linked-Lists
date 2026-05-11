/*
 *  CharLinkedList.cpp
 *  Edgar Gonzalez
 *  20260207
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 * This file contains the implementation of the CharLinkedList class,
 * which is a linked list implementation of a list of characters.
 * The class includes constructors, a destructor, and
 * various member functions for manipulating the list, such as
 * adding/removing characters, and accessing elements. This file will
 * implement the functions declared in CharLinkedList.h. Additionally,
 * this list is implemented as a doubly linked list, meaning each node
 * has a pointer to both the next and previous nodes in the list. Overall,
 * this file's purpose is to provide the functionality for a character
 * linked list.
 *
 */

#include "CharLinkedList.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <ciso646> 
using namespace std;


/*
 * Lifecycle functions
 * These functions are responsible for creating, copying, and destroying
 * CharLinkedList objects. They manage memory and ensure that the list is
 * properly initialized and cleaned up.
 */


/*  
 * name:     CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList
 * arguments: none
 * returns:   none
 * effects:   initializes front and back to nullptr, numItems to 0    
 * 
*/
CharLinkedList::CharLinkedList() : 
front(nullptr), back(nullptr), numItems(0) {}

/*  
 * name:      CharLinkedList single character constructor
 * purpose:   initialize a CharLinkedList with a single character
 * arguments: a character to add to the CharLinkedList
 * returns:   none  
 * effects:   initializes capacity and numItems to 1, 
 * allocates memory for data,
 * and stores the character in data[0]
*/
CharLinkedList::CharLinkedList(char c) : 
front(new Node{c, nullptr, nullptr}), back(front), numItems(1) {}

/*
    *  name:     CharLinkedList array constructor
    * purpose:   initialize a CharLinkedList with an array of characters
    * arguments: an array of characters and the size of the array
    * returns:   none 
    * effects:   tbd
*/
CharLinkedList::CharLinkedList(char arr[], int size) : 
front(nullptr), back(nullptr), numItems(0) {
    for (int i = 0; i < size; i++) {
        pushAtBack(arr[i]);
    }
}

/* 
 * name:     CharLinkedList copy constructor
 * purpose:   create a deep copy of another CharLinkedList
 * arguments: a reference to another CharLinkedList
 * returns:   none  
 * effects:   allocates new memory for data and copies the contents of the 
 * other CharLinkedList
 * 
*/
CharLinkedList::CharLinkedList(const CharLinkedList &other) : 
front(nullptr), back(nullptr), numItems(0) {
    if (other.front != nullptr) {
        front = copyRecursive(other.front);
        numItems = other.numItems;
        // Update back pointer
        Node *curr = front;
        while (curr != nullptr and curr->next != nullptr) curr = curr->next; 
        back = curr;
    }
}

/* 
 * name:      CharLinkedList destructor
 * purpose:   free memory associated with the CharLinkedList
 * arguments: calls the private recursive helper function to delete nodes
 * returns:   none  
 * effects:   frees the memory allocated for data
*/
CharLinkedList::~CharLinkedList() {
    clear();
    // front and back are set to nullptr in clear()    
}       


/* Public member functions*/

/* 
 * name:      CharLinkedList assignment operator overload
 * purpose:   assign the contents of another CharLinkedList to this 
 * CharLinkedList
 * arguments: a reference to another CharLinkedList
 * returns:   a reference to this CharLinkedList
 * effects:   frees existing memory, allocates new memory, 
 * and copies contents of other CharLinkedList 
*/
CharLinkedList& CharLinkedList::operator=(const CharLinkedList &other) {
    if (this != &other) {
        clear(); 

        if (other.front == nullptr) {          
            front = nullptr;
            back = nullptr;
            numItems = 0;
        } else {            
            front = copyRecursive(other.front);
            numItems = other.numItems;
            Node *curr = front;
            while (curr != nullptr and curr->next != nullptr) {
                curr = curr->next;
            }
            back = curr;
        }
    }
    return *this;
}
/*
* name:      clear function
* purpose:   to clear the CharLinkedList
* arguments: none
* returns:   none   
*/
void CharLinkedList::clear() {
    clearRecursive(front);
    front = nullptr;
    back = nullptr;
    numItems = 0;
}


/* 
* name:      isEmpty function
* purpose:   to check if the CharLinkedList is empty
* arguments: none (boolean function)
* returns:   true if empty, false otherwise
*/
bool CharLinkedList::isEmpty() const {
    return numItems == 0;
}

/* 
 * name:      size function
 * purpose:   to return the number of elements in the CharLinkedList
 * arguments: none
 * returns:   number of elements in the CharLinkedList  
*/
int CharLinkedList::size() const {
    return numItems;
}

/* 
 * name:      int first function
 * purpose:   to return the first element in the CharLinkedList
 * arguments: none
 * returns:   the first element in the CharLinkedList  
 * effects:   it was tested and returned the correct first element 
 * and gave the correct error message when empty.
*/ 
char CharLinkedList::first() const {
        if (isEmpty()) {
            throw std::runtime_error
            ("cannot get first of empty LinkedList");
        }
        return front->info;
}

/*
* name:      last function
* purpose:   to return the last element in the CharLinkedList
* arguments: none
* returns:   the last element in the CharLinkedList  
* effects:   it was tested
*/
char CharLinkedList::last() const {
        if (isEmpty()) {
            throw std::runtime_error
            ("cannot get last of empty LinkedList");
        }
        return back->info;
}

/* 
    * name:      elementAt function
    * purpose:   to return the element at a specified index
    * arguments: an index
    * returns:   the element at the specified index  
    * effects:   it was tested and returned the correct element and gave the 
    * correct error message for out-of-range index
*/
char CharLinkedList::elementAt(int index) const {
    //standard bounds check 
    if (index < 0) {
        throw std::range_error("Index (" + std::to_string(index) +
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }
    if (index >= numItems) { 
        throw std::range_error("Index (" + std::to_string(index) +
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }
return elementAtRecursive(front, index);
}

/*
*   name: toString function
*   purpose: to return a string representation of the CharLinkedList
*   arguments: none
*   returns: a string representation of the CharLinkedList
*   effects: it was tested and returned the correct string representation
*/
std::string CharLinkedList::toString() const {
    std::string result = "[CharLinkedList of size " + 
    std::to_string(numItems) + " <<";
    toStringHelper(front, result);
    result += ">>]";
    return result;
}
/*
*   name: toReverseString function
*   purpose: to return a string representation of the 
*   CharLinkedList in reverse
*   arguments: none
*   returns: a string representation of the CharLinkedList 
*   in reverse order
*   effects: it was tested and returned the correct reverse 
*   string representation   
*/
std::string CharLinkedList::toReverseString() const {
    std::string result = "[CharLinkedList of size " + 
    std::to_string(numItems) + " <<";
    reverseHelper(back, result);
    result += ">>]";
    return result;
}

/* 
 * name:      pushAtFront function 
 * purpose:   to add a character to the front of the CharLinkedList
 * arguments: a character to add
 * returns:   none  
 * effects:   after testing, it 
 * added the character to the front correctly
*/
void CharLinkedList::pushAtFront(char c)  {
    Node *newNode = new Node{c, front, nullptr}; 
    if (isEmpty()) {
        front = back = newNode;
    } else {
        front->prev = newNode; // Link old front back to new node
        front = newNode;       // Move head
    }
    numItems++;
}

/* 
 * name:      pushAtBack function 
 * purpose:   to add a character to the back of the CharLinkedList
 * arguments: a character to add
 * returns:   none  
 * effects:   after testing, it added the character to the back correctly
*/
void CharLinkedList::pushAtBack(char c) {
    Node *newNode = new Node{c, nullptr, back}; 
    // next is null, prev is old back
    if (isEmpty()) {
        front = back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
    numItems++;
}   

/*
* name:      insertAt function
* purpose:   to insert a character at a specified index
* arguments: a character and an index
* returns:   none  
* effects:   after testing, it inserted the character at the specified index
*
*/
void CharLinkedList::insertAt(char c, int index) {
    if (index < 0) {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems) + "]");
    }
    if (index > numItems)
    {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems) + "]");
    }
    
    front = insertRecursive(front, nullptr, c, index);
    numItems++;
}

/*
* name:      insertInOrder function
* purpose:   to insert a character in order 
* (assuming the list is sorted)
* arguments: a character to insert
* returns:   none  
* effects:   after testing, it inserted the 
* character correctly in order
*/
void CharLinkedList::insertInOrder(char c) {
// If the list is empty or the new character should be at the front
    if (isEmpty()) {
        pushAtFront(c);
        return;
    }
    if (c <= front->info) {
        pushAtFront(c);
        return;
    }
    // If the new character should be at the back
    if (c >= back->info) {
        pushAtBack(c);
        return;
    }
    // Otherwise, find the correct position to insert
    Node *current = front;
    while (current != nullptr and current->info < c) {
        current = current->next;
    }
    // Insert before current
    Node *newNode = new Node{c, current, current->prev};
    current->prev->next = newNode;
    current->prev = newNode;
    numItems++;
}
/*
* name:      popFromFront function
* purpose:   to remove the first character from the CharLinkedList
* arguments: none
* returns:   none  
* effects:   after testing, it removed the first character correctly
*/
void CharLinkedList::popFromFront() {
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    Node *temp = front;
    front = front->next; 
    if (front != nullptr) {
        front->prev = nullptr; 
    } else {
        back = nullptr;     
    }
    delete temp;
    numItems--;
}

/*
* name:      popFromBack function
* purpose:   to remove the last character from the CharLinkedList
* arguments: none
* returns:   none  
* effects:   after testing, it removed the last character correctly
*/
void CharLinkedList::popFromBack() {
    if (isEmpty()) return;
    Node *temp = back;
    back = back->prev; 
    if (back != nullptr) {
        back->next = nullptr; 
    } else {
        front = nullptr;     
    }
    delete temp;
    numItems--;
}

/*
* name:      removeAt function
* purpose:   to remove the character at a specified index
* arguments: an index
* returns:   none  
* effects:   after testing, it removed the character at the
* specified index correctly
*/
void CharLinkedList::removeAt(int index) {
    // Check lower bound
    if (index < 0) {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }
    
    // Check upper bound
    if (index >= numItems) {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }

    front = removeRecursive(front, index);
    numItems--;
}
/*
* name:      replaceAt function
* purpose:   to replace the character at a specified index with a 
* new character
* arguments: a character and an index
* returns:   none  
* effects:   after testing, it replaced the character at the
* specified index correctly
*/
void CharLinkedList::replaceAt(char c, int index) {
    // Check lower bound
    if (index < 0) {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }
    
    // Check upper bound
    if (index >= numItems) {
        throw std::range_error("index (" + std::to_string(index) + 
        ") not in range [0.." + std::to_string(numItems - 1) + ")");
    }
    replaceRecursive(front, c, index);

}   


/*
* name:      concatenate function
* purpose:   to concatenate another CharLinkedList to this one
* arguments: a pointer to another CharLinkedList
* returns:   none  
* effects:   after testing, it concatenated the other CharLinkedList 
* correctly
*/
void CharLinkedList::concatenate(CharLinkedList *other) {
    if (other == nullptr) { 
        return;
    } // Nothing to concatenate
     if (other->isEmpty()) {
        return;
    } 
    // Nothing to concatenate
     if (this == other) {
        return; // Avoid self-concatenation
    }
    //back = concatRecursive(back, other->front);
    concatRecursive(back, other->front);
}   

/* Private Helper Functions */

/* 
* name: Recursive Copy function 
* purpose:  Returns a pointer to a new chain that matches the old one
* arguments: a pointer to the current position in the old chain
* returns:  a pointer to the new chain
*/
CharLinkedList::Node* CharLinkedList::copyRecursive
(const Node *otherCurr) {
    if (otherCurr == nullptr){
         return nullptr;
    }
    Node *newNode = new Node;
    newNode->info = otherCurr->info;
    newNode->prev = nullptr; // Will be set in the next step
    newNode->next = copyRecursive(otherCurr->next);

    if (newNode->next != nullptr) {
        newNode->next->prev = newNode;
    }
    return newNode;
}

/*
* name: Recursive Clear function
* purpose:  to clear the CharLinkedList using recursion
* arguments: a pointer to the current position in the chain
* returns:  none
* effects:  it was tested and cleared the CharLinkedList correctly
*/
void CharLinkedList::clearRecursive(Node *curr) {
    if (curr == nullptr) return;
    clearRecursive(curr->next);
    delete curr;
}   

/*
* NAME:     elementAt recursive helper function
* PURPOSE:  to return the element at a specified index using 
* recursion
* ARGUMENTS: a pointer to the current position in the data array and 
* the index
* RETURNS:  the element at the specified index
* EFFECTS:  it was tested and returned the correct element at the 
* specified index
*/
char CharLinkedList::elementAtRecursive(Node *curr, int index) 
const {
    if (curr == nullptr) {
        throw std::out_of_range("Index out of bounds");
    }

    if (index == 0) {
        return curr->info;
    }
    return elementAtRecursive(curr->next, index - 1);
}

/*
* name:   Replace Recursive helper function
* purpose: to replace the character at a specified index with a 
* new character       
* arguments: a pointer to the current position in the data array, 
* a character, and the index
*/
void CharLinkedList::replaceRecursive(Node *curr, char c, int index) {
    if (index == 0) {
        curr->info = c;
        return;
    }
    replaceRecursive(curr->next, c, index - 1);
}

/*
* name:   Insert Recursive helper function
* purpose: to insert a character at a specified index using recursion
* arguments: a pointer to the current position in the data array,
*/
CharLinkedList::Node* CharLinkedList::insertRecursive(Node *curr, 
    Node *previous, char c, int index) {
    if (index == 0) {
        Node *newNode = new Node{c, curr, previous};
    if (curr != nullptr) curr->prev = newNode;
    // CRITICAL: If there is no next node, this new node is the new back
    if (curr == nullptr) back = newNode; 
    numItems++;
    return newNode;
}
    curr->next = insertRecursive(curr->next, curr, c, index - 1);
    if (curr->next != nullptr) {
        curr->next->prev = curr; // Update back link after insertion
    } else {
        back = curr; // Update back pointer if we inserted at the end
    }
    return curr;
}

/*
*concatenate Recursive helper function
* purpose: to concatenate another CharLinkedList using recursion
* arguments: a pointer to the current position in the data array and
* a pointer to the current position in the other CharLinkedList 
*/
CharLinkedList::Node* CharLinkedList::concatRecursive
(Node *curr, const Node *otherCurr) {
    if (otherCurr == nullptr) {
        return curr;
    }
    Node *newNode = new Node{otherCurr->info, nullptr, curr};
    if (curr != nullptr) {
        curr->next = newNode;
    } else {
        front = newNode; // If curr is null, we're adding to an empty list
    }
    back = newNode; // Update back to the new last node
    numItems++;
    return concatRecursive(newNode, otherCurr->next);
}

/*
* name:   Remove Recursive helper function
* purpose: to remove the character at a specified index 
* using recursion
* arguments: a pointer to the current position in the 
* data array and the index
* returns:  a pointer to the modified chain   
*/
CharLinkedList::Node* CharLinkedList::removeRecursive
(Node *curr, int index) {
    if (index == 0) {
        Node *temp = curr->next;
        if (temp != nullptr) {
            temp->prev = curr->prev; 
        } else {
            back = curr->prev;
        }
        delete curr;
        return temp;
    }
    curr->next = removeRecursive(curr->next, index - 1);
    if (curr->next != nullptr) {
        curr->next->prev = curr;
    }
    return curr;
}

/*
* NAME:     popBackRecursive helper function
* PURPOSE:  to remove the last character from the CharLinkedList 
* using recursion    
* ARGUMENTS: a pointer to the current position in the data array
* RETURNS:  a pointer to the modified chain
* EFFECTS:  it was tested and removed the last character correctly
*/
CharLinkedList::Node* CharLinkedList::popBackRecursive(Node *curr) {
    if (curr == nullptr) return nullptr; 
    // Base case: empty list
    if (curr->next == nullptr) { 
        // Base case: last node
        if (curr == back) {
                back = curr->prev; 
                // Move back to the previous node (or nullptr)
        }
        delete curr;
        numItems--; // Don't forget to decrement here!
        return nullptr;
    }
    curr->next = popBackRecursive(curr->next);
    if (curr->next != nullptr) {
        curr->next->prev = curr; 
        // Update back link after removal
    } else {
        back = curr; 
        // Update back pointer if we removed the last node
    }
    return curr;
}


/*
* name:   To String Helper function
* purpose: to build the string representation using recursion   
* arguments: a pointer to the current position in the data array and a 
* reference to the result string.
*/
void CharLinkedList::toStringHelper
(Node *curr, std::string &result) const {
    if (curr == nullptr) return;
    
    result += curr->info;                
    // Action: Add char first
    toStringHelper(curr->next, result);  
    // Recursive step: Move to next
}

/*
* name:   Reverse Helper function
* purpose: to build the reverse string representation using recursion   
* arguments: a pointer to the current position in the data array and a 
* reference to the result string.
*/
void CharLinkedList::reverseHelper
(Node *curr, std::string &result) const {
    if (curr == nullptr) return;
    
    result += curr->info;                
    // Action: Add char first
    reverseHelper(curr->prev, result);  
    // Recursive step: Move to previous
}
