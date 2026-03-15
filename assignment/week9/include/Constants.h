#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const std::string ROAD_LAYOUT = R"(

                    [ Road A ]
                        ||
                        ||
                        ||
  [ Road D ] ========== ++ ===========[ Road B ]
                        ||
                        ||
                        ||
                     [ Road C ]

)";

const std::string TRAFFIC_LIGHT_MENU = R"(

===== Traffic Light Menu =====
1. Process Vehicle
2. Exit

)";
 
constexpr const char*  ROAD = "Road ";
constexpr char FIRST_ROAD_NAME = 'A';
constexpr char SECOND_ROAD_NAME = 'B';
constexpr char THIRD_ROAD_NAME = 'C';
constexpr char FOURTH_ROAD_NAME = 'D';
constexpr int GREEN_SIGNAL_DURATION_SECONDS = 10;

constexpr const char* TIME_REMAINING_MESSAGE = " light is red. Time remaining: ";
constexpr const char* SECOND =  " sec   " ;
constexpr const char* SOURCE_ROAD_NAME_INPUT_MESSAGE = "\nEnter source road name (A/B/C/D): ";
constexpr const char* DESTINATION_ROAD_NAME_INPUT_MESSAGE = "\nEnter destination road name (A/B/C/D): ";
constexpr const char* PASS_BY_ROAD_MESSAGE = " light is red, but left pass is allowed. Vehicle can go to road ";
constexpr const char* RED_LIGHT_MESSAGE =  " light is red. Please wait until it turns green.\n";
constexpr const char* GREEN_LIGHT_MESSAGE =  " light is green  . Vehicle can go to road ";
constexpr const char* ENTER_YOUR_CHOICE_MESSAGE = "Enter your choice: ";
constexpr const char* ENTER_SOURCE_ROAD_NAME_MESSAGE = "Enter source road name: ";
constexpr const char* ENTER_DESTINATION_ROAD_NAME_MESSAGE = "Enter destination road name: ";
constexpr const char* EXIT_PROGRAM_MESSAGE = "Traffic simulation stopped.\n";

constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";
constexpr const char* INVALID_ROAD_NAME_ERROR_MESSAGE = "Invalid road name. Please enter A, B, C or D.\n";
constexpr const char* SAME_ROAD_ERROR_MESSAGE = "Source road and destination road cannot be the same. You are already on road ";
constexpr const char* MAIN_LOOP_INVALID_INPUT_ERROR_MESSAGE = "Invalid choice. Please enter 1 or 2.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* INVALID_INPUT_ROAD_ERROR_MESSAGE = "Invalid source road or destination road.\n";

#endif
