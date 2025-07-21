#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <cctype>

using namespace std;

// node class
	

// implement a link list for storing words
class Linked_List
{
	class Node
	{
	public:
		char letter;
		Node* next;
		Node()
		{
			next = NULL;
			letter = '\0';
		}
	};
	
	Node* head;
	Node* tail;
	
public:
	Linked_List()
	{
		head = tail = NULL;
	}
	
	~ Linked_List()
	{
		if (head != NULL)
		{
			for (Node *ptr = head; ptr != NULL; ptr = head)
			{
				head = head->next;
				delete ptr;
			}
			head = NULL;
		}
	}
	
	// insert at end
	void insert(char l)
	{
		Node *temp = new Node;
		temp->letter = l;
		temp->next = NULL;
			
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	
	void make_NULL()
	{
		if (head != NULL)
		{
			for (Node *ptr = head; ptr != NULL; ptr = head)
			{
				head = head->next;
				delete ptr;
			}
			head = NULL;
		}
	}
	
	char remove_from_end()
	{
		char letter = '\0';
		for (Node *ptr = head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->next == tail)
			{
				Node *temp = tail;
				tail = ptr;
				letter = temp->letter;
				delete temp;
				break;
			}
		}
		
		return letter;
	}
	
	char remove(char l)
	{
		char removed;
		
		// if on head
		
		// if on tail
		
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{			
			if (ptr->next->letter == l)
			{
				Node *temp = ptr->next;
				removed = temp->letter;
				
				ptr->next = ptr->next->next;
				delete temp;
				
				//cout<<"Node removed"<<endl;
				break;
			}
		}
		
		return removed;
	}
};

// implement a circular queue through array
template <typename T>
class Queue
{
    int capacity = 45; // longest word in english
    T *word;
    int front, rear;

public:
    Queue()
    {
        word = new T [capacity];
        front = rear = -1;
    }

    ~ Queue()
    {
		delete []word;
    }

    void enqueue(T letter)
    {
        if (rear == -1)
        {
            front = rear = 0;
        }

        else if (is_full())
        {
            cout<<"Queue Capacity Reached"<<endl;
            return;
        }

        else
        {
            rear = (rear + 1) % capacity;
        }

        word[rear] = letter;
    }
    
    void remove_rear()
    {
    	rear = (rear - 1 + capacity) % capacity;
    }

    T dequeue()
    {
    
        if (front == -1)
        {
        	T temp = ' ';
            cout<<"Queue is empty"<<endl;
            return temp;
        }

        else
        {
            T temp = word[front];
            
            if (front == rear)
            {
            	front = -1;
            	rear = -1;
            }
            else
            {
            	front = (front + 1) % capacity;
            }
            
            return temp;
        }
    }

    T top() const
    {
        return word[front];
    }

    bool is_full()
    {
        if ((rear+1)%capacity == front)
        {
            return true;
        }

        return false;
    }

    bool is_empty()
    {
        if (front == -1)
            return true;

        return false;
    }
};

// avl tree for dictionary load and store
class AVL
{
    class AVL_Node
    {
        public:
            string word;
            int height; // calculated by taking max height using left and right subtree + 1
            AVL_Node *right;
            AVL_Node *left;

            AVL_Node()
            {
                right = left = NULL;
                height = 0;
            }
    };

    AVL_Node *root;
    
public:

    AVL()
    {
        root = NULL;
    }

    ~ AVL()
    {
		root = delete_AVL(root);
    }

	AVL_Node* get_root() 
	{
		if (this->root == nullptr)
		    cout << "Root is NULL" << endl;

		return this->root;
	}

    // load
    void load(string file_path)
    {
        ifstream dictionary;
        dictionary.open(file_path);
        if(!dictionary)
        {
            cout<<"Could not open file"<<endl;
            return;
        }

        string line = "\0";
        while (getline(dictionary, line))
        {
        	line.erase(line.find_last_not_of(" \n\r\t") + 1);
            this->root = insert(this->root, line);
            line = "\0";
        }

        return;
    }

    AVL_Node* insert(AVL_Node* root, string word)
    {
        if (root == NULL)
        {
            AVL_Node* temp = new AVL_Node;
            temp->word = word;
            temp->right = temp->left = NULL;
            root = temp;
            return root;
        }

    
        if (toLowerCase(word) < toLowerCase(root->word))
        {
            root->left = insert(root->left, word);
            //cout<<"left called "<<word<<endl;
        }
        else if (toLowerCase(word) > toLowerCase(root->word))
        {
            root->right = insert(root->right, word);
            //cout<<"right called "<<word<<endl;
        }
        else
        {
            //cout<<"DUPLICATE DATA INSERTION ATTEMPTED! "<<root->word<<endl;
        }
        
        //cout<<"Before: "<<root->word<<endl;
        //cout<<root->height<<endl;

        // height calculate for root after insertion
        root = calculate_height(root);
        

        // balance after height update
        root = balance(root);

        //cout<<"After: "<<root->word<<endl;
        //cout<<root->height<<endl;

        return root;
    }
    
	// Function to convert string to lowercase
	string toLowerCase(string &str) 
	{
		for (int count = 0; str[count] != '\0'; count++)
		{
			if (str[count] >= 'A' && str[count] <= 'Z')
			{
				str[count] += 32;
			}
		}
		return str;
	}

    AVL_Node* balance(AVL_Node* root)
    {

        int balance_factor = 0;
        if (root->left && root->right)
            balance_factor = root->left->height - root->right->height;
        else if (root->left)
            balance_factor = root->height;
        else if (root->right)
            balance_factor = (root->height*-1);
        else 
            balance_factor = 0;
            
        //cout<<"Balance Factor: "<<balance_factor<<endl;

        // right rotation
        if (balance_factor > 1)
        {
            if (root->left->left && root->left->right)
            {
                if (root->left->left->height - root->left->right->height >= 0)
                {
                    root = rightRotate(root);
                    //cout<<"RIGHT"<<endl;
                }
            }
            else if (root->left->left)
            {
                root = rightRotate(root);
                //cout<<"RIGHT"<<endl;
            }
            else if(root->left->right)
            {
                root = leftRightRotate(root);
                //cout<<"LEFTRIGHT"<<endl;
            }
        }

        // left rotation
        else if (balance_factor < -1)
        {
            if (root->right->left && root->right->right)
            {
                if (root->right->left->height - root->right->right->height <= 0)
                {
                    root = leftRotate(root);
                    //cout<<"LEFT"<<endl;
                }
            }
            else if (root->right->left)
            {
                root = rightLeftRotate(root);
                //cout<<"RIGHTLEFT"<<endl;
            }
            
            else if(root->right->right)
            {
                root = leftRotate(root);
                //cout<<"LEFT"<<endl;
            }
        }

        return root;
    }

    AVL_Node* rightRotate(AVL_Node*& root)
    {
        AVL_Node* temp = root->left;
        root->left = temp->right;
        temp->right = root;

        root = calculate_height(root);
        temp = calculate_height(temp);

        return temp;
    }

    AVL_Node* leftRightRotate(AVL_Node*& root)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);

        return root;
    }

    AVL_Node* leftRotate(AVL_Node*& root)
    {
        AVL_Node* temp = root->right;
        root->right = temp->left;
        temp->left = root;

        root = calculate_height(root);
        temp = calculate_height(temp);

        return temp;
    }

    AVL_Node* rightLeftRotate(AVL_Node*& root)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);

        return root;
    }

    AVL_Node* calculate_height(AVL_Node* root)
    {
        if (root->left && root->right)
        {
        	//cout<<"left and right"<<endl;
            root->height = max(root->left->height, root->right->height) + 1;
            
        }
        else if (root->left != NULL)
        {
        	//cout<<"left"<<endl;
            root->height = root->left->height + 1;
        }
        else if (root->right != NULL)
        {
        	//cout<<"right"<<endl;
            root->height = root->right->height + 1;
        }
        else
        {
        	//cout<<"None"<<endl;
        	root->height = 0;
        }

        return root;
    }
    
    int max(int h1, int h2)
    {
    	if (h1 > h2)
    		return h1;
    		
    	return h2;
    }
    

    // postorder deletion starting from root
    AVL_Node* delete_AVL(AVL_Node* root)
    {
        if (root == NULL)
        {
            return root;
        }

        root->left = delete_AVL(root->left);
        root->right = delete_AVL(root->right);

        delete root;
        return NULL;
    }
    

    /*AVL_Node* delete_node(string word)
    {

    }*/

    void preorder(AVL_Node* root)
    {
        if (root == NULL)
        {
        	//cout<<"UUIGUG"<<endl;
            return;
        }

        cout<<(root->word)<<endl;
        preorder(root->left);
        preorder(root->right);
    }

	bool search(AVL_Node* root, string word)
	{
		if (root == NULL)
		{
			//cout<<"Word not found"<<endl;
			return false;
		}
		
		if (toLowerCase(word) > toLowerCase(root->word))
		{
			//cout<<root->word<<endl;
			return search(root->right, word);
		}
		
		else if (toLowerCase(word) < toLowerCase(root->word))
		{
			//cout<<root->word<<endl;
			return search(root->left, word);
		}
		
		else
		{
			//cout<<"FOUND"<<endl;
			return true;
		}

	}
};

class Notepad
{
	Queue <char>word;
	Linked_List letters;
	AVL dict;
	
public:
	Notepad()
	{
		dict.load("dictionary.txt");
		//cout<<dict.get_root()->word<<endl;
	}
	
	void store_letter(char l)
	{
		//cout<<l;
		word.enqueue(l);
		letters.insert(l);
	}
	
	string get_word()
	{
		string temp = "";
		while (!word.is_empty())
		{
			temp += word.dequeue();
		}
		
		
		delete_list();
		
		return temp;
	}
	
	void backspace()
	{
		// remove last added element from both queue and linked list
		letters.remove_from_end();
		word.remove_rear();
	}
	
	void delete_list()
	{
		// delete all nodes and make head NULL
		letters.make_NULL();
	}
	
	void autocorrect(string word, int y)
	{
		int rows, cols;
		getmaxyx(stdscr, rows, cols);

		// clear all previous autocorrect suggestions
		for (int count = y; count < rows; count++)
		{
			move(count, 0);
			clrtoeol();
		}
		
		move(y, 0);
		
		// search for word in dictionary - if not present, offer suggestions
		if (dict.search(dict.get_root(), word))
		{
			return;
		}

		printw("Do you mean: ");
		
		string temp = word;
		
		// letter substitution
		char start = 'a';
		for (int count = 0; temp[count] != '\0'; count++)
		{
			for (start = 'a'; start <= 'z'; start++)
			{
				// replace
				temp[count] = start;
				
				// search in dictionary - if present in dictionary, display
				if (dict.search(dict.get_root(), temp))
				{	
					printw("%s? ", temp.c_str());
				}
				
				temp = word;
			}
		}
				
		// letter omission
		temp = "";
		for (int count = 0; word[count] != '\0'; count++)
		{
			for (int count2 = 0; word[count2] != '\0'; count2++) 
			{
				if (count2 != count)
				{
					temp += word[count2];
				}
			}
			
			// search
			if (dict.search(dict.get_root(), temp))
			{	
				printw("%s? ", temp.c_str());
			}
			
			temp = "";
		}
		
		// letter insertion
		for (int count = 0; word[count] != '\0'; count++)
		{
			for (char start = 'a'; start < 'z'; start++)
			{
				for (int count2 = 0; word[count2] != '\0'; count2++)
				{
					if (count == count2)
					{
						temp = temp + start;
					}
					temp = temp + word[count2];
				}
				
				// search for word
				if (dict.search(dict.get_root(), temp))
				{	
					printw("%s? ", temp.c_str());
				}
				
				temp = "";
			}
		}
		
		// insert at end
		for (char start = 'a'; start < 'z'; start++)
		{
			temp = word + start;
			
			if (dict.search(dict.get_root(), temp))
			{	
				printw("%s? ", temp.c_str());
			}
			
			temp = "";
		}
		
		// letter reversal
		temp = word;

		for (int count = 0; word[count+1] != '\0'; count++)
		{
			/*
			for (int count2 = 0; word[count2+1] != '\0'; count2++)
			{
				if (count2 == count)
				{
					temp += word[count2+1];
					temp += word[count2];
				}
				else
				{
					temp += word[count2];
					temp += word[count2+1];
				}
			}
			*/
			
			char temp2 = temp[count];
			temp[count] = temp[count+1];
			temp[count+1] = temp2;
			
			// search
			if (dict.search(dict.get_root(), temp))
			{	
				printw("%s? ", temp.c_str());
			}
			
			temp = word;
		}
	}
	
	void save()
	{
		int rows, cols;
		getmaxyx(stdscr, rows, cols);
		
		int x, y;
		getyx(stdscr, y, x);
		
		ofstream file;
		string file_name;
		printw("Enter file name: ");
		char temp = getch();
		
		while (temp != '\n')
		{
			file_name += temp;
			temp = getch();
		}
		
		move(y, x);
		clrtoeol();
		refresh();
		
		file.open(file_name + ".txt");
		if (!file)
		{
			printw("Could not open file");
			return;
		}
		
		move(0, 0);
		char current;
		for (int count = 0; count <= y; count++)
		{
			for(int count2 = 0; count2 <= x; count2++)
			{
				current = mvinch(count, count2);
				file<<current;
			}
		}
		move(y, x);
		
		file.close();
	}
	
	void load()
	{
		string file_name;
		printw("Enter file name: ");
		char temp = getch();
		
		while (temp != '\n')
		{
			file_name += temp;
			temp = getch();
		}

		move(0, 0);
		clrtoeol();
		refresh();
		
		ifstream file;
		file.open(file_name + ".txt");
		if (!file)
		{
			printw("Could not open file");
			refresh();
			return;
		}
		
		char current;
		while (file.get(current)) // this preserves all whitespace
		{
			printw("%c", current);
			refresh();
		}
		
/*		
		char current;
		while (!file.eof())
		{
			file>>current;
			printw("%c", current);
			refresh();
		}
*/
	
		file.close();
	}
	
	void requeue()
	{
		int x, y;
		getyx(stdscr, y, x);
		x--;
		char temp;
		
		while ((temp = mvinch(y, x)) != ' ')
		{
			x--;
		}
		
		x++;
		temp = mvinch(y, x);
		
		while ((temp != '\n') && (temp != ' '))
		{
			word.enqueue(temp);
			letters.insert(temp);
			x++;
			temp = mvinch(y, x);
		}
		
		move(y, x);
	}
};

int main()
{
    Notepad notepad;
    
    initscr();      
          
    string word = "";
    char letter = '\0';
    while (true)
    {
		letter = getch();
		
		if (letter == ' ')
		{
			// get initial coordinates of cursor
			int y, x;
			getyx(stdscr, y, x);
			
			// get word 
			word = notepad.get_word();
			
			notepad.autocorrect(word, y+5);

			//get to intial coordinates of cursor 
			move(y, x);
		}

		// start from an if condition
		// ctrl + s to store text to a file
		// why making it if works weirdly for the program
		else if (letter == 19)
		{
			int y, x;
			getyx(stdscr, y, x);
			move(y, x-2);
			clrtoeol();
			notepad.save();
		}
		
		// ctrl + l to load text from a file
		else if (letter == 12)
		{
			int y, x;
			getyx(stdscr, y, x);
			move(y, x-2);
			clrtoeol();
			notepad.load();
		}
		// esc to exit
		else if (letter == 27)
		{
			notepad.delete_list();
			return 0;
		}
		
		
		// if back space, remove a letter from the linked list
		else if (letter == 127)
		{
			// go one col back - get character in front, clear everything in front
			int y, x;
			getyx(stdscr, y, x);
			char character = mvinch(y, x-3);
			move(y, x-3);
			clrtoeol();
			//cout<<character<<endl;
			
			// if last letter not space
			if (character != ' ')
			{
				// remove it from linked list and queue
				notepad.backspace();
			}
			
			// if last letter space - first enqueue all words again and make the linked list again for the word becaus eit has been dequeud and the list is empty - we can use stack for undoes, maintaining last state of the queue and list (in short the notepad)
			else
			{
				notepad.requeue();
			}
		}
		
		// store
		else
		{
			// store letter in linked list and queue
			notepad.store_letter(letter);
		}
		
		letter = '\0';
			
		refresh();
	}
}
