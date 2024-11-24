#include <iostream>
#include <string>
#include <list>
using namespace std;

const std::string red = "\033[0;1;40;31m";
const std::string green = "\033[0;1;40;32m";
const std::string magenta = "\033[0;1;35;40m";
const std::string endColor = "\033[0m\n";

class Book {
private:
	int bookID;
	std::string title;
	std::string author;
	bool isIssued;
public:

	Book(int bookID, std::string title, std::string author) {
		this->bookID = bookID;
		this->title = title;
		this->author = author;
		isIssued = false;
	}

	void addDetails(std::string title, std::string author) {
		this->title = title;
		this->author = author;
	}

	void display() {
		std::cout << bookID << "\t"
				<< (isIssued == true ? "ISSUED" : "AVLBLE") << "\t" << author
				<< "\t" << title << std::endl;
	}

	bool isAvailable() {
		return isIssued;
	}

	void setIssued(bool issued) {
		this->isIssued = issued;
	}

	int getID() {
		return bookID;
	}

};

class Member {
private:
	int memberID;
	std::string name;
	int issuedBookID;

public:
	Member(int memberID, std::string name) {
		this->memberID = memberID;
		this->name = name;
		issuedBookID = -1;
	}

	//	Add member details,
	void addDetails(std::string name) {
		this->name = name;
	}

	//	display member details
	void display() {
		std::cout << memberID << "\t" << name << "\t"
				<< (issuedBookID == -1 ? "None" : std::to_string(issuedBookID))
				<< std::endl;
	}

	//	issue/return book.
	void setIssued(int issuedBookID) {
		this->issuedBookID = issuedBookID;
	}

	int getIssuedID() {
		return issuedBookID;
	}

	int getID() {
		return memberID;
	}
};

class Library {
	//	Attributes: Collection of Book and Member objects.
private:

	list<Member> members;

	Member* getMember(int memberID) {
		for (auto &member : members) {
			if (member.getID() == memberID) {
				return &member;
			}
		}
		return nullptr;
	}

	Book* getBook(int bookID) {
		for (auto &book : books) {
			if (book.getID() == bookID) {
				return &book;
			}
		}
		return nullptr;
	}

public:
	list<Book> books;
	//	Add a book.
	Book& addBook(std::string name, std::string author) {
		int bookID = books.empty() ? 1 : books.back().getID() + 1;
		Book b(bookID, name, author);
		books.push_back(b);
		return books.back();
	}

	//	Add a member.
	Member& addMember(std::string name) {
		int memberID = members.empty() ? 1 : members.back().getID() + 1;
		Member m(memberID, name);
		members.push_back(m);
		return members.back();
	}

	//	Issue a book (ensure book availability and member eligibility).
	bool issueBook(Book &book, Member &member) {
		Member *m = getMember(member.getID());
		Book *b = getBook(book.getID());
		std::string error;

		if (m == nullptr || b == nullptr) {
			error = "Either book or member not registered!";

		} else if (member.getIssuedID() != -1) {
			error = "Member has a book already!";

		} else if (book.isAvailable()) {
			error = "Book is not available!";

		} else {
			member.setIssued(book.getID());
			book.setIssued(true);
		}

		if (error != "") {
			cout << red << error << endColor;
			return 0;

		} else {
			cout << green << "Success" << endColor;
			return 1;
		}
	}

	//	Return a book.
	bool returnBook(Book &book, Member &member) {
		Member *m = getMember(member.getID());
		Book *b = getBook(book.getID());
		std::string error;

		if (m == nullptr || b == nullptr) {
			error = "Either book or member not registered!";

		} else if (member.getIssuedID() == book.getID()) {
			member.setIssued(-1);
			book.setIssued(false);
		} else if (member.getIssuedID() == -1) {
			error = "Member has no issued book!";

		} else if (book.isAvailable() == false) {
			error = "Book is not issued!";

		} else if (member.getIssuedID() != book.getID()) {
			error = "Member has issued another book!";
		}

		if (error != "") {
			cout << red << error << endColor;
			return 0;

		} else {
			cout << green << "Success" << endColor;
			return 1;
		}

	}
	//	Display all books/members.
	void display() {
		std::cout << "\n\n\033[1;4;35;40mBOOKS\n";
		std::cout << "ID \t STATUS \t AUTHOR \t TITLE \n";
		std::cout << magenta;
		for (auto &book : books) {
			book.display();
		}
		std::cout << endColor;
		std::cout << "\033[1;4;35;40mMEMBERS\n";
		std::cout << "ID \t Name \t ISSUED BOOKS\n";
		std::cout << magenta;
		for (auto &member : members) {
			member.display();
		}
		std::cout << endColor;
	}
};


int main() {
	Library lib;
	Book& b1 = lib.addBook("Wizard of Oz", "L. Frank Baum");
	Book& b2 = lib.addBook("Robinson Crusoe", "Daniel Defoe");
	Book& b3 = lib.addBook("Crime and Punishment", "F. Dostoevsky");

	Member& m1 = lib.addMember("Alice");
	Member& m2 = lib.addMember("Alex");
	Member& m3 = lib.addMember("Bob");
//
	lib.issueBook(b1, m1);
	lib.issueBook(b2, m2);


	lib.display();

	return 0;
}

