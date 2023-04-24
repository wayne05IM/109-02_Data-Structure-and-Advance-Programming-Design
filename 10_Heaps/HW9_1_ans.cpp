#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
#include <sstream>
#include <queue>

using namespace std;


class BST {

    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* n) {
        if (n == NULL)
            return NULL;
        {
            makeEmpty(n->left);
            makeEmpty(n->right);
            delete n;
        }
        return NULL;
    }

    node* insert(node* n, int x)
    {
        if (n == NULL)
        {
            n = new node;
            n->data = x;
            n->left = n->right = NULL;
        }
        else if (x < n->data)
            n->left = insert(n->left, x);
        else if (x > n->data)
            n->right = insert(n->right, x);
        return n;
    }

    node* findMin(node* n)
    {
        if (n == NULL)
            return NULL;
        else if (n->left == NULL)
            return n;
        else
            return findMin(n->left);
    }

    node* remove(node* n, int x) {
        node* temp;
        if (n == NULL)
            return NULL;
        else if (x < n->data)
            n->left = remove(n->left, x);
        else if (x > n->data)
            n->right = remove(n->right, x);
        else if (n->left && n->right)
        {
            temp = findMin(n->right);
            n->data = temp->data;
            n->right = remove(n->right, n->data);
        }
        else
        {
            temp = n;
            if (n->left == NULL)
                n = n->right;
            else if (n->right == NULL)
                n = n->left;
            delete temp;
        }

        return n;
    }

    void inorder(node* n) {
        if (n == NULL)
            return;
        inorder(n->left);
        cout << " " << n->data;
        inorder(n->right);
    }

    int getleaves(node* n) {
        if (n == NULL)
            return 0;
        if (n->left == NULL && n->right == NULL)
            return 1;
        else
            return getleaves(n->left) + getleaves(n->right);
    }

    int getheight(node* n) {
        if (n == NULL)
            return 0;
        else
            return 1 + max(getheight(n->left), getheight(n->right));
    }

    int numberofnode(node* n) {
        if (n == NULL)
            return 0;
        else
            return 1 + numberofnode(n->left) + numberofnode(n->right);
    }

    void preorder(node* n) {
        if (n == NULL)
            return;
        cout << " " << n->data;
        preorder(n->left);
        preorder(n->right);
    }

    void postorder(node* n) {
        if (n == NULL)
            return;
        postorder(n->left);
        postorder(n->right);
        cout << " " << n->data;
    }

    node* find(node* n, int x) {
        if (n == NULL)
            return NULL;
        else if (x < n->data)
            return find(n->left, x);
        else if (x > n->data)
            return find(n->right, x);
        else
            return n;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(root, x);
    }

    void remove(int x) {
        root = remove(root, x);
    }

    void printInorder() {
        cout << "Inorder:";
        inorder(root);
        cout << endl;
    }

    void printPreorder() {
        cout << "Preorder:";
        preorder(root);
        cout << endl;
    }

    void printPostorder() {
        cout << "Postorder:";
        postorder(root);
        cout << endl;
    }

    void printLeaves() {
        cout << "Number of leave nodes: ";
        cout << getleaves(root);
        cout << endl;
    }

    void printHeight() {
        cout << "Height: ";
        cout << getheight(root);
        cout << endl;
    }

    void printNode() {
        cout << "Number of nodes: ";
        cout << numberofnode(root);
        cout << endl;
    }
};

int main() {
    string str;
    while (getline(cin, str)) {
        BST bst;
        queue<int> q;
        int n = 0;

        string s = str;

        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            int g;
            stringstream stringS;
            stringS << s;
            stringS >> g;
            bst.insert(g);
            q.push(g);
            s.erase(0, pos + delimiter.length());
            n++;
        }

        int b;
        stringstream stringS;
        stringS << s;
        stringS >> b;
        bst.insert(b);
        q.push(b);
        n++;


        bst.printPreorder();
        bst.printInorder();
        bst.printPostorder();
        bst.printNode();
        bst.printLeaves();
        bst.printHeight();

        for (int i = 0; i < n / 2; i++) {
            bst.remove(q.front());
            q.pop();
        }

        cout << "** after removing " << n / 2 << " nodes **" << endl;
        bst.printPreorder();
        bst.printInorder();
        bst.printPostorder();
        bst.printNode();
        bst.printLeaves();
        bst.printHeight();
    }
    return 0;
}