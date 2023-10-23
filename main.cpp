//
//  Project - DNA Profiling:
//  Writing a menu system to build DNA strands using STRs and ourvector:
// - load_db: Read data from text file & save it in appropriate containers
// - load_dna: Read data from dna file & save it
// - process: Count the longest consecutive sequence of repeated STRS for DNA
// - display: Display the database, the dna, and STR count on the screen
// - search: Determine who the DNA matches to in a database
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ourvector.h"

using namespace std;

struct Profile {
    string name;
    ourvector<int> number;
};


// // Function prototypes
int main();
void load_strs(string first_line, ourvector<ourvector<char>>& all_strs);
void load_people(string rest_lines, ourvector<Profile> &people);
void load_db(ifstream &readFile,
ourvector<ourvector<char>>& all_strs, ourvector<Profile> &people);
void load_database_function(string& filename, ifstream& readFile,
ourvector<ourvector<char>>& all_strs, ourvector<Profile>& people,
bool& loadedDB_before, bool& database_loaded);

void load_dna(ourvector<char> &dna, bool &dna_loaded);
void load_dna_function(ourvector<char>& dna,
bool& loadedDNA_before, bool& dna_loaded);

void display_dna_2(ourvector<ourvector<char>>& all_strs,
bool dna_processed, ourvector<char>& dna, ourvector<int>& str_count);
void display_dna(ourvector<ourvector<char>> &all_strs,
ourvector<Profile> &people, bool dna_loaded, bool dna_processed,
ourvector<char> &dna, ourvector<int> &str_count);
void display(ourvector<ourvector<char>> &all_strs,
ourvector<Profile> &people, bool dna_loaded, bool dna_processed,
bool database_loaded, ourvector<char> &dna, ourvector<int> &str_count);
void print_statements();

bool match(ourvector<char> &str, ourvector<char> &dna, int i);
int processOneSTR(ourvector<char> &str, ourvector<char> &dna);
void process(ourvector<ourvector<char>> &all_strs, ourvector<char> &dna,
ourvector<int> &str_count);
void process_function(ourvector<ourvector<char>> &all_strs,
ourvector<Profile> &people, bool dna_loaded, bool &dna_processed,
bool database_loaded, ourvector<char> &dna, ourvector<int> &str_count);

bool check_restSTRs(ourvector<Profile> &people, ourvector<int> &str_count,
int i);
void searching_dna(ourvector<Profile> &people, ourvector<int> &str_count);
void search(ourvector<Profile> &people, bool dna_loaded,
bool dna_processed, bool database_loaded, ourvector<int> &str_count);

void creative_function(ourvector<Profile>& people, bool database_loaded);
bool STR_match(ourvector<Profile>& people, int length_of_vector,
int& userinput, int i, int& check);
void search_currentDB(ourvector<Profile>& people, int length_of_vector);

void complicated_commands(string command,
ourvector<ourvector<char>> &all_strs, ourvector<Profile> &people,
bool dna_loaded, bool &dna_processed, bool database_loaded,
ourvector<char> &dna, ourvector<int> &str_count);
void coutStatements(string command, string& filename, ifstream& readFile,
ourvector<ourvector<char>>& all_strs, ourvector<Profile>& people,
ourvector<char>& dna, bool& loadedDB_before, bool& loadedDNA_before,
ourvector<int>& str_count);

// MILESTONE 1

// load_strs - loads all the STRs from the text file into appropriate container

void load_strs(string first_line, ourvector<ourvector<char>> &all_strs) {
    stringstream parser(first_line);
    string name;
    string value;
    getline(parser, name, ',');

    while (getline(parser, value, ',')) {  // get STRs one by one
        ourvector<char> str;

        for (char c : value) {
            str.push_back(c);
        }

        all_strs.push_back(str);
    }
}


// load_people - it loads all names and their respective STR counts from file

void load_people(string rest_lines, ourvector<Profile> &people) {
    stringstream parser(rest_lines);
    string person_name, value;

    Profile new_person;

    getline(parser, person_name, ',');
    new_person.name = person_name;

    while (getline(parser, value, ',')) {
        int integer_val = stoi(value);  // converting type to store in struct
        new_person.number.push_back(integer_val);
    }

    people.push_back(new_person);
}


// load_db - loading database function

void load_db(ifstream &readFile,
             ourvector<ourvector<char>> &all_strs, ourvector<Profile> &people) {
    string first_line;
    string rest_lines;
    readFile >> first_line;
    load_strs(first_line, all_strs);

    while (!readFile.eof()) {
        readFile >> rest_lines;
        load_people(rest_lines, people);
    }
}

void load_database_function(string& filename,
ifstream& readFile, ourvector<ourvector<char>>& all_strs,
ourvector<Profile>& people, bool& loadedDB_before, bool& database_loaded) {
  if (loadedDB_before == true) {  // checks if database is loaded before
                all_strs.clear();  // clears the vectors if true
                people.clear();
            }
            cout << "Loading database..." << endl;
            cin >> filename;
            readFile.open(filename);
            if (!readFile.is_open()) {
                cout << "Error: unable to open '" << filename << "'" << endl;
            } else {
                database_loaded = true;
                load_db(readFile, all_strs, people);
                loadedDB_before = true;
            }
            readFile.close();
}


// MILESTONE 2

// display_dna_2 - function supporting displaying dna stands

void display_dna_2(ourvector<ourvector<char>> &all_strs,
                   bool dna_processed, ourvector<char> &
                   dna, ourvector<int> &str_count) {
    cout << endl;
    cout << "DNA loaded: " << endl;

    for (int i = 0; i < dna.size() - 1; i++) {
        cout << dna[i];
    }
    cout << endl;
    cout << endl;
    if (dna_processed == false) {  // only works if dna is processed prior
        cout << "No DNA has been processed." << endl;
    } else {
        cout << "DNA processed, STR counts: " << endl;
        int k = 0;
        for (int i = 0; i < all_strs.size(); i++) {
            for (int j = 0; j < all_strs[i].size(); j++) {
                cout << all_strs[i][j];
            }
            cout << ": ";
            cout << str_count[k] << endl;
            k++;
        }
        cout << endl;
    }
}


// display_dna - function supporting displaying dna stands

void display_dna(ourvector<ourvector<char>> &all_strs,
                 ourvector<Profile> &people,
                 bool dna_loaded, bool dna_processed,
                 ourvector<char> &dna, ourvector<int> &str_count) {
    if (dna_loaded == false) {  // works only if dna is loaded and processed
        cout << endl;
        cout << "No DNA loaded." << endl;
        cout << endl;

        if (dna_processed == false) {
            cout << "No DNA has been processed." << endl;
        }
    } else {
        display_dna_2(all_strs, dna_processed, dna, str_count);
    }
}


// display - display command, that displays loaded database, dna & process

void display(ourvector<ourvector<char>> &all_strs,
             ourvector<Profile> &people,
             bool dna_loaded, bool dna_processed, bool database_loaded,
             ourvector<char> &dna, ourvector<int> &str_count) {
    if (database_loaded == true) {
        cout << "Database loaded: " << endl;

        for (int i = 0; i < people.size() - 1; i++) {
            cout << people[i].name << " ";
            // checks all str counts
            for (int t = 0; t < people[i].number.size(); t++) {
              //  going through struct of vector
                cout << people[i].number[t];
                // size()-1 because it always goes one ahead than necessary
                if (t == (people[i].number.size() - 1)) {
                    break;
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    display_dna(all_strs, people, dna_loaded, dna_processed, dna, str_count);
}


// MILESTONE 3

// load_dna - command to load dna

// load_dna - function to load dna
void load_dna(ourvector<char> &dna, bool &dna_loaded) {
    string dna_file;
    cin >> dna_file;
    // variable to store file data in order to push back later
    char storing_dna;
    ifstream infile;
    infile.open(dna_file);
    if (!infile.is_open()) {
        cout << "Error: unable to open '" << dna_file << "'" << endl;
    } else {
        dna_loaded = true;
        while (!infile.eof()) {
            infile >> storing_dna;
            dna.push_back(storing_dna);
        }
    }
}


// load_dna_function - 	reads dna file and saves data in appropriate containers

void load_dna_function(ourvector<char>& dna,
bool& loadedDNA_before, bool& dna_loaded) {
  if (loadedDNA_before == true) {
                dna.clear();
            }
            cout << "Loading DNA..." << endl;
            load_dna(dna, dna_loaded);
            loadedDNA_before = true;
}


// MILESTONE 4

// match - checks if strs in file loaded match dna from another file

bool match(ourvector<char> &str, ourvector<char> &dna, int i) {
    for (char c : str) {
        if (i >= dna.size()) {
            return false;
        }
        if (c != dna[i]) {
            return false;
        }
        i++;
    }
    return true;
}


// processOneSTR - function supporting process command - check the STR passed

int processOneSTR(ourvector<char> &str, ourvector<char> &dna) {
    int count = 0;  // count = amount of times it's repeated
    int longest = 0;  // longest sequence length
    for (int i = 0; i < dna.size(); i++) {
        if (dna[i] == str[0]) {
          // check if dna of that index matches str
          if (match(str, dna, i) == true) {
            count++;
            if (i == dna.size() - str.size() ) {  // edge case - if at the end
              if (longest < count) {
                longest = count;
              }
            }
            i = i + (str.size() - 1);
          }
        } else {
          if (longest < count) {
            longest = count;
          }
          count = 0;
        }
    }
    return longest;
}


// process - loops through all str sequences pass 1 to check with dna sequence

void process(ourvector<ourvector<char>> &all_strs,
             ourvector<char> &dna, ourvector<int> &str_count) {
    int count;

    for (int i = 0; i < all_strs.size(); i++) {  // looping vector of vector
        count = processOneSTR(all_strs[i], dna);
        str_count.push_back(count);
    }
}


// process_function - find the longest consecutive sequence of repeated STRs

void process_function(ourvector<ourvector<char>> &all_strs,
                      ourvector<Profile> &people, bool dna_loaded,
                      bool &dna_processed, bool database_loaded,
                      ourvector<char> &dna, ourvector<int> &str_count) {
    if (database_loaded == false) {
        cout << "No database loaded." << endl;
    } else {
        if (dna_loaded == false) {
            cout << "No DNA loaded." << endl;
        } else {
            cout << "Processing DNA..." << endl;
            process(all_strs, dna, str_count);
            dna_processed = true;
        }
    }
}


// MILESTONE 5

// check_restSTRs - function supporting search command
// similar to match function of process - - if first match, check rest strs

bool check_restSTRs(ourvector<Profile> &people,
ourvector<int> &str_count, int i) {
    bool found = false;

    for (int j = 0; j < str_count.size(); j++) {
        if (str_count[j] == people[i].number[j]) {
            found = true;
        } else {
            return false;
        }
    }
    return found;
}


// searching_dna - to loop through loaded data base and search if dna matches

void searching_dna(ourvector<Profile> &people, ourvector<int> &str_count) {
    bool found;
    for (int i = 0; i < people.size(); i++) {
        if (people[i].number[0] == str_count[0]) {
            found = check_restSTRs(people, str_count, i);
            if (found == true) {
                cout << "Found in database!  DNA matches: ";
                cout << people[i].name << endl;
                return;
            }
        }
    }
    cout << "Not found in database." << endl;
}


// search - command to determine who the DNA matches to in a database

void search(ourvector<Profile> &people,
            bool dna_loaded, bool dna_processed, bool database_loaded,
            ourvector<int> &str_count) {
    // doesn't search if data base isn't loaded
    if (database_loaded == false) {
        cout << "No database loaded." << endl;
    } else {
        if (dna_loaded == false) {  // doesn't go through if dna isn't loaded
            cout << "No DNA loaded." << endl;
        } else {
            if (dna_processed == false) {  // if dna not processed
                cout << "No DNA processed." << endl;
            } else {
                cout << "Searching database..." << endl;
                searching_dna(people, str_count);
            }
        }
    }
}


// MILESTONE 6

// Creative component
// STR_match - check if str matches guesses

bool STR_match(ourvector<Profile>& people, int length_of_vector, int& userinput,
int i, int& check) {
    for (int k : people[i].number) {  // goes through each element in number
      if (check >= length_of_vector) {
          return false;
      }
      if (k != userinput) {
          return false;
      }
      check++;
      k++;
      if (check != length_of_vector) {
        cout << "Enter an STR count: ";
        cin >> userinput;
      }
    }
    return true;
}

void search_currentDB(ourvector<Profile>& people, int length_of_vector) {
  cout << "You should guess " << length_of_vector << " sequences." << endl;
  int userinput;
  int check = 0;
  bool found_match;
  cout << "Enter an STR count: ";
  cin >> userinput;
  for (int i = 0; i < people.size(); i++) {
    if (userinput == people[i].number[0]) {
      found_match = STR_match(people, length_of_vector, userinput, i, check);
      if (found_match == true) {
        cout << "Found match! STRs count match: " << people[i].name << endl;
        return;
      }
    }
  }
  if (found_match == false) {
    while (check != length_of_vector-1) {
    // even if the user guesses the first input incorrect,
    // they still have to continue guessing till its = the amount of STR sequences
      cout << "Enter an STR count: ";
      cin >> userinput;
      check++;
    }
    cout << "No match found!" << endl;
  }
}


void creative_function (ourvector<Profile>& people, bool database_loaded) {
      if (database_loaded == false) {
        cout << "No database loaded." << endl;
      } else {
        int length_of_vector;
        length_of_vector = people[0].number.size();
        search_currentDB(people, length_of_vector);
      }
}


// MAIN FUNCTIONS

// print_statements - statements if database and dna hasn't loaded

void print_statements() {
    cout << "No database loaded." << endl;
    cout << "No DNA loaded." << endl;
    cout << endl;
    cout << "No DNA has been processed." << endl;
}


// complicated_commands - include commands for display, process and search

void complicated_commands(string command, ourvector<ourvector<char>> &all_strs,
ourvector<Profile> &people,
bool dna_loaded, bool &dna_processed, bool database_loaded,
ourvector<char> &dna, ourvector<int> &str_count) {

    if (command == "display") {
        if (dna_loaded == false) {
            if (database_loaded == false) {
                print_statements();
            } else {
                display(all_strs, people, dna_loaded, dna_processed, database_loaded,
                dna, str_count);
            }
        } else {
            if (database_loaded == false) {
                cout << "No database loaded.";
            }
            display(all_strs, people, dna_loaded, dna_processed, database_loaded,
            dna, str_count);
        }
    }

    else if (command == "process") {
        if (dna_processed == true) {  // dna been processed before? if so, clear vector
            str_count.clear();
        }
        process_function(all_strs, people, dna_loaded, dna_processed,
        database_loaded, dna, str_count);
    } else {
        search(people, dna_loaded, dna_processed, database_loaded, str_count);
    }
}


// // main loop that interacts with user
void coutStatements (string command, string& filename,
ifstream& readFile, ourvector<ourvector<char>>& all_strs,
ourvector<Profile>& people, ourvector<char>& dna,
bool& loadedDB_before, bool& loadedDNA_before, ourvector<int>& str_count) {
    bool dna_loaded = false; bool dna_processed = false;
    bool database_loaded = false;  // booleans - have they been used before?

    while (command != "#") {
        if (command == "load_db") {
          load_database_function(filename, readFile, all_strs,
          people, loadedDB_before, database_loaded);
        }
        else if (command == "load_dna") {
          load_dna_function(dna, loadedDNA_before, dna_loaded);
        }
        else if (command == "display" || command == "process" || command == "search") {
          complicated_commands(command, all_strs, people, dna_loaded,
          dna_processed, database_loaded, dna, str_count);
        }
        else if (command == "guess") {  // creative function
          creative_function (people, database_loaded);
        }
        cout << "Enter command or # to exit: ";
        cin >> command;
    }
}


// Creative component functions:
  // command = "guess"
  // functions required before this function: "load_db"
  // This function allows the user to input the amount of strs required
  // Their guesses is then compared to the actual STR counts per person
  // If the str counts matches, then the name of the person is displayed
  //
  // example: if small.txt file is loaded,
  //          "You should guess 3 sequences."
  //          user inputs: 2 8 3
  //          "Found match! STRs count match: Alice"

int main() {
    cout << "Welcome to the DNA Profiling Application." << endl;

    // first command
    string command;
    string filename;
    cout << "Enter command or # to exit: ";
    cin >> command;

    ifstream readFile;

    // data structures for storing STRs
    ourvector<ourvector<char>> all_strs;

    // loading people and their str counts
    ourvector<Profile> people;
    ourvector<char> dna;
    ourvector<int> str_count;

    // boolean functions to see if database/dna has been loaded before
    bool loadedDB_before = false;   
    bool loadedDNA_before = false;

    coutStatements(command, filename, readFile, all_strs, people, dna,
    loadedDB_before, loadedDNA_before, str_count);

    return 0;
}