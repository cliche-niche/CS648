#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int pivot(vector<int> (&v), const int (&l), const int (&r), int p){
    // * v : vector, l : left end (inclusive), r : right end (inclusive), p : initial position of pivot [l, r]
    // * Partitions the subarray v[l:r] about the pivot currently at index l<=p<=r

    swap(v[p], v[r]);
    p = l;

    for(int i = l; i < r; i++){
        if(v[i] < v[r]){
            if(i != p){
                swap(v[i], v[p]);
            }
            p++;
        }
    }

    swap(v[p], v[r]);
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
    // * Quick Sort the subarray v[l:r] (both ends inclusive) with the leftmost element as pivot
    if(l >= r){
        return;
    }

    int p = pivot(v, l, r, l); // Default pivot is the first element in the subarray
    quick_sort(v, l, p-1);
    quick_sort(v, p+1, r);
    return;
}

void random_quick_sort(vector<int> (&v), const int (&l), const int (&r), uniform_int_distribution<> (&d), mt19937 (&g)){
    // * Quick Sort the subarray v[l:r] (both ends inclusive) with random choice of pivot
    if(l >= r){
        return;
    }

    int p = d(g) % (r-l+1) + l; // Choose random pivot in the inclusive range [l, r]
    p = pivot(v, l, r, p);
    quick_sort(v, l, p-1);
    quick_sort(v, p+1, r);
    return;

    return;
}

void merge(vector<int> (&v), int i, vector<int> (&left), vector<int> (&right)){
    // * Merging starts from v[i], ends at a suitable index. The original array v is overwritten with elements of newer arrays
    int le = 0, re = 0;                         // Number of elements read from left array, and right array
    int ls = left.size(), rs = right.size();    // Sizes of the two arrays, "left" and "right"

    // Standard code for merging two sorted arrays
    while(le < ls && re < rs){
        if(left[le] < right [re]){
            v[i] = left[le];
            i++; le++;
        }else{
            v[i] = right[re];
            i++; re++;
        }
    }

    while(le < ls){
            v[i] = left[le];
            i++; le++;
    }

    while(re < rs){
        v[i] = right[re];
        i++; re++;
    }

    return;
}

void merge_sort(vector<int> (&v), const int (&l), const int (&r)){
    // * subarray v[l:r] to be sorted, both inclusive

    if(l >= r){
        return;
    }

    int m = (l+r)>>1;
    merge_sort(v, l, m);        // Recur for left half
    merge_sort(v, m+1, r);      // Recur for right half

    vector<int> left(v.begin()+l, v.begin()+m+1), right(v.begin()+m+1, v.begin()+r+1); // Copy the two sorted halves

    merge(v, l, left, right);   // Merge the two sorted halves

    return;
}

int main(){

    // * For Randomized Quick Sort
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> distr(0, n-1); // (distr(gen) % (r-l+1) + l) \in [l, r]
    // ***************************

    return 0;
}