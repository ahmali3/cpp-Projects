#include<iostream>
#include<sstream>
#include<fstream>
#include <algorithm>
#include<string>
#include<vector>
#include<list>
#include"Book.h"
using namespace std;
class Menu
{
private :

public:
	int Main_Menu(); //Main Menu of this whole program and return the option to database class to perform the action
	Book Book_Menu();//shows the book record menu and gets the input from user and put into book variable and return it which will be used in database's function add book
	vector<string> Update_Menu(); //show the updated menu and get the input from user and put into vector data structure and return it
	vector<string> Search_Menu(); //get the parameter from user to search the record on the bases of different fields
};