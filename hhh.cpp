#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include<algorithm>
using namespace std;

struct Book {
    int id;
     string title;
     string author;
    int year;
};

const  string FILENAME = "library.txt";
int nextId = 1; 

void addBook( vector<Book>& library) {
    Book newBook;
     newBook.id = nextId++; 
     cout << "Enter book title: ";
     getline( cin, newBook.title);
    for (const auto& book : library) {
        if (book.title == newBook.title) {
            cout << "Error: Book with the same title already exists.";
            return;
        }
    }
     cout << "Enter author name: ";
     getline( cin, newBook.author);
     
     cout << "Enter publication year: ";
     cin >> newBook.year;
 
    library.push_back(newBook);

  
     ofstream outFile(FILENAME,  ios::app);
    if (outFile.is_open()) {
        outFile <<newBook.id <<','<<newBook.title << ',' << newBook.author << ',' << newBook.year << '\n';
        outFile.close();
         cout << "Book added successfully!\n";
    } else {
         cerr << "Error opening file for writing.\n";
    }
}

void displayBooks(const  vector<Book>& library) {
    if (library.empty()) {
         cout << "Library is empty.\n";
        return;
    }
     cout <<  setw(20) <<  left << "ID";
     cout <<  setw(20) <<  left << "Title";
     cout <<  setw(20) <<  left << "Author";
     cout <<  setw(10) <<  left << "Year" <<  endl;

    for (const auto& book : library) {
         cout <<  setw(20) << left<< book.id;
         cout <<  setw(20) <<  left << book.title;
         cout <<  setw(20) <<  left << book.author;
         cout <<  setw(10) <<  left << book.year <<  endl;

    }
}

void searchBook(const  vector<Book>& library, const  string& title) {
    for (const auto& book : library) {
        if (book.title == title) {
             cout << "Book found:\n";
             cout <<"ID:"<<book.id <<"\nTitle: " << book.title << "\nAuthor: " << book.author << "\nYear: " << book.year << "\n";
            return;
        }
    }

     cout << "Book not found.\n";
}

void deleteBook(vector<Book>& library, const string& title) {
    auto it = remove_if(library.begin(), library.end(), [&](const Book& book) {
        return book.title == title;
    });

    if (it != library.end()) {
        library.erase(it, library.end());

        // Update the file after removing the book
        ofstream outFile("library.txt");
        for (const auto& book : library) {
            outFile << book.title << ',' << book.author << ',' << book.year << '\n';
        }
        outFile.close();

        cout << "Book deleted successfully!\n";
    } else {
        cout << "Book not found.\n";
    }
}

int main() {
     vector<Book> library;

 
     ifstream inFile("library.txt");
    if (inFile.is_open()) {
        while (!inFile.eof()) {
            Book book;
             inFile >> book.id; // Read the id from the file
            inFile.ignore(); 
             getline(inFile, book.title, ',');
             getline(inFile, book.author, ',');
             
            inFile >> book.year;
            inFile.ignore();

            if (!book.title.empty()) {
                library.push_back(book);
            }
        }
        inFile.close();
    }
     if (!library.empty()) {
        nextId = library.back().id + 1;
    }

    int choice;
    do {
         cout << "\nLibrary Management System\n";
         cout << "1. Add Book\n";
         cout << "2. Display All Books\n";
         cout << "3. Search Book\n";
         cout << "4. Delete Book\n";
         cout<< "5. Quit\n";
         cout << "Enter your choice: ";
         cin >> choice;
         cin.ignore(); 

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                displayBooks(library);
                break;
            case 3: {
                 string searchTitle;
                 cout << "Enter the title to search: ";
                 getline( cin, searchTitle);
                searchBook(library, searchTitle);
                break;
            }
             case 4: {
                string deleteTitle;
                cout << "Enter the title to delete: ";
                getline(cin, deleteTitle);
                deleteBook(library, deleteTitle);
                break;
            }
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                 cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}