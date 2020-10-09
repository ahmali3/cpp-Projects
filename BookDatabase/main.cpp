#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<list>
#include"Database.h"
using namespace std;
int main()
{
	Database obj; //database object
	Menu obj1;    // create the menu object
	while(1){
	int choice=obj1.Main_Menu(); //get the input from user for option to perform the action 
	if(choice ==1)   // if option is 1 then add the record of book
	{
		obj.Add(obj1.Book_Menu());  
	}
	else if(choice==2)   //if option is 2 then the user enters the book to delete
	{
		cout<<"------- Enter the Book record to Delete From Database -------"<<endl;
	    if(obj.Delete(obj1.Book_Menu()))  //if record deleted successfully it will return true
		{
		   cout<<"Record Deleted Successfully!!"<<endl;
		}
		else   //if not deleted
		{
		   cout<<"Record Not Deleted!!"<<endl;
		}
	}
	else if(choice==3)  // if the option is 3 then the user will enter the updated data and the program will update it
	{
	    if( obj.Update(obj1.Update_Menu())) //if record updated successfully it will return true
		{
		   cout<<"Record Updated Successfully!!"<<endl;
		}
		else //if not updated
		{
		   cout<<"Record Not Updated!!"<<endl;
		}
	}
	else if(choice==4) // if the option is 4 then the user enters the data to search the record 
	{
		vector<Book> helo=obj.Search(obj1.Search_Menu());
		obj.print(helo);
	}
	else if(choice==5)  // option 5 saves the record of books into database of textfile
	{
		obj.Save_Database_into_TextFile();
	}
	else if(choice==6)  // option 6 reads the record from file and loads into database 
	{ 
	  obj.Load_Database_From_TextFile();
	}
	else if(choice==7)  //option 7 shows the record on screen 
	{
		cout<<"----------------List of Records----------"<<endl<<endl;
		obj.print();
	}
	else if(choice==8) //option 8 exits the program
	{
		break;
	}
	}
}
