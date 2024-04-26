#include <bits/stdc++.h>
using namespace std;

template <typename T>

class ArrayBasedList{
    private:

    T* list; // array 
    int maxSize; // maximum capacity
    int length; // number of elements that existed in the array

    public:

    ArrayBasedList(int size);  
    ~ArrayBasedList(); 

    void insertAt(int index , T value); 
    T get(int index) const; 
    int listSize() const; 
    void remove(T value);
    bool isEmpty() const; 
    bool isFull() const; 
    int maxListSize() const; 
    void print() const ; 
    bool isItemAtEqual(int index ,T value) ;
    void insertEnd(T value);
    void removeAt(int index);
    void retrieveAt(int index , T& value);  
    void replaceAt(int index , T value);
    void clearList();
    int seqSearch(T value) const;


};

template <typename T>
ArrayBasedList<T>::ArrayBasedList(int size):maxSize(size),length(0){
    list = new T[maxSize];
}

template <typename T>
ArrayBasedList<T>::~ArrayBasedList() {
  delete[] list;
}

template <typename T>
void ArrayBasedList<T>::insertAt(int index, T value) {
    if (index < 0 || index > maxSize) { //invalid index
        return;
    }
    
    
    if (isFull()) {// full list
        return;
    }

    
    if (index == length) { // inserting at the end
        insertEnd(value);
        return;
    }

    else{ //inserting between elements
        for (int i = length; i > index; i--) { //shifting to right and make space to the inserted value
        list[i] = list[i - 1];
            }
        list[index] = value;
        length++; //increase the length by one 
    }    
}

template <typename T>
T ArrayBasedList<T>::get(int index)const{
    return list[index];
}

template <typename T>
int ArrayBasedList<T>::listSize() const{
    return length;
}

template <typename T>
void ArrayBasedList<T>::remove(T value) {
  int index = seqSearch(value);
  removeAt(index);
}

template <typename T>
bool ArrayBasedList<T>::isEmpty()const{
  if(length == 0){
    return true;
  }
  else{
    return false;
  }
}

template <typename T>
bool ArrayBasedList<T>::isFull()const{
  if(length == maxSize){
    return true;
  }
  else{
    return false;
  }
}

template <typename T>
int ArrayBasedList<T>::maxListSize()const{
  return maxSize;
}

template <typename T>
void ArrayBasedList<T>::print()const{
  for(int i=0 ; i<length ; i++){
    cout << list[i] << " ";
  }
  cout << endl;
}

template <typename T>
bool ArrayBasedList<T>::isItemAtEqual(int index , T value){
  if(list[index] == value){
    return true;
  }
  else{return false;
  }
}

template <typename T>
void ArrayBasedList<T>::insertEnd(T value) {
  if(length!=maxSize){
    list[length]=value;
    length++;
  }
}
template <typename T>
void ArrayBasedList<T>::removeAt(int index){
  for(int i = index; i < length - 1; i++) {
    list[i] = list[i + 1]; //shifting to left
  }
  length--;
}

template <typename T>
void ArrayBasedList<T>::retrieveAt(int index, T& value) {
    value = list[index];
}

template <typename T>
void ArrayBasedList<T>::replaceAt(int index, T value) {
  list[index] = value;
}

template <typename T>
void ArrayBasedList<T>::clearList() {
  length = 0;
}

template <typename T>
int ArrayBasedList<T>::seqSearch(T value) const{
  for (int index = 0; index < length; index++) {
    if (list[index] == value) {
      return index;
      break;
    }
  }

}


int main(){
    ArrayBasedList<int> list(5); 
    list.insertEnd(0);
    list.insertEnd(1);
    list.insertEnd(2);
    list.insertEnd(3);
    list.insertEnd(4);
    list.print();
    cout << "Size: " << list.listSize() << endl; 
    cout << "Is Full: " << (list.isFull() ? "true" : "false") << endl; 
    cout << "Is Empty: " << (list.isEmpty() ? "true" : "false") << endl; 
    cout << "Value at index 2: " << list.get(2) << endl; 
    cout << "Is item at index 3 equal to 2: " << (list.isItemAtEqual(3, 2) ? "true" : "false") << endl; 
    list.removeAt(2);
    list.print(); 
    cout << "Size: " << list.listSize() << endl; //4
    list.insertEnd(6); 
    list.print();  
    cout << "Size: " << list.listSize() << endl;
    list.remove(4);
    list.print();
    cout << "Size: " << list.listSize() << endl;
    list.insertAt(0 , 100);
    list.print();
    cout << "the value you looking for is in index : "<<list.seqSearch(100)<<endl;
    list.clearList();
    cout << "Is Empty: " << (list.isEmpty() ? "true" : "false") << endl;
    return 0;
}
