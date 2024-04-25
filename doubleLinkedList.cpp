#include<bits/stdc++.h>
using namespace std;
#define Fatma ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
int N = 1e5+ 5 ;
template<class t>
class Node{
public:
    t data ;
    Node *next ;
    Node *prev ;
};
template <class t>
class circularSinglyLinkedList{
private:
    Node<t>*head;
    Node<t>*tail;
    int Length ;
public:
    circularSinglyLinkedList(){
        head = NULL ;
        tail = NULL ;
        Length = 0 ;
    }
    Node<t>* newNode(t key){
     Node<t>*node = new Node<t> ;
     node->data = key ;
     node->next = NULL ;
        return node ;
    }
    void insertAtHead(t el) {
        Node<t> *node = newNode(el);
        if (head == NULL) {
            head = node;
            tail = node;
            head->next = NULL;
            head->prev = NULL;
        } else {
            head->prev = node ;
            node->next = head ;
            node->prev = NULL ;
            head = node ;
        }
        Length++;
    }
    void insertAtTail(t el){
       Node<t> *node = newNode(el);
        if(head == NULL){
            head = node;
            tail = node;
            head->next = NULL;
            head->prev = NULL;
        }
        else {
            tail->next = node ;
            node->prev = tail ;
            node->next = NULL ;
            tail = node ;
        }
        Length++;
    }
    void insertAt(t el , int idx){
        if(idx > Length + 1)
            return;
        else if(idx == 1)
            insertAtHead(el) ;
        else if(idx == Length + 1)
            insertAtTail(el) ;
        else {
            int cnt = 1 ;
            Node<t> *first = head , *second = first->next;
            while (cnt != idx - 1){
                first = first->next ;
                second = second->next ;
                cnt++;
            }
            Node<t> *node ;
            node = newNode(el) ;
            node->next = second ;
            node->prev = first ;
            second->prev = node ;
            first->next = node ;
            Length++;
        }
    }
    void removeAtTail (){
        Node<t> *temp ;
        if(head == NULL)
            return;
        temp = tail ;
        tail = tail->prev ;
        tail->next = NULL ;
        Length--;
        delete temp ;

    }
    void removeAtHead () {
        if(head == NULL)
            return;
        Node<t> *temp = head ;
        head = head->next ;
        head->prev = NULL ;
        delete temp ;
        Length--;
    }
    void removeAt(int idx) {
      Node<t> *prev , *current = head  , *temp;
      if(head == NULL)
          return;
      if(idx == 1)
          removeAtHead() ;
      else if(idx == Length)
          removeAtTail() ;
      else {
          int cnt = 1;
          while (cnt != idx) {
              prev = current;
              current = current->next;
              cnt++;
          }
         temp = current ;
          prev->next = current->next ;
          current->next->prev = prev ;
          delete temp;
          Length--;
      }
    }
    void retrieveAt(int idx) {
        Node<t> *current = head ;
        int cnt = 1 ;
        while (cnt != idx){
            current = current->next ;
            cnt++;
        }
        cout << current->data << endl;
    }
    void replaceAt(t el , int idx) {
        Node<t> *current = head ;
        int cnt = 1 ;
        while (cnt != idx){
            current = current->next ;
            cnt++;
        }
        current->data = el ;
    }
    bool isExist(t el) {
        Node<t> *current = head;
        if (head == NULL)
            return 0;
        while (current->next != NULL) {
            if (current->data == el)
                return 1;
            current = current->next;
        }
        if (current->data == el)
            return 1;
        return 0;
    }
    bool isItemAtEqual(t el , int idx){
        Node<t> *current = head ;
        int cnt = 1 ;
        while (cnt != idx){
            current = current->next ;
            cnt++;
        }
        if(current->data == el)
            return 1;
        return 0;
    }
    void swap(int firstItemIdx, int secondItemIdx){
        Node<t> *node1 , *node2 , *current = head;
        int cnt = 1 ;
        while (current->next != NULL){
            if(firstItemIdx == cnt)
                node1 = current ;
            if(secondItemIdx == cnt)
                node2 = current ;
            current = current->next ;
            cnt++;
        }
        if(firstItemIdx == Length)
            node1 = current ;
        if(secondItemIdx == Length)
            node2 = current ;
        t temp = node1->data ;
        node1->data = node2->data ;
        node2->data = temp ;
    }
    bool isEmpty () {
        return head == NULL ;
    }
    int linkedListSize() const{
        return Length ;
    }
    void clear() {
        if (head == NULL)
            return;
        else {
            Node<t> *current = head  ;
            while (current->next != NULL){
                Node<t>*temp = head;
                head = current->next ;
                head->prev = NULL ;
                current = current->next ;
                delete temp ;
            }
            tail = NULL ;
            head = NULL;
        }
        Length = 0;
    }
    void printForward() {
        Node<t> *current = head;
        if (head == NULL)
            return;
        while (current->next != NULL) {
            cout << current->data << ' ';
            current = current->next;
        }
        cout << current->data << endl;
    }
        void printBackward() {
            Node<t>* current = tail ;
            if(head == NULL)
                return;
            while (current->prev != NULL){
                cout << current->data << ' ' ;
                current = current->prev ;
            }
            cout << current->data << endl;
        }
};

signed main() {
    Fatma
    circularSinglyLinkedList<int> c;
    c.insertAtHead(10);
    c.insertAtHead(5);
    c.insertAtHead(50);
    c.insertAtTail(13);
    c.insertAtTail(5);
    c.insertAtTail(24);
    c.insertAt(40, 3);
    c.insertAt(15, 6);
    c.insertAt(13, 8);
    c.insertAt(100, 10);
    c.insertAt(44, 1);
    c.removeAtHead();
    c.removeAtTail();
    c.removeAt(2);
    c.retrieveAt(1);
    c.replaceAt(500, 4);
    cout << (c.isExist(500) ? "YES\n" : "NO\n");
    cout << (c.isExist(5) ? "YES\n" : "NO\n");
    cout << (c.isExist(10) ? "YES\n" : "NO\n");
    cout << (c.isExist(30) ? "YES\n" : "NO\n");
    cout << (c.isItemAtEqual(10, 3) ? "YES\n" : "NO\n");
    cout << (c.isItemAtEqual(50, 1) ? "YES\n" : "NO\n");
    cout << (c.isItemAtEqual(24, 8) ? "YES\n" : "NO\n");
    cout << (c.isItemAtEqual(1000, 3) ? "YES\n" : "NO\n");
    cout << (c.isEmpty() ? "Empty\n" : "NotEmpty\n");
    cout << c.linkedListSize() << endl;
    c.swap(3, 6);
    c.swap(1, 8);
    c.printForward();
    c.printBackward();
    c.clear();
    c.printForward();
    cout << (c.isEmpty() ? "Empty\n" : "NotEmpty\n");
    return 0;
}