#include <iostream>
#include <cassert>
#include <stdexcept>
#include <string>
#include <sstream>
#include <queue>
#include<vector>
#include <algorithm>
#include<math.h>

using namespace std;


void preorder(vector<int> v, int i, int n) {
    if (i >= n)
        return;
    cout << " " << v[i];
    preorder(v, 2 * i + 1, n);
    preorder(v, 2 * i + 2, n);
}

void inorder(vector<int> v, int i, int n) {
    if (i >= n)
        return;
    inorder(v, 2 * i + 1, n);
    cout << " " << v[i];
    inorder(v, 2 * i + 2, n);
}

void postorder(vector<int> v, int i, int n) {
    if (i >= n)
        return;
    postorder(v, 2 * i + 1, n);
    postorder(v, 2 * i + 2, n);
    cout << " " << v[i];
}

vector<int> heaprebuild(int i, vector<int> v, int n) {
    if (2 * i + 1 < n) {
        int smallIndex = 2 * i + 1;
        if (smallIndex + 1 < n) {
            int rightchild = smallIndex + 1;
            if (v[rightchild] < v[smallIndex])
                smallIndex = rightchild;
        }
        if (v[i] > v[smallIndex]) {
            int a = v[i];
            v[i] = v[smallIndex];
            v[smallIndex] = a;
            return vector<int>(heaprebuild(smallIndex, v, n));
        }
        else
            return v;
    }
    else
        return v;
}

int leaves(vector<int> v, int i, int n) {
    if (i >= n)
        return 0;
    if (2 * i + 1 >= n)
        return 1;
    else
        return leaves(v, 2 * i + 1, n) + leaves(v, 2 * i + 2, n);
}


int height(vector<int> v, int i, int n) {
    if (i >= n)
        return 0;
    else
        return 1 + max(height(v, 2 * i + 1, n), height(v, 2 * i + 2, n));
}


int main() {
    string str;
    while (getline(cin, str)) {

        int n = 0;
        vector<int> v;
        queue<int> q;
        string s = str;

        //make a min heap
        make_heap(v.begin(), v.end(), greater<int>{});

        std::string delimiter = " ";

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            int g;
            stringstream stringS;
            stringS << s;
            stringS >> g;
            v.push_back(g);
            q.push(g);

            //add
            push_heap(v.begin(), v.end(), greater<int>{});
            s.erase(0, pos + delimiter.length());
            n++;
        }

        int b;
        stringstream stringS;
        stringS << s;
        stringS >> b;
        v.push_back(b);
        q.push(b);

        //add
        push_heap(v.begin(), v.end(), greater<int>{});
        n++;

        cout << "Preorder:";
        preorder(v, 0, n);
        cout << endl;
        cout << "Inorder:";
        inorder(v, 0, n);
        cout << endl;
        cout << "Postorder:";
        postorder(v, 0, n);
        cout << endl;

        cout << "Number of nodes: ";
        cout << n << endl;
        cout << "Number of leave nodes: ";
        cout << leaves(v, 0, n) << endl;
        cout << "Height: ";
        cout << height(v, 0, n) << endl;
        cout << "** after removing " << n / 2 << " nodes **" << endl;

        int n3 = n;
        for (int j = 0; j < n3 / 2; j++) {
            v[0] = v[n - 1];
            n--;
            v.pop_back();
            v = heaprebuild(0, v, n);

            q.pop();
        }

        cout << "Preorder:";
        preorder(v, 0, n);
        cout << endl;
        cout << "Inorder:";
        inorder(v, 0, n);
        cout << endl;
        cout << "Postorder:";
        postorder(v, 0, n);
        cout << endl;

        cout << "Number of nodes: ";
        cout << n << endl;
        cout << "Number of leave nodes: ";
        cout << leaves(v, 0, n) << endl;
        cout << "Height: ";
        cout << height(v, 0, n) << endl;

    }
    return 0;
}