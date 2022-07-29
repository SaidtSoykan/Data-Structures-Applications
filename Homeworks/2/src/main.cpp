#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Agent.h"
#include "Passenger.h"

int main(int argc, char **argv) {

  int time; // 120/180 mins
  int passenger_count, agent_count;

  int ID, miles, disabled, pregnant, minute, checkin_time;
  int current_time = 0; // Initial timing
  int pop_count = 0;

  vector<Passenger> my_list; // Passenger list
  vector<Agent> agent_list;  // Agent list

  PriorityQueue passengerhouse; // PQ for holding passengers

  // Filling in the passenger list
  ifstream myfile(argv[1]);
  myfile >> passenger_count >> agent_count >> time;
  for (int i = 0; i < passenger_count; i++) {
    myfile >> ID >> miles >> disabled >> pregnant >> minute >> checkin_time;
    Passenger *temp =
        new Passenger(ID, miles, disabled, pregnant, minute, checkin_time);
    my_list.push_back(*temp);
    delete temp;
  }

  // Filling in the agent list
  myfile.close();
  for (int i = 0; i < agent_count; i++) {
    Agent *temp = new Agent();
    agent_list.push_back(*temp);
    delete temp;
  }
  if (time == 0) {
    time = 120; // domestic;
  } else if (time == 1) {
    time = 180; // international
  }

  int passenger_tracker = 0;

  bool NotFinish = true;
  int EmptyAgentCount = 0;
  while (NotFinish) {
    // Check incoming passengers and enqueue
    while (my_list[passenger_tracker].getminute() == current_time &&
           passenger_tracker < passenger_count) {
      Passenger temp = my_list[passenger_tracker];
      passengerhouse.push(temp);
      passenger_tracker++;
    }
    // Check whether any of the agents become free and
    // updaate their waiting time accordingly
    for (int i = 0; i < agent_count; i++) {
      if (agent_list[i].getwaitingtime() != 0) {
        if (agent_list[i].full) {
          agent_list[i].ReduceWaitingtime();
        }
      } else {
        agent_list[i].EmptyIt();
      }
    }
    // Pop passengers from the queue if any of the agents become free
    for (int i = 0; i < agent_count; i++) {
      if (!agent_list[i].full && !passengerhouse.empty()) {
        agent_list[i].FullIt();
        cout << "Agent " << i + 1 << " takes passenger "
             << passengerhouse.top().getID() << " at minute " << current_time
             << endl;
        agent_list[i].setwaitingtime(passengerhouse.top().getCheckintime() - 1);
        passengerhouse.pop();
        pop_count++;
      }
    }
    // Check if all passengers are handled and agents are available.
    if (pop_count == passenger_count) {
      for (int i = 0; i < agent_count; i++) {
        if (!agent_list[i].full) {
          EmptyAgentCount++;
        }
      }
      if (EmptyAgentCount == agent_count) {
        NotFinish = false;
      }
      EmptyAgentCount = 0;
    }
    // If not done, increment time by 1
    if (NotFinish) {
      current_time++;
    }
  }

  if (current_time > time) {
    cout << "Check-in failed to be completed on time, it took " << current_time
         << " minutes ";
  } else {
    cout << "Check in is complete on time in " << current_time << " minutes ";
  }

  return EXIT_SUCCESS;
}
