#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

struct HuffNode {
    char c;
    int f;
    HuffNode* left;
    HuffNode* right;
    HuffNode() {
        
    };
    HuffNode(char c, int f) {
        this->c = c;
        this->f = f;
        this->left = NULL;
        this->right = NULL;
    }
};

struct QNode {
    char c;
    int f;
    QNode* next;
    QNode(char c, int f) {
        this->c = c;
        this->f = f;
        this->next = NULL;
    }
};

struct SNode {
    char i;
    SNode* next;
    SNode(char i) {
        this->i = i;
        this->next = NULL;
    }
};

class Queue {
    QNode* head;
    QNode* tail;
public:
    Queue() {
        head = NULL;
        tail = NULL;
    }

    void enqueue(char c, int f) {
        QNode* New = new QNode(c, f);
        if(head == NULL) {
            head = New;
            tail = New;
        }
        else {
            QNode* temp = head;
            while(temp->next != NULL && temp->next->f >= f) {
                temp = temp->next;
            }
            New->next = temp->next;
            temp->next = New;
        }
        QNode* t = head;
        while(t->next != NULL) {
            t = t->next;
        }
        tail = t;
        tail->next = NULL;
    }

    HuffNode* dequeue() {
        QNode* temp = head;
        QNode* tem;
        while(temp->next != NULL) {
      //      cout << temp->c << "\t";
            tem = temp;
            temp = temp->next;
        }
        HuffNode* t = new HuffNode(temp->c, temp->f);
        tail = tem;
        tail->next = NULL;
        delete temp;
       // cout << t->c << "\t";
        return t;
    }

    void display() {
        QNode* temp = head;
        while(temp->next != NULL) {
            cout << temp->c << "-" << temp->f << "\t";
            temp = temp->next;
        }
        cout << temp->c << "-" << temp->f << "\t";
    }

    bool good() {
        int count = 0;
        QNode* temp = head;
        while(temp != NULL && temp->f > 0) {
            ++count;
            if(temp->next && temp->next->f > 0)
                temp = temp->next;
            else
                break;
        }
        if(count > 0) {
            return true;
        }
        else {
            return false;
        }
    }
};

class CodeStack {
    SNode* top;
public:
    CodeStack() {
        top = NULL;
    }
    void push(char i) {
        SNode* New = new SNode(i);
        if(top == NULL) {
            top = New;
        }
        else {
            New->next = top;
            top = New;
        }
    }
    char pop() {
        if(top != NULL) {
            SNode* temp = top;
            top = top->next;
            temp->next = NULL;
            char i = temp->i;
            delete temp;
            return i;
        }
        else {
            cout << "Stack Underflow!\n";
            return 'f';
        }
    }
    void display() {
        SNode* temp = top;
        while(temp->next != NULL) {
            cout << temp->i;
            temp = temp->next;
        };
        cout << endl;
    }
};

CodeStack codes[7];

class HuffmanTree {
    HuffNode* root;
    Queue q;
public:
    HuffmanTree(Queue q) {
        root = NULL;
        this->q = q;
    }

    void makeNodes() {
        HuffNode *New = new HuffNode();
        HuffNode *left = q.dequeue();
        HuffNode *right = q.dequeue();
        while (q.good()) {
            New = new HuffNode();
            cout << "Node " << left->c << " (left) and node " << right->c << " (right) added to root node with value: ";
            New->f = left->f + right->f;
            cout << New->f << endl;
            New->c = '$';
            New->left = left;
            New->right = right;
            root = New;
            left = root;
            right = q.dequeue();
        }
        New = new HuffNode();
        cout << "Node " << left->c << " (left) and node" << right->c << " (right) added to root node with value: ";
        New->f = left->f + right->f;
        cout << New->f << endl;
        New->c = '$';
        New->left = left;
        New->right = right;
        root = New;
    }

    HuffNode* PEEK() {
        return root;
    }

    void traverse(HuffNode* r) {
        if(r) {
            if(r->left) {
                traverse(r->left);
            }
            cout << r->f << "\t";
            if(r->right) {
                traverse(r->right);
            }
        }
    }

    void find(HuffNode* r, char c, int i) {
        bool found = false;
        if(r != NULL) {
            if(r->left && !found) {
                find(r->left, c, i);
                codes[i].push('0');
            }
            if(r->right && !found) {
                find(r->right, c, i);
                codes[i].push('1');
            }
            
            if(r->c == c)
                found = true;
        }
        return;
    }
};

int freq[52]; // first frequency is at freq[1]
char alpha[52];

void populate();
void Codes(HuffmanTree);

int main() {
    populate();
    Queue q;
    int i = 1;
    while(i <= 7) {
        q.enqueue(alpha[i - 1], freq[i]);
        ++i;
    }
    HuffmanTree Tree(q);
    Tree.makeNodes();
    cout << endl;
    cout << "Simple Inorder Traversal: " << endl;
    Tree.traverse(Tree.PEEK());
    cout << endl;
    Codes(Tree);
    cout << "Dispalying Codes: \n";
    for(int i = 0; i < 7; ++i) {
        cout << "Code for " << alpha[i] << ": \n";
        codes[i].display();
        cout << endl << endl;
    }
    cout << "\n";
    return 0;
}

void populate() {
    for(int i = 0; i < 52; i++) {
        freq[i] = 0;
    }
    char c[52];
    ifstream file;
    file.open("a4-1.txt", ios::in);
    file.read(c, 100);
    file.close();
    int k = 0;
    int i = 0;
    int inc = 0;
    int ii = 0;
    int f = 10;
    while(i < 52) {
        if(c[i] >= '0' && c[i] <= '9') {
            inc += f*(int(c[i] - '0'));
            f = f / 10;
            ++ii;
        }
        if(c[i] == '\n') {
            if(ii == 1) {
                freq[k] = inc / 10;
            }
            else {
                freq[k] = inc;
            }
            f = 10;
            inc = 0;
            ii = 0;
            ++k; 
        }
        ++i;
    }
    i = 0;
    k = 0;
    while(i < 52) {
        if(isalpha(c[i])) {
            alpha[k] = c[i];
            ++k;
        }
        ++i;
    }
}

void Codes(HuffmanTree t) {
    for(int i = 0; i < 7; ++i) {
        t.find(t.PEEK(), alpha[i], i);
    }
}