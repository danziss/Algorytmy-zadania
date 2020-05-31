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

int main() {

    Lista* lista = new Lista();
    lista->addElement(5);
    lista->addElement(2);
    lista->addElement(12);
    lista->addElement(1);
    std::cout << "Size: " << lista->size() << std::endl;
    lista->addElement(132);
    lista->addElement(9);
    lista->addElement(14);
    lista->addElement(6);
    lista->addElement(76);
    std::cout << "Size: " << lista->size() << std::endl;
    Node* temp = new Node();
    temp = lista->getHeader();
    std::cout << temp->getVal() << std::endl;
    lista->display();
    lista->removeElement(3);
    lista->removeElement(10);
    std::cout << "Size: " << lista->size() << std::endl;
    lista->display();
    lista->addAt(44, 2);
    std::cout << lista->retrieve(2) << "\n";
    lista->addAt(10, 5);
    std::cout << lista->retrieve(0) << "\n";
    std::cout << "Size: " << lista->size() << std::endl;
    lista->display();
    delete lista;

    return 0;
}