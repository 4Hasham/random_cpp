#define START_X 100
#define START_Y 100
#define END_X 500
#define END_Y 500

#include<iostream>
#include<graphics.h>
#include<random>

struct Node;
struct QNode;
class Queue;
class MazeGUI;
class Maze;

struct Node {
    int x, y;
    Node* cons[4]; // cons[4] = { left, top, right, bottom };
    bool wall;
    bool visited;
    bool explored;
    Node(int x, int y, bool wall) {
        this->x = x;
        this->y = y;
        this->wall = wall;
        this->visited = false;
        for (int i = 0; i < 4; ++i) {
            cons[i] = NULL;
        }
    }
};

struct QNode {
    int x, y;
    bool wall;
    Node* cons[4]; // cons[4] = { left, top, right, bottom };
    QNode* next;
    QNode(){}
    QNode(int x, int y) {
        this->x = x;
        this->y = y;
        this->next = NULL;
        this->wall = false;
        for(int i = 0; i < 4; ++i)
             this->cons[i] = NULL;
    }
    QNode(int x, int y, Node* cons[4]) {
        this->x = x;
        this->y = y;
        for(int i = 0; i < 4; ++i)
             this->cons[i] = cons[i];
    }
};

struct N {
    Node* n;
    N *next;
    N() {

    }
    N(Node* n) {
        this->n = n;
        next = NULL;
    }
};

class Queue {
    QNode* head, * tail;
public:
    Queue() {
        head = NULL;
        tail = NULL;
    }
    bool good() {
        QNode* temp = head;
        int count = 0;
        while (temp != NULL) {
            ++count;
            if (temp->next)
                temp = temp->next;
            else
                break;
        }
        return count > 0;
    }
    int left() {
        QNode* temp = head;
        int count = 0;
        while (temp != NULL) {
            ++count;
            if (temp->next)
                temp = temp->next;
            else
                break;
        }
        return count;
    }
    void enqueue(int x, int y) {
        QNode* New = new QNode(x, y);
        if(head == NULL) {
            head = New;
            tail = New;
        }
        else {
            tail->next = New;
            tail = New;
        }
    }
    void enqueue(QNode* New) {
        if(head == NULL) {
            head = New;
            tail = New;
        }
        else {
            tail->next = New;
            tail = New;
        }
    }
    Node* dequeue() {
        QNode* temp = head;
        head = temp->next;
        Node* New = new Node(temp->x, temp->y, temp->wall);
        for(int i = 0; i < 4; ++i)
            New->cons[i] = temp->cons[i];
        delete temp;
        return New;
    }
    void empty() {
        QNode* temp = head;
        QNode* next = new QNode();
        while(temp) {
            next = temp->next;
            delete temp;
            if(next)
                temp = next;
            else
                break;
        }
    }
    void display() {
        QNode* temp = head;
        while(temp) {
            std::cout << temp->x << ", " << temp->y << std::endl;
            if(temp->next)
                temp = temp->next;
            else
                break;  
        }
    }
};

class BFSQ {
    N *head, *tail;
public:
    BFSQ() {
        head = NULL;
        tail = NULL;
    }
    void enqueue(Node* n) {
        N* New = new N(n);
        if(head == NULL) {
            head = New;
            tail = New;
        }
        else {
            tail->next = New;
            tail = New;
        }
    }
    Node* dequeue() {
        N* temp = head;
        head = temp->next;
        Node* ret = temp->n;
        delete temp;
        return ret;
    }
    int left() {
        int count = 0;
        N* temp = head;
        while(temp) {
            ++count;
            temp = temp->next;
        }
        return count;
    }
};

int unit = 20;
Queue *top = new Queue();
Queue *bottom = new Queue();
BFSQ q, w;

class Maze {
    Node* start, * end;
    int a, b;
    bool solved;
public:
    Maze() {
        start = NULL;
        end = NULL;
        a = 0;
        b = 0;
        solved = false;
    }
    void getCellInfo() {
        a = 0;
        if (!top->good() && !bottom->good()) {
            while (a < 10) {
                top->enqueue((a * unit) + START_X, (b * unit) + START_Y);
                bottom->enqueue((a * unit) + START_X, ((b + 1) * unit) + START_Y);
                ++a;
            }
            ++b;
        }
        else {
            while(a < 10) {
                bottom->enqueue((a * unit) + START_X, (b * unit) + START_Y);
                ++a;
            }
        }
        ++b;
    }
    Queue* connect(int i) {
        Queue* temp = new Queue();
        Node* t = NULL;
        Node* b = NULL;
        Node* tp = NULL;
        Node* bp = NULL;
        bool start = false;
        bool end = false;
        while (top->good() && bottom->good()) {
            t = top->dequeue();
            b = bottom->dequeue();
            if (i == 0 && !start) {
                this->start = t;
                start = true;
            }
            if (tp && bp) {
                tp->cons[2] = t;
                bp->cons[2] = b;
            }
            t->cons[0] = tp;
            b->cons[0] = bp;
            t->cons[3] = b;
            b->cons[1] = t;
            QNode* Q = new QNode(b->x, b->y, b->cons);
            temp->enqueue(Q);
            tp = t;
            bp = b;
        }
        if (i == 9 && !end) {
            this->end = b;
            end = true;
        }
        return temp;
    }
    bool validMaze(Node* root) {
        if(root && root != end && !root->wall && !root->visited) {
            root->visited = true;
            if(!solved)
                validMaze(root->cons[2]);
            if(!solved)
                validMaze(root->cons[3]);
            if(!solved)
                validMaze(root->cons[0]);
            if(!solved)
                validMaze(root->cons[1]);
        }
        else if(root == end) {
            solved = true;
        }
        return solved;
    }
    void makeBlocks(Node* root) {
        if(root && !root->visited) {
            root->visited = true;
            //This part is copied from the internet, to generate random number better
            std::random_device random_device;
            std::mt19937 random_engine(random_device());
            std::uniform_int_distribution<int> distribution_0_2(0, 2);
            //
            auto const randomNumber = distribution_0_2(random_engine);
            if(randomNumber > 0 || root == start || root == end)
                root->wall = false;
            else
                root->wall = true;
            makeBlocks(root->cons[0]);
            makeBlocks(root->cons[1]);
            makeBlocks(root->cons[2]);
            makeBlocks(root->cons[3]);
        }
    }
    Node* END() {
        return end;
    }
    Node* PEEK() {
        return start;
    }
    Node* backwardIterate(Node* root) {
        if(root->cons[1]) {
            root->cons[1]->cons[3] = root;
            backwardIterate(root->cons[1]);
        }
        return root;
    }
    void backwardConnect(Node* root) {
        Node* r = backwardIterate(root);
        while(r->cons[0])
            r = backwardIterate(r->cons[0]);
    }
    void depthFirstSearch(Node* root) {
        if(root && !root->visited) {
            root->visited = true;
            std::cout << root->x << ", " << root->y << std::endl;
            depthFirstSearch(root->cons[0]);
            depthFirstSearch(root->cons[1]);
            depthFirstSearch(root->cons[2]);
            depthFirstSearch(root->cons[3]);
        }
        return;
    }
   void unsee(Node* root) {
        if(root && root->visited) {
            root->visited = false;
            unsee(root->cons[0]);
            unsee(root->cons[1]);
            unsee(root->cons[2]);
            unsee(root->cons[3]);
        }
        return;
    }
    void unsolve() {
        solved = false;
    }
    void solve(Node* root) { //This is a maze solver that uses DFS algorithm (not efficient)
        if(root && root != end && !root->wall && !root->visited) {
            root->visited = true;
            if(!solved)
                solve(root->cons[2]);
            if(!solved)
                solve(root->cons[3]);
            if(!solved)
                solve(root->cons[0]);
            if(!solved)
                solve(root->cons[1]);
        }
        else if(root == end) {
            solved = true;
        }
        if(solved) {
            setcolor(GREEN);
            rectangle(root->x, root->y, root->x + unit, root->y + unit);
            floodfill(root->x + 1, root->y + 1, GREEN);
        }   
    }

    // void solve(Node* root) { // This algorithm uses BFS (more efficient)
    //     if(root && !solved) {
    //         q.enqueue(root);
    //         root->visited = true;
    //         if(root == end) {
    //             solved = true;
    //             return;
    //         }
    //         int j;
    //         for(int i = 6; i <= 9; ++i) {
    //             j = i % 4;
    //             if(root->cons[j]) {
    //                 if(!root->cons[j]->visited && !root->cons[j]->wall)
    //                     q.enqueue(root->cons[j]);
    //             }
    //         }
    //         w.enqueue(q.dequeue());
    //         solve(q.dequeue());
    //         std::cout << w.dequeue()->x << ", " << w.dequeue()->y << std::endl;
    //     }
    //     if(solved && root->visited) {
    //         setcolor(GREEN);
    //         rectangle(root->x, root->y, root->x + unit, root->y + unit);
    //         floodfill(root->x + 1, root->y + 1, GREEN);
    //     }
    // }
};

Maze maze;

class MazeGUI {
    int i, j;
public:
    MazeGUI() {
        i = 0;
        j = 0;
    }
    void print(Node* root) {
        if(root && !root->visited) {
            root->visited = true;
            setcolor(WHITE);
            rectangle(root->x, root->y, root->x + unit, root->y + unit);
            if(root->wall) {
                setcolor(RED); 
                rectangle(root->x, root->y, root->x + unit, root->y + unit);
                floodfill(root->x + 1, root->y + 1, WHITE);
            }
            print(root->cons[2]);
            print(root->cons[3]);
            print(root->cons[0]);
            print(root->cons[1]);
        }
        return;
    }
};

MazeGUI mgui;

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    //mgui.populate(START_X, START_Y);
    for (int i = 0; i < 10; ++i) {
        maze.getCellInfo();
        Queue* temp = maze.connect(i);
        top->empty();
        bottom->empty();
        top = temp;
    }
    maze.backwardConnect(maze.END());
    maze.makeBlocks(maze.PEEK());
    maze.unsee(maze.PEEK());
    do {
        maze.unsee(maze.PEEK());
        maze.makeBlocks(maze.PEEK());
        maze.unsee(maze.PEEK());
    } while (!maze.validMaze(maze.PEEK())); 
    maze.unsee(maze.PEEK());
    mgui.print(maze.PEEK());
    maze.unsee(maze.PEEK());
    
    getch();

    maze.unsolve();
    maze.solve(maze.PEEK());

    getch();
    closegraph();
    return 0;
}