/*
 *  unit_tests.cpp
 *  Edgar Gonzalez
 *  20260206
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  This file contains unit tests for the CharLinkedList class.
 *  Each test function checks a specific functionality of the CharLinkedList
 *  class to ensure it behaves as expected.
 *  Each test function returns true if the test passes and false otherwise.
 *  The main function runs all the tests and reports the results.
 *  
 *
 */

#include "CharLinkedList.h"

#include <cassert>
#include <iostream>
#include <string> 
using namespace std;

void runTests(){   

    
    //basic constructor test
    std::cout << "Successful start!" << std::endl;    

/* function: list1 test
*   list constructor unit tests
*  tests the default constructor by creating an empty list
*  the second test asserts that the list is empty, and the size is 0
*/
    CharLinkedList list1;
    assert(list1.isEmpty());
    assert(list1.size() == 0);
    
/* function: list2 test
* the tests range from testing the single character constructor
* to testing first(), last(), elementAt() functions
* this shoulld cover all edge casses for a list with one element
*/
    CharLinkedList list2('a');
    if (list2.isEmpty()){
        cout << "list2 is empty" << endl;
    } else {
        cout << "list2 is not empty" << endl;
    }
    assert(list2.size() == 1);
    assert(list2.first() == 'a');
    assert(list2.last() == 'a');
    assert(list2.elementAt(0) == 'a'); 

/* function: list3 test
* tests the array constructor by creating a list from a character array
* this should cover edge cases for a list with multiple elements
* assert tests the isEmpty(), size(), first(), last(), and 
* elementAt() functions. 
*/
    char arr[] = {'A', 'l', 'i', 'c', 'e'};
    CharLinkedList list3(arr, 5);
    if(list3.isEmpty()) {
        cout << "list3 is empty" << endl;
    } else {
        cout << "list3 is not empty" << endl;
    }
    // should print list3 is not empty
    assert(list3.size() == 5);
    assert(list3.last() == 'e');
    assert(list3.elementAt(0) == 'A');


/*
* function: CharLinkedListOne and CharLinkedListTwo test
* tests the array constructor by creating two lists from character arrays
*/
    char arr2[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr2, 3);
    if (CharLinkedListOne.isEmpty()) {
        cout << "CharLinkedListOne is empty" << endl;
    } else {
        cout << "CharLinkedListOne is not empty" << endl;
    }
    assert(CharLinkedListOne.size() == 3);
    assert(CharLinkedListOne.first() == 'c');
    assert(CharLinkedListOne.last() == 't');
    assert(CharLinkedListOne.elementAt(1) == 'a');  

    char arr3[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListTwo(arr3, 8);
    if(CharLinkedListTwo.isEmpty()) {
        cout << "CharLinkedListTwo is empty" << endl;
    } else {
        cout << "CharLinkedListTwo is not empty" << endl;
    }
    assert(CharLinkedListTwo.size() == 8);
    assert(CharLinkedListTwo.first() == 'C');
    assert(CharLinkedListTwo.last() == 'E'); 
    try {
        CharLinkedListTwo.elementAt(8); // Out-of-range access
    } catch (const std::range_error &e) {
        // This runs if elementAt() throws the error
        std::cerr << e.what() << std::endl;
    }
    assert(CharLinkedListTwo.elementAt(5) == 'I');
}

void testPushandPop() {
    std::cout << "Testing push and pop functions..." << std::endl;  
    CharLinkedList list1;

    // Test pushAtFront
    list1.pushAtFront('b');
    list1.pushAtFront('a'); // List should be: a -> b
    assert(list1.size() == 2);
    assert(list1.first() == 'a');
    assert(list1.last() == 'b'); 
    std::cout << list1.toString() << ","; 
    // should print [CharLinkedList of size 2 <<ab>>]
    
    // Test pushAtBack
    list1.pushAtBack('c'); // List should be: a -> b -> c
    assert(list1.size() == 3);
    assert(list1.first() == 'a');
    assert(list1.last() == 'c'); 
    std::cout << list1.toString() << ",";  
    // should print [CharLinkedList of size 3 <<abc>>]

    // Test popFromFront
    list1.popFromFront(); // List should be: b -> c
    assert(list1.size() == 2);
    assert(list1.first() == 'b');
    assert(list1.last() == 'c');
    std::cout << list1.toString() << ",";  

    // Test popFromBack
    list1.popFromBack(); // List should be: b
    assert(list1.size() == 1);       
    assert(list1.first() == 'b');
    assert(list1.last() == 'b');
    std::cout << list1.toString() << ",";  
    std::cout << "popFromBack test passed!, " << std::endl;  
}

void testDeepCopyAndAssignment() {
    std::cout << "Testing deep copy and assignment operator..." 
    << std::endl;  
    char arr[] = {'d', 'o', 'g'};
    CharLinkedList originalList(arr, 3); 
    // List: d -> o -> g 

    // Test Copy Constructor
    CharLinkedList copiedList(originalList);
    assert(copiedList.size() == 3);
    assert(copiedList.first() == 'd');
    assert(copiedList.last() == 'g');
    assert(copiedList.elementAt(1) == 'o');
    // Modify original list and check copied list 
    originalList.popFromBack(); 
    // Original List: d -> o
    assert(copiedList.size() == 3); 
    // Copied list should still have 3 elements
    std::cout << copiedList.toString() << ","; 
    // should print [CharLinkedList of size 3 <<dog>>]

    // Test Assignment Operator
    CharLinkedList assignedList;
    assignedList = originalList; 
    // assignedList should be: d -> o
    assert(assignedList.size() == 2);
    assert(assignedList.first() == 'd');
    assert(assignedList.last() == 'o');
    // Modify original list 
    originalList.popFromBack();
    // Original List: d
    assert(assignedList.size() == 2); 
    // assignedList should still have 2 
    std::cout << assignedList.toString() << "," << std::endl;
    // should print [CharLinkedList of size 2 <<do>>]  
}   


void testedgeCases() {
    std::cout << "Testing edge cases..." << std::endl;
        char arr[] = {'A', 'l', 'i', 'c', 'e'};
    CharLinkedList list1;
    CharLinkedList list2('a');
    CharLinkedList list3(arr, 5);
    char arr2[] = {'c', 'a', 't'};
    CharLinkedList CharLinkedListOne(arr2, 3);
    char arr3[] = {'C', 'H', 'E', 'S', 'H', 'I', 'R', 'E'};
    CharLinkedList CharLinkedListTwo(arr3, 8);   



    //insertAt edge cases
    list1.insertAt('M', 0);          
    // inserting 'M' at index 0 of empty list
    cout << list1.toString() << ","; 
    // should print [CharLinkedList of size 1 <<M>>]
    list2.insertAt('N', 1);          
    // inserting 'N' at index 1 of list with one element 
    cout << list2.toString() << ",";
    // should print [CharLinkedList of size 2 <<aN>>]
    list3.insertAt('O', 3);          
    // inserting 'O' at index 3 of list with elements 'A', 'l', 'i', 'c', 'e'
    cout << list3.toString() << endl; 
    // should print [CharLinkedList of size 6 <<AliOce>>]
    try {
        list3.insertAt('c', 10);     
        // inserting 'c' at out-of-range index 10
    } catch (const std::range_error &e) {                                   
        std::cerr << e.what() << endl;  
        // This runs if list.elementAt() throws the error
    }


    list1 = CharLinkedList();   // resetting list1 
    list2 = CharLinkedList('a'); // resetting list2 
    list3 = CharLinkedList(arr, 5); // resetting list3
    
     // Test first() on an empty list to see if it throws an error
    try {
        list1.first(); // Should throw an error since list1 is empty
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    // Test last() on an empty list to see if it throws an error
    try {
        list1.last(); // Should throw an error since list1 is empty
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    //test insertinorder edge cases
    list3.insertInOrder('B');
    cout << list3.toString() << endl;
    // should print [CharLinkedList of size 6 <<ABlice>>]   
    list3.pushAtBack('C');
    cout << list3.toString() << endl;
    // should print [CharLinkedList of size 7 <<ABliceC>>]


    // Test reverse function
    try {
        cout << list3.toReverseString() << endl;
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << endl;
    }
    // should print [CharLinkedList of size 7 <<CecilBA>>]

    list1 = CharLinkedList();   // resetting list1 
    list2 = CharLinkedList('a'); // resetting list2 
    list3 = CharLinkedList(arr, 5); // resetting list3

    //TEst Concatenate edge cases
    list1.concatenate(&list2);
    cout << list1.toString() << ","; 
    // should print [CharLinkedList of size 1 <<a>>] 
    list2.concatenate(&list3);        
    // concatenating list2 with list3
    cout << list2.toString() << ",";            
    // should print [CharLinkedList of size 6 <<Alice>>]
    list3.concatenate(&list3); 
    cout << list3.toString() << endl;   
    // should print [CharLinkedList of size 10 <<AliceAlice>>]
    CharLinkedListOne.concatenate(&CharLinkedListTwo);
    cout << CharLinkedListOne.toString() << endl;
    // should print [CharLinkedList of size 11 <<catCHESHIRE>>] 
    CharLinkedListTwo.concatenate(&CharLinkedListTwo);
    cout << CharLinkedListTwo.toString() << endl;
    // should print [CharLinkedList of size 16 <<CHESHIRECHESHIRE>>]


    list1 = CharLinkedList();   // resetting list1 
    list2 = CharLinkedList('a'); // resetting list2 
    list3 = CharLinkedList(arr, 5); // resetting list3


    // test clear function
    list1.clear();              // clearing an already empty list
    list2.clear();              // clearing a non-empty list
    list3.clear();              // clearing a non-empty list
    assert(list1.size() == 0);
    assert(list2.size() == 0);
    assert(list3.size() == 0);
    cout << "Clear test passed!, ";


    // Test isEmpty() on an empty list
    cout << std::boolalpha << list1.isEmpty() << ","; 
    // should print true 
        //Test isEmpty() on a list that was just cleared
    cout << std::boolalpha << list2.isEmpty() << ","; 
    // should print true
    // Test isEmpty() on a non-empty list
    cout << std::boolalpha << list3.isEmpty() << ","; 
    // should print true
    cout << std::boolalpha << CharLinkedListOne.isEmpty() << ","; 
    // should print false
    cout << std::boolalpha << CharLinkedListTwo.isEmpty() << endl; 
    // should print false
    cout << "isEmpty() tests passed!, ";
}

int main() {
    runTests();
    testPushandPop();
    testDeepCopyAndAssignment();
    testedgeCases();
    std::cout << "All tests passed successfully!" << std::endl;  
    return 0;
}