#include<iostream>
#include<sstream>
#include<fstream>
#include <algorithm>
#include<string>
#include<vector>
#include<list>
#include"Menu.h"
using namespace std;


class Database
{
private :
	vector<Book> list;
public :
	Database();  //Database constructor 
	void Add(struct Book book); // add new record  of book into database
	bool Delete(struct Book book);  // delete record of book from database
	bool Update(vector<string> newlist);  //update record of book from database
	vector<Book> Helper_Search(int index,vector<Book> list1,vector<string> newlist); //searching helper function of book record 
	static bool SortByTitle(Book a , Book b)   //sort the books on the bases of title in database
	{
		return (a.Title>b.Title);  //return true if first book is large title name
	}
	static bool SortByAuthor(Book a , Book b) //sort the books on the bases of author name in database
	{
		return (a.Author>b.Author);  //return true if first book is large author name
	}
	static bool SortByDateofPublication(Book a , Book b)  //sort the books on the bases of date of publication in database
	{
		return (a.Date_of_Publication>b.Date_of_Publication);  //return true if first book is large data of publication
	}
	static bool SortByBookType(Book a , Book b) //sort the books on the bases of book type in database
	{
		return (a.Book_Type>b.Book_Type); //return true if first book is large book type
	}
	static bool SortByNoofPages(Book a , Book b) //sort the books on the bases of no of pages in database
	{
		return (a.No_of_Pages>b.No_of_Pages); //return true if first book is large no of pages
	}
	static bool SortByISBN(Book a , Book b) //sort the books on the bases of isbn number in database
	{
		return (a.ISBN>b.ISBN);  //return true if first book is large isbn number
	}
	vector<Book> Search(vector<string> newlist);  //search the record on bases of provided parameters
	void print();  //print the records
	void print(vector<Book> helo);  //print the record provided list
	void Save_Database_into_TextFile();  //save all records into file database
	void Load_Database_From_TextFile(); //load the records from file into database
	
};