#include<bits/stdc++.h>
using namespace std;
#define Fatma ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
int N = 1e5+ 5 ;
template<class t>
class Node{
public:
    t data ;
    Node *next ;
};
template <class t>
class circularSinglyLinkedList{
private:
    Node<t>*head ;
    int Length ;
public:
    circularSinglyLinkedList(){
        head = NULL ;
        Length = 0 ;
    }
    Node<t>* newNode(t key){
     Node<t>*node = new Node<t> ;
     node->data = key ;
     node->next = NULL ;
        return node ;
    }
    void insertAtHead(t el) {
        Node<t> *node = newNode(el) , *last = head;
        if (head == NULL) {
            head = node ;
            head->next = head ;

        } else {
            while (last->next != head){
                last = last->next ;
            }
            last->next = node ;
            node->next = head ;
            head = node ;
        }
        Length++;
    }
    void insertAtTail(t el){
       Node<t> *node = newNode(el) , *last = head;
        if(head == NULL){
            head = node ;
            head->next = head ;
        }
        else {
            while (last->next != head){
                last = last->next ;
            }
            last->next = node ;
            node->next = head ;
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
            first->next = node ;
            node->next = second ;
            Length++;
        }
    }
    void removeAtTail (){
        Node<t> *temp , *last = head , *prev;
        if(head == NULL)
            return;
        while (last->next != head){
            prev = last ;
            last = last->next ;
        }
        temp = last ;
        prev->next = head ;
        Length--;
        delete temp ;

    }
    void removeAtHead () {
        if(head == NULL)
            return;
        else {
            Node<t> *temp = head , *last = head;
            while (last->next != head){
                last = last->next ;
            }
            head = head->next;
            last->next = head ;
            delete temp;
            Length--;
        }
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
        while (current->next != head) {
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
        while (current->next != head){
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
            Node<t> *current = head->next ;
            while (current!= head){
                Node<t>*temp = current;
                head = current->next ;
                current = current->next ;
                delete temp ;
            }
            head = NULL;
        }
        Length = 0;
    }
    void print() {
        Node<t>* current = head ;
        if(head == NULL)
            return;
        while (current->next != head){
            cout << current->data << ' ' ;
            current = current->next ;
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
    c.retrieveAt(1) ;
    c.replaceAt(500 , 4) ;
    cout <<(c.isExist(500) ? "YES\n" : "NO\n") ;
    cout <<(c.isExist(5) ? "YES\n" : "NO\n") ;
    cout <<(c.isExist(10) ? "YES\n" : "NO\n") ;
    cout <<(c.isExist(30) ? "YES\n" : "NO\n") ;
    cout << (c.isItemAtEqual(10 , 3) ? "YES\n" : "NO\n") ;
    cout << (c.isItemAtEqual(50 , 1) ? "YES\n" : "NO\n") ;
    cout << (c.isItemAtEqual(24 , 8) ? "YES\n" : "NO\n") ;
    cout << (c.isItemAtEqual(1000 , 3) ? "YES\n" : "NO\n") ;
    cout << (c.isEmpty() ? "Empty\n" : "NotEmpty\n") ;
    cout << c.linkedListSize() << endl;
    c.swap(3 , 6) ;
    c.swap(1 , 8) ;
    c.print() ;
    c.clear() ;
//    c.print() ;
    cout << (c.isEmpty() ? "Empty\n" : "NotEmpty\n") ;
    return 0;
}