#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Queue
{
    vector<T> v;
    int startIndex;
    int size;

    public:
    Queue():startIndex(0), size(0){};
    Queue(vector<T> newV):v(newV),startIndex(0),size(newV.size()){};
    void clear();
    void pop_front();
    void push_back(T data);
    T top();
    void print();
};

int main()
{
    vector<int> v = {0,1,2,3,4,5,6,7,8};
    Queue<int> q(v);

    q.print();
    q.pop_front();
    q.print();
    q.push_back(7);
    q.print();
    cout<<q.top()<<endl;
    q.clear();
    q.print();

    return 0;
}

template <class T>
void Queue<T>::clear()
{
    v.clear();
    v.shrink_to_fit();
    startIndex = 0;
    size =0;
}

template <class T>
void Queue<T>::pop_front()
{
    if(startIndex<size){
        startIndex++;
        size--;
    }
    else{
        cout<<"Error: List is empty";
    }
}

template <class T>
void Queue<T>::push_back(T data)
{
    v.push_back(data);
    size++;
}

template <class T>
T Queue<T>::top()
{
    return v[startIndex];
}

template <class T>
void Queue<T>::print()
{
    if(size!=0){
        cout<<"[";
        for(int i=startIndex; i<(size+startIndex); i++){
            cout<<v[i]<<" ";
        }
        cout<<"]"<<endl;
    }
    else{
        cout<<"List is empty \n";
    }
}