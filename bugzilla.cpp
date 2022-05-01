// Bugzilla
// Licensed under the MIT License
// Copyright (c) 2022 Diamond Bond <diamondbond1@gmail.com>
// Author: Diamond Bond <diamondbond1@gmail.com>
// URL: https://github.com/diamondbond/bugzilla

#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

using namespace std;

// Version
const string VERSION = "0.7.5";

// Function prototypes for NT/POSIX portability
void clear_screen();
void pause_screen();

// Bug Class
class bug {
public:
  // Instance variables
  char Name[20];
  char Type[50];
  char Desc[1000];
  int ID;
  int Priority;
  int Status;

  // Meta variables
  char filename[50];
  char tstamp[1000];
  char last_tstamp[1000];

  // Function to create a bug report
  void create_bug();

  // Function to display a bug report
  void display_bug();

  // Function to list bug reports
  void list_bug();

  // Function to update a bug report
  void update_bug();

  // Function to delete a bug report
  void delete_bug();

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

  // Give Bug ID a random number
  obj.ID = rand();

  // Get Bug Timestamp
  char *utcTimestamp;
  utcTimestamp = get_tstamp();

  // Populate Created & Last Edited with Timestamp
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
  pause_screen();
  clear_screen();
}

// ****** //
// UPDATE
// ****** //
void bug::update_bug() {
  // Object to read from file
  ifstream file_obj;

  // Get filename from user
  get_fname();

  // Opening file in input mode
  file_obj.open(filename, ios::in);
  file_obj.seekg(0, ios::beg);

  // Object of class bug to update data in file
  bug obj;

  // Reading from file into object "obj"
  file_obj.read((char *)&obj, sizeof(obj));

  // Output Bug Report
  cout << "Bug Report:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Priority: " << obj.Priority << endl;
  cout << "Bug Status: " << obj.Status << endl;
  cout << "\nBug Created: " << obj.tstamp << endl;
  cout << "Last Edited: " << obj.last_tstamp << endl;

  // Store Created at Timestamp
  char *createdAt;
  strcpy(createdAt, obj.tstamp);

  // Close the file
  file_obj.close();

  // Wait for user input
  pause_screen();

  // Object to write in file
  ofstream file_obj_upd;

  // Prompt user for new information
  cout << "\nPlease enter the new Bug Report:\n" << endl;

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

  // Copy over Created At Timestamp
  strcpy(obj.tstamp, createdAt);

  // Get Last Edited Timestamp
  char *LastEdit;
  LastEdit = get_tstamp();
  strcpy(obj.last_tstamp, LastEdit);

  // Writing the object's data in file
  file_obj_upd.write((char *)&obj, sizeof(obj));

  // Close file
  file_obj_upd.close();

  // Wait for user input
  pause_screen();
  clear_screen();
}

// ******* //
// DISPLAY
// ******* //
void bug::display_bug() {
  // Object to read from file
  ifstream file_obj;

  // Get filename from user
  get_fname();

  // Opening file in input mode
  file_obj.open(filename, ios::in);
  file_obj.seekg(0, ios::beg);

  // Object of class bug to output data to file
  bug obj;

  // Reading from file into object "obj"
  file_obj.read((char *)&obj, sizeof(obj));

  // Output Bug Report
  cout << "Bug Report:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Priority: " << obj.Priority << endl;
  cout << "Bug Status: " << obj.Status << endl;
  cout << "\nBug Created: " << obj.tstamp << endl;
  cout << "Last Edited: " << obj.last_tstamp << endl;

  // Close the file
  file_obj.close();

  // Wait for user input
  pause_screen();
  // clear_screen();
}

// ******* //
// LIST
// ******* //
void bug::list_bug() {
  // list files & folders in current working directory

  // create struct and pointer to cwd
  struct dirent *d;
  DIR *dr;

  // open cwd
  dr = opendir(".");

  // check if dir exists then loop through files and print
  if (dr != NULL) {
    cout << "List of Files & Folders: \n";
    for (d = readdir(dr); d != NULL; d = readdir(dr)) {
      cout << d->d_name << endl;
    }
    closedir(dr); // close the dir
  } else
    cout << "\nError Occurred!";
  cout << endl;

  pause_screen();
  clear_screen();
}

// ******* //
// DELETE
// ******* //
void bug::delete_bug() {
  // Get filename to delete from user
  get_fname();

  // Confirmation variables
  char confirm;
  int i = 1;

  // Get confirmation from user
  cout << "Are you sure you want to remove '" << filename << "'? [y/n] ";
  while (i != 0) {
    // Get y or n from user and convert to uppercase
    cin >> confirm;
    confirm = toupper(confirm);

    // Switch to handle user confirmation
    switch (confirm) {
    case 'Y':
      remove(filename); // Remove file
      cout << "\nRemoved '" << filename << "' bug report.\n" << endl;
      pause_screen();
      i = 0;
      break;
    case 'N':
      i = 0;
      break;
    default:
      cout << "\nInvalid entry!" << endl;
      i = 0;
      break;
    }
  }

  clear_screen();
}

// **** //
// MAIN
// **** //
int main() {

  // Object of bug class
  bug object;

  // Variables for main loop handling
  int i = 1;
  char choice;

  // Main loop
  while (i != 0) {
    clear_screen();

    // Print title & menu
    cout << "===== BUGZILLA v" << VERSION << " =====";
    cout << "\n|                         |";
    cout << "\n| [C]reate Bug Report     |";
    cout << "\n| [L]ist Bug Reports      |";
    cout << "\n| [D]isplay Bug Report    |";
    cout << "\n| [U]pdate Bug Report     |";
    cout << "\n| [R]emove Bug Report     |";
    cout << "\n| [H]elp                  |";
    cout << "\n| [Q]uit                  |";
    cout << "\n|                         |";
    cout << "\n===========================" << endl;

    cout << "\n > ";

    // Get user input as choice
    cin >> choice;
    choice = toupper(choice);

    // Switch to handle user choice
    switch (choice) {
    case 'C':
      clear_screen();
      object.create_bug();
      break;
    case 'L':
      clear_screen();
      object.list_bug();
      break;
    case 'D':
      clear_screen();
      object.display_bug();
      break;
    case 'U':
      clear_screen();
      object.update_bug();
      break;
    case 'R':
      clear_screen();
      object.delete_bug();
      break;
    case 'H':
      clear_screen();
      object.help();
      break;
    case 'Q':
      clear_screen();
      cout << "Thank you for using Bugzilla." << endl;
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
  clear_screen();

  // Get filename from user input
  cout << "Bug Report Name: " << endl;
  cout << " > ";
  cin >> filename;

  clear_screen();
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

  // convert & assign gmtm to dt
  dt = asctime(gmtm);

  // dt is our final converted & formatted date
  return dt;
}

// ********** //
// PRINT HELP
// ********** //
void bug::help() {
  clear_screen();

  // Print out help info in style of man page
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
  cout << "\tList Bug Reports - lists bug reports in the current working "
          "directory.\n"
       << endl;
  cout << "\tDisplay Bug Report - display a bug report.\n" << endl;
  cout << "\tUpdate Bug Report - update a bug report.\n" << endl;
  cout << "\tRemove Bug Report - deletes a bug report.\n" << endl;
  cout << "RESOURCES" << endl;
  cout << "\tHomepage: https://github.com/diamondbond/bugzilla\n" << endl;
  cout << "SEE ALSO" << endl;
  cout << "\tOfficial BugZilla: https://www.bugzilla.org" << endl;

  // Wait for user input
  pause_screen();
  clear_screen();
}

// Platform agnostic clear screen function
void clear_screen() {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#endif
}

// Platform agnostic pause screen function
void pause_screen() {
#ifdef _WIN32
  system("PAUSE");
#elif __linux__
  system("sleep 3"); // Note: on POSIX this will just wait for 3 seconds then
                     // continue unlike on NT where it will actually wait for a
                     // char from the user before continuing.
#endif
}
