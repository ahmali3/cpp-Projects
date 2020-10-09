#include<string>
#include<bits/stdc++.h>
#include"Database.h"
    Database::Database()  // database constructor
	{}
	void Database::Add(struct Book book)   //Add Book
	{
	list.push_back(book);  // add the new record of book into database list
	}
	bool Database::Delete(struct Book book) //Delete Book
	{
		for(size_t i=0;i<list.size();i++)  // find the book from database list to delete 
		{   //check the provided parameter in database to delete
			if(book.Title==list[i].Title && book.ISBN==list[i].ISBN && book.Author==list[i].Author && book.Date_of_Publication==list[i].Date_of_Publication) 
			{
				list.erase(list.begin()+i);  //delete the record from database list
				return true;  // return true if record deleted
			}
		}
		return false;  //return false if record not found
	}
	bool Database::Update(vector<string> newlist)  //Update Book
	{
		int index=0;
		for(size_t i=0;i<list.size();i++)  //iterate the database record book
		{
			if(list[i].Title==newlist[index])  //find the record by title
			{
				if(newlist[index+1]=="1")  //find the type of updating attribute to update if 1 then update the author name
				{
					list[i].Author=newlist[index+2];    //update the author name
				}
				else if(newlist[index+1]=="2") //find the type of updating attribute to update if 2 then update the Date_of_Publication
				{
				    list[i].Date_of_Publication=newlist[index+2]; //update the Date_of_Publication
				}
				else if(newlist[index+1]=="3")  //find the type of updating attribute to update if 3 then update the Book_Type
				{
				    list[i].Book_Type=newlist[index+2];  //update the Book_Type
				}
				else if(newlist[index+1]=="4")  //find the type of updating attribute to update if 4 then update the No_of_Pages
				{
				    list[i].No_of_Pages=newlist[index+2]; //update the No_of_Pages
				}
				else if(newlist[index+1]=="5")  //find the type of updating attribute to update if 5 then update the ISBN
				{
				     list[i].ISBN=newlist[index+2];  //update the ISBN
				}
				return true;  //after update return true
			}
		
		}
		return false;  //if not found return false
	}
	vector<Book> Database::Helper_Search(int index,vector<Book> list1,vector<string> newlist)  // search the record by using provided field from user
	{
		vector<Book> Filter_Books;   //temp list of filter book
	    for(size_t i=0;i<list1.size();i++)   //iterate the list of book record database
		 {
			 if(newlist[index+1]=="1")   // search by title 
			 {
				 if(newlist[index+3]=="1")  //select the searching title with type is equal 
				 {
			       if(list1[i].Title==newlist[index+2]) //if title is equal then 
				   {
					   Filter_Books.push_back(list1[i]); // add into a filtered list of records
				   }
				 }
				 else if(newlist[index+3]=="2")   //select the searching title with type is not equal 
				 {
					 if(list1[i].Title!=newlist[index+2])   //if title is not equal then
					 {
						 Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					 }
				 }
			 }
			 else if(newlist[index+1]=="2") //Search by author name
			 {
				  if(newlist[index+3]=="1")  //select the searching author with type is equal 
				 {
			       if(list1[i].Author==newlist[index+2])  //if author is equal then
				   {
					   Filter_Books.push_back(list1[i]);   // add into a filtered list of records
				   }
				 }
				 else if(newlist[index+3]=="2")  //select the searching author with type if not equal 
				 {
					 if(list1[i].Author!=newlist[index+2])  //if author is not equal then
					 {
						 Filter_Books.push_back(list1[i]); // add into a filtered list of records
					 }
				 }
			 }
			 else if(newlist[index+1]=="3")  //search by data of publication 
			 {
				 if(newlist[index+3]=="1")   //select the searching data of publication  with type that is equal 
				 {
					 if(list1[i].Date_of_Publication==newlist[index+2]) //if data of publication  is equal then
					 {
						 Filter_Books.push_back(list1[i]); // add into a filtered list of records
					 }
			  
				 }
				 else if(newlist[index+3]=="2")   //select the searching data of publication  with type that is not equal 
				 {
					 if(list1[i].Date_of_Publication!=newlist[index+2]) //if data of publication is not equal then
					 {
						 Filter_Books.push_back(list1[i]);  //add into a filtered list of records
					 }
				 }
				 else if(newlist[index+3]=="5")   //select the searching data of publication with type that is less than 
				 {
					 if(atol(list1[i].Date_of_Publication.c_str())<atol(newlist[index+2].c_str()))  //if data of publication is not equal then
					 {
						 Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					 }
			 
				 }
				 else if(newlist[index+3]=="6")  //select the searching data of publication  with type its greater than
				 {
					 if(atol(list1[i].Date_of_Publication.c_str())>atol(newlist[index+2].c_str()))  //if data of publication is greater than
					 {
						 Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					 }
			 
				 }
			 }
			 else if(newlist[index+1]=="4")  // search by book type
			 {
				 if(newlist[index+3]=="1")  //select the searching book type  with type is equal
				 {
					  if(list1[i].Book_Type==newlist[index+2])  //if book type is equal
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="2")  //select the searching book type  with type is not equal
				 {
					  if(list1[i].Book_Type!=newlist[index+2])  //if book type is not equal
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
			 
				 }
			 }
			 else if(newlist[index+1]=="5") //search by no of pages
			 {
				 if(newlist[index+3]=="1")  //select the searching no of pages  with type is equal
				 {
					 if(atol(list1[i].No_of_Pages.c_str())==atol(newlist[index+2].c_str()))  //if no of pages is equal
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="2")     //select the searching no of pages  with type is not equal
				 {
					 if(atol(list1[i].No_of_Pages.c_str())!=atol(newlist[index+2].c_str()))  //if no of pages is not equal
					  {
						  Filter_Books.push_back(list1[i]);   // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="3")   //select the searching no of pages  with type is greater than and equal to
				 {
					 if(atol(list1[i].No_of_Pages.c_str())>=atol(newlist[index+2].c_str()))  //if no of pages is greater than and equal to then
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="4")   //select the searching no of pages  with type is less than and equal to 
				 {
					 if(atol(list1[i].No_of_Pages.c_str())<=atol(newlist[index+2].c_str()))  //if no of pages is less than and equal to then
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="5")   //select the searching no of pages  with type is less than
				 {
					 if(atol(list1[i].No_of_Pages.c_str())<atol(newlist[index+2].c_str()))  //if no of pages is less than 
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="6")   //select the searching no of pages  with type is greater than
				 {
					 if(atol(list1[i].No_of_Pages.c_str())>atol(newlist[index+2].c_str()))  //if no of pages is greater than
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
			 }
			 else if(newlist[index+1]=="6") //search by ISBN number
			 {
				 if(newlist[index+3]=="1")   //select the searching ISBN number with type that is equal
				 {
					 if(list1[i].ISBN==newlist[index+2])  //if ISBN number is equal
					  {
						  Filter_Books.push_back(list1[i]);  // add into a filtered list of records
					  }
				 }
				 else if(newlist[index+3]=="2")   //select the searching ISBN number  with type is not equal
				 {
					 if(list1[i].ISBN!=newlist[index+2])  //if ISBN number is not equal
					  {
						  Filter_Books.push_back(list1[i]);  //add into a filtered list of records
					  }
				 }
			 }
		 
		 }
		 return Filter_Books;  //return the searched list
	}
	
	vector<Book> Database::Search(vector<string> newlist)
	{
		int index=0;
		vector<Book> Filter_Books,Helper_Book;
		if(newlist[index]=="1") //simple type
		{
			Filter_Books = Helper_Search(index,list,newlist);  //get the filtered list of book records by applying the simple search engine
		}
		else if(newlist[index]=="2") //complex Search
		{
			for(size_t i=0; i<list.size(); i++) //make a copy of book record 
			{
				Helper_Book.push_back(list[i]); //make the copy
			}
			for(size_t i=0;i<newlist.size()-1;i+=3) //apply more than 1 field to search the records if complex type search
			{
				Filter_Books=Helper_Search(i,Helper_Book,newlist);  //get the filtered list of book records by applying the simple search engine
				Helper_Book.clear();   //clear the copy of the records list of book of database
				for(size_t i=0; i<Filter_Books.size(); i++) //again fill the list with latest record of filtered list
				{
					Helper_Book.push_back(Filter_Books[i]);  //make a copy
				}
			}
		}
		string sort_type;
		cout<<"---Select the option to sort the Search Results---"<<endl;  //show the menu of sort on the screen and to user
		cout<<"1 : Sort By Title"<<endl;
		cout<<"2 : Sort By Author Name"<<endl;
	    cout<<"3 : Sort By Date of Publication"<<endl;
	    cout<<"4 : Sort By Book Type"<<endl;
	    cout<<"5 : Sort By No of Pages"<<endl;
	    cout<<"6 : Sort By ISBN Number"<<endl;
		cin.ignore();
		getline(cin,sort_type);  //get the type to sort the filtered list
		while(sort_type<"1" && sort_type>"6")  //if user enters the wrong input and now try to get it again
		{
			cout<<"---please try again to select the option to sort the search results---"<<endl; //print the menu on screen
			cout<<"1 : Sort By Title"<<endl;
			cout<<"2 : Sort By Author Name"<<endl;
			cout<<"3 : Sort By Date of Publication"<<endl;
			cout<<"4 : Sort By Book Type"<<endl;
			cout<<"5 : Sort By No of Pages"<<endl;
			cout<<"6 : Sort By ISBN Number"<<endl;
			getline(cin,sort_type); // get the input of sort type
		}
		if(sort_type=="1")  //if option 1 then
		{
			sort(Filter_Books.begin(),Filter_Books.end(),SortByTitle); //sort the filtered list by title
		}
		else if(sort_type=="2") //if option 2 then
		{
			sort(Filter_Books.begin(),Filter_Books.end(),SortByAuthor); //sort the filtered list by author name
		}
		else if(sort_type=="3") //if option 3 then
		{
			sort(Filter_Books.begin(),Filter_Books.end(),SortByDateofPublication); //sort the filtered list by date of publication
		}
		else if(sort_type=="4") //if option 4 then
		{
		    sort(Filter_Books.begin(),Filter_Books.end(),SortByBookType); //sort the filtered list by book type
		}
		else if(sort_type=="5") //if option 5 then
		{
			sort(Filter_Books.begin(),Filter_Books.end(),SortByNoofPages); //sort the filtered list by no of pages
		}
		else if(sort_type=="6") //if option 6 then
		{
			sort(Filter_Books.begin(),Filter_Books.end(),SortByISBN); //sort the filtered list by ISBN number
		}
		return Filter_Books;
	}
	void Database::print()  // print the list of records in database
	{
	 for(size_t i=0 ;i<list.size();i++) //iterate the loop of size of record present in a database
	 {
	 cout<<list[i].Title <<"  "<<list[i].Author<<"  "<<list[i].Date_of_Publication<<"  "<<list[i].ISBN<<"  "<<list[i].No_of_Pages<<"  "<<list[i].Book_Type<<endl;
	 
	 }
	}
	void Database::print(vector<Book> helo) // print the list of provided list of records
	{
	for(size_t i=0 ;i<helo.size();i++) //iterate the loop of size of record present in a database
	 {
	 cout<<helo[i].Title <<"  "<<helo[i].Author<<"  "<<helo[i].Date_of_Publication<<"  "<<helo[i].ISBN<<"  "<<helo[i].No_of_Pages<<"  "<<helo[i].Book_Type<<endl;
	 
	 }
	}
	void Database::Save_Database_into_TextFile() // save the database into a file
	{
		ofstream fout;
		fout.open("Database.txt"); //open the file
		if(fout.is_open())
		{
			for(size_t i=0;i<list.size();i++) //iterate the list of records
			{  //print into a file each recors with value
				fout<<list[i].Title<<"	"<<list[i].Author<<"	"<<list[i].Date_of_Publication<<"	"<<list[i].Book_Type<<"	"<<list[i].No_of_Pages<<"	"<<list[i].ISBN<<endl;
			}
			fout.close(); //close the text file 
			cout<<"Data Stored into Database!!"<<endl;
		}
		else  // file is not created 
		{
			cout<<"File is not opened!!"<<endl;
		}
	
	}
	void Database::Load_Database_From_TextFile()  // Load the data into a database from file 
	{
		ifstream fin;  //local variables
		string Record,intermediate; 
		vector <string> tokens;
		fin.open("Database.txt"); //opens an input file to load into database
		if(fin.is_open())  //check if file is open or not
		{                         //if open then read the line of record 
			getline(fin,Record); 
			while(!fin.eof())  //read the file till end
			{
               stringstream check1(Record); 
               while(getline(check1, intermediate, '	')) //split the record value by tab to generate the tokens
               { 
                   tokens.push_back(intermediate);   //save the tokens
               } 
			   Book book;   // create the object of book and load the data
			   book.Title=tokens[0];    //load title
			   book.Author=tokens[1];   //load author name
			   book.Date_of_Publication=tokens[2]; //load date of publication
			   book.Book_Type=tokens[3]; //load book type
			   book.No_of_Pages=tokens[4]; //load no of pages 
			   book.ISBN=tokens[5]; //load ISBN number
			   list.push_back(book); // push the data into database list
			   tokens.clear();
			   getline(fin,Record); //read next line from file
			}
		}
		else  //if file is not open
		{
			cout<<"File is not open!"<<endl;
		}
	}
	
