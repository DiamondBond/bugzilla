#include <ctime>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

// Load conio.h if running on DOS
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_)
#define PLATFORM_NAME "windows" // Windows
#include <conio.h>
#elif defined(__APPLE__) || defined(__linux__)
#define PLATFORM_NAME "unix"
#endif

using namespace std;

// Declare Constants
const double VERSION = 0.4;

// Class to define the properties
class bug {
public:
  // Instance variables
  char Name[20];
  char Type[50];
  char Desc[1000];
  int ID;
  int Priority;
  int Status;
  char filename[50];
  char tstamp[1000];
  char last_tstamp[1000];

  // Function to create a bug ticket
  void create_bug();

  // Function to display a bug ticket
  void display_bug();

  // Function to update a bug ticket
  void update_bug();

  // Function to get filename from user
  void get_fname();

  // Function to get filename from user
  char *get_tstamp();

  // Function to print help
  void help();
};

// ****** //
// CREATE
// ****** //
void bug::create_bug() {
  // Object to write in file
  ofstream file_obj;

  // Prompt user for filename and open it
  get_fname();
  file_obj.open(filename, ios::out);

  // Object of class bug to input data in file
  bug obj;

  // Seed Rand()
  srand(time(NULL));

  // Get Bug ID
  obj.ID = rand();

  // Get Bug Timestamp
  char *utcTimestamp;
  utcTimestamp = get_tstamp();

  strcpy(obj.tstamp, utcTimestamp);
  strcpy(obj.last_tstamp, utcTimestamp);

  // Get Bug Name
  cout << "Enter Bug Name: ";
  cin.ignore();
  cin.getline(obj.Name, sizeof(obj.Name));

  // Get Bug Type
  cout << "\nEnter Bug Type: ";
  cin.getline(obj.Type, sizeof(obj.Type));

  // Get Bug Desc
  cout << "\nEnter Bug Description: ";
  cin.getline(obj.Desc, sizeof(obj.Desc));

  // Get Bug Priority
  cout << "\nEnter Bug Priority [0-100]: ";
  cin >> obj.Priority;

  // Get Bug Status
  cout << "\nStatus of bug:\n";
  cout << "1.NOT YET ASSIGNED\n";
  cout << "2.IN PROGRESS\n3.FIXED\n";
  cout << "4.DELIVERED\n > ";
  cin >> obj.Status;

  // Writing the object's data in file
  file_obj.write((char *)&obj, sizeof(obj));

  // Close file
  file_obj.close();

  // Wait for user input
  cout << "\nPress any key to continue..." << endl;
  getch();
  system("cls");
}

// ****** //
// UPDATE
// ****** //
void bug::update_bug() {
  // Object to read from file
  ifstream file_obj;

  // Opening file in input mode
  get_fname();
  file_obj.open(filename, ios::in);
  file_obj.seekg(0, ios::beg);

  // Object of class bug to update data in file
  bug obj;

  // Reading from file into object "obj"
  file_obj.read((char *)&obj, sizeof(obj));

  // Output
  cout << "Bug Information:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Priority: " << obj.Priority << endl;
  cout << "Bug Status: " << obj.Status << endl;
  cout << "\nBug Created: " << obj.tstamp << endl;
  cout << "Last Edited: " << obj.last_tstamp << endl;

  // Close file
  file_obj.close();

  // Wait for user input
  cout << "Press any key to continue..." << endl;
  getch();

  // Object to write in file
  ofstream file_obj_upd;

  // Prompt user for new information
  cout << "\nNew Bug Information:\n" << endl;

  // Opening file
  file_obj_upd.open(filename, ios::out);

  // Get New Bug Name
  cout << "Enter Bug Name: ";
  cin.ignore();
  cin.getline(obj.Name, sizeof(obj.Name));

  // Get New Bug Type
  cout << "\nEnter Bug Type: ";
  cin.getline(obj.Type, sizeof(obj.Type));

  // Get New Bug Desc
  cout << "\nEnter Bug Description: ";
  cin.getline(obj.Desc, sizeof(obj.Desc));

  // Get New Bug Priority
  cout << "\nEnter Bug Priority [0-100]: ";
  cin >> obj.Priority;

  // Get New Bug Status
  cout << "\nStatus of bug:\n";
  cout << "1.NOT YET ASSIGNED\n";
  cout << "2.IN PROGRESS\n3.FIXED\n";
  cout << "4.DELIVERED\n > ";
  cin >> obj.Status;

  // Get Last Edited Timestamp
  char *LastEdit;
  LastEdit = get_tstamp();
  strcpy(obj.last_tstamp, LastEdit);

  // Writing the object's data in file
  file_obj_upd.write((char *)&obj, sizeof(obj));

  // Close file
  file_obj_upd.close();

  // Wait for user input
  cout << "Press any key to continue..." << endl;
  getch();
  system("cls");
}

// ******* //
// DISPLAY
// ******* //
void bug::display_bug() {
  // Object to read from file
  ifstream file_obj;

  // Opening file in input mode
  get_fname();
  file_obj.open(filename, ios::in);
  file_obj.seekg(0, ios::beg);

  // Object of class bug to output data to file
  bug obj;

  // Reading from file into object "obj"
  file_obj.read((char *)&obj, sizeof(obj));

  // Output
  cout << "Bug Information:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Priority: " << obj.Priority << endl;
  cout << "Bug Status: " << obj.Status << endl;
  cout << "\nBug Created: " << obj.tstamp << endl;
  cout << "Last Edited: " << obj.last_tstamp << endl;

  // Close file
  file_obj.close();

  // Wait for user input
  cout << "Press any key to continue..." << endl;
  getch();
  system("cls");
}

// **** //
// MAIN
// **** //
int main() {

  // Create object of the class
  bug object;

  // Create variables for main loop handling
  int i = 1;
  char choice;

  // Main loop
  while (i != 0) {
    // Clear Screen
    system("cls");

    // Print title
    cout << "===== BUGZILLA v" << VERSION << " =====" << endl;

    // Print menu
    cout << "\n[C]reate Bug Report";
    cout << "\n[D]isplay Bug Report";
    cout << "\n[U]pdate Bug Report";
    cout << "\n[H]elp";
    cout << "\n[Q]uit\n";
    cout << "\n > ";

    // Get user choice as input
    cin >> choice;
    choice = toupper(choice);

    // Switch to handle user choice
    switch (choice) {
    case 'C':
      system("cls");
      object.create_bug();
      break;
    case 'U':
      system("cls");
      object.update_bug();
      break;
    case 'D':
      system("cls");
      object.display_bug();
      break;
    case 'H':
      system("cls");
      object.help();
      break;
    case 'Q':
      i = 0;
      break;
    default:
      cout << "\nInvalid entry!" << endl;
      break;
    }
  }

  return 0;
}

// ************ //
// GET FILENAME
// ************ //
void bug::get_fname() {
  system("cls");
  cout << "Bug Report Name: " << endl;
  cout << " > ";
  cin >> filename;
  system("cls");
}

// ************* //
// GET TIMESTAMP
// ************* //
char *bug::get_tstamp() {
  // current date/time based on current system
  time_t now = time(0);

  // convert now to string form
  char *dt = ctime(&now);

  // convert now to tm struct for UTC
  tm *gmtm = gmtime(&now);

  dt = asctime(gmtm);

  return dt;
}

// ********** //
// PRINT HELP
// ********** //
void bug::help() {
  system("cls");

  // Print out help info
  cout << "\nNAME" << endl;
  cout << "\tBUGZILLA - minimal bug tracker.\n" << endl;
  cout << "VERSION" << endl;
  cout << "\tv" << VERSION << "\n" << endl;
  cout << "SYNPOSIS" << endl;
  cout << "\t./bugzilla.exe\n" << endl;
  cout << "DESCRIPTION" << endl;
  cout << "\tBug tracking and management.\n" << endl;
  cout << "FEATURES" << endl;
  cout << "\tCreate Bug Report - file a bug for tracking.\n" << endl;
  cout << "\tUpdate Bug Report - update a bugs tracking information.\n" << endl;
  cout << "\tDisplay Bug Report - generate bug report from a bugs tracking "
          "information.\n"
       << endl;
  cout << "RESOURCES" << endl;
  cout << "\tHomepage: https://github.com/diamondbond/bugzilla\n" << endl;
  cout << "SEE ALSO" << endl;
  cout << "\tOfficial BugZilla: https://www.bugzilla.org" << endl;

  // Wait for user input
  cout << "\nPress any key to continue..." << endl;
  getch();
  system("cls");
}
