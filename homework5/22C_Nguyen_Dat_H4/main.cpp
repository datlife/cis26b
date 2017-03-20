// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by  Dat Thanh Nguyen
/*
CIS 22C - Winter 2016
------------------------------------------------------------------
HOMEWORK 4 - Binary Search Tree
------------------------------------------------------------------
Author:			 Dat Thanh Nguyen
IDE:			 Microsoft Visual Studio 2015
Debugging Tools: Native Memory Diagnostic Tools + Visual Leak Detector

Last Update: 8:35 PM 2/21/2016
------------------------------------------------------------------

1. Update Info:
-  Updated member height and updateHeight() in BinaryNode class
-  Added Student object. 
-  Added iterative depth-first traversals int BinaryTree class
-  Memory Leak checked.

*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"  // BST ADT 
#include "Student.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;
#define FILENAME "gpa.txt"


// Function prototypes
int		importData(const char*,BinarySearchTree<Student>*);
void	requestAction(BinarySearchTree<Student>*);
void	print_indented_tree(BinaryNode<Student>*, int);
void	longestBranch(BinaryNode<Student>*,Stack<Student>&);
void	searchManager(BinarySearchTree<Student>*);
void	tokenizer(Student&, string);
void	display(Student & anItem)
{
	anItem.showInfo();
}  
void	displayHeader()
{
	//cout <<left;
	cout<<setw(5)  << "ID" << " " <<
		  setw(13) << "|First Name " <<
		  setw(20) << "|Last Name " 
		           << "|GPA" << endl;
	for (int i = 0; i < 47; i++) cout << "-";
	cout << endl;
}  


int main()
{
	BinarySearchTree<Student>* pStudent_Database = new BinarySearchTree<Student>();
//	bool success = true;
	int line = importData(FILENAME, pStudent_Database);
	if (line > 0)
	{
		//Display Main Menu
		requestAction(pStudent_Database);
		cout << "\nThank you for using this program. Press enter to quit.";
	}
	else
		cout << "There is no data in input file. Press enter to quit; ";

	//Destroy the tree
	pStudent_Database->removeTree(pStudent_Database->getroot()); 
	//Delete dynamic allocated value.
	delete pStudent_Database;

	cin.get();
   return 0;
}  


/************************************************************
Import Data Manager: Builds a string list from an input file
return the number of lines in the file
*************************************************************/
int importData(const char* filename, BinarySearchTree<Student>* pStudent_Database)
{
	ifstream inputFile;
	int counter = 0;
	// open the input file
	inputFile.open(filename);
	if (!inputFile) {
		cout << "Error opening file \"" << filename << "\"\n";
		return counter = -1;
	}
	//Read each line of text into its own country object, then insert it into the list
	while (!inputFile.eof()) {
		string new_line;
		getline(inputFile, new_line);
		if (!new_line.empty())
		{
			Student new_student;
			//String manipulation
			tokenizer(new_student, new_line);
			//new_student.showInfo();
			pStudent_Database->insert(new_student);
			counter++; // total number of input
		}
	}
	inputFile.close();
	return counter;
}
/************************************************************
Tokenzier: Seperate string of input into token 
then pass to Student Object.
*************************************************************/
void tokenizer(Student& new_student, string new_line) {

	//1700 Dat, Nguyen Thanh; 3.8
	//Find the space " " between 1700 and Dat
	size_t id_pos = new_line.find_first_of(" ");
	string ID = new_line.substr(0, id_pos);
	new_student.setID(ID);
	
	//Get the position of the first","
	size_t name_pos = new_line.find_first_of(",");
	//Get the position of first","
	size_t gpa_pos= new_line.find_first_of(";");

	//Set First Name by starting at "id_pos +1 , length = name_pos - idpos -1
	string fName = new_line.substr(id_pos+1, name_pos - id_pos -1);
	new_student.setFirstName(fName);
	//Set LastName
	string lname = new_line.substr(name_pos + 2, gpa_pos - name_pos -2);
	new_student.setLastName(lname);
	//Set GPA
	string GPA = new_line.substr(gpa_pos + 2, new_line.length() - gpa_pos -1);
	new_student.setGPA(GPA);
	

}

/************************************************************
Display Indented List: Seperate string of input into token
then pass to Student Object.
*************************************************************/
void print_indented_tree(BinaryNode<Student>* parentNode, int level) {
	if (parentNode != 0) {
		//Identation
		for (int i = 0; i < level; i++)cout << "\t";
		//Print the current Node
		cout << level << ". ";
		parentNode->getItem().showInfoIndividual();
		cout << endl;

		//if Node is a leaf. Stop here
		if (!parentNode->isLeaf()) {		
			int new_level = level + 1;	
			//Recursive Algorithm
			print_indented_tree(parentNode->getRightPtr(), new_level);
			print_indented_tree(parentNode->getLeftPtr(), new_level); 
		}
	}
}

//**********************************************************
// Menu Manger: displays a menu
// and calls the requested function
//*********************************************************
void requestAction(BinarySearchTree<Student>* pStudent_Database){

	string input = "1";
	do{
		cout << "\n\t\t\tMAIN MENU\n";
		for (int i = 0; i < 60; i++) { cout << '-'; }
		cout << endl
			 <<"T: Display as indented List\t"
		     <<"B: Breadth-First Traversals|\n"
			 <<"D: Depth-First Traversals\t"
			 <<"S: Search student by ID\t   |\n"
			 <<"R: Print Longest Branch\t\t"
			 <<"H: Help \t\t   |\n"
			 <<"A: About\t\t\t"
		     <<"Q: Quit\t     E:Extra Credit|"
			<< endl;
		for (int i = 0; i < 60; i++) { cout << '-'; }
		cout << "\nPlease select a letter as shown: ";
		getline(cin, input);
		if (input == "Q") break;
		cout << endl;
		//If valid input, execute corresponding functionality"
		if (input == "T" || input == "B" || input == "D" || input == "S" ||
			input == "R" || input == "A" || input == "H" || input == "E"){
			//Process input
			//Print Intended List
			if (input == "T"){
				cout << "\t\tIndented Student Database: " << endl;
				int level = 0;
				print_indented_tree(pStudent_Database->getroot(), level);
			}
			//Display Breath-first Traversals
			else if (input == "B"){
				Queue<Student> result; 
				//Breadth-first traversal
				pStudent_Database->BFT(pStudent_Database->getroot(), result);
				displayHeader();
				//Display the result
				while (!result.isEmpty()){
					Student temp;
					result.dequeue(temp);
					temp.showInfo();
				}

			}
			//Display Depth-first Traversals
			else if (input == "D"){

				cout << "*****************In-Order Display***************** " << endl;
				displayHeader();
				pStudent_Database->inOrder(display);
				cout << endl;
	
				cout << "*****************Post-Order Display***************** " << endl;
				displayHeader();
				pStudent_Database->postOrder(display);
				cout << endl;

				cout << "*****************Pre-Order Display*****************" << endl;
				displayHeader();
				pStudent_Database->preOrder(display);
				cout << endl;
			}
			//Search Student by ID
			else if (input == "S"){
				searchManager(pStudent_Database);
			}
			else if (input == "R"){
				Stack<Student> result;
				longestBranch(pStudent_Database->getroot(), result);
				//Display the longest branch.
				displayHeader();
				while (!result.isEmpty()){
					Student temp;
					result.pop(temp);
					temp.showInfo();
				}
			}
			else if (input == "A"){
				cout << "Author: Dat Nguyen" << endl;
				cout << "CIS 22C - WINTER 2016" << endl;
				cout << "Homework 4 - Binary Search Tree" << endl;
			}
			else if (input == "H"){
				//Show help
				cout << "*****************************HELP INFORMATION***************************************" << endl;
				cout << "Please input a single character as shown below (the first letter) to use the program" << endl;
				cout << "*************************************************************************************" << endl;
			}
			else if (input == "E") {
				cout << "*****************In-Order Display***************** " << endl;
				displayHeader();
				pStudent_Database->IinOrder(display);
				cout << endl;


				cout << "*****************Post-Order Display***************** " << endl;
				displayHeader();
				pStudent_Database->IpostOrder(display);
				cout << endl;

				cout << "*****************Pre-Order Display*****************" << endl;
				displayHeader();		
				pStudent_Database->IpreOrder(display);
				cout << endl;
			}
		}
		else{
			cout << "Please type H for help." << endl;
		}
		//4 corresponds with the quit option
	} while (input != "Q");
}

//**********************************************************
// Search Manger: Look for student information by ID
//*********************************************************
void	searchManager(BinarySearchTree<Student>* pStudent_Database){
	string input;
	do{
		//stores the result of the list.findCountry function
		//Country* country = new Country;

		cout << "Please enter a student ID to search (type QUIT to exit): " << endl;
		getline(cin, input);
		cout << endl;
		Student student_info(input);
		//INPUT VALIDATAION!
		if ("QUIT" == input) {
			//delete country;
			break;
		}
		bool found = pStudent_Database->getEntry(student_info);
		//list.findCountry(input.c_str(), country);
		//if country is still null display error message. Ignore this check if user is trying to quit
		if (found == false){
			cout << "Could not find a student with this ID: " << input << endl;
		}
		else{
			cout << "Found Student:" << endl;
			student_info.showInfoIndividual();
		}
		cout << endl;

		//delete student_info;

	} while (input != "QUIT");

}

//***********************************************************
// Find Longest Branch of BST: Look for student information by ID
// Using recursion to find the longest path and store in Stack
//***********************************************************
void	longestBranch(BinaryNode<Student>* current_Node,Stack<Student> &result){	
	if (!current_Node->isLeaf()){		
		int left_height;
		if (current_Node->getLeftPtr()){
			left_height = current_Node->getLeftPtr()->getHeight();
		}
		else left_height = -1;

		if (left_height == current_Node->getHeight() -  1){
			result.push(current_Node->getItem());
			longestBranch(current_Node->getLeftPtr(),result);
		}
		else
		{
			result.push(current_Node->getItem());
			longestBranch(current_Node->getRightPtr(), result);
		}
	}
	else {
		result.push(current_Node->getItem());
	}
}
/*
SAMPLE OUT PUT

                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: T

                Indented Student Database:
0. 3800 Lee Victor 2.8

        1. 4300 Trapp Amanda Elizabeth 4

                2. 5000 Lee Lucy Marie 3.4

                2. 3900 Brown Joanne 3.5

                        3. 4200 Brown Joanne 4

        1. 3000 Brown Joanne 4

                2. 3500 Marcus John 3.2

                        3. 3300 Lee Victor 3.6

                2. 1900 Walljasper Bryan 3.9

                        3. 2100 Andrews Dennis 2.9

                                4. 2800 Brown Joanne 2.6

                                        5. 2500 Lee Mary 3.8

                        3. 1500 Marcus John 4


                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: B

ID    |First Name  |Last Name          |GPA
-----------------------------------------------
3800   Lee          Victor              2.80
3000   Brown        Joanne              4.00
4300   Trapp        Amanda Elizabeth    4.00
1900   Walljasper   Bryan               3.90
3500   Marcus       John                3.20
3900   Brown        Joanne              3.50
5000   Lee          Lucy Marie          3.40
1500   Marcus       John                4.00
2100   Andrews      Dennis              2.90
3300   Lee          Victor              3.60
4200   Brown        Joanne              4.00
2800   Brown        Joanne              2.60
2500   Lee          Mary                3.80

                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: D

*****************In-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
1500   Marcus       John                4.00
1900   Walljasper   Bryan               3.90
2100   Andrews      Dennis              2.90
2500   Lee          Mary                3.80
2800   Brown        Joanne              2.60
3000   Brown        Joanne              4.00
3300   Lee          Victor              3.60
3500   Marcus       John                3.20
3800   Lee          Victor              2.80
3900   Brown        Joanne              3.50
4200   Brown        Joanne              4.00
4300   Trapp        Amanda Elizabeth    4.00
5000   Lee          Lucy Marie          3.40

*****************Post-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
1500   Marcus       John                4.00
2500   Lee          Mary                3.80
2800   Brown        Joanne              2.60
2100   Andrews      Dennis              2.90
1900   Walljasper   Bryan               3.90
3300   Lee          Victor              3.60
3500   Marcus       John                3.20
3000   Brown        Joanne              4.00
4200   Brown        Joanne              4.00
3900   Brown        Joanne              3.50
5000   Lee          Lucy Marie          3.40
4300   Trapp        Amanda Elizabeth    4.00
3800   Lee          Victor              2.80

*****************Pre-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
3800   Lee          Victor              2.80
3000   Brown        Joanne              4.00
1900   Walljasper   Bryan               3.90
1500   Marcus       John                4.00
2100   Andrews      Dennis              2.90
2800   Brown        Joanne              2.60
2500   Lee          Mary                3.80
3500   Marcus       John                3.20
3300   Lee          Victor              3.60
4300   Trapp        Amanda Elizabeth    4.00
3900   Brown        Joanne              3.50
4200   Brown        Joanne              4.00
5000   Lee          Lucy Marie          3.40


                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: E

*****************In-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
1500   Marcus       John                4.00
1900   Walljasper   Bryan               3.90
2100   Andrews      Dennis              2.90
2500   Lee          Mary                3.80
2800   Brown        Joanne              2.60
3000   Brown        Joanne              4.00
3300   Lee          Victor              3.60
3500   Marcus       John                3.20
3800   Lee          Victor              2.80
3900   Brown        Joanne              3.50
4200   Brown        Joanne              4.00
4300   Trapp        Amanda Elizabeth    4.00
5000   Lee          Lucy Marie          3.40

*****************Post-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
1500   Marcus       John                4.00
2500   Lee          Mary                3.80
2800   Brown        Joanne              2.60
2100   Andrews      Dennis              2.90
1900   Walljasper   Bryan               3.90
3300   Lee          Victor              3.60
3500   Marcus       John                3.20
3000   Brown        Joanne              4.00
4200   Brown        Joanne              4.00
3900   Brown        Joanne              3.50
5000   Lee          Lucy Marie          3.40
4300   Trapp        Amanda Elizabeth    4.00
3800   Lee          Victor              2.80

*****************Pre-Order Display*****************
ID    |First Name  |Last Name          |GPA
-----------------------------------------------
3800   Lee          Victor              2.80
3000   Brown        Joanne              4.00
1900   Walljasper   Bryan               3.90
1500   Marcus       John                4.00
2100   Andrews      Dennis              2.90
2800   Brown        Joanne              2.60
2500   Lee          Mary                3.80
3500   Marcus       John                3.20
3300   Lee          Victor              3.60
4300   Trapp        Amanda Elizabeth    4.00
3900   Brown        Joanne              3.50
4200   Brown        Joanne              4.00
5000   Lee          Lucy Marie          3.40


                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: S

Please enter a student ID to search (type QUIT to exit):
1500

Found Student:
1500 Marcus John 4.00

Please enter a student ID to search (type QUIT to exit):
5000

Found Student:
5000 Lee Lucy Marie 3.40

Please enter a student ID to search (type QUIT to exit):
231

Could not find a student with this ID: 231

Please enter a student ID to search (type QUIT to exit):
QUIT


                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: A

Author: Dat Nguyen
CIS 22C - WINTER 2016
Homework 4 - Binary Search Tree

                        MAIN MENU
------------------------------------------------------------
T: Display as indented List     B: Breadth-First Traversals|
D: Depth-First Traversals       S: Search student by ID    |
R: Print Longest Branch         H: Help                    |
A: About                        Q: Quit      E:Extra Credit|
------------------------------------------------------------
Please select a letter as shown: Q

Thank you for using this program. Press enter to quit.
*/
