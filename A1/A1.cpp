#include <vector>
#include <algorithm>

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

    return 0;
}