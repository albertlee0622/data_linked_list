/*
psdata.cpp
Programmer: Albert Lee
Date: March 12, 2019
Description: This program prompts the user to enter passenger information
			 stores, and displays the data entered by the user.
Visual Studio Community 2017
Version: 2.1
*/
#include "header1.h"

int main()
{
	PassData customer_data;

	customer_data.initial_prompt();

	return 0;
}

PassData::PassData()
{
	head = nullptr;
	error_input = false;
	count = 0;
}

void PassData::initial_prompt()
{
	char temp_ans1 = '\0';

	do
	{
		system("CLS");

		cout << "******************************************************\n";
		cout << "*                      Main Menu                     *\n";
		cout << "******************************************************\n";
		cout << "* [E]nter the passenger information                  *\n";
		cout << "* [D]isplay the passenger information                *\n";
		cout << "* [I]nsert a new passenger in the middle of the list *\n";
		cout << "* [R]emove a passenger from the list                 *\n";
		cout << "* [Q]uit the program                                 *\n";
		cout << "******************************************************\n\n";
		cout << "Please enter a character from the selection : ";

		cin >> temp_ans1;
		cin.ignore(1000, '\n');

		switch (temp_ans1)
		{
		case 'E':
		case 'e':
			if (count == PASS_MAX)
			{
				system("CLS");
				cout << "\nYou have entered the maximum number of passengers.\n";
				system("pause");
			}
			else
			{
				system("CLS");
				append_node();
			}
			break;
		case 'D':
		case 'd':
			display_list();
			system("pause");
			break;
		case 'I':
		case 'i':
			if (count == PASS_MAX)
			{
				system("CLS");
				cout << "\nYou have entered the maximum number of passengers.\n";
				system("pause");
			}
			else
				insert_node();
			break;
		case 'R':
		case 'r':
			remove_node();
			break;
		case 'Q':
		case 'q':
			break;
		default:
			temp_ans1 = 'f';
		}
	} while (temp_ans1 != 'Q' && temp_ans1 != 'q');
}

void PassData::append_node()
{
	InfoPtr new_node = nullptr;
	InfoPtr curr_node = nullptr;

	new_node = new PassInfo;
	if (new_node == nullptr)
	{
		cout << "Error: allocation failed.\n";
		exit(1);
	}

	count++;

	cout << "Please enter the following information.\n";
	cout << "\n********** Passenger# " << count << " **********\n";

	get_input(new_node);
	new_node->next = nullptr;

	if (head == nullptr)
	{
		head = new_node;
	}
	else
	{
		curr_node = head;

		while (curr_node->next != nullptr)
		{
			curr_node = curr_node->next;
		}

		curr_node->next = new_node;
	}
}

void PassData::display_list()
{
	InfoPtr curr_node = nullptr;
	char	dummy = '\0';
	short	size_input = 0;
	short	arr_index1 = 0;
	short	temp_num1 = 0;

	system("CLS");

	if (head == nullptr)
	{

		cout << "\nYour list is currently empty.\n";
	}
	else
	{
		curr_node = head;

		do
		{
			temp_num1++;
			curr_node->pass_num = temp_num1;
			curr_node = curr_node->next;

		} while (curr_node != nullptr);

		cout << "************************************************************";
		cout << "****************************************************\n";
		cout << "*" << setw(62) << right << "PASSENGER LIST" << setw(50) << right << "*\n";
		cout << "************************************************************";
		cout << "****************************************************\n";
		cout << "* Pass#  " << setw(31) << left << "First Name" << setw(31) << left << "Last Name";
		cout << setw(31) << left << "Flight Number" << setw(10) << left << "Priority *\n";
		cout << "*" << setw(112) << right << "*\n";

		curr_node = head;

		while (curr_node != nullptr)
		{
			cout << "* [" << setw(2) << right << curr_node->pass_num << "]   ";

			size_input = strlen(curr_node->FName);
			for (arr_index1 = 0; arr_index1 < size_input; arr_index1++)
				cout << curr_node->FName[arr_index1];
			cout << setw((31 - size_input)) << left << dummy;

			size_input = strlen(curr_node->LName);
			for (arr_index1 = 0; arr_index1 < size_input; arr_index1++)
				cout << curr_node->LName[arr_index1];
			cout << setw((31 - size_input)) << left << dummy;

			size_input = strlen(curr_node->FltNum);
			for (arr_index1 = 0; arr_index1 < size_input; arr_index1++)
				cout << curr_node->FltNum[arr_index1];
			cout << setw((31 - size_input)) << left << dummy;

			if (curr_node->Priority == 'P' || curr_node->Priority == 'p')
				cout << setw(9) << left << "Platinum" << "*\n";
			else if (curr_node->Priority == 'G' || curr_node->Priority == 'g')
				cout << setw(9) << left << "Gold" << "*\n";
			else if (curr_node->Priority == 'S' || curr_node->Priority == 's')
				cout << setw(9) << left << "Silver" << "*\n";
			else
				cout << setw(9) << left << "Lead" << "*\n";

			curr_node = curr_node->next;
		}
		cout << "************************************************************";
		cout << "****************************************************\n\n";
	}
}

void PassData::insert_node()
{
	InfoPtr new_node = nullptr;
	InfoPtr curr_node = nullptr;
	InfoPtr prev_node = nullptr;
	short	insert_num = 0;

	system("CLS");

	if (head == nullptr)
	{
		cout << "Your list is currently empty.\n\n";

		append_node();
	}
	else
	{
		display_list();

		do
		{
			cout << "Select the Pass# to insert a new passenger : ";
			cin >> insert_num;

			error_input = cin.fail();

			if (error_input == true)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				insert_num = PASS_MAX;
			}
		} while (error_input == true || insert_num > count || insert_num <= 0);

		cin.ignore(1000, '\n');

		cout << "\n********** Passenger# " << insert_num << " **********\n";

		new_node = new PassInfo;
		if (new_node == nullptr)
		{
			cout << "Error: Insufficient storage.\n";
			exit(1);
		}

		get_input(new_node);

		count++;

		curr_node = head;

		if (head->pass_num == insert_num)
		{
			new_node->next = head;
			head = new_node;
		}
		else
		{
			while (curr_node != nullptr && curr_node->pass_num != insert_num)
			{
				prev_node = curr_node;
				curr_node = curr_node->next;
			}

			new_node->next = curr_node;
			prev_node->next = new_node;
		}
	}
}

void PassData::remove_node()
{
	InfoPtr curr_node = nullptr;
	InfoPtr prev_node = nullptr;
	short	remove_num = 0;

	if (head == nullptr)
	{
		system("CLS");
		cout << "\nYour list is currently empty.\n";
		system("pause");
	}
	else
	{
		display_list();

		do
		{
			cout << "Select the Pass# to delete : ";
			cin >> remove_num;

			error_input = cin.fail();
			cin.ignore(1000, '\n');

		} while (error_input == true || remove_num > count || remove_num <= 0);

		curr_node = head;

		if (head->pass_num == remove_num)
		{
			curr_node = head->next;
			delete head;
			head = curr_node;
			count--;
		}
		else
		{
			curr_node = head;
			prev_node = curr_node;

			while (curr_node != nullptr && curr_node->pass_num != remove_num)
			{
				prev_node = curr_node;
				curr_node = curr_node->next;
			}

			prev_node->next = curr_node->next;
			delete curr_node;
			count--;
		}

		cout << "\nPassenger# " << remove_num << " is successfully deleted.\n";
		system("pause");
	}
}

void PassData::get_input(InfoPtr& nodeptr)
{
	cout << "First Name    : ";
	cin.getline(nodeptr->FName, INPUT_MAX);
	check_input(nodeptr->FName);

	cout << "Last Name     : ";
	cin.getline(nodeptr->LName, INPUT_MAX);
	check_input(nodeptr->LName);

	cout << "Flight Number : ";
	cin.getline(nodeptr->FltNum, INPUT_MAX);
	check_input(nodeptr->FName);

	cout << "\nBoarding Priority\n";
	cout << " [P]latinum\n";
	cout << " [G]old\n";
	cout << " [S]ilver\n";
	cout << " [L]ead\n\n";

	do
	{
		cout << "Select a letter for the Boarding Priority : ";
		cin >> nodeptr->Priority;

		cin.ignore(1000, '\n');

	} while (nodeptr->Priority != 'P' && nodeptr->Priority != 'p'
		&& nodeptr->Priority != 'G' && nodeptr->Priority != 'g'
		&& nodeptr->Priority != 'S' && nodeptr->Priority != 's'
		&& nodeptr->Priority != 'L' && nodeptr->Priority != 'l');
}

void PassData::check_input(char arr_par[])
{
	short arr_index2 = 0;

	error_input = cin.fail();

	while (error_input == true)
	{
		cin.clear();
		cin.ignore(1000, '\n');

		for (arr_index2 = 0; arr_index2 < INPUT_MAX; arr_index2++)
			arr_par[arr_index2] = '\0';

		cout << "Re-enter Less than " << INPUT_MAX << " Characters : ";
		cin.getline(arr_par, INPUT_MAX);

		error_input = cin.fail();
	}
}