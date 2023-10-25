#include<iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <cmath>
// i = 2, j = 3

using namespace std;

const string red = "\033[1;31m";
const string green = "\033[1;32m";
const string resetColor = "\033[0m";
const string underline = "\033[4m";

class Node {
private:
    int key;
    Node *left;
    Node *right;
    int height;
    int balance;

public:
    Node(int key) : key(key), left(nullptr), right(nullptr), height(1), balance(0) {
        this->key = key;
    }

    int calculateHeight() {

        stack<Node*> nodes;
        stack<int> depths;

        nodes.push(this);
        depths.push(0);

        int maxHeight = 0;

        while(!nodes.empty()) {
            Node *currentNode = nodes.top();
            nodes.pop();

            int currentDepth = depths.top();

            maxHeight = max(maxHeight, currentDepth);

            if(currentNode->getLeft() != nullptr) {
                nodes.push(currentNode->getLeft());
                depths.push(currentDepth+1);
            }
            if(currentNode->getRight() != nullptr) {
                nodes.push(currentNode->getRight());
                depths.push(currentDepth+1);
            }
        }

        return maxHeight;
    }

    //<editor-fold desc="Getters">

    int getKey() const {
        return this->key;
    }

    Node *getLeft() const {
        return this->left;
    }

    Node *getRight() const {
        return this->right;
    }

    int getHeight() const {
        return this->height;
    }

    int getBalance() const {
        return this->balance;
    }

    //</editor-fold>

    //<editor-fold desc="Setters">

    void setKey(int key) {
        this->key = key;
    }

    void setLeft(Node *left) {
        this->left = left;
    }

    void setRight(Node *right) {
        this->right = right;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setBalance(int balance) {
        this->balance = balance;
    }

    //</editor-fold>

};

class AVL {
private:
    Node *root;
    int height;

public:
    AVL() : root(nullptr), height(0) {}

    void updateHeight(Node *node) {
        node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));
    }

    //<editor-fold desc="Rotations">

    Node *rightRotation(Node *x) {
        Node *y = x->getLeft();
        Node *temp = y->getRight();
        y->setRight(x);
        x->setLeft(temp);
        updateHeight(y);
        updateHeight(x);
        return y;
    }

    Node *leftRotation(Node *x) {
        Node *y = x->getRight();
        Node *temp = y->getLeft();
        y->setLeft(x);
        x->setRight(temp);
        updateHeight(y);
        updateHeight(x);

        return y;
    }

//</editor-fold>

    int getHeight(Node *node) const {
        if (node == nullptr) return 0;
        return this->height;
    }

    int getBalanceOfNode(Node *node) const {
        if (node == nullptr) return 0;
        return getHeight(node->getLeft()) - getHeight(node->getRight());
    }

    //<editor-fold desc="Insert 1">
    void MyAVLInsert(int key) {
        stack<Node *> path;
        Node *node = root;

        while (node != nullptr) {
            if (node->getKey() == key) return; // Duplicates

            path.push(node);
            if (key < node->getKey()) {
                if (node->getLeft() == nullptr) {
                    node->setLeft(new Node(key));
                    break;
                }
                node = node->getLeft();
            } else {
                if (node->getRight() == nullptr) {
                    node->setRight(new Node(key));
                    break;
                }
                node = node->getRight();
            }
        }

        if (root == nullptr) {
            root = new Node(key);
            return;
        }

        while (!path.empty()) {
            Node *current_node = path.top();
            path.pop();

            updateHeight(current_node);
            int balance = getBalanceOfNode(current_node);

            // LL
            if (balance > 1 && key < current_node->getLeft()->getKey()) {
                if (current_node == root) root = rightRotation(current_node);
                else current_node = rightRotation(current_node);
            }
            // RR
            else if (balance < -1 && key > current_node->getRight()->getKey()) {
                if (current_node == root) root = leftRotation(current_node);
                else current_node = leftRotation(current_node);
            }
            // LR
            else if (balance > 1 && key > current_node->getLeft()->getKey()) {
                current_node->setLeft(leftRotation(current_node->getLeft()));
                if (current_node == root) root = rightRotation(current_node);
                else current_node = rightRotation(current_node);
            }
            // RL
            else if (balance < -1 && key < current_node->getRight()->getKey()) {
                current_node->setRight(rightRotation(current_node->getRight()));
                if (current_node == root) root = leftRotation(current_node);
                else current_node = leftRotation(current_node);
            }
        }
    }
//</editor-fold>

    //<editor-fold desc="Insert 2 (used in the project)">

    Node *AVLInsert(int K) {

        Node *node = new Node(K);
        Node *fp = nullptr;
        Node *fx = nullptr;
        Node *p = root;
        Node *x = p;
        Node *q = new Node(K);
        int imbal;

        if(!root) {
            root = node;
            return node;
        }

        while(p != nullptr) {
            if(K == p->getKey()) {
                return p;
            }
            if(K < p->getKey()) {
                q = p->getLeft();
            }
            else {
                q = p->getRight();
            }
            if(q != nullptr) {
                if(q->getBalance() != 0) {
                    fx = p;
                    x = q;
                }
            }
            fp = p;
            p = q;
        }
        q = new Node(K);
        q->setBalance(0);

        if(K < fp->getKey()) {
            fp->setLeft(q);
        }
        else {
            fp->setRight(q);
        }
        if(K < x->getKey()) {
            p = x->getLeft();
        }
        else {
            p = x->getRight();
        }
        Node *y = p;
        while(p != q) {
            if(K < p->getKey()) {
                p->setBalance(1);
                p = p->getLeft();
            }
            else {
                p->setBalance(-1);
                p = p->getRight();
            }
        }

        if(K < x->getKey()) {
            imbal = 1;
        }
        else imbal = -1;

        if(x->getBalance() == 0) {
            x->setBalance(imbal);
            return q;
        }

        if(x->getBalance() != imbal) {
            x->setBalance(0);
            return q;
        }
        if(y->getBalance() == imbal) {
            p = y;
            if(imbal == 1) {
                rightRotation(x);
            }
            else {
                leftRotation(x);
            }
            x->setBalance(0);
            y->setBalance(0);
        }

        else {

            if(imbal == 1) {
                p = y->getRight();
                leftRotation(y);
                x->setLeft(p);
                rightRotation(x);
            }
            else {
                p = y->getLeft();
                x->setRight(p);
                rightRotation(y);
                leftRotation(x);
            }
            if(p->getBalance() == 0) {
                x->setBalance(0);
                y->setBalance(0);
            }
            else {
                if(p->getBalance() == imbal) {
                    x->setBalance(-imbal);
                    y->setBalance(0);
                }
                else {
                    x->setBalance(0);
                    y->setBalance(imbal);
                }
                p->setBalance(0);
            }

        }


        if(fx == nullptr) {
            root = p;
        }
        else {
            if(x == fx->getRight()) {
                fx->setRight(p);
            }
            else {
                fx->setLeft(p);
            }
        }
        return q;
    }

    //</editor-fold>

    void printTree(AVL *tree) {

        if (!tree) return;
        if (!tree->root) return;

        queue<Node *> q;
        int i, line_len = 62;
        int first_skip = line_len, in_between_skip;
        q.push(tree->root);

        for (i = 0; i <= tree->getRoot()->calculateHeight(); i++) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip - 2) / 2;
            for (k = 0; k < first_skip; k++) cout << " ";
            for (k = 0; k < j; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    q.push(btn->getLeft());
                    q.push(btn->getRight());
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                }
                if (btn) cout << setw(2) << btn->getKey();
                else printf("  ");
                for (l = 0; l < in_between_skip; l++) cout << " ";
            }
            cout << endl << endl;
        }
    }

    void Inorder(Node *root) {
        stack<Node*> s;
        Node *curr = root;

        while(curr != nullptr || !s.empty()) {
            while(curr != nullptr) {
                s.push(curr);
                curr = curr->getLeft();
            }
            curr = s.top();
            s.pop();

            cout << curr->getKey() << " ";

            curr = curr->getRight();
        }
    }

    bool isElementInSet(Node *searchNode) {
        Node *root = this->getRoot();
        while (root != nullptr) {
            if (searchNode->getKey() == root->getKey()) {
                return true;
            } else if (searchNode->getKey() < root->getKey()) {
                root = root->getLeft();
            } else {
                root = root->getRight();
            }
        }
        return false;
    }

    void symmetricDifference(Node *root1, Node *root2, AVL &result) {
        stack<Node*> s1;
        stack<Node*> s2;
        Node *current1 = root1, *current2 = root2;
        bool ok = true;

        while(ok) {
            while(current1 != nullptr) {
                s1.push(current1);
                current1 = current1->getLeft();
            }
            while(current2 != nullptr) {
                s2.push(current2);
                current2 = current2->getLeft();
            }

            if(!s1.empty() && !s2.empty()) {
                current1 = s1.top();
                current2 = s2.top();

                if(current1->getKey() == current2->getKey()) {
                    s1.pop();
                    s2.pop();
                    current1 = current1->getRight();
                    current2 = current2->getRight();
                }
                else if(current1->getKey() < current2->getKey()) {
                    result.AVLInsert(current1->getKey());
                    s1.pop();
                    current1 = current1->getRight();
                    current2 = nullptr;
                }
                else {
                    result.AVLInsert(current2->getKey());
                    s2.pop();
                    current2 = current2->getRight();
                    current1 = nullptr;
                }

            }
            else if(!s1.empty()) {
                current1 = s1.top();
                s1.pop();
                result.AVLInsert(current1->getKey());
                current1 = current1->getRight();
            }
            else if(!s2.empty()) {
                current2 = s2.top();
                s2.pop();
                result.AVLInsert(current2->getKey());
                current2 = current2->getRight();
            }
            else {
                ok = false;
            }

        }

    }

    void deleteTree() {
        if (root == nullptr) {
            cout << "\nThe tree is already empty." << endl;
        } else {
            std::stack<Node*> nodeStack;
            nodeStack.push(root);

            while (!nodeStack.empty()) {
                Node* current = nodeStack.top();
                nodeStack.pop();

                if (current->getRight())
                    nodeStack.push(current->getRight());
                if (current->getLeft())
                    nodeStack.push(current->getLeft());

                delete current;
            }

            root = nullptr;  // Root reset
            cout << "\nThe tree was successfully deleted." << endl;
        }
    }

    // <editor-fold desc="Getters">

    Node *getRoot() {
        return root;
    }

    int getHeight() const {
        return this->height;
    }

    //</editor-fold>

    //<editor-fold desc="Setters">

    void setRoot(Node *root) {
        this->root = root;
    }

    void setHeight(int height) {
        this->height = height;
    }

    //</editor-fold>

};

void finish() {
    printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printf("\xB3         Exiting the program...       \xB3\n");
    printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    printf("----------------------------------------");
    printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
    printf("\xB3    Program successfully completed!   \xB3\n");
    printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
    exit(0);
}

int main() {

        AVL *set = nullptr;
        int choice;
    do {
        printf("\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n");
        printf("\xB3                 MENU                 \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  1. CREATE AN EMPTY SET              \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  2. INSERT ELEMENTS INTO SET         \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  3. ELEMENT BELONGS TO A SET?        \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  4. SYMMETRIC DIFFERENCE OF TWO SETS \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  5. PRINT THE TREE                   \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  6. DELETE THE SET                   \xB3\n");
        printf("\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n");
        printf("\xB3  0. EXIT                             \xB3\n");
        printf("\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n");
        cout << "\xB3Unesite broj za odabir zeljene opcije: " << endl << "\xC4>";
        cin >> choice;

        switch (choice) {
            case 1: {
                delete set;
                cout << "You have selected an option \"CREATE AN EMPTY SET\"" << endl;
                set = new AVL();
                cout << "\nYou have successfully created an empty set!" << endl;
                break;
            }
            case 2: {
                cout << "You have selected an option \"INSERT ELEMENTS INTO SET\"" << endl;
                if(set == nullptr) {
                    cout << "\nFirst, create an empty set." << endl;
                    break;
                }
                cout << "\xB3" << "Enter the elements you want to insert into the set (separate elements with a space): " << endl << "\xC4>";
                cin.ignore();
                string line;
                getline(cin, line);
                stringstream ss(line);
                putchar('\n');
                if(line.empty()) {
                    cout << "You have not added anything to the set." << endl;
                    break;
                }
                int data;
                while(ss >> data) {
                    Node *node = new Node(data);
                    if(!set->isElementInSet(node)) {
                        set->AVLInsert(data);
                        cout << "Element with key " << data << " has been successfully added to the set." << endl;
                    }
                    else {
                        cout << "Element with key " << data << " already exists in the set." << endl;
                    }
                }

                break;
            }

            case 3: {
                cout << "You have selected an option \"ELEMENT BELONGS TO A SET?\"" << endl;
                if(!set) {
                    cout << "\nFirst, create an empty set and add elements to it." << endl;
                    break;
                }
                cout << "\xB3" << "Enter the element you want to check if it's in the set: " << endl << "\xC4>";
                int data;
                cin >> data;
                Node *node = new Node(data);
                if(set->isElementInSet(node)) {
                    cout << green << "Successfully found the element with key " << node->getKey() << " in the set!" << resetColor << endl;
                }
                else {
                    cout << red << "The key " << node->getKey() << " was not successfully found in the set." << resetColor << endl;
                }
                break;
            }

            case 4: {
                cout << "You have selected an option \"SYMMETRIC DIFFERENCE OF TWO SETS\"" << endl;
                cout << "\xB3" << "Enter the elements of the first set (separate elements with a space): " << endl << "\xC4>";
                cin.ignore();
                string line;
                getline(cin, line);
                stringstream ss(line);
                int data;

                AVL *set1 = new AVL();
                while(ss >> data) {
                    Node *node = new Node(data);
                    if(!set1->isElementInSet(node)) {
                        set1->MyAVLInsert(data);
                    }
                }
                cout << "The first set is: " << endl;
                set1->printTree(set1);
                cout << "Inorder traversal of the first set: " << endl;
                set1->Inorder(set1->getRoot());
                cout << "\n\n";

                cout << "\xB3" << "Enter the elements of the second set (separate elements with a space): " << endl << "\xC4>";
                getline(cin, line);
                stringstream ss2(line);
                AVL *set2 = new AVL();
                while(ss2 >> data) {
                    Node *node = new Node(data);
                    if(!set2->isElementInSet(node)) {
                        set2->AVLInsert(data);
                    }
                }
                cout << "The second set is: " << endl;
                set2->printTree(set2);
                cout << "Inorder traversal of the second set: " << endl;
                set2->Inorder(set2->getRoot());
                cout << "\n\n";

                AVL *result = new AVL();
                set1->symmetricDifference(set1->getRoot(), set2->getRoot(), *result);
                cout << "The resulting set is: " << endl;
                result->printTree(result);
                cout << "The symmetric difference of the two sets is: " << endl;
                result->Inorder(result->getRoot());

                break;
            }

            case 5: {
                cout << "You have selected an option \"PRINT THE TREE\"" << endl;
                if(!set) {
                    cout << "\nFirst, create an empty set and add elements to it." << endl;
                    break;
                }
                if(!set->getRoot()) {
                    cout << "\nThe tree is empty. Enter elements into the set to display it." << endl;
                    break;
                }
                cout << endl;
                cout << "\t\t\t     " << underline << "TREE\n" << resetColor << endl;
                set->printTree(set);
                cout << "Inorder traversal: " << endl;
                set->Inorder(set->getRoot());
                break;
            }

            case 6: {
                cout << "You have selected an option \"DELETE THE SET\"" << endl;
                if(!set) {
                    cout << "\nFirst create a tree so you can delete it." << endl;
                    break;
                }
                set->deleteTree();
                break;
            }

            case 0:
                finish();
                break;

            default:
                cout << "Wrong choice, please enter the numbers 1, 2, 3, 4, 5, 6, or 0 to exit." << endl;
        }

    } while (choice != 0);

    return 0;
}