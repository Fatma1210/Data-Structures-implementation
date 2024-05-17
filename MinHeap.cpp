#include <iostream>
#include <fstream>
#include <climits>
#include <algorithm>
using namespace std ;
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
class MinHeap {
private:
    Item *arr;
    int MaxSize;
    int heapSize;
    int deleted ;
    Item min ;
public:

    MinHeap(int maxSize) {
        heapSize = 0;
        this->MaxSize = maxSize;
        arr = new Item[maxSize];
        deleted = 0 ;
    }
    void setMaxSize(int max) {
        MaxSize = max ;
    }
    void insert(Item value) {
        if (heapSize == MaxSize) {
            cerr << "the array is full , couldn't insert any item\n";
        }
        heapSize++;
        int i = heapSize - 1;
        arr[i] = value;
        while (i != 0 and arr[i] < arr[Parent(i)]) {
            swap(arr[i], arr[Parent(i)]);
            i = Parent(i);
        }
    }

    void MinHeapifyWithPrice(int i) {
        int left = LeftChild(i);
        int right = RightChild(i);
        int Min = i;
        if (left < heapSize and arr[left].getItemPrice() < arr[Min].getItemPrice())
            Min = left;
        if (right < heapSize and arr[right].getItemPrice() < arr[Min].getItemPrice())
            Min = right;
        if (Min != i) {
            swap(arr[Min], arr[i]);
            MinHeapifyWithPrice(Min);
        }
    }
    void MinHeapifyWithName(int i) {
        int left = LeftChild(i);
        int right = RightChild(i);
        int Min = i;
        if (left < heapSize and arr[left].getItemName() < arr[Min].getItemName())
            Min = left;
        if (right < heapSize and arr[right].getItemName() < arr[Min].getItemName())
            Min = right;
        if (Min != i) {
            swap(arr[Min], arr[i]);
            MinHeapifyWithName(Min);
        }
    }
    int Parent(int i) {
        return ((i - 1) / 2);
    }
    void BuildHeap(string type){
        for(int i = (heapSize / 2) - 1 ; i >= 0 ; --i){
            if(type == "name")
            MinHeapifyWithName(i) ;
            else
                MinHeapifyWithPrice(i) ;
        }
    }
    int LeftChild(int i) {
        return (2 * i) + 1;
    }

    int RightChild(int i) {
        return (2 * i) + 2;
    }

    void RemoveMin(string type) {
        if (heapSize <= 0)
            return ;
        Item root = arr[0];
        arr[0] = arr[heapSize - 1];
        heapSize--;
        arr[heapSize] = root ;
        if(type == "name")
           MinHeapifyWithName(0);
        else
            MinHeapifyWithPrice(0) ;
    }
    void Decrease(int i , Item val){
        arr[i] = val ;
        while (i != 0 and arr[i] < arr[Parent(i)]){
            swap(arr[i]  ,arr[Parent(i)]) ;
            MinHeapifyWithName(0) ;
        }
    }
    void Delete(int i){
        Decrease(i , min) ;
        RemoveMin("name") ;
        deleted++;
    }
    void HeapSort(string type) {
             BuildHeap(type) ;
        while (heapSize) {
            RemoveMin(type) ;
        }
    }
   void PrintHeap(){
        BuildHeap("name") ;
        cout << "heap according Names : \n" ;
        for(int i = 0 ; i < heapSize ; ++i){
                arr[i].Print() ;
        }
        cout << endl;
       BuildHeap("Price") ;
       cout << "heap according Prices : \n";
       for(int i = 0 ; i < heapSize ; ++i){
           arr[i].Print() ;
       }
       cout << endl;
    }
    void PrintSortedInDescendingOrder(string type) {
        HeapSort(type);
        for (int i = 0; i < MaxSize - deleted - 1; ++i) {
            arr[i].Print() ;
        }
        cout << endl;
    }

    void PrintSortedInAscendingOrder(string type) {
        HeapSort(type);
        for (int i = MaxSize - deleted - 2; i >= 0; --i) {
            arr[i].Print() ;
        }
        cout << endl;
    }

    ~MinHeap() {
        delete []arr;
    }
};
int toInt(string line){
    int num = 0 ;
    int base = 1 ;
    for(int i = line.size() - 1; i >= 0 ; i--){
        if(line[i] != ' '){
            num += ((line[i] - '0') * base) ;
            base *= 10 ;
        }
    }
    return num ;
}
int main() {
    MinHeap  heap(12) ;
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    string line ;
    int cnt = 0 ;
    Item item ;

    while (getline(inputFile ,line)){
        string l = "" ;
        for(char c : line){
            if(c != ' ') l += c ;
        }
        if(cnt == 0)
            heap.setMaxSize(toInt(l)) ;
        else if(cnt == 1)
            item.setItemName(l) ;
        else if(cnt == 2)
            item.setItemCategory(l) ;
        else if(cnt == 3)
            item.setItemPrice(toInt(l)) ;
        else {
            heap.insert(item);
            cnt = 0 ;
        }
        cnt++;
    }
    inputFile.close() ;
    heap.PrintHeap() ;
    heap.Delete(3) ;
 heap.PrintHeap() ;
heap.PrintSortedInDescendingOrder("price");
heap.PrintSortedInAscendingOrder("price");
heap.PrintSortedInDescendingOrder("name");
heap.PrintSortedInAscendingOrder("name");
    return 0;
}
