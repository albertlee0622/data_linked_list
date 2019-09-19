/*
header1.h
Programmer: Albert Lee
Date: March 12, 2019
Description: This program prompts the user to enter passenger information
			 stores, and displays the data entered by the user.
Visual Studio Community 2017
Version: 2.1
*/

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <iostream>
#include <cstring> //strlen
#include <cstdlib> //exit 
#include <iomanip> //setw 

using namespace std;

const short PASS_MAX = 10;
const short INPUT_MAX = 30;

class PassData
{
	//This class has initial_prompt() method that can be called from outside the class 
	//to display the main menu for the user; initial_prompt method then prompts the user
	//to enter a selection from the menu in order to add data, display the stored data, 
	//insert data in the middle of the list, remove data, or quit the program.
public:
	PassData();
	//This default constructor initializes data members
	void initial_prompt();

private:
	struct PassInfo
	{
		//This structure stores the maximum of 10 passengers' names; 
		//flight numbers; and bording priorities.
		char      FName[INPUT_MAX];
		char      LName[INPUT_MAX];
		char      FltNum[INPUT_MAX];
		char	  Priority;
		short	  pass_num;
		PassInfo* next;
	};

	typedef PassInfo* InfoPtr;

	InfoPtr head;
	bool	error_input;
	short	count;

	void	append_node();
	//Pre-condition: the user enters 'E' or 'e' from the main menu 
	//Post-condition: it prompts the user to enter the maximum of 10 passengers' names; 
	//				  flight numbers; and boarding priorities and stores the data. 
	//				  it doesn't return any values	
	void	display_list();
	//Pre-condition: the user enters 'D' or 'd' from the main menu
	//Post-condition: it displays the passengers' information entered by the user.
	//				  it doesn't return any values
	void	insert_node();
	//Pre-condition: the user enters 'I' or 'i' from the main menu
	//Post-condition: it prompts the user to enter a pass# to insert a new passenger;
	//				  store the new passenger inforamtion; and re-arrange the the list.
	//				  it doesn't return any values
	void	remove_node();
	//Pre-condition: the user enters 'R' or 'r' from the main menu
	//Post-condition: it prompts the user to enter a pass# to delete the passenger from
	//				  the list; delete the data; and re-arrange the list.
	//				  it doesn't return any values
	void	get_input(InfoPtr& nodeptr);
	//Pre-condition: append_node and insert_node methods call this method,
	//				 and a parameter of the type InfoPtr is passed by reference 
	//Post-condition: it asks the user to enter first name, last name, flight number,
	//				  and boarding priority; check inputs; and store the data.
	//				  it doesn't return any values
	void	check_input(char arr_par[]);
	//Pre-condition: get_input method calls this method, and an array of type char is
	//				 passed as a parameter
	//Post-condition: it checks inputs read by cin.getline. if an error is detected,
	//				  it sets the array to null and prompts the user for a valid input	
	//				  it doesn't return any values
};

#endif 
