/*************************************************
* Tester<Class_name>
* The top-level testing class.  Each derived
* class inherits the routines:
*
*    int run()
*
* For a derived class to function, it must
* override the void process() member function.
* The process function should read in a line from
* the input file and tests the routine based on
* those instructions.
*
* The member variables are:
*
*   Class_name *object   A pointer to the object
*                       being tested.
*
*   string command      The string read in from
*                       the input file indicating
*                       the next command to be
*                       tested.
*
*   int count           The number of the current
*                       test being run.
*
* The member functions are:
*
*   int run()           Start a test run testing until
*                       the end of the file, one test
*                       per line.
*   void process()      Process and run an individual
*                       test.
*
*
* DO NOT EDIT THIS FILE
*************************************************/

#ifndef TESTER_H
#define TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <string>
#include <sstream>

#include "ECE2552.h"

template <class Class_name>
class Tester {
protected:
	Class_name *object;
	std::string command;

public:
	Tester(Class_name *obj = nullptr) :
		object(obj) {
		// emtpy constructor
	}

	int run();
	virtual void process() = 0;
};

/****************************************************
* int run()
*
* Indefinite run of test cases: continue reading console
* input until the end of the file.
****************************************************/

template <class Class_name>
int Tester<Class_name>::run() {
	// read the flag which indicates the command to be test and
	// stop if we have reached the end of the file

	ECE2552::allocation_table.stop_recording();

	const static std::string prompt = " % ";

	while (true) {
		// terminate if there is an end-of-file or the user types 'exit'

		if (std::cin.eof()) {
			break;
		}

		++ECE2552::count;
		std::cout << ECE2552::count << prompt;

		std::cin >> command;

		// Remove any comments
		if (command.substr(0, 2) == "//") {
			char comment[1024];
			std::cin.getline(comment, 1024);

			std::cout << command << comment << std::endl;
			continue;
		}

		// terminate if there is an end-of-file or the user types 'exit'

		if (std::cin.eof()) {
			std::cout << "Exiting..." << std::endl;
			break;
		}

		// If the user enters !!,
		//    set the command to be the last command
		// If the user enters !n where n is a number,  (1 <= n < count)
		//    set the command ot be the nth command

		if (command == "!!") {
			if (ECE2552::count == 1) {
				std::cout << "Event not found" << std::endl;
				continue;
			}

			command = ECE2552::history[ECE2552::count - 1];
		}
		else if (command[0] == '!') {
			int n;
			std::istringstream number(command.substr(1, command.length() - 1));
			number >> n;

			if (n <= 0 || n >= ECE2552::count || n >= 1000) {
				std::cout << "Event not found" << std::endl;
				continue;
			}

			command = ECE2552::history[n];
		}

		// only track the first 1001 commands
		if (ECE2552::count < 1000) {
			ECE2552::history[ECE2552::count] = command;
		}

		// start tracking any memory allocations made
		ECE2552::allocation_table.start_recording();

		// There are five key commands

		if (command == "exit") {
			std::cout << "Okay" << std::endl;
			ECE2552::allocation_table.stop_recording();
			break;
		}
		else if (command == "delete") {
			delete object;
			object = nullptr;
			std::cout << "Okay" << std::endl;
		}
		else if (command == "summary") {
			ECE2552::allocation_table.summary();
		}
		else if (command == "details") {
			ECE2552::allocation_table.details();
		}
		else if (command == "memory") {
			int n;

			std::cin >> n;

			if (n == ECE2552::allocation_table.memory_alloc()) {
				std::cout << "Okay" << std::endl;
			}
			else {
				std::cout << "Failure in memory allocation: expecting "
					<< n << " bytes to be allocated, but "
					<< ECE2552::allocation_table.memory_alloc()
					<< " bytes were allocated" << std::endl;
			}
		}
		else if (command == "memory_store") {
			ECE2552::allocation_table.memory_store();
			std::cout << "Okay" << std::endl;
		}
		else if (command == "memory_change") {
			int n;

			std::cin >> n;

			ECE2552::allocation_table.memory_change(n);
		}
		else {
			process();
		}

		// stop tracking any memory allocations made
		ECE2552::allocation_table.stop_recording();
	}

	return 0;
}
#endif