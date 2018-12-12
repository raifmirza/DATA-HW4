/* @Author
Student Name: Raif Mirza Erten
Student ID : 150160022
Date: 12.12.2018 */

#include <iostream>
#include <fstream>

using namespace std;

typedef int QueueDataType;

struct Node{
  QueueDataType data;
  Node *next;
};


struct stackAnt{
  Node *head;
  int size = 0;
  QueueDataType topstack;
  void create();
  void close();
  void push(QueueDataType);
  QueueDataType pop();
};


void stackAnt::create(){
  head = NULL;
}
void stackAnt::close(){
  Node *p;
  while(head){
    p = head;
    head = head->next;
    delete p;
  }
}

void stackAnt::push(QueueDataType newdata){
  Node *newnode = new Node;
  newnode->data = newdata;
  newnode->next = head;
  head = newnode;
  topstack = newdata;
  size++;
}

QueueDataType stackAnt::pop(){
  Node *topnode;
  QueueDataType temp;
  topnode = head;
  head = head->next;
  if(head == NULL){
    topstack = 0;
  }
  else{
      topstack = head->data;
  }

  temp = topnode->data;
  delete topnode;
  size--;
  return temp;

}


struct queueAnt {
  Node *front;
  Node *back;
  void create();
  void close();
  void display();
  void enqueue(QueueDataType);
  QueueDataType dequeue();
  bool isempty();
};

void queueAnt::create(){
front = NULL; back = NULL;
}
void queueAnt::close(){
  Node *p;
  while (front) {
    p = front;
    front = front->next;
    delete p;
  }
}

void queueAnt::display(){
  Node *p;
  p = front;
  while(p != NULL){
    cout<<p->data<<" ";
    p = p->next;
  }
  cout<<endl;
  delete p;
}
void queueAnt::enqueue(QueueDataType newdata){
  Node *newnode = new Node;
  newnode->data = newdata;
  newnode->next = NULL;
  if (isempty()) {
    back = newnode;
    front = back;
    }
  else {
    back->next = newnode;
    back = newnode;
  }
}

QueueDataType queueAnt::dequeue() {
  Node *topnode;
  QueueDataType temp;
  topnode = front;
  front = front->next;
  temp = topnode->data;
  delete topnode;
  return temp;
}
bool queueAnt::isempty() {
  return front == NULL;
}

struct Ants{
  queueAnt ants;
  queueAnt holeDepths;
  stackAnt hole;
  void ReadFile(char*);
  void ShowContents(bool);
  void CrossRoad();
};

void Ants::ReadFile(char* file){
  QueueDataType countofant,numberofhole;
  ifstream thatfile(file);
  if(thatfile.is_open()){
    thatfile>>countofant;
    for(int i = 1;i<countofant+1;i++){
      ants.enqueue(i);
    }
    while(true){
      thatfile>>numberofhole;
      if(thatfile.eof()){
       break;
      }
      holeDepths.enqueue(numberofhole);
    }
  thatfile.close();
  }
  else{cout<<"Unable to open file."<<endl;}
}

void Ants::ShowContents(bool choice){
  if(choice == 1){
    ants.display();
  }
  else if(choice == 0){
    holeDepths.display();
  }
}

void Ants::CrossRoad(){
  while(!holeDepths.isempty()){
    int x = holeDepths.dequeue();
    for(int i = 0;i<x;i++){
      hole.push(ants.dequeue());
    }
    for(int i = 0;i<x;i++){
      ants.enqueue(hole.pop());
    }
  }
}


int main ( int argc , char ** argv ){
  Ants a ;
  a.ants.create();
  a.holeDepths.create();
  a.ReadFile(argv[1]); // store the number of ants and depths of holes
  cout <<"The initial Ant sequence is: ";
  a.ShowContents(1); // list ant sequence ( initially : 1 , 2 , ... , N )
  cout <<"The depth of holes are: " ;
  a.ShowContents(0); // list depth of holes
  a.CrossRoad();
  cout <<"The final Ant sequence is: " ;
  a.ShowContents(1);
  a.ants.close();
  a.holeDepths.close();
  (void) argc;
  return 0;
}
