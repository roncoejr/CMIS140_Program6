
/*
**********************************************************************************************
Name: Ronald Coe, Jr.		Date: May 05, 2004				File Name: Coe6.cpp

CMIS140
Assignment: Program 6

PURPOSE: This program implements a database program that could be used for tracking inventory at a video store - with a C++ class.

COMPILER: gcc 3.3 on Mac OS X 10.3.3

LIMITATIONS: As this version of the program has been written in a compressed timeframe and is based on structures, the features are not as robust
			 they could be.  The storage of actor names is a severe limitation, its really only meant for one actor.
			 
			 The number of videos managed, from the perspective of the delete functionality, has an upper limit of 200.
**********************************************************************************************
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Coe6.h";

using namespace std;

/*************************************************************
***  Constants used for the heading on the output are defined 
***  here
***
**************************************************************/
const string MY_NAME = "Coe, Jr., Ronald";
const string ASSIGNMENT = "CMIS140: Assignment #6";
const string THE_DATE = "May 05, 2004";


// **********************************************************
// Function prototypes are defined here.
//
// **********************************************************
char displayMenu();

/***********************************************************
Function: main()
Purpose: Program entry point
***********************************************************/
int main () {

	// ***********************
	//  Define variables used in the main function
	//
	char c_result = ' ';
	cl_VideoStore m_VideoStore;

	// ***********************
	// Perform initial file operations before main program processing begins
	//

	// ***********************
	// Display header information for this assignment in the output
	//
	cout << MY_NAME << setw(40) << ASSIGNMENT << setw(38) << THE_DATE;
	cout << endl << endl << endl << endl << endl;

	//outFile << MY_NAME << setw(40) << ASSIGNMENT << setw(38) << THE_DATE;
	//outFile << endl << endl << endl << endl << endl;
	
	// ***********************
	// Initialize the array so that all records contain information representative of an empty record
	//


	// ****************************************************
	//
	// Continue processing inventory requests until the user selects the option to quit the program
	//
	while(c_result != 'q' && c_result != 'Q')
	{
		// ************************
		//		Display the menu and obtain the user's selection
		//
		c_result = displayMenu();
		
		// ************************
		// Execute the appropriate function based on the selection made
		//
		switch(c_result)
		{
			case 'a':
			case 'A':
					cin.ignore(2, '\n');
					m_VideoStore.addVideo();
					break;
			case 'd':
			case 'D':
					cin.ignore(2, '\n');
					m_VideoStore.deleteVideo();
					break;
			case 's':
			case 'S':
					cin.ignore(2, '\n');
					m_VideoStore.searchVideo();
					break;
			case 'l':
			case 'L':
					cin.ignore(2, '\n');
					m_VideoStore.listVideos();
					break;
			case 'q':
			case 'Q':
					break;
			default:
					cin.ignore(2, '\n');
					cout << endl << endl << "You have chosen an invalid selection, please try again." << endl << endl;
		}
	
	
	}
	
    return 0;
}

/***********************************************************
Function: displayMenu()
Purpose: Display's the menu the user uses to manage the video inventory
***********************************************************/
char displayMenu()
{

	char c_selection;
	
	cout << "Please select from the following actions:" << endl << endl;
	cout << "\t'A': Add a Video" << endl << "\t'D': Delete a Video" << endl << "\t'S': Search for a Video" << endl << "\t'L': List all Videos" << endl << "\t'Q': Quit the program"  << endl << endl;
	
	cin >> c_selection;
	
	return c_selection;
}

