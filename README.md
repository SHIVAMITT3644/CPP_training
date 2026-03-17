Traffic Light Simulation 
Overview

This project simulates a traffic light system at a four-way intersection using C++. The simulation manages traffic flow between roads A, B, C, and D while ensuring safe vehicle movement based on traffic signal rules.

The system runs a background traffic light cycle using multithreading while the main program interacts with the user to process vehicle movement requests.

Features

Simulates a four-road intersection (A, B, C, D)
Traffic lights change automatically in the background
Vehicles move based on signal state
Vehicles wait if the light is red
Supports left-pass rule when allowed
Input validation for roads and menu choices
Prevents invalid operations (same source and destination road)
Thread-safe traffic light access using std::binary_semaphore
System Architecture
The system is divided into multiple components following object-oriented design principles.

Components
ITrafficLight

Interface defining the behavior of a traffic light.

Responsibilities:
Turn light green
Turn light red
Check if the light is green
TrafficLight
Concrete implementation of ITrafficLight.

Responsibilities:
Maintain the current state of the signal
Provide state transitions between Red and Green
Road
Represents a road in the intersection.

Each road contains:
Road identifier (A, B, C, D)
Associated traffic light
IntersectionController
Central controller managing the traffic system.

Responsibilities:
Control traffic signal switching
Manage vehicle movement
Apply left-pass rules
Synchronize signal access using semaphore
Run background traffic cycle
TrafficSimulation
Handles program execution.

Responsibilities:

Initialize roads and traffic lights
Display user menu
Process vehicle movement requests
Concurrency Model

The simulation uses two threads:

1. Main Thread
Handles:
Menu display
User input
Vehicle movement requests

2. Traffic Cycle Thread
Runs continuously in the background to:
Change traffic signals
Rotate the green signal across all roads
Synchronization between threads is handled using std::binary_semaphore.

Traffic Rules
The following rules govern vehicle movement:
If the traffic light is green, the vehicle can proceed immediately.
If the traffic light is red, the vehicle must wait until it turns green.
Vehicles may pass on the left under specific conditions:
A → B
B → C
C → D
D → A

Source and destination roads cannot be the same.

Project Structure
assignment/week9
│
├── include
│   ├── Constants.h
│   ├── Input.h
│   ├── IntersectionController.h
│   ├── ITrafficLight.h
│   ├── Road.h
│   ├── TrafficLight.h
│   └── TrafficSimulation.h
│
├── src
│   ├── Input.cpp
│   ├── IntersectionController.cpp
│   ├── Road.cpp
│   ├── TrafficLight.cpp
│   └── TrafficSimulation.cpp
│
├── main.cpp
└── README.md

How It Works:-
Program starts the traffic signal cycle thread.
Signals rotate every few seconds among roads A, B, C, and D.
User selects source and destination roads.
Controller checks the signal state:
Green → vehicle moves
Red → vehicle waits
Left-pass allowed → vehicle moves immediately

Once the signal turns green, the vehicle proceeds.

Example Output
===== Traffic Light Menu =====
1. Process Vehicle
2. Exit

Enter your choice: 1

Road Layout:
A  B
D  C

Enter source road name (A/B/C/D): A
Enter destination road name (A/B/C/D): C

Road A light is red. Please wait until it turns green.
Road A light is green now. Vehicle can go to road C.
Build and Run

Compile the project using C++20.
g++ -std=c++20 -pthread src/*.cpp main.cpp -o traffic_simulation

Run the program:
./traffic_simulation