#include <iostream>
#include <fstream>
#include <ctype.h>
#include <cstring>

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
    SNode() {
        this->next = NULL;
    }
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
        if(this->getLeft() == 1) {
            HuffNode* ret = new HuffNode(head->c, head->f);
            head = NULL;
            return ret;
        }
        QNode* temp = head;
        QNode* tem = NULL;
        if(temp == NULL) {
            cout << "Tryna access nulllptr";
            return NULL;
        }
        while(temp->next != NULL) {
            tem = temp;
            temp = temp->next;
        }
        HuffNode* t = new HuffNode(temp->c, temp->f);
        tail = tem;
        tail->next = NULL;
        delete temp;
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
        while(temp != NULL) {
            ++count;
            if(temp->next)
                temp = temp->next;
            else
                break;
        }
        return (count > 0);
    }

    int getLeft() {
        int count = 0;
        QNode* temp = head;
        while(temp != NULL) {
            ++count;
            if(temp->next)
                temp = temp->next;
            else
                break;
        }
        return count;
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
    bool good() {
        SNode* temp = top;
        int count = 0;
        while(temp != NULL) {
            ++count;
            if(temp->next)
                temp = temp->next;
        }
        return (count > 0);
    }
    void popA() {
        SNode* temp = top;
        SNode* next = NULL;
        while(temp != NULL) {
            next = temp->next;
            delete temp;
            temp = next;
        }
    }
    void popTill(int i) {
        SNode* next = NULL, *temp = top;
        int j = 0;
        while(j <= i) {
            next = temp->next;
            delete temp;
            temp = next;
            ++j;
        }
    }
    void display() {
        SNode* temp = top;
        while(temp->next != NULL) {
            cout << temp->i;
            temp = temp->next;
        };
        cout << temp->i;
        cout << endl;
    }
};

CodeStack codes[7];

class HuffmanTree {
    HuffNode* root;
    Queue q;
    bool found;
public:
    HuffmanTree(Queue q) {
        root = NULL;
        this->q = q;
        this->found = false;
    } 

    void makeNodes() {  //This function is a naive alternative to constructTree()
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

    void constructTree() { //Better approach
        HuffNode *New = new HuffNode();
        cout << q.getLeft() << "\n";
        HuffNode *left = q.dequeue();
        HuffNode *right = q.dequeue();
        while(q.good()) {
            cout << "Node " << left->c << " (left) and node " << right->c << " (right) added to root node with value: ";
            New->f = left->f + right->f;
            cout << New->f << endl;
            New->c = '$';
            New->left = left;
            New->right = right;
            if(root == NULL) {
                root = New;
            }
            else {
                HuffNode* temp = new HuffNode();
                temp->left = root;
                temp->right = New;
                temp->f = root->f + New->f;
                temp->c = '$';
                root = temp;
                cout << "Node " << root->left->c << " (left) and node " << root->right->c << " (right) added to root node with value: " << root->f << endl;
            }
            New = new HuffNode();
            if(q.getLeft() > 1) {
                left = q.dequeue();
                right = q.dequeue();
            }
            else {
                left = root;
                right = q.dequeue();
                New->f = left->f + right->f;
                New->c = '$';
                New->left = left;
                New->right = right;
                root = New;
            }
        }
        cout << "Node " << root->left->c << " (left) and node " << root->right->c << " (right) added to root node with value: " << root->f << endl;
    }

    HuffNode* PEEK() {
        return root;
    }

    void traverse(HuffNode* r) {
        if(r) {
            cout << r->c << "-" << r->f << "\t";
            if(r->left) {
                traverse(r->left);
            }
            if(r->right) {
                traverse(r->right);
            }
        }
    }

    void find(HuffNode* r, char c, int i) {
        if(r->left && !found) {
            find(r->left, c, i);
            if(found)
                codes[i].push('0');
        }
        if(r->right && !found) {
            find(r->right, c, i);
            if(found)
                codes[i].push('1');
        }
        if(r->c == c) {
            found = true;
        }
        return;
    }

    void unsetFound() {
        this->found = false;
    }
};

int freq[52]; // first frequency is at freq[1]
char alpha[52];

void populate();
void Codes(HuffmanTree);
bool compare(CodeStack, CodeStack);
void translate(char[]);

int main() {
    populate();
    Queue q;
    int i = 1;
    while(i <= 7) {
        q.enqueue(alpha[i - 1], freq[i]);
        ++i;
    }
    HuffmanTree Tree(q);
//    Tree.makeNodes();
    Tree.constructTree();
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
    //translate("011011011");
    // char a[] = "1";
    // translate(a);
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
        t.unsetFound();
    }
}
bool compare(CodeStack s, CodeStack c) {
    while(s.good() && c.good()) {
        if(s.pop() != c.pop())
            return false;
    }
    if(!(c.good() || c.good()))
        return true;
    else
        return false;
}

void translate(char a[]) {
    CodeStack s;
    char output[] = "";
    int _size = strlen(a);
    for(int i = _size-1; i >= 0; --i) {
        s.push(a[i]);
    }
    int j = 0;
    int lastValid = 0;
    CodeStack _s = s;
    CodeStack _c;
    CodeStack temp;
    char c, f;
    _c = codes[j];
    for(int i = 0; i < _size; ++i) {
        c = _s.pop();
        f = _c.pop();
        cout << c << f;
        if(c == f && c != 'f' && f != 'f') {
            temp.push(c);
            if(compare(temp, codes[j])) {
                output[i] = alpha[j];
                j = 0;
                _c = codes[j];
                lastValid = i;
                _s = s;
                _s.popTill(i);
                temp.popA();
            }
        }
        if(c == f && c == 'f') {
            if(compare(temp, codes[j])) {
                output[i] = alpha[j];
                j = 0;
                _c = codes[j];
                lastValid = i;
                _s = s;
                _s.popTill(i);
                temp.popA();
            }
            else {
                cout << "STRANGE # 1\n";
                i = lastValid;
                _s = s;
                _s.popTill(i);
            }
        }
        else {
            if(!compare(temp, codes[j])) {
                cout << "It isn't ";
                codes[j].display();
                ++j;
                _c = codes[j];
                temp.popA();
                i = lastValid;
                _s = s;
                _s.popTill(i); 
            }
            else {
                cout << "STRANGE # 2\n";
                i = lastValid;
            }
        }
        cout << endl;
        temp.display();
    }
    cout << "Output: ";
    for(int i = 0; i < _size; ++i) {
        cout << output[i];
    }
    cout << endl;
}