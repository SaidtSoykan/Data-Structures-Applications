#include "Agent.h"

// Switches the state an agent to occupied
void Agent::FullIt() { full = true; };

// Switches the state an agent to free
void Agent::EmptyIt() { full = false; };

// Agent constructor, state is false initially
Agent::Agent() { full = false; };

// Returns the time of an agent becoming free
int Agent::getwaitingtime() { return waitingtime; };

// Assigns the time of an agent becoming free
void Agent::setwaitingtime(int Time) { this->waitingtime = Time; };

// Reduces the waiting time of an agent by 1
void Agent::ReduceWaitingtime() { waitingtime--; };
