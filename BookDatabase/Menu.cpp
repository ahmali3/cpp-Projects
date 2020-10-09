#include"Menu.h"
    int Menu::Main_Menu()   //these are all the options and functions of the program
	{
	   cout<<"1 : Add Book"<<endl;   
	   cout<<"2 : Delete Book"<<endl;
	   cout<<"3 : Update Book"<<endl;
	   cout<<"4 : Search Book"<<endl;
	   cout<<"5 : Save Database into Text File"<<endl;
	   cout<<"6 : Load Database from Text File"<<endl;
	   cout<<"7 : Print the Record"<<endl;
	   cout<<"8 : EXIT"<<endl;
	   int num;
	   cout<<"Enter your choice : ";
	   cin>>num;   //get the main option from user
	   while(num<1 && num<6)  // if user enter wrong input it will ask to try again for the right input
	   {
		   cout<<"Enter the choice Again your previous choice is not Correct : ";
		   cin>>num;
	   }
	   return num;
	}
	Book Menu::Book_Menu()  //menu of book to add the book into database
	{
		string num;
		Book book;  //make the book object to put all data into its variables 
		cin.ignore();
		cout<<"Enter Title of Book : ";
		getline(cin,book.Title);    //get title 
		cout<<"Enter the Author Name of Book : ";
		getline(cin,book.Author);  //get author name from user
		cout<<"Enter the Date of Publication of Book : ";
		getline(cin,book.Date_of_Publication);  //get the date of publication of book
		cout<<"Enter the Book Type ";
		cout<<"1 : hardcover"<<endl;
		cout<<"2 : softcover"<<endl;
		cout<<"3 : digital"<<endl;
		getline(cin,num);   //get the option number 
		while(num>"3" && num<"1")   // if user enters the wrong input of book type it will ask again for the correct input
		{
			cout<<"Please Try again to Enter the Book Type"<<endl;
		    cout<<"1 : hardcover"<<endl;
		    cout<<"2 : softcover"<<endl;
		    cout<<"3 : digital"<<endl;
			getline(cin,num);
		}
		if(num=="1")  // this is to store the book type according to user input
		{
		book.Book_Type="hardcover";  //first type
		}
		else if(num=="2")
		{
		book.Book_Type="softcover";  //second type
		}
		else if(num=="3")
		{
		book.Book_Type="digital";  //third type
		}
		cout<<"Enter the No of Pages of this Book : ";
		getline(cin,book.No_of_Pages);  //get the total page of a book 
		cout<<"Enter the ISBN Number : ";
		getline(cin,book.ISBN);  //get the isbn number from user
	  return book;    //returns the complete record of book
	}
	vector<string> Menu::Update_Menu()   //menu of updated function to update the record of book
	{
	  string title,number,updating_string;  //local variables
	  vector<string> Updating_material;
	  cout<<"Enter the Title of a Book you want to Update the Record : ";
	  cin.ignore();
	  getline(cin,title);     //get the title record which you want to update
	  
	  cout<<"---------Enter the option you want to Update--------------"<<endl; 
	  cout<<"1 : Update the Author Name"<<endl;
	  cout<<"2 : Update the Date of Publication"<<endl;
	  cout<<"3 : Update the Book Type"<<endl;
	  cout<<"4 : Update the No of Pages"<<endl;
	  cout<<"5 : Update the ISBN Number"<<endl;
	  getline(cin,number);  //get input
	  while(number<"1" && number>"5")  //if user enters wrong input program will ask again
	  {
		  cout<<"---------Please again Enter the option you want to Update--------------"<<endl;
	      cout<<"1 : Update the Author Name"<<endl;
	      cout<<"2 : Update the Date of Publication"<<endl;
	      cout<<"3 : Update the Book Type"<<endl;
	      cout<<"4 : Update the No of Pages"<<endl;
	      cout<<"5 : Update the ISBN Number"<<endl; 
	      getline(cin,number);  //get input of updating data from record
	  }
	  cout<<"Enter the Updating Data : ";
	  getline(cin,updating_string);  //get the updating data from user
	  Updating_material.push_back(title);
	  Updating_material.push_back(number);
	  Updating_material.push_back(updating_string);
	  return Updating_material;  //return the updated data to updated function of database
	}
	vector<string> Menu::Search_Menu()   //menu of search a record on the bases of different arguments
	{
		vector<string> Searching_input_parameters;  //local variable
		string Search_Type,Simple_Search_Type,Simple_Search,Equal_Type;
		cout<<"----Search the Record------"<<endl;  //search menu on screen
		cout<<"1 : Simple Search"<<endl;
		cout<<"2 : Complex Search"<<endl;
		cin.ignore();
		getline(cin,Search_Type);  //get searching type from user 
		
		while(Search_Type<"1" && Search_Type>"2")  //if the option is wrong program asks again
		{
			cout<<"----Search the Record------"<<endl;
		    cout<<"1 : Simple Search"<<endl;
		    cout<<"2 : Complex Search"<<endl;
		    getline(cin,Search_Type); //get the searching main type
		
		}
		if(Search_Type=="1")   //show menu for search type 1
		{
		    cout<<"------Choose the Field to Search the Records------"<<endl;  //menu to show on screen
			cout<<"1 : Search By Title"<<endl;
		    cout<<"2 : Search By Author Name"<<endl;
	        cout<<"3 : Search By Date of Publication"<<endl;
	        cout<<"4 : Search By Book Type"<<endl;
	        cout<<"5 : Search By No of Pages"<<endl;
	        cout<<"6 : Search By ISBN Number"<<endl;
			getline(cin,Simple_Search_Type);  //get the option from user
			while(Simple_Search_Type<"1" && Simple_Search_Type>"6")  //if option is wrong program asks again
			{
				cout<<"------Please Try Again to Choose the Field to Search the Records------"<<endl; 
			    cout<<"1 : Search By Title"<<endl;
		        cout<<"2 : Search By Author Name"<<endl;
				cout<<"3 : Search By Date of Publication"<<endl;
				cout<<"4 : Search By Book Type"<<endl;
				cout<<"5 : Search By No of Pages"<<endl;
				cout<<"6 : Search By ISBN Number"<<endl;
				getline(cin,Simple_Search_Type);  //get searching type  
			
			}
			cout<<"Enter the string to Search the Records : ";    
			getline(cin,Simple_Search);   //get the string from user to search on the bases of selected option from menu
			cout<<"Search for any book record whose field is __________ to a value given by the user"<<endl;  //show menu on screen of search engine
			cout<<"1 : Equal to"<<endl;
			cout<<"2 : Not Equal to"<<endl;
			cout<<"3 : At most"<<endl;
			cout<<"4 : At least"<<endl;
			cout<<"5 : Less than"<<endl;
			cout<<"6 : Greater than"<<endl;
			getline(cin,Equal_Type);  // get the type of selected option for search
			while(Equal_Type<"1" && Equal_Type>"6")  //ask again for input from user if given option is wrong
			{
				cout<<"Search for any book record whose field is __________ to a value given by the user"<<endl;  //print the menu on screen
				cout<<"1 : Equal to"<<endl;
				cout<<"2 : Not Equal to"<<endl;
				cout<<"3 : At most"<<endl;
				cout<<"4 : At least"<<endl;
				cout<<"5 : Less than"<<endl;
				cout<<"6 : Greater than"<<endl;
				getline(cin,Equal_Type); //get type 
			
			}
			Searching_input_parameters.push_back(Search_Type);  //put searching parameter into vector and send it to search function of database
			Searching_input_parameters.push_back(Simple_Search_Type);
			Searching_input_parameters.push_back(Simple_Search);
			Searching_input_parameters.push_back(Equal_Type);
		}
		else if(Search_Type=="2")  //show menu for search type 2
		{
			Searching_input_parameters.push_back(Search_Type);   //save the searching type into vector
			while(1){
		    cout<<"------Choose the Multiple Field to Search the Records------"<<endl;  //print the menu on screen
			cout<<"1 : Search By Title"<<endl;
		    cout<<"2 : Search By Author Name"<<endl;
	        cout<<"3 : Search By Date of Publication"<<endl;
	        cout<<"4 : Search By Book Type"<<endl;
	        cout<<"5 : Search By No of Pages"<<endl;
	        cout<<"6 : Search By ISBN Number"<<endl;
			cout<<"7 : EXIT"<<endl;
			getline(cin,Simple_Search_Type);  //get the searching by field input 
			while(Simple_Search_Type<"1" && Simple_Search_Type>"7")  // get input again from user if it is not correct
			{
				cout<<"------Please Try Again to Choose the Multiple Field to Search the Records------"<<endl;  //show the menu on screen to get the field from user
			    cout<<"1 : Search By Title"<<endl;
		        cout<<"2 : Search By Author Name"<<endl;
				cout<<"3 : Search By Date of Publication"<<endl;
				cout<<"4 : Search By Book Type"<<endl;
				cout<<"5 : Search By No of Pages"<<endl;
				cout<<"6 : Search By ISBN Number"<<endl;
				cout<<"7 : EXIT"<<endl;
				getline(cin,Simple_Search_Type); //get the searching by field input 
			}
			if(Simple_Search_Type=="7")  //exit option of searching input field
			{
				break;
			}
			Searching_input_parameters.push_back(Simple_Search_Type);  //save the seraching parameter into vector
			cout<<"Enter the string to Search the Records : ";
			getline(cin,Simple_Search);  //get the string to search the record
			Searching_input_parameters.push_back(Simple_Search);  //save it
			cout<<"Search for any book record whose field is __________ to a value given by the user"<<endl;  //menu to get the field type of equal or not
			cout<<"1 : Equal to"<<endl;
			cout<<"2 : Not Equal to"<<endl;
			cout<<"3 : At most"<<endl;
			cout<<"4 : At least"<<endl;
			cout<<"5 : Less than"<<endl;
			cout<<"6 : Greater than"<<endl;
			getline(cin,Equal_Type);  //get the field from user
			while(Equal_Type<"1" && Equal_Type>"6")  //program takes input again from user in case of wrong option
			{
				cout<<"Search for any book record whose field is __________ to a value given by the user"<<endl;  //print the menu on screen
				cout<<"1 : Equal to"<<endl;
				cout<<"2 : Not Equal to"<<endl;
				cout<<"3 : At most"<<endl;
				cout<<"4 : At least"<<endl;
				cout<<"5 : Less than"<<endl;
				cout<<"6 : Greater than"<<endl;
				getline(cin,Equal_Type);  //get the input again
			}
			Searching_input_parameters.push_back(Equal_Type);  //put into searching parameter database 
		}
		}
		return Searching_input_parameters; //return the searching field data to database class and to searching function
	}