// Bugzilla
// Licensed under the MIT License
// Copyright (c) 2022 Diamond Bond <diamondbond1@gmail.com>
// Author: Diamond Bond <diamondbond1@gmail.com>
// URL: https://github.com/diamondbond/bugzilla

#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>

using namespace std;

// Version
const string VERSION = "1.3";

// Function prototypes for NT/POSIX portability
void clear_screen();
void pause_screen();

// Bug Class
class bug {
  // Instance variables
  int ID;
  char Name[20];
  char Type[50];
  char Desc[1000];
  char Status;

  // Meta variables
  char filename[50];
  char tstamp[26];
  char last_tstamp[26];

public:
  void create_bug();
  void display_bug();
  void list_bug();
  void update_bug();
  void delete_bug();
  void get_fname();
  char *get_tstamp();
  void help();
};

// ****** //
// CREATE
// ****** //
void bug::create_bug() {
  // Object to write in file
  ofstream file_obj;

  // Prompt user for filename
  get_fname();

  // Open file
  file_obj.open(filename, ios::out);

  // Seed Rand()
  srand(time(NULL));

  // Object of class bug to input data in file
  bug obj;

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
  cin.getline(obj.Name, 20);

  // Get Bug Type
  cout << "\nEnter Bug Type: ";
  cin.getline(obj.Type, 50);

  // Get Bug Desc
  cout << "\nEnter Bug Description: ";
  cin.getline(obj.Desc, 1000);

  // Get Bug Status
  cout << "\nStatus of bug:\n";
  cout << "[N]: NOT YET ASSIGNED\n";
  cout << "[P]: IN PROGRESS\n[F]: FIXED\n";
  cout << "[D]: DELIVERED\n > ";
  cin >> obj.Status;
  obj.Status = toupper(obj.Status);

  // Writing the object's data in file
  file_obj.write(reinterpret_cast<char *>(&obj), sizeof(obj));

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
  // List out bug report files first
  list_bug();

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
  file_obj.read(reinterpret_cast<char *>(&obj), sizeof(obj));

  // Convert Char Status to String CurrStatus
  string currStatus;
  switch (obj.Status) {
  case 'N':
    currStatus = "NOT YET ASSIGNED";
    break;
  case 'P':
    currStatus = "IN PROGRESS";
    break;
  case 'F':
    currStatus = "FIXED";
    break;
  case 'D':
    currStatus = "DELIVERED";
    break;
  default:
    currStatus = "ERROR";
    break;
  }

  // Output Bug Report
  cout << "Original Bug Report:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Status: " << currStatus << endl;
  cout << "\nBug Created: " << obj.tstamp << endl;
  cout << "Last Edited: " << obj.last_tstamp << endl;

  // Close the file
  file_obj.close();

  // Wait for user input
  pause_screen();

  // Object to write in file
  ofstream file_obj_upd;

  // Prompt user for new information
  cout << "\nPlease enter the updated Bug Report Information:\n" << endl;

  // Opening file
  file_obj_upd.open(filename, ios::out);

  // Get New Bug Name
  cout << "Enter New Bug Name: ";
  cin.ignore();
  cin.getline(obj.Name, 20);

  // Get New Bug Type
  cout << "\nEnter New Bug Type: ";
  cin.getline(obj.Type, 50);

  // Get New Bug Desc
  cout << "\nEnter New Bug Description: ";
  cin.getline(obj.Desc, 1000);

  // Get New Bug Status
  cout << "\nNew Status of bug:\n";
  cout << "[N]: NOT YET ASSIGNED\n";
  cout << "[P]: IN PROGRESS\n[F]: FIXED\n";
  cout << "[D]: DELIVERED\n > ";
  cin >> obj.Status;
  obj.Status = toupper(obj.Status);

  // Get Last Edited Timestamp
  char *LastEdit;
  LastEdit = get_tstamp();
  strcpy(obj.last_tstamp, LastEdit);

  // Writing the object's data in file
  file_obj_upd.write(reinterpret_cast<char *>(&obj), sizeof(obj));

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
  // List out bug report files first
  list_bug();

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
  file_obj.read(reinterpret_cast<char *>(&obj), sizeof(obj));

  // Convert Char Status to String CurrStatus
  string currStatus;
  switch (obj.Status) {
  case 'N':
    currStatus = "NOT YET ASSIGNED";
    break;
  case 'P':
    currStatus = "IN PROGRESS";
    break;
  case 'F':
    currStatus = "FIXED";
    break;
  case 'D':
    currStatus = "DELIVERED";
    break;
  default:
    currStatus = "ERROR";
    break;
  }

  // Output Bug Report
  cout << "Bug Report:\n" << endl;
  cout << "Bug ID: " << obj.ID << endl;
  cout << "Bug Name: " << obj.Name << endl;
  cout << "Bug Type: " << obj.Type << endl;
  cout << "Bug Desc: " << obj.Desc << endl;
  cout << "Bug Status: " << currStatus << endl;
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
  // List out bug report files first
  list_bug();

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
      // Remove file
      if (remove(filename) != 0) {
        cout << "Error deleting '" << filename << "'." << endl;
      } else {
        cout << "\nRemoved '" << filename << "' bug report file.\n" << endl;
      }
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
    cout << "====== BUGZILLA v" << VERSION << " ======";
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
  cout << "Bug Report Filename: " << endl;
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
  cout << "DESCRIPTION" << endl;
  cout << "\tBug & Ticket tracking." << endl;
  cout << "\tCreate, list, view, update and delete bug reports.\n" << endl;
  cout << "RESOURCES" << endl;
  cout << "\tHomepage: https://github.com/diamondbond/bugzilla\n" << endl;
  cout << "NOTES" << endl;
  cout << "\tAll input in this program is case-insensitive.\n" << endl;
  cout << "SEE ALSO" << endl;
  cout << "\tOfficial BugZilla: https://www.bugzilla.org\n" << endl;

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
  cout << endl << "Press <Enter> to continue...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
#endif
}
