#include <string>
#include<iostream>
#include<queue>
#include <fstream>
#include <sstream>
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
////////////////////////////
class BST {
    struct BST_Node {
        Item item;
        BST_Node* left;
        BST_Node* right;
    };


    BST_Node* DeleteAllNodes(BST_Node* node) {
        if (node == NULL)
            return NULL;
        {
            DeleteAllNodes(node->left);
            DeleteAllNodes(node->right);
            delete node;
        }
        return NULL;
    }

    BST_Node* AddNode(Item item, BST_Node* node, string attribute) {
        if (node == NULL) {    // tree is empty
            node = new BST_Node;
            node->item = item;
            node->left = NULL;
            node->right = NULL;
        } else if (attribute == "Name") {
            if (item.getItemName() < node->item.getItemName())
                node->left = AddNode(item, node->left, attribute);
            else if (item.getItemName() > node->item.getItemName())
                node->right = AddNode(item, node->right, attribute);
        }
        else if (attribute == "Category") {
            if (item.getItemCategory() < node->item.getItemCategory())
                node->left = AddNode(item, node->left, attribute);
            else if (item.getItemCategory() > node->item.getItemCategory())
                node->right = AddNode(item, node->right, attribute);
        }
         else if (attribute == "Price") {
            if (item.getItemPrice() < node->item.getItemPrice())
                node->left = AddNode(item, node->left, attribute);
            else if (item.getItemPrice() > node->item.getItemPrice())
                node->right = AddNode(item, node->right, attribute);
        }
        return node;
    }
    BST_Node* deleteNode(Item item, BST_Node* node) {
        BST_Node* temp;
        if (node == NULL) {
            cout << "No items found with name " <<item.getItemName()<< endl;
            return NULL;
        }
        if (item.getItemName() < node->item.getItemName())
            node->left = deleteNode(item, node->left);
        else if (item.getItemName() > node->item.getItemName())
            node->right = deleteNode(item, node->right);
        else {
            if (node->left && node->right) {
                temp = Min(node->right);
                node->item = temp->item;
                node->right = deleteNode(temp->item, node->right);
            } else {
                temp = node;
                if (node->left == NULL)
                    node = node->right;
                else if (node->right == NULL)
                    node = node->left;
                delete temp;
            }
        }
        return node;
    }
    BST_Node* root;
    BST_Node* Min(BST_Node* node) {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;

    }
    void ASCorder(BST_Node* node, string attribute) {
        if (node == NULL)
            return;
        ASCorder(node->left, attribute);

        node->item.Print();
        ASCorder(node->right, attribute);
    }

    void DESCorder(BST_Node* node, string attribute) {
        if (node == NULL)
            return;
        DESCorder(node->right, attribute);

        node->item.Print();
        DESCorder(node->left, attribute);
    }





public:
    BST() {
        root = NULL;
    };
    ~BST() {
        root = DeleteAllNodes(root);
    };
    BST_Node* getRoot() const {
        return root;
    }
    void AddNode(Item item, string attribute) {
        root = AddNode(item, root, attribute);
    }

    void deleteNode(Item item) {
        root = deleteNode(item, root);
    }
    void PrintASC(string attribute) {
        ASCorder(root,attribute);
        cout << endl;
    }

    void PrintDESC(string attribute) {
        DESCorder(root,attribute);
        cout << endl;
    }
    void PrintLevelOrder() {
        if (root == NULL)
            return;

        queue<BST_Node *> q;
        q.push(root);

        while (!q.empty()) {
            BST_Node *current = q.front();
            q.pop();

            current->item.Print();

            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
        }
    }

    void DeleteAllNode() {
        DeleteAllNodes(root);
        root = nullptr; // After deleting all nodes, set the root pointer to nullptr
    }
};

void readItems(istream& fileStream, BST& bst, string attribute) {
    int numItems;
    fileStream >> numItems;

    string line;
    getline(fileStream, line);

    for (int i = 0; i < numItems; ++i) {
        string name, category;
        int price;
        getline(fileStream, name);
        getline(fileStream, category);
        fileStream >> price;
        getline(fileStream, line);
        Item item(name,category, price);
        bst.AddNode(item, attribute);
    }
};
int main() {
    BST bst;
    BST bst1;
    ifstream inputFile("input.txt");
    string attribute ;

    cout << "Enter the attribute by which you want to compare items in the tree:" << endl
         << "Options: Name, Price, or Category" << endl;
    cin>>attribute;
    if (attribute != "Price" && attribute != "Name" && attribute != "Category") {
        cout << "Invalid attribute" << endl;
        cin >> attribute;
    }


    if (inputFile.is_open()) {
        readItems(inputFile,bst,attribute);

    } else {
        cout << "Unable to open file" << endl;
    }
    while (true){
        cout << "1. Add item " << endl << "2. Remove item " << endl
             << "3. Display the item data normally" << endl
             << "4. Display all the items sorted by their name ascending" << endl
             << "5. Display all the items sorted by their name descending" << endl
             << "6. Display all the items sorted by their prices ascending" << endl
             << "7. Display all the items sorted by their prices descending" << endl
             << "8. Exit" << endl;

        int choice;
        cin >> choice;
        if (choice==1){
            string name, category,attri;
            int price;
            attri=attribute;
            cout << "Enter item attributes:" << endl;
            cout << "Name: ";
            cin >> name;
            cout << "Category: ";
            cin >> category;
            cout << "Price: ";
            cin >> price;
            bst.AddNode(Item(name, category, price), attri);
            cout << "Item added successfully"<<endl;
        }
        else if (choice ==2){
            string name, category;
            int price;

            cout << "Name: ";
            cin >> name;

            bst.deleteNode(Item(name, "", 0));
            cout << "Item deleted successfully"<<endl;
        }
        else if(choice==3){
            bst.PrintLevelOrder();
        }
        else if(choice==4){
            if (attribute == "Price" || attribute == "Category") {
                bst.DeleteAllNode();
                ifstream inputFile("items.txt");
                if (inputFile.is_open()) {
                    readItems(inputFile, bst, "Name");
                    inputFile.clear();
                    inputFile.seekg(0, ios::beg);
                    inputFile.close();
                    cout << "Items sorted by Name and printed in ascending order:" << endl;
                    bst.PrintASC("Name");
                } else {
                    cout << "Unable to open file" << endl;
                }
                break;
            }
            bst.PrintASC("Name");
        }
        else   if(choice==5){
            if (attribute == "Price" || attribute == "Category") {
                bst.DeleteAllNode();
                ifstream inputFile("items.txt");
                if (inputFile.is_open()) {
                    readItems(inputFile, bst, "Name");
                    inputFile.clear();
                    inputFile.seekg(0, ios::beg);
                    inputFile.close();
                    cout << "Items sorted by name and printed in descending order:" << endl;
                    bst.PrintDESC("Name");
                } else {
                    cout << "Unable to open file" << endl;
                }
                break;
            }
            bst.PrintDESC("Name");
}
        else  if(choice==6){
       if (attribute == "Name"|| attribute == "Category") {
           bst.DeleteAllNode();
           ifstream inputFile("items.txt");
           if (inputFile.is_open()) {
               readItems(inputFile, bst, "Price");
               inputFile.clear();
               inputFile.seekg(0, ios::beg);
               inputFile.close();
               cout << "Items sorted by price and printed in ascending order:" << endl;
               bst.PrintASC("Price");
           } else {
               cout << "Unable to open file" << endl;
           }
           break;
       }
           else{
            bst.PrintASC("Price");}
        }
   else if(choice==7){
            if(attribute=="Name"|| attribute == "Category"){
            bst.DeleteAllNode();
            ifstream inputFile("items.txt");
            if (inputFile.is_open()) {
                readItems(inputFile, bst, "Price");
                inputFile.clear();
                inputFile.seekg(0, ios::beg);
                inputFile.close();
                cout << "Items sorted by price and printed in descending order:" << endl;
                bst.PrintDESC("Price");
            } else {
                cout << "Unable to open file" << endl;
            }
            break;}
            else{
                bst.PrintDESC("Price");
            }
        }
     else if(choice==8){
            break;
     }
        else{
            cout<<"invalid input"<<endl;
        }
    }

}
