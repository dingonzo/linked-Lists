# LinkedLists
# Program Purpose
This program implements a CharLinkedList class, which is a linked 
    list implementation of a list of characters. The class includes 
    constructors, a destructor, and various member functions for
    manipulating the list, such as adding/removing characters,
    and accessing elements. The implementation of these functions
    will be provided in the corresponding CharLinkedList.cpp file.
    Using a doubly linked list structure, each node will have
    a pointer to both the next and previous nodes in the list.
    Additionally, a unit test file is provided to test the functionality
    of the CharLinkedList class. Two other files are incldued that test 
    time measurements, (timer_main.cpp) and a Makefile to build the program.

        

Compile/run:
-----------

    Compile using the command "make unit_test"
    Run using the command "./unit_test"
    Then compile using the command "make timer"
    Run using the command "./timer"


Acknowledgments:
---------------

    I used github, c++, and w3 schools to assist me in understanding 
    and solving this assignment. The rest of the time was dedicated to "

Files:
-----

CharLinkedList.h: 
This header file is the blueprint/ interface for the
doubly linked list. It defines the "shape" of the class and the rules
for interacting with it, without containing the actual logic for 
how the functions operate. Within this file there is class structure 
declaration, node definition, and function prototypes. Finally it features 
encapsulation by separting the public interface from the private interface.

CharLinkedList.cpp: 
This file is the implementation of the blueprint file
provided by CharLinkedList.h. This file is what makes the program start.
It provides function definitions, management of memory and recursive logic,
(recursive copying, insertion, and deletion by "stitching" together next 
and prev pointers.)
----It also manages the internal state of the list, ensuring that
front, back, and numItems are updated correctly after every operation.
----It implements the bounds checking and throws the specific exceptions 
(like std::range_error).

unit_tests.cpp: 
This file contains a variety of tests that feature of the 
functions defined and implemented by the above two files. I 
implemented edge case testing that  featured "insertAt", "first", "last", 
"insertinOrder", "reverse" "concatenate" and other testers. 
It also tests pop functions.

timer_main.cpp: 
This file has already been premade and has been implemented 
for further testing. 

Makefile: File to build the program.


Data Structures:
---------------
The data Structures formed in this program are as followed:
Node structure - the core linkage
*info - stores data, *next points to the next node, *prev points to the
previous node. 
This is followed by the Recursive helper funcitons----
These functions move down the chain via next pointers and then "repair"
or update the prev pointers during the backtracking phase of the recursion.
I used the doubly linked list since it features the backtracking repair. 
This is  due to the fact that this type of list brings a repair strategy
that ensures pointer consistency and atomic operations (dangling pointers)
By the time the recursion fully resolves, the entire list is guaranteed 
to be in a valid state, rather than having half-finished links if a 
loop were to be interrupted.

(F)A Linked List is a linear data structure where elements (nodes) are stored 
in non-contiguous memory locations. Each node consists of a data part and 
a pointer (or reference) that links it to the next node in the sequence.
---One major advantage to this approach is Dynamic Memory Allocation. 
This means that it can grow indefinitely as long as memory is available, 
avoiding the "overflow" issues common with fixed-size arrays.
---One major disadvantage is Memory Overhead. Each node requires extra memory 
to store the pointers in addition to the actual data, making it less 
memory-efficient than a simple array for small data types

Testing:
-------

Testing has been done by every created class, constructor,
and deconstructor. I would add cout text to ensure that each phase 
worked. Most of the testing files have not been commented out incase for 
any review. The above file descriptions list the tests in order. My logic when approaching the test went about like this:
1. list tester function by descending order listed in the header file.
2. When possible, test the empty list 
3. followed by testing a non-empty list.
4. Print the result.
There were several times that I used try catch else statements for additional
testing concering run_time and range_errors. I knowingly would throw these 
exceptions to provide a more well rounded test for my functions. I found
myself using assert statements more frequently as well. Another testing 
function that I would use as testing "markers" as my code would be executed 
were "if else" statements. These staements allowed me to benchmark my progress. 
I also  frequently used valgrind./unit_testing to measure the amount of memory 
I was losing. This was especially helpful since at one point i lost track
of the nodes I was creating and I received a recurring implementation 
fault.

(I) - 
All operations below are run on a separate, randomly generated
CharLinkedList of size 10000.

3. Pushat front and pushat back seemed to be much faster using this doubly
linked list as opposed to the single linked list.
--- call elemntAt in a single array list worked significantly faster than 
in the double linked list.
