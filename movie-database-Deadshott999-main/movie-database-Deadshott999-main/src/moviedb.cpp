#include "moviedb.h"
#include "csv.h"
#include <stdexcept>


using namespace std;

MovieDatabase::MovieDatabase(): head(new Node(Movie("", 0))), tail(new Node(Movie("", 0))), cursor(nullptr), size(0)
{
    head->next = tail;
    tail->previous = head;
    // cursor = nullptr;
    // transactionStart = nullptr;
    // inTransaction = false;
}

MovieDatabase::~MovieDatabase()
{
    Node* current = head->next;
    while(current != tail){
        Node* next = current->next;
        delete current;
        current = next;
    }
    delete head;
    delete tail;
}

bool MovieDatabase::isEmpty() const
{
    return size == 0;
}

int MovieDatabase::getSize() const 
{
    return size;
}

const Movie& MovieDatabase::getFront() const
{
    if (isEmpty()){
        throw runtime_error("Database is empty\n");
    }
    return head->next->movieData;
}

const Movie& MovieDatabase::getBack() const
{
    if (isEmpty()){
        throw runtime_error("Database is empty\n");
    }
    return tail->previous->movieData;
}

void MovieDatabase::addFront(const Movie& movie)
{
   Node* newNode = new Node(movie);

    newNode->next = head->next;
    newNode->previous = head;
    head->next->previous = newNode;
    head->next = newNode;
    size++;
}

void MovieDatabase::addBack(const Movie& movie)
{
    Node* newNode = new Node(movie);
    newNode->next = tail;
    newNode->previous = tail->previous;
    tail->previous->next = newNode;
    tail->previous = newNode;
    
    size++;
}

void MovieDatabase::removeFront()
{
    if(isEmpty()){
        throw runtime_error("Database is empty.\n");
    }
    Node* front = head->next;
    head->next = front->next;
    front->next->previous = head;
    delete front;
    size--;
}

void MovieDatabase::removeBack()
{
    if(isEmpty()){
        throw runtime_error("Database is empty.\n");
    }
    Node* back = tail->previous;
    tail->previous = back->previous;
    back->previous->next = tail;
    delete back;
    size--;
}

void MovieDatabase::append(const MovieDatabase& otherDB, function<bool(const Movie&)> predicate)
{
    Node* current = otherDB.head;
    while(current != nullptr){
        if(predicate(current->movieData)){
            addBack(current->movieData);
        }
        current = current->next;
    }
}

void MovieDatabase::load(const std::string& filename)
{
    io::CSVReader<2> in(filename);
    in.read_header(io::ignore_extra_column, "Title", "Year");

    string title;
    int year;
    while(in.read_row(title, year)){
        addBack(Movie(title, year));
        
    }
    cursor = head->next;
}

void MovieDatabase::beginTransaction()
{
    
    cursor = head;
}

void MovieDatabase::next()
{
    if(cursor == nullptr){
        throw runtime_error("Transaction not started.\n");
    }
    if(cursor == tail){
        throw runtime_error("Cursor is already pointing to the last element.\n");
    }
    cursor = cursor->next;
}
// void MovieDatabase::next(int i)
// {
//     if(cursor == nullptr){
//         throw runtime_error("Transactions haven't started yet.\n");
//     }
//     if(cursor->next == nullptr){
//         throw runtime_error("Cursor is already pointing to the last element.\n");
//     }
//     for(int index = 0; index < i - 1 && cursor->next != nullptr; index++){
//         cursor = cursor->next;
//     }
// }

void MovieDatabase::previous()
{
    if (cursor == nullptr){
        throw runtime_error("Transactions haven't started.\n");
    }
    if (cursor == head){
        throw runtime_error("Cursor is already before the first element.\n");
    }
    cursor = cursor->previous;
}

void MovieDatabase::insert(const Movie& movie)
{
    if(cursor == nullptr){
        throw runtime_error("Transaction not started.\n");
    }
    if(cursor == tail){
        throw runtime_error("Cursor is at an invalid location.\n");
    }
    Node* newNode = new Node(movie);
    newNode->next = cursor->next;
    newNode->previous = cursor;
    cursor->next->previous = newNode;
    cursor->next = newNode;
    cursor = newNode;
    size++;
}

void MovieDatabase::remove()
{
    if (cursor == nullptr){
        throw runtime_error("Transactions haven't started.\n");
    }
    if (cursor == head || cursor == tail){
        throw runtime_error("Cannot remove head or tail.\n");
    }
    Node* toRemove = cursor;
    cursor->previous->next = cursor->next;
    cursor->next->previous = cursor->previous;
    cursor = cursor->next;
    delete toRemove;
    size--;
}

const Movie& MovieDatabase::getCurrent() const
{
    if (cursor == nullptr){
        throw runtime_error("Transactions haven't started.\n");
    }
    if (cursor == head || cursor == tail){
        throw runtime_error("Cursor not pointing to a valid movie.\n");
    }
    return cursor->movieData;
}

void MovieDatabase::endTransaction()
{
    cursor = nullptr;
}
