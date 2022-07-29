#include "Passenger.h"

// Constructs the Passenger class
Passenger::Passenger(int id, int miles, bool disabled, bool pregnant,
                     int minute, int checkin_time) {
  this->ID = id;
  this->miles = miles;
  this->disabled = disabled;
  this->pregnant = pregnant;
  this->minute = minute;
  this->checkin_time = checkin_time;
  this->priority = 0;

  // Pregnant & Disabled people should be prioritized over normal people
  if (disabled || pregnant) {
    this->priority += 101.0;
  }

  // Miles should also be taken into account, but it should be less than
  // the priority that is given for the Pregnant & Disabled people
  this->priority += 100.0 - (100.0 / (miles + 1.0));
};

// Returns the priority
double Passenger::getpriority() { return priority; };

// Returns the time to handle the passenger
int Passenger::getminute() { return minute; };

// Returns the check-in time
int Passenger::getCheckintime() { return checkin_time; }

// Returns the passenger ID
int Passenger::getID() { return ID; }

// Constructs via copying from an existing passenger
Passenger::Passenger(const Passenger &passenger1) {
  ID = passenger1.ID;
  checkin_time = passenger1.checkin_time;
  disabled = passenger1.disabled;
  pregnant = passenger1.pregnant;
  minute = passenger1.minute;
  checkin_time = passenger1.checkin_time;
  priority = passenger1.priority;
}

// Returns the size of the PQ
int PriorityQueue::size() { return A.size(); }

// Returns the emptiness status of the PQ
bool PriorityQueue::empty() { return size() == 0; }

// Pushes a passenger into a PQ
void PriorityQueue::push(Passenger key) {
  A.push_back(key);       // Add
  int index = size() - 1; // Get the idx of the added element
  heap_up(index);         // Heapify Up
}

// Pops from a PQ
void PriorityQueue::pop() {
  A[0] = A.back(); // Update the 0th idx with the max-element
  A.pop_back();    // Drop the element
  heap_down(0);    // Heapify Down
}

// Gets the maximum element from the PQ
Passenger PriorityQueue::top() { return A[0]; }

// Gets the parent of a heap node
int PriorityQueue::parent(int i) { return (i - 1) / 2; }

// Gets the left children of a heap node
int PriorityQueue::Left(int i) { return (2 * i + 1); }

// Gets the right children of a heap node
int PriorityQueue::Right(int i) { return (2 * i + 2); }

// Changes the ordering of 2 passengers within a heap
void PriorityQueue::swap(Passenger &a, Passenger &b) {
  Passenger temp = b;
  b = a;
  a = temp;
}

//
void PriorityQueue::heap_down(int i) {
  int left = Left(i);
  int right = Right(i);
  int largest = i;

  // Finding if the left or right child has higher priority
  if (left < size() && A[left].getpriority() > A[i].getpriority()) {
    largest = left;
  }
  if (right < size() && A[right].getpriority() > A[largest].getpriority()) {
    largest = right;
  }

  // If there is a change, swap elements and proceed heapification
  if (largest != i) {
    swap(A[i], A[largest]);
    heap_down(largest);
  }
}

// Checks and resorts if the newly added element has higher priority
void PriorityQueue::heap_up(int i) {
  if (i && A[parent(i)].getpriority() < A[i].getpriority()) {
    swap(A[i], A[parent(i)]);
    heap_up(parent(i));
  }
}
