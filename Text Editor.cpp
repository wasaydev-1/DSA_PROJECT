#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class Node
{
	public:
		
	string data;
	Node *next;
};

class Undo
{
	public:
		
	int line_num;
	string text;
	int cmd_num;
};

class linked_list
{
    private:
	
	Node *head;
	Node *tail;
	int lines_count = 0;
	int next = 1;
	stack<Undo> undoStack;
    
	public:

	void addtohead(string data)
    {
        if(head==NULL)
        {
            Node *temp=new Node;
            temp->data=data;
            temp->next=NULL;
            head=temp;
            tail=head;
            lines_count++;
        }
        else
        {
            Node *temp = new Node;
            temp->data = data;
            temp->next = NULL;
            temp->next = head;
            head = temp;
            lines_count++;
        }
        Undo headadder;
        headadder.line_num = 1;
        headadder.cmd_num = 1;
        undoStack.push(headadder);
    }
    
	void addTotailwhatever(string data)
    {
        if (head == NULL)
        {
            Node *temp= new Node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            lines_count++;
		}
        else
        {
            Node *temp = new Node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            lines_count++;
        }
    }

    void deletetailwhatever()
    {
        Node *temp = head;
        
		if (head == NULL)
        {
            cout<<"Nothing deleted."<<endl;
        }
        else if (head == tail)
        {
            temp = head;
            string backup = temp->data;
            delete(temp);
            head = tail = NULL;
            lines_count--;
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            delete temp->next;
            temp->next = NULL;
            lines_count--;
        }
    }

    void addToTail(string data)
    {
        if (head == NULL)
        {
            Node *temp = new Node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            lines_count++;
        }
        else
        {
            Node *temp = new Node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            lines_count++;
        }
        Undo tailadder;
        tailadder.line_num = 1;
        tailadder.cmd_num = 8;
        undoStack.push(tailadder);
    }
    
    void headdelete()
	{
        string store = head->data;
        Node *temp = head;
        Node *nextNode = head->next;
        head = nextNode;
        delete(temp);
        lines_count--;
        Undo deletedhead;
        deletedhead.text = store;
        deletedhead.line_num = 1;
        deletedhead.cmd_num = 3;
        undoStack.push(deletedhead);
    }

    void Taildelete()
    {
        Node *temp = head;
            
			if (head == NULL)
            {
                cout<<"Delete nothing."<<endl;
            }
            else if (head == tail)
            {
                temp = head;
                string store = temp->data;
                delete(temp);
                head = tail = NULL;
                lines_count--;
                Undo deletedTail;
                deletedTail.text = store;
                deletedTail.line_num = 1;
                deletedTail.cmd_num = 7;
                undoStack.push(deletedTail);
            }
            else
            {
                while (temp->next != NULL && temp->next->next != NULL)
                {
                    temp = temp->next;
                }
                tail = temp;
                string backup = temp->next->data;
                delete temp->next;
                temp->next = NULL;
                lines_count--;
                Undo deletedTail;
                deletedTail.text = backup;
                deletedTail.line_num = 1;
                deletedTail.cmd_num = 7;
                undoStack.push(deletedTail);
            }
    }
    	void Textreplace(string givendata,int givenline)
	{	
		Undo linereplaced;
		if (lines_count < givenline)
		{
			cout<<"Exceed number of lines"<<endl;
		}
		else if (givenline == 0)
		{
			cout<<"No line 0 exist"<<endl;
		}
		else if (lines_count >= givenline )
		{
			Node *temp = head;
			int gotoline = 1;
			while(gotoline < givenline)
			{
				temp = temp->next;
				gotoline++;
			}
			string backup = temp->data;
			temp->data = givendata;	
			linereplaced.line_num = givenline;
			linereplaced.text = backup;
			linereplaced.cmd_num = 4;
			undoStack.push(linereplaced);
		}
	}
		void insertfurther(string datagiven, int linegiven)
	{	
		Undo insertedfurtheraway;
		insertedfurtheraway.line_num = 0;
		insertedfurtheraway.cmd_num = 9;
		if (head == NULL)
		{
			while(lines_count < linegiven-1)
			{
				addTotailwhatever("\n");
				insertedfurtheraway.line_num++;
			}
			addTotailwhatever(datagiven);
		}
		else{
			while(lines_count < linegiven-1)
			{
				addTotailwhatever("\n");
				insertedfurtheraway.line_num++;
			}
			addTotailwhatever(datagiven);
		}
		undoStack.push(insertedfurtheraway);
	}
		void deleteLine(int linegiven){						
		if (head == NULL)
		{
			cout<<"No line to be deleted"<<endl;
		}
		else if(head == tail){
			Node *t = head;
			delete(t);
			head = NULL;
			tail = NULL;
			lines_count--;
		}
		else if(linegiven == 0){
			cout<<"No line 0"<<endl;
		}
		else if(linegiven == 1){
			string backup = head->data;
			Node *temp = head;
			Node *nodenext = head->next;
			head = nodenext;
			delete(temp);
			lines_count--;
			Undo removehead;
			removehead.text = backup;
			removehead.line_num = 1;
			removehead.cmd_num = 12;
			undoStack.push(removehead);
		}
		else if(linegiven == lines_count){
			Node *temp = head;
			Undo deletedLine;
			deletedLine.cmd_num = 11;
			while (temp->next != NULL && temp->next->next != NULL)
			{
				temp = temp->next;
			}
			tail = temp;
			string backup = temp->next->data;
			delete temp->next;
			temp->next = NULL;
			lines_count--;
			deletedLine.text = backup;
			deletedLine.line_num = linegiven;
			undoStack.push(deletedLine);

		}
		else if (linegiven > lines_count)
		{
			cout<<"Line is larger."<<endl;
		}
		else if (linegiven < lines_count)
		{
			Undo deletedLine;
			deletedLine.cmd_num = 10;
			Node *prevNode = head;
			Node *nextNode = head;
			Node *temp = head;
			int iterator = 2;
			while(iterator < linegiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			temp = nextNode;
			nextNode = nextNode->next;
			prevNode->next = nextNode;
			string backup = temp->data;
			delete(temp);
			lines_count--;
			deletedLine.text = backup;
			deletedLine.line_num = linegiven;
			undoStack.push(deletedLine);
		}
	}


	
//void Check_File()                      //function used to open a file from the same folder this cpp file is in
//{			
//        ifstream myfile;		
//		string fileName;
//		cout << "Enter the file name : ";
//		getline(cin,filename);
//		fileName += ".txt";
//		
//		myfile.open(fileName);
//		string s;
//		
//		while (getline(myfile, s))
//		{
//			addToTail(s);
//		}
//		
//		myfile.close();
//	}

void Print()                   //function used to print the whole linked list
{						
		Node* temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		
		if (head == NULL)
		{
			cout << "-------------------Nothing is present---------------------------\n" << endl;
		}
		else 
		{
			while (temp != NULL)
			{
				if (linePrinted == 1)
				{
					cout << "-------------------Page " << "1" << "-------------------\n";
				}
				else if ((linePrinted - 1) % 10 == 0)
				{
					cout << "-------------------Page " << pagePrinted << "-------------------\n";
					pagePrinted++;
				}
				cout << linePrinted << ") " << temp->data << endl;
				temp = temp->next;
				linePrinted++;
			}
		}
	}


//void Save_Data()
//{
//	ofstream outfile;
//	Node* temp = head;
//	int linePrinted=1;
//	string fileName;
//	
//	cout << "Enter the file name : ";
//	getline(cin,filename);
//	fileName += ".txt";
//	
//	outfile.open(fileName, ios_base::app);
//	
//	while (temp != NULL)
//	{
//		outfile << temp->data;
//		temp = temp->next;
//		linePrinted++;
//	}
//	outfile.flush();
//	outfile.close()
//}
};
