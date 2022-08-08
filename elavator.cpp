// UMBC - CMSC 341 - Spring 2022 - Proj1
//Gurnoor Hira
//elevator.cpp
#include "elevator.h"
const int ZERO = 0;
const string EMPTY = "";
Elevator::Elevator(){
    m_ground = nullptr; //linked list head
    m_top = nullptr; //linked list tail
}
Elevator::~Elevator(){
    clear();
}

void Elevator::clear(){
    //traversing through linked list and deleting each node's data then setting it to null
    Floor *temp;
    while(m_ground != nullptr){
        temp = m_ground;
        m_ground = m_ground->m_next;
        temp->m_next = nullptr;
        temp->m_previous = nullptr;
        delete temp;
    }
    temp = nullptr;
    m_top = nullptr;
}

//O(1)
bool Elevator::insertAtHead(int floor, string passenger){
    //inserting node to beginning of linked list
    Floor* temp = m_ground;

    while(temp != nullptr){
        if(temp->m_floorNum == floor){ //if floor already exists
            return false;
        }
        temp = temp->m_next;
    }
    if(m_ground == nullptr){
        m_ground = m_top = new Floor(floor,passenger);
        return true;
    }
    else if(m_ground->m_floorNum > floor){
        m_ground->m_previous = new Floor(floor,passenger);
        m_ground -> m_previous -> m_next = m_ground;
        m_ground = m_ground -> m_previous;
        return true;
    }
    return false;
}

//O(1)
bool Elevator::insertAtTail(int floor, string passenger){
    //inserting node end of linked list
    Floor* temp = m_ground;
    while(temp != nullptr){
        if(temp->m_floorNum == floor){ //if floor already exists
            return false;
        }
        temp = temp->m_next;
    }
    Floor *lastNode = new Floor(floor,passenger);
    lastNode->m_next = nullptr;
    if (m_ground == nullptr){ //if list empty
        m_ground = lastNode;
        m_top = lastNode;
        return true;
    }
    if(m_top->m_floorNum > floor){ //if floor is less than tail of linked list
        return false;
    }
    else{
        m_top->m_next = lastNode;
        lastNode->m_previous = m_top;
        m_top = lastNode;
    }
    return true;
}

bool Elevator::removeFloor(int floor){
    //removing floor from elevator
    if(m_ground == nullptr){ //if list empty
        cout << "Linked list empty" <<endl;
        return false;
    }
    if(checkFloor(floor) == false){ //if floor to remove is not in elevator
        cout << "Floor doesn't exist" << endl;
        return false;
    }
    //traverse to floor
    Floor *curr = m_ground;
    while(curr != nullptr && curr->m_floorNum != floor){
        curr = curr->m_next;
    }
    if(curr == nullptr){ 
        cout << "Floor not found" <<endl;
        return false;
    }
    if(curr->m_previous == nullptr){
        //removing first item
        int item = 0;
        Floor *next = m_ground->m_next;
        if(next->m_next != nullptr){
            next->m_previous = nullptr;
        }
        item = m_ground->m_floorNum;
        delete m_ground;
        m_ground = next;
        return true;
    }
    else if(curr->m_next == nullptr){
        //removing last item
        int item;
        item = m_top->m_floorNum;
        Floor *previous = m_top->m_previous;
        if(previous != nullptr) {
            previous->m_next = nullptr;
        }
        m_top->m_previous = nullptr;
        delete m_top;
        m_top = previous;
        return true;
    }
    else{
        //node is ssomewhere in the middle of list
        Floor *nextPtr = curr->m_next;
        Floor *prevPtr = curr->m_previous;
        nextPtr->m_previous = prevPtr;
        prevPtr->m_next = nextPtr;

        curr->m_next = nullptr;
        curr->m_previous = nullptr;
        delete curr;
        curr = nullptr;
        return true;
    }
    return false;
}

bool Elevator::insertFloor(int floor){
   if(m_ground == nullptr){ //if list empty
       return false;
   }
   if(floor < 0){ //floor to add is invalid
       return false;
   }
   Floor *temp = nullptr;
   if(floor - m_ground->m_floorNum < m_top->m_floorNum - floor){ 
       //if floor is closer to head of list than tail
       temp = m_ground;
       while(temp->m_floorNum < floor){
           temp = temp->m_next;
       }
   }
   else{
       //if floor closer to tail of list than head
       temp = m_top;
       while(temp->m_floorNum > floor){
           temp = temp->m_previous;
       }
   }
   if(temp == nullptr){
       throw out_of_range("out of range");
   }
   if(temp->m_floorNum == floor){
       //floor already there, prevents duplicate insertion
       cout << "Floor already exists" <<endl;
       return false;
   }
   if(temp->m_floorNum < floor){
       if(temp == m_top){
           m_top -> m_next = new Floor(floor,EMPTY);
           m_top->m_next ->m_previous = m_top;
           m_top =m_top->m_next;
       }
       else{
           Floor *f = new Floor(floor,EMPTY);
           f->m_next = temp ->m_next;
           temp -> m_next = f;
           f -> m_previous = temp;
           f -> m_next -> m_previous = f;
           f = nullptr;
       }
    
   }
   else{
       if(temp == m_ground){
           m_ground -> m_previous = new Floor(floor,EMPTY);
           m_ground -> m_previous -> m_next = m_ground;
           m_ground = m_ground -> m_previous;
       }
       else{
           Floor *newFloor = new Floor(floor,EMPTY);
           newFloor->m_previous = temp->m_previous;
           temp->m_previous = newFloor;
           newFloor->m_next = temp;
           newFloor->m_previous->m_next = newFloor;
           newFloor = nullptr;
           return true;
       }
   }
   temp = nullptr;
   return true;
}

bool Elevator::checkFloor(int floor){
    //check if given floor is in elevator
    if(m_ground == nullptr){ //if list empty
        return false;
    }
    if(floor < m_ground->m_floorNum || floor > m_top->m_floorNum){ 
        //if floor less than head or greater than tail throw exception
        throw out_of_range("out of range exception(in check floor)");
        return false;
    }
    else{
        Floor *temp = m_ground;
        //traverse through list looking for floor
        while(temp != nullptr){
            if(temp->m_floorNum == floor){
                return true;
            }
            temp = temp->m_next;
        }
        return false;
    }
    return true;

}
bool Elevator::move(int origin, int destination){
    //move a passenger from one floor to the next
    string pass;
    //make sure both parameters are floors that exist in list
    if(checkFloor(origin) == false || checkFloor(destination) == false){
        cout << "cannot move" <<endl;
        return false;
    }
    ///if moving up elevator start at head
    if(origin < destination){
        Floor* temp = m_ground;
        while(temp != nullptr){
            if(temp->m_floorNum == origin){
                pass = temp->m_passenger;
                temp->m_passenger = EMPTY;
            }
            if(temp->m_floorNum == destination){
                temp->m_passenger = pass;
            }
            temp = temp->m_next;
        }
        return true;
    }
    //if already at floor then stay
    if(origin == destination){
        return true;
    }
    //if moving down on elevator start at tail
    if(origin > destination){
       Floor* temp = m_top;
       while(temp != m_ground){
           if(temp->m_floorNum == origin){
               pass = temp->m_passenger;
               temp->m_passenger = EMPTY;
           }
           if(temp->m_floorNum == destination){
               temp->m_passenger = pass;
           }
           temp = temp->m_previous;
       }
       return true;
    }
    else{
        throw out_of_range("out of range exception");
        return false;
    }
    
}
string Elevator::exit(int floor, string passenger){
    //passenger at given floor exists elevator
    if(m_ground == nullptr){
        return "";
    }
    //given floor must exist
    if(checkFloor(floor) == false){
        return "";
    }
    else{
        
        Floor *temp = m_ground;
        while(temp != nullptr){
            //traverse through list till reach floor with passenger
            if(temp->m_floorNum == floor && temp->m_passenger == passenger){
                //set passenger to empty string
                temp->m_passenger = "";
                return passenger;
            }
            temp = temp->m_next;
        }
        return "";
    }
    return "";

}

bool Elevator::enter(int floor, string passenger){
    //add passenger to given floor
    if(m_ground == nullptr){
        return false;
    }
    if(checkFloor(floor) == false){ //floor must exist
        return false;
    }
    else{
        Floor* temp = m_ground;
        while(temp != nullptr){
            //traverse to the floor and check if no passenger is there then add the passenger
            if(temp->m_floorNum == floor && temp->m_passenger == EMPTY){
                temp->m_passenger = passenger;
                return true;
            }
            temp = temp->m_next;

        }
        return false;
    }
}
Elevator::Elevator(const Elevator & rhs){
    //copy constructor makes deep copy
    if(rhs.m_ground == nullptr){
        return;
    }
    this->m_ground = new Floor(rhs.m_ground->m_floorNum,rhs.m_ground->m_passenger);
    Floor *temp = rhs.m_ground->m_next;
    this->m_top = this->m_ground;
    while(temp != nullptr){
        this->m_top->m_next = new Floor(temp->m_floorNum,temp->m_passenger);
        this->m_top->m_next->m_previous = this->m_top;
        this->m_top = this->m_top->m_next;
        temp = temp->m_next;
    }
}

const Elevator & Elevator::operator=(const Elevator & rhs){
    //assignment operator
    if(this != &rhs){
        clear();
        if(rhs.m_ground == nullptr){
            cout << "linked list empty" <<endl;
        }
        this->m_ground = new Floor(rhs.m_ground->m_floorNum,rhs.m_ground->m_passenger);
        Floor *temp = rhs.m_ground->m_next;
        this->m_top = this->m_ground;
        while(temp != nullptr){
            this->m_top->m_next = new Floor(temp->m_floorNum,temp->m_passenger);
            this->m_top->m_next->m_previous = this->m_top;
            this->m_top = this->m_top->m_next;
            temp = temp->m_next;
        }
    }
    return *this;
}

void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}
