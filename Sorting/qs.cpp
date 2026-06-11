#include <bits/stdc++.h>
using namespace std;

void qsort(queue<int>& q) {
    int n = q.size();

    for (int i = 0; i < n-1; i++) {
        int idx = -1;
        int minval = INT_MAX;

        // Find min in first (n - i) elements
        for (int j = 0; j < n; j++) { 
            int cur = q.front(); 
            q.pop();

            if (j < n-i && cur < minval) {
                minval = cur;
                idx = j;
            }

            q.push(cur);
        }

        // Remove the found minimum element
        for (int j = 0; j < n; j++) {
            int cur = q.front();
            q.pop();

            if (j != idx) {
                q.push(cur);
            }
        }

        // Push minimum at the back
        q.push(minval);
    }
}

void stsort(stack<int>& st) {
    stack<int> temp;

    while (!st.empty()) {
        int cur = st.top();
        st.pop();

        // Move smaller elements back to st
        while (!temp.empty() && temp.top() < cur) {
            st.push(temp.top());
            temp.pop();
        }

        temp.push(cur);
    }

    // Move sorted back to original stack
    while (!temp.empty()) {
        st.push(temp.top());
        temp.pop();
    }
}

int main() {
    queue<int> q;
    stack<int> st;
    int n = 5;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q.push(x);
        st.push(x);
    }

    qsort(q);
    stsort(st);

    // Print stack (top to bottom)
    for (int i = 0; i < n; i++) {
        cout << st.top() << '\t';
        st.pop();
    }
    cout << endl;

    // Print queue (front to back)
    for (int i = 0; i < n; i++) {
        cout << q.front() << '\t';
        q.pop();
    }
    cout << endl;

    return 0;
}
