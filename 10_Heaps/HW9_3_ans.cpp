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


int main() {
    int n;
    while (cin >> n) {
        vector<int> v1;
        vector<int> v2;
        vector<int> vSize;

        //make heap
        make_heap(v1.begin(), v1.end());
        make_heap(v2.begin(), v2.end(), greater<int>{});


        for (int i = 0; i < n; i++) {
            int b;
            cin >> b;
            if (i == 0) {
                v1.push_back(b);
                push_heap(v1.begin(), v1.end());
            }
            else if (b > v1[0]) {
                v1.push_back(b);
                push_heap(v1.begin(), v1.end());
            }
            else if (b < v1[0] && v2.size() == 0) {
                v2.push_back(b);
                push_heap(v2.begin(), v2.end(), greater<int>{});
            }
            else if (b < v1[0] && b < v2[0]) {
                v2.push_back(b);
                push_heap(v2.begin(), v2.end(), greater<int>{});
            }
        }
        sort_heap(v2.begin(), v2.end(), greater<int>{});
        sort_heap(v1.begin(), v1.end());
        int q = 0;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int v3;
            bool flag = false;
            cin >> v3;
            int size1 = v1.size();
            int size2 = v2.size();


            if (v3 != v1[size1 - 1]) {

                if (v3 > v1[size1 - 1]) {
                    v1.push_back(v3);
                    flag = true;
                }

                else if (v3 < v1[0]) {
                    v1.insert(v1.begin(), v3);
                    flag = true;
                }

                else {
                    int l = -1;
                    for (int j = 1; j < size1; j++) {
                        if (v3 > v1[j - 1] && v3 < v1[j]) {
                            l = j;
                        }
                    }
                    if (l != -1) {
                        v1.insert(v1.begin() + l, v3);
                        flag = true;
                    }
                }

                if (!flag && size2 == 0) {
                    v2.push_back(v3);
                }

                if (!flag && size2 != 0) {
                    if (v3 < v2[size2 - 1]) {
                        v2.push_back(v3);
                    }

                    else if (v3 > v2[0]) {
                        v2.insert(v2.begin(), v3);
                    }

                    else {
                        int l = -1;
                        for (int j = 1; j < size2; j++) {
                            if (v3 < v2[j - 1] && v3 > v2[j]) {
                                l = j;
                            }
                        }
                        if (l != -1) {
                            v2.insert(v2.begin() + l, v3);
                        }
                    }
                }
            }


            vSize.push_back(v1.size() + v2.size());

        }

        for (int j = 0; j < q; j++) {
            cout << vSize[j] << endl;
        }
        for (int j = 0; j < v1.size() - 1; j++) {
            cout << v1[j] << " ";
        }
        cout << v1[v1.size() - 1];
        for (int j = 0; j < v2.size(); j++) {
            cout << " " << v2[j];
        }
        cout << endl;

    }
    return 0;
}