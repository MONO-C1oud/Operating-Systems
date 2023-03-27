#include <iostream>
#include <queue>

using namespace std;

// Define a structure to represent a process
struct Process {
    int id;           // process ID
    int priority;     // process priority
    int burst_time;   // time required to complete the process
};

// Define a function to compare two processes based on their priority
struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.priority < p2.priority;
    }
};

int main() {
    // Create a queue to store the processes
    queue<Process> process_queue;

    // Add some processes to the queue (in this example, we add 4 processes)
    process_queue.push({1, 2, 10});  // process ID 1, priority 2, burst time 10
    process_queue.push({2, 1, 5});   // process ID 2, priority 1, burst time 5
    process_queue.push({3, 3, 8});   // process ID 3, priority 3, burst time 8
    process_queue.push({4, 2, 12});  // process ID 4, priority 2, burst time 12

    // Set the time quantum to 2 seconds
    const int time_quantum = 2;

    // Run the Round Robin scheduling algorithm
    while (!process_queue.empty()) {
        // Get the first process in the queue
        Process current_process = process_queue.front();
        process_queue.pop();

        // Run the current process for the time quantum
        cout << "Running process " << current_process.id << " for " << time_quantum << " seconds" << endl;
        current_process.burst_time -= time_quantum;

        // If the process has completed, print a message and continue to the next process
        if (current_process.burst_time <= 0) {
            cout << "Process " << current_process.id << " has completed" << endl;
        } 
        // If the process has not completed, add it back to the queue with updated burst time
        else {
            process_queue.push(current_process);
        }
    }

    return 0;
}
