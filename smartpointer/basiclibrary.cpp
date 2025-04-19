#include <iostream>
#include <memory>
#include <vector>

class Member
{
    private:
    std::string name;

    public:
    explicit Member(std::string name) : name(name){}

    std::string getName(){return name;}
};

class Book
{
    private:
    std::string title, author;
    
    std::weak_ptr<Member> borrowedBy;

    public:
    explicit Book(std::string title, std::string author) : title(title), author(author){}
    
    std::string getTitle(){return title;}
    std::string getAuthor(){return author;}

    std::weak_ptr<Member> getBorrowedBy()
    {
        return borrowedBy;
    }

    void setBorrowedBy(std::shared_ptr<Member> member)
    {
        borrowedBy = member;
    }

    void resetBorrowedBy()
    {
        borrowedBy.reset();
    }
};

class Library
{
    private:
    std::vector<std::shared_ptr<Book>> books;

    std::vector<std::shared_ptr<Member>> members;

    public:
    void addBook(std::shared_ptr<Book> book)
    {
        books.push_back(book);
    }
    void addMember(std::shared_ptr<Member> member)
    {
        members.push_back(member);
    }
    std::vector<std::shared_ptr<Book>> getBooks()
    {
        return books;
    }
    std::vector<std::shared_ptr<Member>> getMembers()
    {
        return members;
    }

    void borrowBook(int index, std::shared_ptr<Member> member)
    {
        books.at(index)->setBorrowedBy(member);
    }
    void returnBook(std::shared_ptr<Book> book)
    {
        book->resetBorrowedBy();
    }
};

void lobby(Library library);
void lobby2(Library library, std::shared_ptr<Member> member, int index);

void lobby(Library library)
{
    std::cout << "--- WELCOME TO THE SMART POINTER LIBRARY ---\nTITLE | AUTHOR\n\n";
    short int index = 1;
    for(std::shared_ptr<Book> book : library.getBooks())
    {
        std::cout << index << ". " << book->getTitle() << " | " << book->getAuthor() << std::endl;
        index++;
    }

    std::cout << "Type member name\nIf you a new member type 1\n";
    std::string entry;
    std::cin >> entry;
    if(entry != "1")
    {
        for(std::shared_ptr<Member> member : library.getMembers())
        {
            if(entry == member->getName())
            {
                lobby2(library, member, index);
            }
        }
        std::cout << "Wrong name!\n";
        lobby(library);
    }
    else
    {
        std::cout << "-- NEW MEMBER SIGN UP --\n\n";
        std::string name;
        std::cout << "Name: ";
        std::cin >> name;
        std::shared_ptr<Member> newMember(new Member(name));
        library.addMember(newMember);
        lobby2(library, newMember, index);
    }
}

void lobby2(Library library, std::shared_ptr<Member> member, int index)
{
    std::cout << std::endl << "Which book you wanna borrow? type 0 to " << index - 1 << std::endl;
    std::shared_ptr<Book> savedBook;
    for(std::shared_ptr<Book> book : library.getBooks())
    {
        if(book->getBorrowedBy().lock() == member)
        {
            savedBook = book;
        }
    }
    if(savedBook)
    {
        std::cout << "Or type -1 if you wanna return your " << savedBook->getTitle() << " | " << savedBook->getAuthor() << " book:\n";
    }
    short int request = 0;
    std::cin >> request;
    if(request < index && request > 0)
    {
        if(library.getBooks().at(request-1)->getBorrowedBy().expired())
        {
            library.getBooks().at(request-1)->setBorrowedBy(member);
            lobby2(library, member, index);
        }
        else
        {
            std::cout << "This book already taken!\n";
            lobby2(library, member, index);
        }
    }
    else if(request == -1)
    {
        savedBook->resetBorrowedBy();
        lobby2(library, member, index);
    }
    else
    {
        lobby2(library, member, index);
    }
}

int main()
{
    //ADDING BOOKS TO LIBRARY
    std::shared_ptr<Book> book1(new Book((std::string)"Da Vinci Codes", "Dan Brown")), 
    book2(new Book((std::string)"Twenty Thousand Leagues Under the Sea", "Jules Verne")), 
    book3(new Book((std::string)"Pet Sematary", "Stephen King"));

    Library library;
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    //ADDING COMPLETED

    lobby(library);

    return 0;
}
