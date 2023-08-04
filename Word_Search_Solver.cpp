#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node {
    char ch;
    node* right;
    node* left;
    node* up;
    node* down;
    node* upRight;
    node* upLeft;
    node* downRight;
    node* downLeft;
    
    node(char x) {
        ch = x;
        right = left = up = down = upRight = upLeft = downRight = downLeft = NULL;
    }
};

node* giveHeader(const string& str) {
    node* head = new node(str[0]);
    node* tempHead = head;
    
    for (size_t i = 1; i < str.size(); i++) {
        node* temp = new node(str[i]);
        tempHead->right = temp;
        temp->left = tempHead;
        tempHead = tempHead->right;
    }
    
    return head;
}

void linking(node* headerUp, node* headerDown) {
    while (headerUp != NULL && headerDown != NULL) {
        headerUp->down = headerDown;
        headerDown->up = headerUp;

        if (headerDown->right != NULL) {
            headerUp->downRight = headerDown->right;
            headerDown->right->upLeft = headerUp;
        }

        if (headerUp->right != NULL && headerDown->right == NULL) {
            headerUp->right->downLeft = headerDown;
            headerDown->upRight = headerUp->right;
        }

        if (headerDown->left != NULL) {
            headerUp->downLeft = headerDown->left;
            headerDown->left->upRight = headerUp;
        }

        headerDown = headerDown->right;
        headerUp = headerUp->right;
    }
}

bool search8cells(const string& str, size_t n, node* trv, node* head) {
    if (trv == NULL)
        return false;
    
    if (n == str.size())
        return true;
    
    if (trv->right != NULL) {
        if (trv->right->ch == str[n]) {
            if (search8cells(str, n + 1, trv->right, head))
                return true;
        }
    }
    
    if (trv->left != NULL) {
        if (trv->left->ch == str[n]) {
            if (search8cells(str, n + 1, trv->left, head))
                return true;
        }
    }
    
    if (trv->downRight != NULL) {
        if (trv->downRight->ch == str[n]) {
            if (search8cells(str, n + 1, trv->downRight, head))
                return true;
        }
    }
    
    if (trv->upRight != NULL) {
        if (trv->upRight->ch == str[n]) {
            if (search8cells(str, n + 1, trv->upRight, head))
                return true;
        }
    }
    
    if (trv->down != NULL) {
        if (trv->down->ch == str[n]) {
            if (search8cells(str, n + 1, trv->down, head))
                return true;
        }
    }
    
    if (trv->downLeft != NULL) {
        if (trv->downLeft->ch == str[n]) {
            if (search8cells(str, n + 1, trv->downLeft, head))
                return true;
        }
    }
    
    if (trv->up != NULL) {
        if (trv->up->ch == str[n]) {
            if (search8cells(str, n + 1, trv->up, head))
                return true;
        }
    }
    
    if (trv->upLeft != NULL) {
        if (trv->upLeft->ch == str[n]) {
            if (search8cells(str, n + 1, trv->upLeft, head))
                return true;
        }
    }
    
    return false;
}

bool wordSearch(const string& s, node* head) {
    node* tempHead = head;
    node* trv = head;
    
    while (tempHead != NULL) {
        if (trv->ch == s[0]) {
            if (search8cells(s, 1, trv, head)) {
                return true;
            }
        }
        
        if (trv->right == NULL) {
            trv = tempHead->down;
            tempHead = tempHead->down;
        } else {
            trv = trv->right;
        }
    }
    
    return false;
}

void mesh(node* h) {
    node* h1 = h;
    node* h2 = h->down;
    
    while (h2 != NULL) {
        linking(h1, h2);
        h1 = h2;
        h2 = h2->down;
    }
}

int main() {
    int n;
    cout << "Welcome to Word Search!" << endl;
    cout << "Enter the number of words to be searched: ";
    cin >> n;
    
    vector<string> words(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter word " << i + 1 << ": ";
        cin >> words[i];
    }
    
    node* he = giveHeader(words[0]);
    node* t = he;
    
    for (int i = 1; i < n; i++) {
        node* temp = giveHeader(words[i]);
        t->down = temp;
        t = t->down;
    }
    
    mesh(he);
    
    cout << "Word Search Initialized!" << endl;
    
    while (true) {
        string searchWord;
        cout << "Enter the word to be searched (or 'quit' to exit): ";
        cin >> searchWord;
        
        if (searchWord == "quit")
            break;
        
        bool found = wordSearch(searchWord, he);
        
        if (found)
            cout << "Word \"" << searchWord << "\" Found!" << endl;
        else
            cout << "Word \"" << searchWord << "\" Not Found!" << endl;
    }
    
    cout << "Thank you for using Word Search. Goodbye!" << endl;

    return 0;
}
