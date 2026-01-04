#include "BookFileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
BookFileHandler::BookFileHandler() {
    root = NULL;
}

// Insert book into BST
Book* BookFileHandler::insertBST(Book* node, Book* newBook) {
    if (node == NULL)
        return newBook;

    if (newBook->id < node->id)
        node->left = insertBST(node->left, newBook);
    else
        node->right = insertBST(node->right, newBook);

    return node;
}

// Load books from file
void BookFileHandler::loadBooks() {
    ifstream file("books.txt");
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, author, priceStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, priceStr, ',');

        Book* newBook = new Book;
        newBook->id = stoi(idStr);
        newBook->title = title;
        newBook->author = author;
        newBook->price = stoi(priceStr);
        newBook->left = newBook->right = NULL;

        root = insertBST(root, newBook);
    }

    file.close();
    cout << "Books loaded successfully!" << endl;
}

// Save BST to file (In-order traversal)
void saveInOrder(Book* node, ofstream &file) {
    if (!node) return;
    saveInOrder(node->left, file);
    file << node->id << "," << node->title << "," << node->author << "," << node->price << endl;
    saveInOrder(node->right, file);
}

void BookFileHandler::saveBooks() {
    ofstream file("books.txt");
    if (!file) {
        cout << "Cannot open file!" << endl;
        return;
    }
    saveInOrder(root, file);
    file.close();
    cout << "Books saved successfully!" << endl;
}

// Search by ID
Book* BookFileHandler::searchByID(Book* node, int id) {
    if (!node) return NULLr;
    if (id == node->id) return node;
    if (id < node->id) return searchByID(node->left, id);
    return searchByID(node->right, id);
}

Book* BookFileHandler::searchByID(int id) {
    return searchByID(root, id);
}

// Search by title (simple DFS)
Book* BookFileHandler::searchByTitle(Book* node, string title) {
    if (!node) return NULL;
    if (node->title == title) return node;

    Book* found = searchByTitle(node->left, title);
    if (found) return found;
    return searchByTitle(node->right, title);
}

Book* BookFileHandler::searchByTitle(string title) {
    return searchByTitle(root, title);
}
