//LIBRARIES
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

//COLORS
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN "\033[32m"
	
	//CLASS BOOK
class Book {
private:
    string id, isbn, title, author, edition, publication, category;

public:
    Book() {}
    void setBook(string _id, string _isbn, string _title, string _author, string _edition, string _publication, string _category) {
        id = _id;
        isbn = _isbn;
        title = _title;
        author = _author;
        edition = _edition;
        publication = _publication;
        category = _category;
    }
    string getId() 
	{ 
		return id; 
	}
		
	    string getCategory() 
		{ 
			return category; 
		}
		
	    void displayBook() 
		{
		    cout << "| " << setw(10) << left << id
		         << "| " << setw(13) << left << isbn
		         << "| " << setw(25) << left << title
		         << "| " << setw(20) << left << author
		         << "| " << setw(8) << left << edition
		         << "| " << setw(15) << left << publication
		         << "| " << setw(12) << left << category
		         << " |" << endl;
		}
	    void editBook(string _isbn, string _title, string _author, string _edition, string _publication) {
	        isbn = _isbn;
	        title = _title;
	        author = _author;
	        edition = _edition;
	        publication = _publication;
	    }
	};
	
	bool isValidId(const string &id) 
	{
	    for (char c : id) {
	        if (!isalnum(c)) return false; 
	    }
	    return true;
	}
	
	bool isValidISBN(const string &isbn) {
	    for (char c : isbn) {
	        if (!isalnum(c)) return false; 
	    }
	    return !isbn.empty();
	}
	
	bool isValidAuthor(const string &author) {
	    for (char c : author) {
	        if (!isalpha(c) && c != ' ') return false; 
	    }
	    return !author.empty();
	}
	
	bool isValidEdition(const string &edition) {
	    for (char c : edition) {
	        if (!isalnum(c) && c != ' ') return false;
	    }
	    return !edition.empty();
	}
	
	bool isValidPublication(const string &publication) {
	    for (char c : publication) {
	        if (!isalnum(c) && c != ' ') return false;
	    }
	    return !publication.empty();
	}
	
	
	
	class Library 
	{
	private:
	    Book* books = nullptr;
	    int bookCount = 0;
	    int bookCapacity = 10;
	    string categories[2] = {"Fiction", "Non-fiction"};
	
	public:
	    Library() {
	        books = new Book[bookCapacity];
	    }
	    
	    ~Library() 
		{
	    if (books) {
	        delete[] books;
	        books = nullptr;
	    }
	}
	    
	    void resizeArray() {
	        bookCapacity *= 10;
	        Book* newBooks = new Book[bookCapacity];
	        for (int i = 0; i < bookCount; i++) {
	            newBooks[i] = books[i];
	        }
	        delete[] books;
	        books = newBooks;
	    }
	    
	    bool isValidCategory(string category) 
		{
	    	for (char &c : category) c = toupper(c); 
	    	return (category == "FICTION" || category == "NON-FICTION");
		}
	
	    
	    bool isDuplicateId(string id) {
	        for (int i = 0; i < bookCount; i++) {
	            if (books[i].getId() == id)
	                return true;
	        }
	        return false;
	    }
	    
	    int getBookCount() { return bookCount; }
	    
	    void addBook() {
	    if (bookCount >= bookCapacity) {
	        resizeArray();
	    }
	
	    string id, isbn, title, author, edition, publication, category;
	
	    // Category Validation
	    do {
	        cout << "Enter Category (Fiction/Non-fiction): ";
	        getline(cin, category);
	        if (!isValidCategory(category)) {
	            cout << RED << "Invalid category! Choose Fiction or Non-fiction.\n" << RESET;
	        }
	    } while (!isValidCategory(category));
	
	    // ID Validation
	    do {
	        cout << "Enter Book ID: ";
	        getline(cin, id);
	        for (char &c : id) c = toupper(c); 
	        if (!isValidId(id)) {
	            cout << RED << "Invalid ID! Use alphanumeric characters (no spaces or symbols).\n" << RESET;
	        } else if (isDuplicateId(id)) {
	            cout << RED << "Duplicate ID! Try again.\n" << RESET;
	        }
	    } while (!isValidId(id) || isDuplicateId(id));
		
	    // ISBN Validation
	    do {
	        cout << "Enter ISBN: ";
	        getline(cin, isbn);
	        if (!isValidISBN(isbn)) {
	            cout << RED << "Invalid ISBN! Use alphanumeric characters (no decimals or symbols).\n" << RESET;
	        }
	    } while (!isValidISBN(isbn));
	
	    // Title Input
	    cout << "Enter Title: ";
	    getline(cin, title);
	
	    // Author Validation
	    do {
	        cout << "Enter Author: ";
	        getline(cin, author);
	        if (!isValidAuthor(author)) {
	            cout << RED << "Invalid author name! Use only letters and spaces.\n" << RESET;
	        }
	    } while (!isValidAuthor(author));
	
	    // Edition Validation
		do {
		    cout << "Enter Edition: ";
		    getline(cin, edition);
		    if (!isValidEdition(edition)) {
		        cout << RED << "Invalid Edition! Use only letters, numbers, and spaces (no symbols like ;, #, or @).\n" << RESET;
		    }
		} while (!isValidEdition(edition));
		
		// Publication Validation
		do {
		    cout << "Enter Publication: ";
		    getline(cin, publication);
		    if (!isValidPublication(publication)) {
		        cout << RED << "Invalid Publication! Use only letters, numbers, and spaces.\n" << RESET;
		    }
		} while (!isValidPublication(publication));
	
	
	    books[bookCount].setBook(id, isbn, title, author, edition, publication, category);
	    bookCount++;
	    cout << GREEN << "Book added successfully!\n" << RESET <<endl;
	    
	    cout << "Press any key to continue...";
	    cin.ignore();  // Clear newline from buffer
	    cin.get();     // Wait for key press
	}
	
	//EDIT BOOK
	void editBook() 
	{
	    if (bookCount == 0) {
	        cout << RED << "No Book in the Inventory\n" << RESET << endl;
	        cout << "Press any key to continue...";
			cin.ignore();
			cin.get();
	        return;
	    }
	
	    string id;
	    cout << "Enter Book ID to edit: ";
	    cin >> id;
	    cin.ignore(); 
	
	    for (char &c : id) c = toupper(c); 
	
	    bool found = false; 
	
	    for (int i = 0; i < bookCount; i++) {
	        if (books[i].getId() == id) {
	            found = true;  
	
	            string isbn, title, author, edition, publication;
	
	            // ISBN Validation
	            do {
	                cout << "Enter new ISBN: ";
	                getline(cin, isbn);
	                if (!isValidISBN(isbn)) {
	                    cout << RED << "Invalid ISBN! Only letters and numbers are allowed.\n" << RESET;
	                }
	            } while (!isValidISBN(isbn));
	
	            // Title Input
	            cout << "Enter new Title: ";
	            getline(cin, title);
	
	            // Author Validation
	            do {
	                cout << "Enter new Author: ";
	                getline(cin, author);
	                if (!isValidAuthor(author)) {
	                    cout << RED << "Invalid author name! Only letters and spaces are allowed.\n" << RESET;
	                }
	            } while (!isValidAuthor(author));
	
	            // Edition Validation
	            do {
	                cout << "Enter new Edition: ";
	                getline(cin, edition);
	                if (!isValidEdition(edition)) {
	                    cout << RED << "Invalid edition! Only letters and numbers are allowed (e.g., '12th Edition').\n" << RESET;
	                }
	            } while (!isValidEdition(edition));
	
	            // Publication Validation
	            do {
	                cout << "Enter new Publication: ";
	                getline(cin, publication);
	                if (!isValidPublication(publication)) {
	                    cout << RED << "Invalid publication! Only letters and spaces are allowed.\n" << RESET;
	                }
	            } while (!isValidPublication(publication));
	
	            books[i].editBook(isbn, title, author, edition, publication);
	            cout << GREEN << "Book edited successfully!\n" << RESET;
	            break;  
	        }
	    }
	
	    if (!found) {  
	        cout << RED << "Book not found!\n" << RESET;
	    }
	
	    cout << "Press any key to continue...";
	    cin.ignore();  
	    cin.get();    
	}

	
	
	
	
	//SEARCH BOOK
void searchBook() 
		{
		    if (bookCount == 0) {
		        cout << RED << "No Book in the Inventory\n" << RESET;
		        cout << "Press any key to continue...";
				cin.ignore();
				cin.get();
		        return;
		    }
		
		    string id;
		    cout << "Enter Book ID to search: ";
		    cin >> ws; 
		    getline(cin, id);
		
		    for (char &c : id) c = toupper(c);
		
		    for (int i = 0; i < bookCount; i++) {
		        string bookId = books[i].getId();
		
		        for (char &c : bookId) c = toupper(c);
		
		        if (bookId == id) {
		            cout << GREEN << "Book Found:\n" << RESET;
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		    cout << "| " << left << setw(10) << "ID"
		         << "| " << setw(13) << "ISBN"
		         << "| " << setw(25) << "Title"
		         << "| " << setw(20) << "Author"
		         << "| " << setw(8) << "Edition"
		         << "| " << setw(15) << "Publication"
		         << "| " << setw(12) << "Category"
		         << " |\n";
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		            books[i].displayBook();
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		            return;
		        }
		    }
		
		    cout << RED << "Book not found!\n" << RESET;
		    
		    cout << "Press any key to continue...";
			cin.ignore();
			cin.get();
		}
	
	//DELETE BOOK
	void deleteBook() 
		{
		    if (bookCount == 0) {
		        cout << RED << "No Book in the Inventory\n" << RESET;
		        cout << "Press any key to continue...";
				cin.ignore();
				cin.get();
		        return;
		    }
		
		    string id;
		    cout << "Enter Book ID to delete: ";
		    cin >> ws; 
		    getline(cin, id);
		
		   
		    for (char &c : id) c = toupper(c);
		
		    for (int i = 0; i < bookCount; i++) {
		        string bookId = books[i].getId();
		
		   
		        for (char &c : bookId) c = toupper(c);
		
		        if (bookId == id) 
				{
					cout << GREEN << "Book Found:\n" << RESET;
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		    cout << "| " << left << setw(10) << "ID"
		         << "| " << setw(13) << "ISBN"
		         << "| " << setw(25) << "Title"
		         << "| " << setw(20) << "Author"
		         << "| " << setw(8) << "Edition"
		         << "| " << setw(15) << "Publication"
		         << "| " << setw(12) << "Category"
		         << " |\n";
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		            books[i].displayBook();
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		
		            cout << "Are you sure you want to delete this book? (Y/N): ";	
		            char confirm;
		            cin >> confirm;
		            cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		            if (tolower(confirm) == 'y') {
		   
		                for (int j = i; j < bookCount - 1; j++) {
		                    books[j] = books[j + 1];
		                }
		                bookCount--;
		                cout << GREEN << "Book deleted successfully!\n" << RESET;
		                
		            } 
					else 
					{
		                cout << "Deletion canceled.\n";
		            }
		            cout << "Press any key to continue...";
	    			cin.ignore();  
	    			cin.get();    
	    			return;
		        }
		    }
		
		    cout << RED << "Book not found!\n" << RESET;
		    
		    cout << "Press any key to continue...";
	    	cin.ignore();  
	    	cin.get();    
	}
	
	//VIEWSBOOK BY CATEGORY
	void viewBooksByCategory() 
	{
	    if (bookCount == 0) {
	        cout << RED << "No Book in the Inventory\n" << RESET;
	        cout << "Press any key to continue...";
	        cin.ignore();
	        cin.get();
	        return;
	    }
	
	    string category;
	    bool validInput = false;
	
	    while (!validInput) {
	        cout << "Enter Category (Fiction/Non-fiction): ";
	        cin >> ws;
	        getline(cin, category);
	
	        for (char &c : category) {
	            c = toupper(c);
	        }
	
	        if (!isValidCategory(category)) {
	            cout << RED << "Category not found! Please enter 'Fiction' or 'Non-fiction'.\n" << RESET;
	            continue;
	        }
	
	        bool found = false;
	        for (int i = 0; i < bookCount; i++) {
	            string bookCategory = books[i].getCategory();
	            for (char &c : bookCategory) {
	                c = toupper(c);
	            }
	            if (bookCategory == category) {
	                found = true;
	                break;
	            }
	        }
	
	        if (!found) {
	            cout << RED << "No books found in this category! Try again.\n" << RESET;
	            continue;
	        }
	
	        validInput = true; 
	    }
	
	    // Display the books in the selected category
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		    cout << "| " << left << setw(10) << "ID"
		         << "| " << setw(13) << "ISBN"
		         << "| " << setw(25) << "Title"
		         << "| " << setw(20) << "Author"
		         << "| " << setw(8) << "Edition"
		         << "| " << setw(15) << "Publication"
		         << "| " << setw(12) << "Category"
		         << " |\n";
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
	
	    for (int i = 0; i < bookCount; i++) {
	        string bookCategory = books[i].getCategory();
	        for (char &c : bookCategory) {
	            c = toupper(c);
	        }
	
	        if (bookCategory == category) {
	            books[i].displayBook();
	        }
	    }
	
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
	
	    cout << "Press any key to continue...";
	    cin.ignore();
	    cin.get();
	}

	// VIEWING OF ALL BOOKS
	void viewAllBooks() 
		{
		    if (bookCount == 0) {
		        cout << RED << "No Book in the Inventory\n" << RESET;
		        cout << "Press any key to continue...";
	    		cin.ignore();
	    		cin.get();
		        return;
		    }
		
		    // Print table header
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		    cout << "| " << left << setw(10) << "ID"
		         << "| " << setw(13) << "ISBN"
		         << "| " << setw(25) << "Title"
		         << "| " << setw(20) << "Author"
		         << "| " << setw(8) << "Edition"
		         << "| " << setw(15) << "Publication"
		         << "| " << setw(12) << "Category"
		         << " |\n";
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		
		    // Print each book
		    for (int i = 0; i < bookCount; i++) {
		        books[i].displayBook();
		    }
		
		    // Print footer
		    cout << "+---------------------------------------------------------------------------------------------------------------------+\n";
		    
		    cout << "Press any key to continue...";
		    cin.ignore();
		    cin.get();
		}
	
	};
	
	//MENU
	int getMenuChoice() {
	    string input;
	    int choice;
	    bool validInput = false;
	
	    while (!validInput) 
		{
			cout<<"+---------------------------------------+"<<endl;
			cout<<"    Yabut Learning Mangement System            "<<endl;
			cout<<"+---------------------------------------+"<<endl;
	        cout <<"1 - Add Book\n2 - Edit Book\n3 - Search Book\n4 - Delete Book\n5 - View Books by Category\n6 - View All Books\n7 - Exit";
	        cout<<"\n+---------------------------------------+"<<endl;
			cout<<"Enter your choice: "<< RESET;
	        getline(cin, input);
	
	        bool isValid = true;
	        for (char c : input) {
	            if (!isdigit(c)) { 
	                isValid = false;
	                break;
	            }
	        }
	
	        if (isValid && input.size() == 1) {
	            choice = input[0] - '0'; 
	            if (choice >= 1 && choice <= 7) {
	                validInput = true; 
	            }
	        }
	
	        if (!validInput) {
	            cout << RED << "Invalid input! Please enter a number between 1 and 7.\n" <<RESET <<endl;
	        }
	    }
	
	    return choice;
	}
	
	
	//MAIN MENU
	int main() {
	    Library library;
	    int choice;
	    do {
	        choice = getMenuChoice();
	        switch (choice) {
	            case 1: library.addBook(); break;
	            case 2: library.editBook(); break;
	            case 3: library.searchBook(); break;
	            case 4: library.deleteBook(); break;
	            case 5: library.viewBooksByCategory(); break;
	            case 6: library.viewAllBooks(); break;
	            case 7: cout << "Exiting...\n"; break;
	        }
	    } while (choice != 7);
	    return 0;
	}
	
