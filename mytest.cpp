// UMBC - CMSC 341 - Spring 2022 - Proj1
//Gurnoor Hira
//mytest.cpp
#include "elevator.h"
#include "elevator.cpp"
class Tester{
    public:
    /******************************************
    * Test function declarations go here! *emacs 
    ******************************************/
   bool testCopyConstructor(const Elevator& elev);
   bool testAssignmentOperator(const Elevator& elev);
};
int main(){
    Tester tester;
    Elevator anElev;
    //insert at head testing with normal case making sure each node inserts
    cout << "testing insert at head" <<endl;
    cout <<endl;
    for(int i = 100; i >= 1; i--){
        if(anElev.insertAtHead(i) == true){
            cout <<"Inserting node" <<endl;
        }
    }

    cout <<endl;
    //insert at head testing to make sure duplicate insert does not happen
    if(anElev.insertAtHead(1) == false){
        cout <<"prevents against duplicate insert " <<endl;
    }

    cout << endl;
    //insert at head testing to make sure out of order insertion is prevented
    if(anElev.insertAtHead(101) == false){
        cout << "prevents out of order insertion" <<endl;
    }

    cout << endl;
//finished insert at head testing
    cout << "insert at head successfully completed" <<endl;

    cout << endl;
    Elevator anElev2;
    //insert at tail testing normal case making sure all nodes insert
    cout << "Testing insert at tail" << endl;
    cout << endl;
    for(int i = 1; i <= 100; i++){
        if(anElev2.insertAtTail(i) == true){
            cout << "Inserting node" <<endl;
        }
    }

    cout << endl;
    //insert at tail testing make sure duplicate insertion not possible
    if(anElev2.insertAtTail(100) == false){
        cout << "prevents duplicate insert" << endl;
    }

    cout << endl;
    //insert at tail testing prevent out of order insertion
    if(anElev2.insertAtTail(0) == false){
        cout << "prevents out of order insertion" <<endl;
    }
 
    cout << endl;
    //insert at tail testing finished
    cout <<"insert at tail successful" <<endl;
    cout << endl;

//testing remove function
    cout << "Testing remove" << endl;
    Elevator anElev3;
    //insert floors into elevator
    try{
        for(int j = 1; j <= 10; j++){
            if(anElev3.insertAtTail(j) == false){
                cout << "insert at tail failed" <<endl;
            }
        }
    }catch(std::out_of_range const &e){
        cout << endl;
    }
    anElev3.dump();
    cout << endl;
    //test remove normal case
    try{
        if(anElev3.removeFloor(3) == true){
            cout << "Remove normal case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    cout <<endl;
    //test remove edge case(removing tail)
    try{
        if(anElev3.removeFloor(10) == true){
            cout << "Remove edge case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    //test remove duplicate error case
    try{
        if(anElev3.removeFloor(3) == false){
            cout << "prevents against duplicate remove" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    //test remove normal case
    try{
        if(anElev3.removeFloor(8) == false){
            cout << "Remove normal case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    anElev3.dump();
    //remove test finished
    cout << "remove successful" << endl;
    cout << endl;
    //testing insert function
    cout << "using same elevator to test insert floor " << endl;
    //insert normal case
    try{
        if(anElev3.insertFloor(3) == true){
            cout <<"insert normal case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    //insert normal case
    try{
        if(anElev3.insertFloor(8) == true){
            cout <<"insert normal case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    //insert egde case(inserting a tail)
    try{
        if(anElev3.insertFloor(10) == true){
            cout <<"insert edge case works" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    //insert error caase -- duplicate
    try{
        if(anElev3.insertFloor(5) == false){
            cout <<"prevents against duplicate insertion" <<endl;
        }
    }catch(std::out_of_range const &e){
        cout  << endl;
    }
    anElev3.dump();
    //insert testing finished
    
    cout << "insert successful" <<endl;
    cout << endl;

    cout << "Test copy constructor" << endl;
    Elevator elev4;
    for(int i = 1; i <= 5; i++){
        elev4.insertAtTail(i);
    }
    Elevator copyElev4(elev4); //calling copy constructor
    elev4.removeFloor(2);
    //check if deep copy
    if(elev4.checkFloor(2) || !copyElev4.checkFloor(2)){
        cout << "deep copy failed " <<endl;
    }
    elev4.clear();
    for(int i = 1; i < 5; i++){
        bool exception = false;
        try{
            elev4.checkFloor(i);
        }
        catch(out_of_range e){
            exception = true;
        }
        if(!exception) {
            cout << "Pass: out of range exception not thrown " <<endl;
        }
        if(copyElev4.checkFloor(i) == false){
            cout << "fail floor not in deep copy" <<endl;
        }
    }
    //copy constructor testing done
    cout << "copy constructor testing done" <<endl;
    cout << endl;
    //test assignment operator
    cout << "testing assignment operator" <<endl;
    copyElev4 = copyElev4;
    //test for self assignment
    for(int i = 1; i <5; i++){
        if(copyElev4.checkFloor(i) == false){
            cout << "self assignment detected" <<endl;
        }
    }
    cout << "assignment operator successful" <<endl;
    
}



