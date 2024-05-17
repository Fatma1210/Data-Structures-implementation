#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <climits>
using namespace std;
class Item{
private:
    string Name ;
    string Category ;
    int Price ;
public:
    Item() ;
    Item(string , string , int) ;
    void setItemName(string) ;
    void setItemCategory(string) ;
    void setItemPrice(int) ;
    string getItemName() const ;
    string getItemCategory() const ;
    int getItemPrice() const ;
    bool operator<(const Item&);
    void Print() ;
};
Item ::Item() {
    Name = "" ;
    Category = "" ;
    Price = 0 ;
}
Item ::Item(string name , string category, int price) {
    Name = name ;
    Category = category ;
    Price = price ;
}
bool Item ::operator<(const Item & other) {
    return Name < other.Name ;
}
void Item ::Print() {
    cout << "Item Name : " << Name << endl;
    cout << "Item Category : " << Category << endl;
    cout << "Item Price : " << Price << endl;
}
void Item ::setItemName(string name) {
    this->Name = name ;
}
void Item ::setItemCategory(string category) {
    this->Category = category ;
}
void Item ::setItemPrice(int price) {
    this->Price = price ;
}
string Item ::getItemCategory() const {
    return this->Category ;
}
string Item ::getItemName() const {
    return this->Name;
}
int Item ::getItemPrice() const {
    return this->Price ;
}
Item maxValueItem("zzzzzzzzzz", "zzzzzzzzzz", INT_MAX);
class maxHeap{
private:
    Item item;
    Item *maxHeapp;
    int heapCurrentSize;
    int heapMaxSize;
    int deletedItems;
public:
    maxHeap(int maxSize);
    ~maxHeap();
    void setHeapMaxSize(int heapMaxSize);
    void addItemData(Item data);
    void removeItemData(int i,string type);
    void removeRoot(string type);
    void maximizeItem(int i);
    void displayItemData();
    void sortAsc(string type);
    void sortDes(string type);
    void maxHeapify(int i,string type);
    void buildMaxHeap(string type);
};
//declaring the constructor
maxHeap::maxHeap(int maxSize){
    maxHeapp=new Item[maxSize];
    heapCurrentSize=0;
    heapMaxSize=maxSize;
    deletedItems=0;
}
maxHeap::~maxHeap() {
    delete[] maxHeapp;
}
void maxHeap::setHeapMaxSize(int heapMaxSize) {
    this->heapMaxSize=heapMaxSize;
}
void maxHeap::maxHeapify(int i,string type) {
    //get leftchild
    int leftChild = (2 * i) + 1;
    //get rightchild
    int rightChild = (2 * i) + 2;
    int largest = i;
    if (type == "name") {
        //get the max between leftchild and rightchild
        if (leftChild < heapCurrentSize && strcmp(maxHeapp[leftChild].getItemName().c_str(), maxHeapp[largest].getItemName().c_str()) > 0) {
            largest = leftChild;
        }
        if (rightChild < heapCurrentSize && strcmp(maxHeapp[rightChild].getItemName().c_str(), maxHeapp[largest].getItemName().c_str()) > 0) {
            largest = rightChild;
        }
    } else if (type == "price") {
        //get the max between leftchild and rightchild
        if (leftChild < heapCurrentSize && maxHeapp[largest].getItemPrice() < maxHeapp[leftChild].getItemPrice()) {
            largest = leftChild;
        }
        if (rightChild < heapCurrentSize && maxHeapp[largest].getItemPrice() < maxHeapp[rightChild].getItemPrice()) {
            largest = rightChild;
        }
    } else if (type == "category") {
        //get the max between leftchild and rightchild
        if (leftChild < heapCurrentSize && strcmp(maxHeapp[largest].getItemCategory().c_str(), maxHeapp[leftChild].getItemCategory().c_str()) < 0) {
            largest = leftChild;
        }
        if (rightChild < heapCurrentSize && strcmp(maxHeapp[largest].getItemCategory().c_str(), maxHeapp[rightChild].getItemCategory().c_str()) < 0) {
            largest = rightChild;
        }
    }
    //compare if the largest position changed,then the children greater than the parent
    //which violates maxheap
    if (largest != i) {
        //swap the parent and the max(lchild,rchild) to put the parent in the right position
        swap(maxHeapp[largest], maxHeapp[i]);
        //heapify the rest of the nodes until we get the last element
        maxHeapify(largest, type);
    }
}
//this method takes o(n)
void maxHeap::buildMaxHeap(string type) {
    for (int i = (heapCurrentSize/2)-1; i>=0 ; --i) {
        maxHeapify(i,type);
    }
}
void maxHeap::addItemData(Item data) {
    //check if the array is full
    if(heapCurrentSize==heapMaxSize){
        cout<<"Error, you can't add new item the array is full.";
        return;
    }
    //increment the current size
    heapCurrentSize++;
    int i=heapCurrentSize-1;
    //add the data at the end of the array
    maxHeapp[i]=data;
    //ensure that the added item satisfy the maxheap condition
    //the loop ends when reaching the root(it has no parent)
    while (i>0){
        int parent=((i-1)/2);
        //check if the parent is greater than the current node
        if(maxHeapp[parent]<maxHeapp[i]){
            swap(maxHeapp[parent],maxHeapp[i]);
            //update the i position
            i=parent;
        }
        else{
            break;
        }
    }
}
void maxHeap::maximizeItem(int i) {
    maxHeapp[i]= maxValueItem;
    int parent=(i-1)/2;
    while (i != 0 &&  maxHeapp[parent]<maxHeapp[i] ){
        swap( maxHeapp[parent]  ,maxHeapp[i]) ;
        i=parent;
        parent=(i-1)/2;
    }
}
void maxHeap::removeRoot(string type) {
    //check if the array is empty
    if(heapCurrentSize==0){
        cout<<"Error, you can't remove Item data, the array is empty.";
        return ;
    }
    //check if the heap tree only have a root to delete it
    if(heapCurrentSize==1){
        heapCurrentSize--;
        return ;
    }
    //shifting the last element to equal the root and deleting the root
    Item root=maxHeapp[0];
    maxHeapp[0]=maxHeapp[heapCurrentSize-1];
    heapCurrentSize--;
    maxHeapp[heapCurrentSize]=root;
    //rearrange the array to maintain the max heap condition after deleting the root and swap
    maxHeapify(0,type);
}
void maxHeap::removeItemData(int i,string type) {
    //check if the array is empty
    if(heapCurrentSize==0){
        cout<<"Error, you can't remove Item data, the array is empty.";
        return;
    }
    if (i >= heapCurrentSize) {
        std::cout << "Error, index out of bounds.";
        return;
    }
    // Promote the element to the root by maximizing it
    maximizeItem(i);
    // Now remove the root element
    removeRoot(type);
}
void maxHeap::displayItemData() {
    //check if the array is empty
    if(heapCurrentSize==0){
        cout<<"Error, you can't display Item data, the array is empty.";
        return;
    }
    //ensure that the array satisfy max heap condition
    buildMaxHeap("name");
    cout<<"Heap according names: "<<endl;
    //print the current elements of the array
    for (int i = 0; i < heapCurrentSize; ++i) {
        maxHeapp[i].Print();
    }
    cout<<endl;
    //ensure that the array satisfy max heap condition
    buildMaxHeap("price");
    cout<<"Heap according prices: "<<endl;
    //print the current elements of the array
    for (int i = 0; i < heapCurrentSize; ++i) {
        maxHeapp[i].Print();
    }
    cout<<endl;
    //ensure that the array satisfy max heap condition
    buildMaxHeap("category");
    cout<<"Heap according categories: "<<endl;
    //print the current elements of the array
    for (int i = 0; i < heapCurrentSize; ++i) {
        maxHeapp[i].Print();
    }
    cout<<endl;
}
void maxHeap::sortAsc(string type) {
    //building heap ,then deleting to make the max elements at the end of the array
    buildMaxHeap(type);
    int originalSize = heapCurrentSize;
    for (int i = heapCurrentSize - 1; i >= 0; --i) {
        swap(maxHeapp[0], maxHeapp[i]);
        heapCurrentSize--;
        maxHeapify(0,type);
    }
    //update the current size as it's not actually deleted those elements,it's just a technique
    heapCurrentSize = originalSize;
    cout<<"maxHeap sorted by "<<type<<" in ascending order"<<endl;
    for(int i = 0; i < heapCurrentSize; ++i) {
        maxHeapp[i].Print();
    }
}

void maxHeap::sortDes(string type) {
    //building heap ,then deleting to make the max elements at the end of the array
    buildMaxHeap(type);
    int originalSize = heapCurrentSize;
    for (int i = heapCurrentSize - 1; i >= 0; --i) {
        swap(maxHeapp[0], maxHeapp[i]);
        heapCurrentSize--;
        maxHeapify(0,type);
    }
    //update the current size as it's not actually deleted those elements,it's just a technique
    heapCurrentSize = originalSize;
    cout<<"maxHeap sorted by "<<type<<" in descending order"<<endl;
    //prenting the array in reverse order
    for(int i = heapCurrentSize-1; i >= 0; --i) {
        maxHeapp[i].Print();
    }
}
void readItems(istream& input, maxHeap& maxHeap) {
    int numItems;
    string name, category, priceStr;
    int price;
    // Read the number of items (first line)
    input >> numItems;
    input.ignore(); // Consume newline character
    // Set max size of the heap based on number of items
    maxHeap.setHeapMaxSize(numItems) ;
    // Loop to read item data
    for (int i = 0; i < numItems; i++) {
        // Read name, category, and price
        getline(input, name);
        getline(input, category);
        getline(input, priceStr);
        // Convert price string to int
        stringstream(priceStr) >> price;
        Item newItem(name, category, price);
        maxHeap.addItemData(newItem);
        // Skip the empty line (if present)
        if (i < numItems - 1) {
            input.ignore(); // Consume the empty line
        }
    }
}
void displayMenu() {
    cout << "\nMini Menu\n";
    cout << "1. Add item data\n";
    cout << "2. Remove item data\n";
    cout << "3. Display the item data normally\n";
    cout << "4. Display all items sorted by their name ascending\n";
    cout << "5. Display all items sorted by their name descending\n";
    cout << "6. Display all items sorted by their prices ascending\n";
    cout << "7. Display all items sorted by their prices descending\n";
    cout << "8. Exit\n";
}
int main() {
    maxHeap heap(12);
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    readItems(inputFile,heap);
    inputFile.close() ;
    int choice;

    do {
        displayMenu();
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name, category;
                int price;
                cout << "Enter item name, category, and price: ";
                cin.ignore(); // Consume newline character
                getline(cin, name);
                getline(cin, category);
                cin >> price;
                cin.ignore();
                Item newItem(name, category, price);
                heap.addItemData(newItem);
                break;
            }
            case 2: {
                int index;
                cout << "Enter the index of the item to remove: ";
                cin >> index;
                heap.removeItemData(index,"name");
                break;
            }
            case 3:
                heap.displayItemData();
                break;
            case 4:
                heap.sortAsc("name");
                break;
            case 5:
                heap.sortDes("name");
                break;
            case 6:
                heap.sortAsc("price");
                break;
            case 7:
                heap.sortDes("price");
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 8);
}
