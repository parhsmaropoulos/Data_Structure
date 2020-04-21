#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <list>
#include <cmath>

#define GMT (+2)

class Record
{
    public:
    int ID;
    int userID;
    int posx;
    int posy;
    int stayed;
    int hour;
    int min;
    int day;
    Record *next;
};
int ID = 0;

class Patient
{
    public:
    int patientID;
    int posx;
    int posy;
    int hour;
    int min;
    int day;
    Patient *next;
};
int patientID;

class Trajectory {
    public:
    int TrajID;
    Record* records;
};
int TrajID = 0;

class Point {
    public:
        int x;
        int y;
};

class Sqr {
    public:
        Point* p1;
        Point* p2;
        Point* p3;
        Point* p4;
        bool CheckIfInside(int, int);
};

bool Sqr::CheckIfInside(int posx, int posy){
    int dify = p1->y - p3->y;
    if (dify < 0) {
        dify = 0 - dify;
    }
    int difx= p1->x - p2->x;
    if (difx < 0) {
        difx = 0 - difx;
    }

    if ( posy - p1->y < dify && posy- p3->y < dify && posx - p1->x <difx && posx - p2->x < difx ){
        return true;
    }else{
        return false;
    }
}

//Returns true if give time is inside the given time limit
int MinutesLater(int recHour, int recMin, int patHour, int patMin){
    int mins;
    if(patHour <= recHour){
        mins = mins + 60*(recHour-patHour);
        mins = mins + (recMin - patMin);
    }
    return mins;
}

//Calculate the distance between two points with cords(x1,y1) and (x2,y2)
int Distance(int x1, int x2, int y1, int y2)
{
    int xdist = x1 - x2 ;
    int ydist = y1 - y2 ;
    int dist = sqrt(pow(xdist, 2) + pow(ydist, 2));
    return dist;

}
//Initialize the box 100X100(km) and trajectories list;
    std::list<Trajectory> trajectories;
    std::list<Trajectory>::iterator tit;

//Initialize newPatient list
    std::list<Patient> Patients;

void pushRec(Record** head_ref, int posx, int posy, int stayed, int day, int hour, int min, int userID)  
{  
    /* 1. allocate node */
    Record* new_record = new Record(); 
  
    /* 2. put in the data */
    new_record->posx = posx;  
    new_record->posy = posy;  
    new_record->day = day; 
    new_record->stayed = stayed; 
    new_record->hour = hour;  
    new_record->min = min;
    new_record->ID = ID;
    new_record->userID = userID;
  
    /* 3. Make next of new node as head */
    new_record->next = (*head_ref);  
  
    /* 4. move the head to point to the new node */
    (*head_ref) = new_record;  
    ID++;
} 

void insertAfterRec(Record* prev_record, int posx, int posy, int day, int hour, int min)  
{  
    /*1. check if the given prev_node is NULL */
    if (prev_record == NULL)  
    {  
        std::cout<<"the given previous record cannot be NULL";  
        return;  
    }  
  
    /* 2. allocate new node */
    Record* new_record = new Record(); 
  
    /* 3. put in the data */
    new_record->posx = posx;  
    new_record->posy = posy;  
    new_record->day = day;  
    new_record->hour = hour;  
    new_record->min = min; 
    new_record->ID = ID;
  
    /* 4. Make next of new node as next of prev_node */
    new_record->next = prev_record->next;  
  
    /* 5. move the next of prev_node as new_node */
    prev_record->next = new_record;  
    ID++;
}

void appendRec(Record** head_ref, int posx, int posy,int stayed, int day, int hour, int min, int userID)  
{  
    /* 1. allocate node */
    Record* new_record = new Record(); 
  
    Record *last = *head_ref; /* used in step 5*/
  
    /* 2. put in the data */
    new_record->posx = posx;  
    new_record->posy = posy; 
    new_record->stayed = stayed; 
    new_record->day = day;  
    new_record->hour = hour;  
    new_record->min = min;  
    new_record->ID  = ID;
    new_record->userID = userID;
  
    /* 3. This new node is going to be  
    the last node, so make next of  
    it as NULL*/
    new_record->next = NULL;  
  
    /* 4. If the Linked List is empty, 
    then make the new node as head */
    if (*head_ref == NULL)  
    {  
        *head_ref = new_record;  
        return;  
    }  
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL)  
        last = last->next;  
  
    /* 6. Change the next of last node */
    last->next = new_record;  
    ID++;
    return;  
} 


/* Given a reference (pointer to pointer) to the head of a list 
   and a key, deletes the first occurrence of key in linked list */
void deleteRecNode(struct Record **head_ref, int key) 
{ 
    // Store head node 
    struct Record* temp = *head_ref, *prev; 
  
    // If head node itself holds the key to be deleted 
    if (temp != NULL && temp->ID == key) 
    { 
        *head_ref = temp->next;   // Changed head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && temp->ID != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 
  
    free(temp);  // Free memory 
} 

//Insert a patient
void pushPatient(Patient** head_ref, int posx, int posy, int day, int hour, int min)  
{  
    /* 1. allocate node */
    Patient* new_patient = new Patient(); 
  
    /* 2. put in the data */
    new_patient->posx = posx;  
    new_patient->posy = posy;  
    new_patient->day = day;  
    new_patient->hour = hour;  
    new_patient->min = min;
    new_patient->patientID = patientID;
  
    /* 3. Make next of new node as head */
    new_patient->next = (*head_ref);  
  
    /* 4. move the head to point to the new node */
    (*head_ref) = new_patient;  
    patientID++;
} 


// This function prints contents of 
// linked list starting from head  
void printRecList(Record *rec)  
{  
    std::cout << "got her"<< std::endl;
    while (rec != NULL)  
    {  
        printf("Record info : ID { %i } for user with ID { %i } PosX %i PosY %i Day %i Hour %i Min %i Stayed for %i \n", rec->ID, rec->userID, rec->posx, rec->posy, rec->day, rec->hour, rec->min, rec->stayed);
        rec = rec->next;  
    }  
} 

void printPatientList(Patient *pat)  
{  
    while (pat != NULL)  
    {  
        printf("Patient info : ID { %i } PosX %i PosY %i Day %i Hour %i Min %i \n", pat->patientID, pat->posx, pat->posy, pat->day, pat->hour, pat->min);
        pat = pat->next;  
    }  
} 


//Summarize thetrajectory

void Summarize_Trajectory(int DayInp, int Days_Before, Record *rec){
    //Chain starts at day 0
    std::cout << "summarize" << std::endl;
    //So until we reach DayInp if rec->Day > Days_Before change trraj
    while( rec != NULL){
        Record* nextrec;
        if (rec->day == DayInp || DayInp - rec->day < Days_Before){
            break;
        }
        //If we find one day that is more than Days_Before we start to remove nodes so we summarize thetrajectory
        if (DayInp - rec->day >= Days_Before ){
            int day = rec->day;
            int startX = rec->posx;
            int staryY = rec->posy;
            nextrec = rec->next;
            //Loop until the end of that day
            while(nextrec->day == day && rec != NULL){
                //Until we find a rec that has more than distance D=7 we remove the node.   
                //To calculate the distance i will use a function called Distance(x1,x2,y1,y2)
                if (Distance(startX, nextrec->posx, staryY, nextrec->posy) > 7){
                    startX = nextrec->posx;
                    staryY = nextrec->posy;
                    nextrec = nextrec->next;   
                } else {
                    int tempID = nextrec->ID;
                    nextrec= nextrec->next;
                    deleteRecNode(&rec, tempID);
                }
            }
        }
        rec = nextrec;
    }
    return;
}
// Repair function for the trajectory.
void Repair(Record *rec, Record** head_ref, int daynum)
{
    int prevX = 0;
    int prevY = 0;
    int nextX = 0;
    int nextY = 0;
    while ( rec != NULL){
        //TODO fix day change
        // if (rec->day == daynum){
            if (rec->posx == 101 && rec->posy == 101 && rec->day == daynum)
            {
                //Get the next positions
                Record *tempnext = rec->next;
                nextX= tempnext->posx;
                nextY= tempnext->posy;

                rec->posx = (nextX + prevX) / 2;
                std::cout << nextX << ' '<< prevX << std::endl;

                rec->posy = (nextY + prevY) / 2;
                std::cout << nextY << ' '<< prevY << std::endl;

                // deleteRecNode(head_ref, rec->ID);
            }
            prevX = rec->posx;
            prevY = rec->posy;
            rec = rec->next;
        }
    // }
}

void Crowded_Places(int DayInp, int Start, int End, Sqr Sqrt, int MinStay ){
    int NumInPlace = 0;
    //Loop through the trajectories
    for (auto const& i : trajectories){
        Record *rec = i.records;
            std::cout << "checking record"<<std::endl;
            std::cout << rec->day << std::endl;

        //Loop throug each traj
        while( rec != NULL){
            std::cout << "checking day"<<std::endl;
            //Check the day
            if (rec->day == DayInp){
                //Check if they were in the give place
            std::cout << "checking place"<<std::endl;

                if(Sqrt.CheckIfInside(rec->posx, rec->posy)){
                    //Check if the time is inside the interval
            std::cout << "checking time"<<std::endl;

                    if(rec->hour >= Start && rec->hour <= End)
                    //Check if they stayed for longer than the given MinStay
            std::cout << "checking staytime"<<std::endl;

                        if(rec->stayed >= MinStay){
                            NumInPlace++;
                            break;
                        }
                }
            }
            rec = rec->next;
        }

    }
    printf("Number of people stayed for longer than the given time inside the give area and time interval are: %i" , NumInPlace);
}

void PrintTrajectories(std::list<Trajectory> const &list){
    std::cout << "got here" << std::endl;
    for (auto const& i: list)
    {
    std::cout << "got here 2" << std::endl;

        printRecList(i.records);
    std::cout << "got here 3" << std::endl;

        std::cout << i.TrajID <<"\n"<< std::endl;
    }
}

bool Possible_Infection(Record *rec, int Day, Patient *pat){
    bool infected = false;
    Patient *tempHead = pat;
    while(rec != NULL){
        if (rec->day == Day)
        {

        //Get the record position
        int x = rec->posx;
        int y = rec->posy;
        int minstay = 3;
        int mintimedifference = 50;
        int R = 4;
        while(pat !=NULL){
            std::cout<<"Check patient with id:"<< pat->patientID << std::endl;
            //Check if was inside the distance
            if (Distance(x, pat->posx, y, pat->posy) > R){
            std::cout<< "Is inside the distane"<< std::endl;
                //Check if stayed more than the time limit
                if(rec->stayed > minstay){
            std::cout<< "Stayed more than it should"<< std::endl;
                    //Check if the time was near
                    if(MinutesLater(rec->hour, rec->min, pat->hour, pat->min) <= mintimedifference){
                        printf("User with id %i and record with id: %i might got infected on : %i:%i from patient with ID: %i \n", rec->userID, rec->ID, rec->hour, rec->min, pat->patientID);
                        infected = true;
                        return infected;
                        break;
                    }
                }
            }
            pat = pat->next;
        }
        pat = tempHead;
        }
        rec = rec->next;
    }
    return infected;
}

int main() {


   //Initialize time
    time_t currentTime;
    struct tm * localTime;


    //Initial position of the person
    int initial_positionX, initial_positionY;

    

    //Start with empty list  Patients adn records
    Record* head = NULL;
    Patient* headPatient = NULL;

    //Speed of the person (3-6)km/h = Every one hour the person does 3-6 blocks of the box
    int speed = 3;
    /* 
    TIME COUNTERS: 
        Every 30 sec one record === 2*60*24  = 2880 records per day
        Every 30 mins we have a new patient === every 60 records
        DayRecords = 0 (at 2880 reset to 0) (when reset put a new pointer to the trajectory list)
        MoveCounter = 0 (1 hour records) (at 120 reset and move person)
        BlankPointCouter = 0 (every X records put a blank record)
    */
   int DayRecords = 0;
   int Day=0 ; //For debug i will use a counter instead of realtime day number
   int MaxDayRecords = 50; // For debug i use 50 instead of 2880
   int PatientCounter = 0;

   int MakeMove = 6; //Every time there is a move there will be a new number to reach the MakeMove 
   int MoveCounter = 0;
   int BlankPointCounter = 0;
   int min = 0; //Every 2 loops plus 1 when hour change reset to 0
   int hourCounter = 0;
   int hour = 0; //Every 120 loops add 1 

   int stayed = 1; // How long the person stayed when the record was made every time he/she moves it resets

// Start of the program
while(int UserID =0 < 3)
{
// Create 3 user Trajectories
    while (Day < 3)
   {
       /* initialize random seed: */
        srand (time(NULL));
        

        initial_positionX = rand() % 100 +1;
        initial_positionY = rand() % 100 +1;

        //Print the position
        // printf("Initial position x is: %i \n" , initial_positionX);
        // printf("initial position y is: %i \n" , initial_positionY);

       while(DayRecords < MaxDayRecords) // Start of the day
       {
           //Make a record

           //Get current time and extract Hour DayNumber and Min
           time (&currentTime);
           localTime = localtime( &currentTime);
            //int Hour = localTime->tm_hour;
            //int Min = localTime->tm_min;
            //int Day = localTime->tm_mday;
        
            // pushRec(&head, initial_positionX, initial_positionY, stayed,  Day, hour, min);
            // std::cout<< UserID << "is the userID" << std::endl;
            appendRec(&head, initial_positionX, initial_positionY, stayed,  Day, hour, min, UserID);
            stayed++;

           //Increase DayRecord & MoveCounter
           PatientCounter++;
           if (PatientCounter == 10)
           {
               //Insert a new patient at  a random place
                int posx = rand() % 100 +1;
                int posy = rand() % 100 +1;

                pushPatient(&headPatient, posx, posy, Day, hour, min);
            
                PatientCounter = 0;
           };

            //Change the hour and min counters;
           if(min == 0){
                min = 30;
            }else{
                min = 0;
            }
            hourCounter++;
            if (hourCounter % 2 == 0){
                hour++;
            }

           MoveCounter++;
           if (MoveCounter == MakeMove)
           {
                //Make a 'random' move 
                //Case 1 person goes right -> x++ 
                //Case 2 person goes left -> x--
                //Case 3 person goes forward -> y++
                //Case 4 person goes back -> y--
                //TODO add diagonial moves (x++ y++, x++ y--, x-- y++, x-- y--)
                //TODO add Town/Box limits
                while(true){
                int move = rand() %4 + 1;
                    switch (move)
                    {
                        case 1:
                            initial_positionX = initial_positionX + speed;
                            // std::cout << "Changed 1" << std::endl;
                            break;
                        case 2:
                            initial_positionX = initial_positionX - speed;
                            // std::cout << "Changed 2" << std::endl;
                            break;
                        case 3:
                            initial_positionY = initial_positionY + speed;
                            // std::cout << "Changed 3" << std::endl;
                            break;
                        case 4:
                            initial_positionY = initial_positionY - speed;
                            // std::cout << "Changed 4" << std::endl;
                            break;
                    }
                    if (0 <= initial_positionY <= 100 && 0 <= initial_positionX <= 100 ){
                        break;
                    }
                }

                MoveCounter = 0;
                stayed = 1;
                MakeMove = 2 + rand() % 5 + 1;
                //Change speed
                speed = 3 + rand() % 3 + 1;
                // std::cout<< speed << std::endl;
                
           };
           DayRecords++;
           BlankPointCounter++;
           if (BlankPointCounter == 20)
           {
               //We skip 1 loop
               DayRecords++;
               //Because it will not be easy to debug in real time i will put a blank record instead
                // pushRec(&head, 101, 101, NULL,  Day, hour, min);
                appendRec(&head, 101, 101, NULL,  Day, hour, min, UserID);

                BlankPointCounter = 0;
                if(min == 0){
                min = 30;
                }else{
                    min = 0;
                }
                hourCounter++;
                if (hourCounter % 2 == 0){
                    hour++;
                }
           };
           if (hour == 24) break;
       }
        //End of the day
    //    Repair(head, &head, Day);
        //If the day is number 5 do the summarize
        // Possible_Infection(head, Day, headPatient);
        Day++;
       hour = 0;
       hourCounter = 0;
       min = 0;

       DayRecords = 0;
       MoveCounter = 0;
   };

        Day = 0;
        Trajectory *traj = new Trajectory();
        traj->TrajID = UserID;
        traj->records = head;
        trajectories.push_back(*traj);
        UserID++;   
}
// Summarize_Trajectory(2, 1, head);
std::cout<< "ended"<< std::endl;


//Create the square for the check
Sqr *square = new Sqr();
Point *p1 = new Point();
p1->x = 0;
p1->y = 0;
Point *p2 = new Point();
p2->x = 100;
p2->y = 0;
Point *p3 = new Point();
p3->x = 0;
p3->y = 100;
Point *p4 = new Point();
p4->x = 100;
p4->y = 100;
square->p1 = p1;
square->p2 = p2;
square->p3 = p3;
square->p4 = p4;

Crowded_Places(2, 5, 19, *square, 3);
// PrintTrajectories(trajectories);
// printPatientList(headPatient);
// printPatientList(headPatient);
// printRecList(head);

   /*
   Functions:
        Possible_Infection(Trajectory, Day, List_of_Patiens):
            Compare the user trajectory on the given day with patients positions

        Crowded_Places(Day, Time_interval, Sqrt, MinStay ): 
            Given the day, time space, squares and the minimum stay time 
            return the places where meet those criteria.

        Repair(Day, Trajectory):
            Check if the trajectory is normal 
            (normal means that each record has 30 second difference with the next one)
            if it is not normal then add imaginary point in the midst of those two points.
        
        Summarize_Trajectory(Day,Days_Before, Trajectory):
            if there are day more than Days_Before the given Day replace them with a summary**.

            **Summary: Loop through all the points of the day.Starting with x,y remove any points that are less than R
            far away from the x,y until we find one point x1,y1 that is farther than R from the starting point
            repeat until we have the summary of the day.

        !!! At the end of the day call those function in the given order:
            1)Repair
            2)Possible_Infection
            3)Summarize_Trajectory
            4)Crowded_Places
   */
    
}
