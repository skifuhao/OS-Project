#ifndef SCHEDULE
#define SCHEDULE

#include "process.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<process>::iterator process_ptr;

class schedule_algorithm {
public:
  schedule_algorithm(const std::vector<process> &, const int);
  virtual void run() = 0;

protected:
  /* Call context switch. Note this process pressumes that
  this is the initial switch in for the incoming process and final
  switch out for outcoming process
  If this is not the initial switch in or final switch out,
  call wait_for_1ms(false) for t_cs/2 milisecond outside
  this function. */
  void context_switch(process_ptr);
  void check_arrival();
  void do_waiting();
  void do_blocking();
  void prepare_add_to_ready_queue(process_ptr);
  void print_event(const std::string);
  virtual void perform_add_to_ready_queue() = 0;
  // virtual void preempt() = 0;
  std::vector<process> processes;
  const int t_cs;
  int time;
  process_ptr running;
  std::list<process_ptr> ready_queue;
  std::set<process_ptr> blocked;
  std::set<process_ptr> terminated;
  std::vector<process_ptr> pre_ready_queue;
};

class FCFS_scheduling : public schedule_algorithm {
public:
  // Constructor. New arrival added to beggining when add is true
  // end when false
  FCFS_scheduling(const std::vector<process> &p, const int t_cs);
  void run();

private:
  void perform_add_to_ready_queue();
};

class RR_scheduling : public schedule_algorithm {
public:
  // Constructor. New arrival added to beggining when add is true
  // end when false
  RR_scheduling(const std::vector<process> &p, const int t_cs,
                const int t_slice, const bool add);
  void run();

private:
  void perform_add_to_ready_queue();
  // time slice value
  int t_slice;
  // New arrival is added to begginning when add is true
  bool add;
};
class SJF_scheduling : public schedule_algorithm{
public:
  // Constructor. New arrival added to beggining when add is true
  // end when false
  SJF_scheduling(const std::vector<process> &p, const int t_cs, 
                  const double lambda,const double alpha);
  void run();
private:
  //update the est_tau
  int est_tau(double tau,int t,alpha);//need const???
  void perform_add_to_ready_queue();
  //lamida for calculate tau0; 
  double lambda;
  //alpha is a parameter in the equation
  double alpha;
};

#endif