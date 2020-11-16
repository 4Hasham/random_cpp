#include<iostream>
#include<string>
#include<fstream>
using namespace std;
 
// Node Structure
struct node
{
​node*left;
​node*right;
​node*next;
​char character;
​int frequency;
​node()
​{
​​left = NULL;
​​right = NULL;
​​next = NULL;
​​character = '*';
​​frequency = 0;
​}
 
};
 
// Huffman Class
class huffman
{
private:
​node*front;
​node*rear;
public:
 
​// Constructor
​huffman()
​{
​​front = NULL;
​​rear = NULL;
​}
​int Frequency(string data, char a)
​{
​​int count = 0;
​​for (int i = 0; i < data.size(); i++)
​​{
​​​if (data[i] == a)
​​​{
​​​​count++;
​​​}
​​}
​​return count;
​}
 
​void initialization(string data)
​{
​​char a = data[0];
​​int frequency = Frequency(data, a);
​​enqueue(a, frequency);
 
​​for (int i = 1; i < data.size(); i++)
​​{
​​​if (a != data[i])
​​​{
​​​​a = data[i];
​​​​frequency = Frequency(data, a);
​​​​if (!duplicate(a))
​​​​{
​​​​​enqueue(a, frequency);
 
​​​​}
 
​​​}
 
​​}
 
​}
 
​// Move  elements into the queue
​void enqueue(char a, int frequency)
​{
​​node*n = new node;
​​n->character = a;
​​n->frequency = frequency;
​​if (rear == NULL)
​​{
​​​front = rear = n;
​​}
​​else
​​{
​​​rear->next = n;
​​​rear = n;
​​​n->next = front;
​​}
​}
 
​// Display the queue
​void display()
​{
​​node*current = front;
​​while (current != rear)
​​{
​​​cout << current->character << endl;
​​​cout << current->frequency << endl;
​​​current = current->next;
​​}
​​cout << current->character << endl;
​​cout << current->frequency << endl;
​}
 
​// Check if the eleemnt is already in the queue or not
​bool duplicate(char a)
​{
​​node*current = front;
​​node*prev = NULL;
​​bool duplicate = false;
​​while (prev != rear)
​​{
​​​if (current->character == a)
​​​{
​​​​duplicate = true;
 
​​​}
​​​prev = current;
​​​current = current->next;
 
​​}
 
​​return duplicate;
​}
 
​// Frmation of binary tree
​node* tree_formation(huffman q)
​{
​​node*n = new node;
​​if (front->next != rear)
​​{
​​​node*temp1 = dequeue();
​​​node*temp2 = dequeue();
​​​int frequency = temp1->frequency + temp2->frequency;
 
​​​n->frequency = frequency;
​​​n->left = temp1;
​​​n->right = temp2;
 
​​​rear->next = n;
​​​rear = n;
​​​n->next = front;
​​​this->sort();
​​​return front;
​​}
​​{
​​​int frequency = front->frequency + rear->frequency;
​​​n->frequency = frequency;
​​​n->left = front;
​​​n->right = rear;
​​​front->next = NULL;
​​​rear->next = NULL;
​​​return n;
​​}
 
 
 
 
 
 
​}
 
 
​//Sorting of the queue
​void sort()
​{
 
​​int count1 = count();     // Number of elements in the list
​​rear->next = NULL;
​​for (int j = 0; j < count1 - 1; j++)
​​{
 
​​​int count = 0;          // Variable to determine whether the first node is in access or node
​​​node*current = this->front->next;    // pointer for current node
​​​node*prev = this->front;             // pointer for previous node
​​​node*temp3 = NULL;
​​​node*temp1 = NULL;               //poniter to hold element next to current
​​​temp3 = this->front;                 // initializing temp3 to head of the list
​​​while (prev->next != NULL)
​​​{
​​​​temp1 = current->next;       // make temp1 ponits towards the node next to current
 
​​​​if (prev->frequency > current->frequency)      // Check whether to swap nodes or not
​​​​{
 
​​​​​if (count == 0)                  // Check for the first element
​​​​​{
​​​​​​temp3 = current;            // Pointer holding node to make linkages
​​​​​​prev->next = current->next; // Swap of the node
​​​​​​current->next = prev;
​​​​​​this->front = current;          // Correcting the head direction after swap
​​​​​​current = temp1;            // move the current forward
​​​​​}
​​​​​else
​​​​​{
 
​​​​​​temp3->next = current;     // make next of temp3 point toward current
​​​​​​prev->next = current->next;
​​​​​​current->next = prev;
​​​​​​current = temp1;
​​​​​​temp3 = temp3->next;      // make temp3 to point current
 
​​​​​}
 
 
​​​​}
​​​​else                             // If swap is not required
​​​​{
​​​​​prev = current;             // make precv point toward next node
​​​​​if (temp3->next != prev)
​​​​​​temp3 = temp3->next;   // make temp3 point toward next node
​​​​​current = temp1;           // make current point towards next node
 
​​​​}
​​​​count++;
​​​}
 
​​}
 
​​node*current = front;
​​while (current->next != NULL)
​​{
​​​current = current->next;
​​}
​​rear = current;
​​current->next = front;
 
​}
 
 
​// Check the number of elements in the queue
​int count()
​{
​​node*current = front;
​​int count = 0;
​​if (current != NULL)
​​{
​​​while (current != rear)
​​​{
​​​​count++;
​​​​current = current->next;
​​​}
​​}
​​return count;
 
​}
 
​// Function to get the tree root
​node* tree(huffman q)
​{
​​node*n = new node;
​​while (front->next != rear)
​​{
​​​n = tree_formation(q);
​​}
​​n = tree_formation(q);
​​return n;
 
​}
 
​// Dequeue an element from the queue
​node* dequeue()
​{
​​node*temp = NULL;
 
 
​​temp = front;
​​front = front->next;
​​temp->next = NULL;
 
 
​​return temp;
​}
 
​//
​
 
};
 
// Linked list implementation
struct node1
{
​char data;
​string code;
​node1 *next;
 
​node1()
​{
​​data = '*';
​​next = NULL;
​​code = "";
​}
};
 
class list
{
private:
​node1 *head;
public:
 
​list()
​{
​​head = NULL;
​}
 
​bool is_empty()
​{
​​if (head == NULL)
​​{
​​​return 0;
​​}
​​else {
​​​return 1;
​​}
​}
​void insert_end(char data, string code)
​{
​​node1*n = new node1;
​​n->data = data;
​​n->code = code;
​​n->next = NULL;
 
​​if (head == NULL)
​​{
​​​head = n;
​​}
​​else
​​{
​​​node1*current = head;
​​​while (current->next != NULL)
​​​{
​​​​current = current->next;
​​​};
​​​current->next = n;
 
​​}
 
​}
 
​int Count()
​{
​​node1 *current = head;
​​int count = 1;
​​while (current != NULL)
​​{
​​​current = current->next;
​​​count++;
​​}
​​return count;
​}
 
​void display()
​{
​​node1 *current = head;
​​while (current != NULL)
​​{
​​​cout << current->data << ",";
​​​cout << "        " << current->code << endl;
​​​current = current->next;
​​};
​}
 
​string serch_by_data(char data)
​{
​​node1*current = head;
​​int count = Count();
​​int incre = 0;
​​while (current->data != data&&count>incre)
​​{
​​​current = current->next;
​​​incre++;
​​}
​​if (count > incre)
​​{
​​​return current->code;
​​}
​​else
​​{
​​​cout << "Index out of bound!" << endl;
​​}
​}
​node1*get_head()
​{
​​return head;
​}
 
 
 
};
 
// Funciton to generate coode for a given string and decode it
void pre_order(node*root, list&l);           // Pre_order traversal to generate code
string code_generation(string b, node1*v);   // Converting given string to biary code
void decode(node*n, string s);               // decoding a given code
string readfile(string filename);            // Reading a file
string convert_to_code(int f);              
string readcode(string filename);            
string binary_equivalent(string s);          // Genearte ASCII character from string nad insert in the text file
string restore(string s);                    // Restore a string from the code
 
int main()
{
​huffman h;
​string scode = "";
​list l;
​char b;
​int u = 0;
​string filename = "test.txt";
​string s = readfile(filename);
​s.pop_back();
​h.initialization(s);
​node*n = h.tree(h);
​pre_order(n, l);
​scode=code_generation(s, l.get_head());
​ofstream outfile("code.txt");
​for (int i = 0; i < scode.size();i++)
​{
​​outfile.put(scode[i]);
​}
​
​outfile.close();
​s=readcode("code.txt");
​decode(n, s);
 
}
string code = "";
void pre_order(node*root, list&l)
{
 
​if (root->left == NULL)
​{
​​l.insert_end(root->character, code);
​}
​else
​{
 
​​if (root->left != NULL)
​​{
​​​code = code + "0";
 
​​}
​​pre_order(root->left, l);
​​{
 
​​​code.pop_back();
​​​if (root->right != NULL)
​​​{
​​​​code = code + "1";
​​​}
 
​​​pre_order(root->right, l);
​​​code.pop_back();
​​}
 
 
​}
}
 
 
string code_generation(string b, node1*v)
{
​string code = "";
​string scode="";
​node1*current = new node1;
​for (int i = 0; i < b.size(); i++)
​{
​​current = v;
​​while (current != NULL)
​​{
​​​if (current->data == b[i])
​​​{
​​​​code = code + current->code;
 
​​​}
​​​current = current->next;
​​}
​}
​
​scode=binary_equivalent(code);
​
​return scode;
 
}
 
void decode(node*n, string s)
{
​node*current = new node;
​current = n;
​string text = "";
​for (int i = 0; i < s.size(); i++)
​{
​​if (s[i] == '0')
​​{
​​​current = current->left;
​​}
​​if (s[i] == '1')
​​{
​​​current = current->right;
​​}
​​if (current->left == NULL&current->right == NULL)
​​{
​​​text = text + current->character;
​​​current = n;
​​}
 
​}
​cout << text << endl;
}
 
string readfile(string filename)
{
​char b;
​string s;
​ifstream infile(filename);
​while (!infile.eof())
​{
​​infile.get(b);
​​s = s + b;
​}
​
​cout << s << endl;
​return s;
}
 
string readcode(string filename)
{
​string s;
​string h;
​char b;
​ifstream infile(filename);
​
​​while (infile)
​​{
​​​infile.get(b);
​​​h = h + b;
​​}
 
​​cout << h << endl;
​​h.pop_back();
​​h=restore(h);
​​
​
​return h;
 
}
 
string binary_equivalent(string s)
{
 
​long int*temp = NULL;
​string j;
​temp = new long int[s.size()];
​long int*temp1 = NULL;
​temp1 = temp;
​long int code = 0;
​int mm = s.size() % 7;
​if (mm != 0)
​{
​​mm = 7 - mm;
​}
​for (int i = 1; i <= mm; i++)
​{
​​s = "0" + s;
​}
​j = to_string(mm) + j;
 
​for (int i = 0; i < s.size(); i++)
​{
​​
​​*temp1 = s[i] - '0';
​​temp1++;
​​
​}
​int y = 6;
​for (int i = 0; i <s.size(); i++)
​{
​​
​​
​​​code = code + ((*temp)*pow(2, y));
​​​temp++;
​​​y--;
​​
​​​if ((i+1)%7==0)
​​{
 
​​​j = j + char(code);
​​​code = 0;
​​​y = 6;
​​}
​​
​​
​}
​return j;
}
 
string restore(string s)
{
​cout << s << endl;
​string h;
​string y;
​string k;
​for (int i = 1; i < s.size(); i++)
​{
​​int j = s[i];
​​h = "";
​​while (j>0)
​​{
​​​if (j % 2 == 0)
​​​{
​​​​h = h + '0';
​​​}
​​​if (j % 2 == 1)
​​​{
​​​​h = h + '1';
​​​}
​​​j = j / 2;
​​}
 
​​int zero_insertion = 7 - h.size();
​​for (int i = 1; i <= zero_insertion; i++)
​​{
​​​h = h + '0';
​​}
​​for (int i = h.size() - 1; i >= 0; i--)
​​{
​​​y = y + h[i];
​​}
​​k = k + y;
​​y = "";
​​cout << k << endl;
​}
​string original;
​int p = int(s[0]) - '0';
​for (int i = p ; i < k.size(); i++)
​original = original + k[i];
​
​return original;
}