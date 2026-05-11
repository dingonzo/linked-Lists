/*
 *  CharLinkedList.h
 *  Edgar Gonzalez
 *  20260206
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This file defines the interface for a CharLinkedList class, 
 *  which is a linked list implementation of a list of characters. 
 *  The class includes constructors, a destructor, and 
 *  various member functions for manipulating the list, such as 
 *  adding/removing characters, and accessing elements. 
 *  The implementation of these functions will be provided in 
 *  the corresponding CharLinkedList.cpp file. This list will be
 *  implemented as a doubly linked list, meaning each node will have
 *  a pointer to both the next and previous nodes in the list.
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include <string>
class CharLinkedList {
    public:
    
    //Default Constructor
    CharLinkedList();
    //Constructor for single character
    CharLinkedList(char c);
    //Constructor for array
    CharLinkedList(char arr[], int size);
    //Copy Constructor
    CharLinkedList(const CharLinkedList &other);
    //default destructor
    ~CharLinkedList(); 
    //add private recursive helper function to delete nodes  

        CharLinkedList& operator=(const CharLinkedList &other); 
        //Assignment Operator overload  
        void clear();               
        //Clears the CharLinkedList
        bool isEmpty() const;     
        //Checks if the CharLinkedList is empty
        int size() const;    
        //Returns the number of elements in the CharLinkedList
        char first() const;      
        //Returns the first element in the CharLinkedList
        char last() const;      
        //Returns the last element in the CharlinkedList
        char elementAt(int index) const; 
        //Returns the element at a specified index
        std::string toString() const;  
        //String representation of CharLinkedList
        std::string toReverseString() const;    
        //String representation of CharLinkedList in reverse order
        void pushAtBack(char c);  
        //Adds a character to the back of the CharLinkedList
        void pushAtFront(char c);   
        //Adds a character to the front of the CharLinkedList
        void insertAt(char c, int index);  
        //Inserts a character at a specified index
        void insertInOrder(char c);  
        //Inserts a character in order (assuming the list is sorted)    
        void popFromFront();   
        //Removes the first character from the CharLinkedList
        void popFromBack();   
        //Removes the last character from the CharLinkedList    
        void removeAt(int index);       
        //Removes the character at a specified index
        void replaceAt(char c, int index);   
        //Replaces the character at a specified index with a new character   
        void concatenate(CharLinkedList *other); 
        //Concatenates another CharLinkedList 


    private:
    struct Node {
        char info;
        Node *next;
        Node *prev; // New backward link
    };
    Node *front;
    Node *back; // Pointer to the last node for efficiency
    int numItems;

    // Helpers
    void clearRecursive(Node *curr);
    Node* copyRecursive(const Node *otherCurr);
    char elementAtRecursive(Node *curr, int index) const;
    void toStringHelper(Node *curr, std::string &result) const;
    void reverseHelper(Node *curr, std::string &result) const;
    Node* popBackRecursive(Node *curr);
    Node* removeRecursive(Node *curr, int index);
    Node* insertRecursive(Node *curr, Node *previous, char c, int index);
    void replaceRecursive(Node *curr, char c, int index);
    Node* concatRecursive(Node *curr, const Node *otherCurr);
};

#endif
