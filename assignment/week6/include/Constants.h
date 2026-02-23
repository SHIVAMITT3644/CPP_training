#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

constexpr const char* MAIN_MENU_BODY = R"(
Welcome to Parser Program
============================
1. Parse Json File(.json extension)
2. Parse Csv File(.csv extension)
3. Parse Xml File(.xml extension)
4. Exit
============================
)";

constexpr const char* PARSER_CONTINUE_EXIT_MENU = R"(
============================
1. Enter File Name
2. Exit
============================
)";

constexpr const char* RESOURCE_FOLDER_CONSTANT = "resources/";
constexpr const char* JSON = "JSON";
constexpr const char* CSV = "CSV";
constexpr const char* XML = "XML";


constexpr const char* ENTER_CHOICE_PROMPT = "\nPlease enter your choice: ";
constexpr const char* CONTINUE_PROGRAM_MESSAGE = "\nEnter 1 to continue and Enter 0 to exit the program : ";
constexpr const char*  EXIT_PROGRAM_MESSAGE = "Thank you for using the Parser Program\n";

constexpr const char* FILENAME_INPUT_MESSAGE =  "Enter Your File Name: ";
constexpr const char* FILE_PARSED_MESSAGE = "\nFile Successfully Parsed.\n";
constexpr const char* EXITING_MESSAGE = "Exiting ..";

constexpr const char* OPERATION_SUCCESS_MESSAGE =  " Parser Operation Completed Successfully.\n";
constexpr const char* OPERATION_CANCELLED_MESSAGE = " Parser Operation Cancelled.\n";
constexpr const char* OPERATION_FAILED_MESSAGE = "Parser Operation Completed With Errors.\n";

constexpr const char* JSON_DATA_TEMPLATE = "\n=========== JSON DATA ===========\n\n";
constexpr const char* JSON_FILE_NOT_OPEN_MESSAGE = "Error: Unable to open JSON file.\n";
constexpr const char* JSON_EMPTY_ERROR_MESSAGE = "Error: JSON file is empty.\n";
constexpr const char* JSON_ERROR_DISPLAYING_MESSAGE = "Error: Unable to display JSON data due to an internal JSON processing issue.\n";
constexpr const char* JSON_PARSING_ERROR_MESSAGE = "\n---------------------------------Error: Invalid JSON format. Please check file syntax.\n\n";

constexpr const char* JSON_EXCEPTION_MESSAGE = "Error: A JSON processing error occurred. Please verify the JSON structure and values.\n";
constexpr const char* STANDARD_EXCEPTION_MESSAGE = "Error: An unexpected system error occurred during execution.\n";
constexpr const char* UNKNOWN_ERROR_MESSAGE = "Unknown error occurred.\n";

constexpr const char* CSV_DATA_TEMPLATE = "\n=========== CSV DATA ===========\n\n";
constexpr const char* CSV_FILE_NOT_OPEN_MESSAGE = "Error: Unable to open CSV file.\n";
constexpr const char* CSV_EMPTY_ERROR_MESSAGE = "Error: An unexpected error occurred while displaying the CSV file.\n";
constexpr const char* CSV_ERROR_DISPLAYING_MESSAGE = "\nError: Unable to display CSV content due to incompatible column length.\n";
constexpr const char* CSV_PARSING_ERROR_MESSAGE = "\n---------------------------------\nError: Failed to parse CSV file. The file may be corrupted or improperly formatted.\n\n";


constexpr const char* XML_DATA_TEMPLATE = "\n=========== XML DATA ===========\n\n";
constexpr const char* XML_EMPTY_ERROR_MESSAGE = "Error: XML file is empty or missing a root element.\n";
constexpr const char* XML_ERROR_DISPLAYING_MESSAGE = "Error: An unexpected error occurred while displaying the XML content.\n";
constexpr const char* XML_PARSING_ERROR_MESSAGE = "Error: Failed to parse XML file. The file may be invalid or corrupted.\n";

constexpr const char* CSV_UNKNOWN_ERROR_MESSAGE = "Unknown error occurred while parsing CSV.\n";
constexpr const char* INVALID_FILE_EXTENSION_ERROR =  "Invalid file extension!\n";
constexpr const char* FILE_NOT_FOUND_ERROR_MESSSAGE = "File not found in resources folder!\n";
constexpr const char* FILE_PARSED_FAILED_MESSAGE = "Error while displaying parsed data.\n";

constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* TECHNICAL_ERROR_MESSAGE = "\nSomething went wrong. Please try again.\n";
constexpr const char* FATAL_ERROR_MESSAGE = "\nInput stream closed. Exiting program...\n";
constexpr const char* FORMATING_MESSAGE = "\n=================================\n";
#endif
