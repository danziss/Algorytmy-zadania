#include <cstdio>
#include <iostream>

class Node{
    private:
        int value;
        Node* next;
    public:
        Node(){value = 0; next = NULL;}
        Node(int val){value = val; next = NULL;}
        Node(int val, Node* n){value = val; next = n;}

        void setVal(int val){value = val;}
        void setNext(Node* n){next = n;}
        int getVal(){return value;}
        Node* getNext(){return next;}
};


class Lista{
    private:
        Node* header;
    public:
        Lista(){header = NULL;}
        ~Lista();

        int size();
        void addElement(int val);
        void addAt(int val, int elemNr);
        void removeElement(int val);
        int retrieve(int elemNr);
        void display();
        Node* getHeader(){return header;};
};

Lista::~Lista(){
    Node* temp = new Node();
    while(header != NULL){
        temp = header->getNext();
        delete header;
        header = temp;
    }
}

int Lista::size(){
    if (header == NULL)return 0;
    int i = 0;
    Node* temp = header;
    while(temp!= NULL){
        i++;
        temp = temp->getNext();
    }
    return i;
}

void Lista::addElement(int val){
  
  Node* newElement = new Node(val);
  if(header == NULL){
      header =  newElement;
  }else{
      Node* temp = header;
      
      while(temp->getNext() != NULL){
          temp = temp->getNext();
      }
      temp->setNext(newElement);
  }
}

void Lista::removeElement(int elemNr){
    if (elemNr <0 || elemNr > this->size())return;
    if (elemNr == 0){
        Node* temp = header;
        header = temp->getNext();
        delete temp;
    }else if(elemNr >= 1){
        int i = 0;

        Node* temp = header;
        while(temp->getNext() != NULL){
            if((i+1) == elemNr)break;
            temp = temp->getNext();
            i++;
        }

        if(temp->getNext() == NULL){
            delete temp->getNext();
            temp->setNext(NULL);
        }else
        {
            Node* temp2 = temp->getNext();
            temp->setNext(temp->getNext()->getNext());
            delete temp2;
        }
        
    }
}

void Lista::addAt(int val, int elemNr){
    if(elemNr < 0 || elemNr > this->size())return;
    Node* newElement = new Node(val);
    if (elemNr == 0){
        Node* temp = header;
        newElement->setNext(temp);
        header = newElement;
    }else if(elemNr >= 1){
        int i = 0;

        Node* temp = header;
        while(temp->getNext() != NULL){
            if((i+1) == elemNr)break;
            temp = temp->getNext();
            i++;
        }
        
        newElement->setNext(temp->getNext());
        temp->setNext(newElement);
        
    }
}

int Lista::retrieve(int elemNr){
    if(elemNr < 0 || elemNr >= this->size())return -1;
    if(elemNr == 0)return header->getVal();
    
    int i = 0;
    Node* temp = header;
    while(temp->getNext() != NULL){
        temp = temp->getNext();
        i++;
        if (elemNr == i){
            return temp->getVal();
        }
    }
}


void Lista::display() {
    Node* temp = header;
    
    std::cout << "Elementy listy: " << "\n";
    while(temp->getNext() != NULL){
        std::cout << temp->getVal() << "\n";
        temp = temp->getNext();
    }std::cout << temp->getVal() << "\n";
    std::cout << "---------- \n";
}

class Stos{
    private:
        Lista* list;
        
    public:
        Stos(){
            list = new Lista();
        } 
        ~Stos();
        void push(int val);
        int pop();
        int top();
        bool empty();
        int size();
        void makenull();
};

Stos::~Stos(){
    delete list;
}

void Stos::push(int val){
    list->addAt(val, 0);
}

int Stos::pop(){
    int top = list->getHeader()->getVal();
    list->removeElement(0);
    return top;
}

int Stos::top(){
    return list->getHeader()->getVal();
}

bool Stos::empty(){
    if(list->size() == 0)return true;
    else return false;
}

void Stos::makenull(){
    while (!this->empty()){
        list->removeElement(0);
    }
}

int main() {
    Stos* stos = new Stos();
    std::cout << "Czy stos pusty: " << stos->empty() << "\n";
    std::cout << "Dodaje 1 na stos\n";
    stos->push(1);
    std::cout << "Czy stos pusty: " << stos->empty() << "\n";
    std::cout << "Uzywam metody pop, otrzymuje i usuwam ze stosu " << stos->pop() << " \n";
    std::cout << "Czy stos pusty: " << stos->empty() << "\n";
    std::cout << "Dodaje 2 na stos\n";
    stos->push(2);
    std::cout << "Dodaje 3 na stos\n";
    stos->push(3);
    std::cout << "Dodaje 4 na stos\n";
    stos->push(4);
    std::cout << "Dodaje 5 na stos\n";
    stos->push(5);
    std::cout << "Dodaje 6 na stos\n";
    stos->push(6);
    std::cout << "Uzywam metody top, dostaje " << stos->top() << " \n";
    std::cout << "Uzywam metody pop, otrzymuje i usuwam ze stosu " << stos->pop() << " \n";
    std::cout << "Uzywam metody top, dostaje " << stos->top() << " \n";
    std::cout << "Uzywam metody makenull\n";
    stos->makenull();
    std::cout << "Czy stos pusty: " << stos->empty() << "\n";

    return 0;
}