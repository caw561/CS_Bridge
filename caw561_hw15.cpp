#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class T>
class LList;

template <class T>
class LListNode
{
    public:
    T data;
    LListNode<T>* next;
    LListNode<T>* prev;
    LListNode(const T& newData = T(), LListNode<T>* newNext = nullptr, LListNode<T>* newPrev = nullptr):data(newData),next(newNext),prev(newPrev){}
    friend class LList<T>;
};

template <class T>
class LList
{
    public:
    int size;
    LListNode<T>* head;
    LListNode<T>* tail;
    
    LList();
    LList(const LList<T>& rhs);
    ~LList(){clear();delete head; delete tail;};
    LList& operator=(const LList& rhs);
    void clear();
    void push_back(const T& data);
    LListNode<T>* get_first()const{return head->next;};
    LListNode<T>* get_tail()const{return tail;};
    LListNode<T>* get_next(LListNode<T>* Node)const{return Node->next;};

};

class Person
{
    string name;
    double amount_paid; //amount paid at the restaurant 
    double amount_owed; //amount still need to pay or be paid
     
    public:
    Person():name(""),amount_paid(0),amount_owed(0){}
    Person(string personName, double paid):name(personName), amount_paid(paid), amount_owed(0){}
    void calcOwed(double split_amount){amount_owed=split_amount-amount_paid;};
    string get_name()const {return name;};
    void set_paid(double new_paid){amount_paid=new_paid;};
    void set_owed(double new_owed){amount_owed=new_owed;};
    double get_paid(){return amount_paid;};
    double get_owed(){return amount_owed;};
};

void openInputFile(ifstream& inputFile);
double calc_owed(LList<Person>& person_list);
void directions(LList<Person>& person_list, ostream& outs);
LListNode<Person>* find_pay_node(LList<Person>& person_list);


int main()
{
    ifstream inFile;
    ofstream outFile("hw15_output.txt");
    openInputFile(inFile);
    LList<Person> myList;
    double paid, split;
    string name;
    
    while(inFile>>paid){
        getline(inFile, name);
        Person new_person(name,paid);
        myList.push_back(new_person);
    }

    split = calc_owed(myList);
    directions(myList,outFile);
    outFile<<"In the end, you should all have spent around $"<<split<<endl;
    outFile.close();

    return 0;
}


template <class T>
LList<T>::LList()
{
    size = 0;
    head = new LListNode<T>;
    tail = new LListNode<T>;
    head->next = tail;
    tail->prev = head;
}

template <class T>
void LList<T>::push_back(const T& data)
{
    LListNode<T>* temp = new LListNode<T>(data, head->next, head);
    head->next = temp;
    temp->next->prev = temp;
    size++;
}

template<class T>
void LList<T>::clear()
{
    while(size!=0){
        LListNode<T>* temp=head->next;
        head->next = temp->next;
        head->next->prev = head;
        delete temp;
        size--;
    }
}

template<class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
    if (this == &rhs)
		return *this;
	clear();
	LListNode<T>* ptr = rhs.head->next;
	while (ptr != rhs.tail) {
		push_back(ptr->data);
	}
	return *this;
}

template <class T>
LList<T>::LList(const LList<T>& rhs) {
	head = new LListNode<T>();
	tail = new LListNode<T>();
	head->next = tail;
	tail->prev = head;
	*this = rhs; //call to the assignment operator!!!
}

void openInputFile(ifstream& inputFile) {
	string fileName;
	cout << "What is the name of the file you would like to open? \n";
	cin >> fileName;
	inputFile.open(fileName);
	while (!inputFile) {
		cout << "FILE FAILED TO OPEN \n";
		cout << "Please re-enter the file name: \n";
		cin >> fileName;
		inputFile.clear();
		inputFile.open(fileName);
	}
}

double calc_owed(LList<Person>& person_list)
{
    double total = 0.0;
    double split_amount;
    if(person_list.size==0){
        return 0.0;
    }
    LListNode<Person>* on=person_list.get_first();
    while(on!=person_list.get_tail()){
        total += on->data.get_paid();
        on = person_list.get_next(on);
    }
    split_amount=total/person_list.size;
    on=person_list.get_first();
    while(on!=person_list.get_tail()){
        on->data.calcOwed(split_amount);
        on = person_list.get_next(on);
    }
    return split_amount;
}

void directions(LList<Person>& person_list, ostream& outs)
{
    //find people who don't need to do anything
    LListNode<Person>* on=person_list.get_first();
    while(on!=person_list.get_tail()){
        if(on->data.get_owed()==0){
            outs<<on->data.get_name()<<", you don't need to do anything \n";
        }
        on = person_list.get_next(on);
    }

    on=person_list.get_first();
    while(on!=person_list.get_tail()){
        double temp_owed = on->data.get_owed();
        string name=on->data.get_name();
        while(temp_owed>0){
                LListNode<Person>* pay_node=find_pay_node(person_list);
                double difference = temp_owed + pay_node->data.get_owed();
            if(pay_node!=person_list.tail){
                if(difference>0&&pay_node!=person_list.tail){
                    outs<<name<<", you give"<<pay_node->data.get_name()<<" $"<<(temp_owed-difference)<<endl;
                    temp_owed=difference;
                    pay_node->data.set_owed(0);
                }
                else{
                    outs<<name<<", you give"<<pay_node->data.get_name()<<" $"<<temp_owed<<endl;
                    temp_owed=0;
                    pay_node->data.set_owed(difference);
                }
            }
            else{
                break;;
            }
            on->data.set_owed(0);
        }
        on = person_list.get_next(on);
    }


}

LListNode<Person>* find_pay_node(LList<Person>& person_list)
{
    LListNode<Person>* on=person_list.get_first();
    while(on!=person_list.get_tail()){
        if(on->data.get_owed()<0){
            return on;
        }
        on = person_list.get_next(on);
    }

    return on=person_list.get_tail();
}