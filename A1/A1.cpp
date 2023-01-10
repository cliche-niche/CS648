#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int pivot(vector<int> (&v), const int (&l), const int (&r), int p){
    // * v : vector, l : left end (inclusive), r : right end (inclusive), p : initial position of pivot [l, r]
    // * Partitions the subarray v[l:r] about the pivot currently at index l<=p<=r

    swap(v[p], v[r]);
    p = r;

    int i = l, j = l;
    for(; i < r; i++){
        if(v[i] < v[p]){
            if(i != j){
                swap(v[i], v[j]);
            }
            j++;
        }
    }

    swap(v[p], v[j]);
    p = j;
    return p;

    // just in case it might be needed later

    // swap(v[p], v[r]);
    // p = r;
    // int s = l;
    // int e = r;

    // while(s < e) {
    //     if(v[s] > v[p]) {
    //         if(v[e] < v[p]) {
    //             swap(v[s], v[e]);
    //             s++;
    //             e--;
    //         }
    //         else {
    //             e--;
    //         }
    //     }
    //     else {
    //         s++;
    //     }
    // }

    // swap(v[p], v[s]);
    // p = s;
    // return p; 
}

void quick_sort(vector<int> (&v), const int (&l), const int (&r)){

    if(l >= r){
        return;
    }

    int p = pivot(v, l, r, l); // Default pivot is the first element in the subarray
    quick_sort(v, l, p-1);
    quick_sort(v, p+1, r);
    return;
}

void random_quick_sort(vector<int> (&v), const int (&l), const int (&r)){

    return;
}

void merge_sort(...){
    // TODO : TO BE FILLED
}

int main(){
    vector<int> V = {2, 4, 3, 5};
    // vector<int> V = {9, 4, 1, 6, 10, 24, 5, 100};
    // quick_sort(V, 0, 9);
    pivot(V, 0, 3, 2);
    for(int i : V) {
        cout << i << " ";
    }
    return 0;
}