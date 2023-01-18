#include <bits/stdc++.h>
#include <chrono>

#define ITERATIONS 2000

using namespace std;

uint64_t get_time_mili(){
    using namespace chrono;
    return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

uint64_t get_time_micro(){
    using namespace chrono;
    return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

int pivot(vector<double> (&v), const int (&l), const int (&r), int p){
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
}

uint64_t quick_sort(vector<double> (&v), const int (&l), const int (&r)){
    // * Quick Sort the subarray v[l:r] (both ends inclusive) with the leftmost element as pivot
    if(l >= r){
        return 0;
    }

    // c = Number of comparisons, Default p = pivot is the first element in the subarray
    uint64_t c = r-l, p = pivot(v, l, r, l);
    c += quick_sort(v, l, p-1);
    c += quick_sort(v, p+1, r);
    return c;
}

uint64_t random_quick_sort(vector<double> (&v), const int (&l), const int (&r), uniform_int_distribution<> (&d), mt19937 (&g)){
    // * Quick Sort the subarray v[l:r] (both ends inclusive) with random choice of pivot
    if(l >= r){
        return 0;
    }

    uint64_t c = r-l, p = (d(g) % (r-l+1)) + l; // Choose random pivot in the inclusive range [l, r]
    p = pivot(v, l, r, p);
    c += random_quick_sort(v, l, p-1, d, g);
    c += random_quick_sort(v, p+1, r, d, g);
    return c;
}

uint64_t merge(vector<double> (&v), int i, vector<int> (&left), vector<int> (&right)){
    // * Merging starts from v[i], ends at a suitable index. The original array v is overwritten with elements of newer arrays
    int le = 0, re = 0;                         // Number of elements read from left array, and right array
    int ls = left.size(), rs = right.size();    // Sizes of the two arrays, "left" and "right"

    // Standard code for merging two sorted arrays
    uint64_t c = 0; // * Number of comparisons
    while(le < ls && re < rs){
        if(left[le] < right [re]){
            v[i] = left[le];
            i++; le++;
        }else{
            v[i] = right[re];
            i++; re++;
        }

        c++;
    }

    while(le < ls){
            v[i] = left[le];
            i++; le++;
    }

    while(re < rs){
        v[i] = right[re];
        i++; re++;
    }

    return c;
}

uint64_t merge_sort(vector<double> (&v), const int (&l), const int (&r)){
    // * subarray v[l:r] to be sorted, both inclusive

    if(l >= r){
        return 0;
    }

    int m = (l+r)>>1;
    uint64_t c = 0;
    c += merge_sort(v, l, m);        // Recur for left half
    c += merge_sort(v, m+1, r);      // Recur for right half

    vector<int> left(v.begin()+l, v.begin()+m+1), right(v.begin()+m+1, v.begin()+r+1); // Copy the two sorted halves

    c += merge(v, l, left, right);   // Merge the two sorted halves

    return c;
}

int main(){
    int QUESTION;
    vector<int> ARRAY_SIZES = {(int)1e2, (int)1e3, (int)1e4, (int)1e5, (int)1e6};
    cout << "Enter question number to generate data for:\n";
    cin >> QUESTION;

    ofstream outfile("dataQ3.csv");

    switch(QUESTION) {
        // Quick Sort v/s Randomized Quick Sort
        case 1: 
        outfile << "n,rt_qs,rt_rqs,c_qs,c_rqs,dst_qs,dst_rqs\n";
        for (int n : ARRAY_SIZES) {
            random_device rd;   // seeding the
            mt19937 gen(rd());  // randomizer
            uniform_real_distribution<> distr_r(0, 1);  // generate a random float between 0 and 1
            uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
            vector<double> v, v_rqs, v_qs;

            while(n--) { v.push_back(distr_r(gen)); } // generating the random array
            n = v.size();
            v_qs = v;

            for(int i = 0; i < ITERATIONS; i++) {
                v_rqs = v;
                shuffle(v_qs.begin(), v_qs.end(), default_random_engine(get_time_mili()));
                
                int s_qs1, e_qs1, e_qs2 = 0;
                uint64_t c_qs = 0;
                
                s_qs1 = get_time_micro();
                c_qs = quick_sort(v_qs, 0, n-1);
                e_qs1 = get_time_micro();
                quick_sort(v_qs, 0, n-1);
                e_qs2 = get_time_micro();

                int s_rqs1, e_rqs1, e_rqs2 = 0;
                uint64_t c_rqs = 0;

                s_rqs1 = get_time_micro();
                c_rqs = random_quick_sort(v_rqs, 0, n-1, distr_i, gen);
                e_rqs1 = get_time_micro();
                random_quick_sort(v_rqs, 0, n-1, distr_i, gen);
                e_rqs2 = get_time_micro();
  
                if(outfile.is_open()) {
                    outfile << n << "," << (e_qs1 - s_qs1) << "," << (e_rqs1 - s_rqs1) << "," << c_qs \
                                               << "," << c_rqs << "," << (e_qs2 - s_qs1) 
                            
                                               << "," << (e_rqs2 - s_rqs1) << endl;
                }
                
                cout << "Iteration done!\n";
            }
        }
        break;

        // Randomized Quick Sort v/s Merge Sort
        case 2:
        outfile << "n,rt_qs,rt_ms,c_qs,c_ms\n";
        for (int n : ARRAY_SIZES) {
            random_device rd;   // seeding the
            mt19937 gen(rd());  // randomizer
            uniform_real_distribution<> distr_r(0, 1);  // generate a random float between 0 and 1
            uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
            vector<double> v, v_ms, v_qs;

            while(n--) { v.push_back(distr_r(gen)); } // generating the random array
            n = v.size();

            for(int i = 0; i < ITERATIONS; i++) {
                shuffle(v.begin(), v.end(), default_random_engine(get_time_mili()));
                v_ms = v_qs = v;
                
                int s_qs1, e_qs1 = 0;
                uint64_t c_qs = 0;
                
                s_qs1 = get_time_micro();
                c_qs = quick_sort(v_qs, 0, n-1);
                e_qs1 = get_time_micro();
                
                int s_ms1, e_ms1 = 0;
                uint64_t c_ms = 0;

                s_ms1 = get_time_micro();
                c_ms = merge_sort(v_ms, 0, n-1);
                e_ms1 = get_time_micro();


                if(outfile.is_open()) {
                    outfile << n << "," << (e_qs1 - s_qs1) << "," << (e_ms1 - s_ms1) << "," << c_qs << "," << c_ms << endl;
                }

                cout << "Iteration done!\n";
            }
        }
        break;

        case 3:
        outfile << "n,rt_qs,c_qs\n";
        for (int n : ARRAY_SIZES) {
            random_device rd;   // seeding the
            mt19937 gen(rd());  // randomizer
            uniform_real_distribution<> distr_r(0, 1);  // generate a random float between 0 and 1
            uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
            vector<double> v, v_qs;

            while(n--) { v.push_back(distr_r(gen)); } // generating the random array
            n = v.size();

            for(int i = 0; i < ITERATIONS; i++) {
                shuffle(v.begin(), v.end(), default_random_engine(get_time_mili()));
                v_qs = v;
                
                int s_qs1, e_qs1 = 0;
                uint64_t c_qs = 0;
                
                s_qs1 = get_time_mili();
                c_qs = quick_sort(v_qs, 0, n-1);
                e_qs1 = get_time_mili();

                if(outfile.is_open()) {
                    outfile << n << "," << (e_qs1 - s_qs1) << "," << c_qs << endl;
                }

                cout << "Iteration done!\n";
            }
        }
        break;

        // case 4 debugging
        case 4:
        for (int n =20; n<21; n++) {
            random_device rd;   // seeding the
            mt19937 gen(rd());  // randomizer
            uniform_real_distribution<> distr_r(0, 1);  // generate a random float between 0 and 1
            uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
            vector<double> v, v_rqs, v_qs;

            while(n--) { v.push_back(-n); } // generating the random array
            n = v.size();
            
            for(auto i : v){
                cout<<i<<' ';
            }
            cout<<'\n';

                v_rqs = v;

            for(int i = 0; i < ITERATIONS; i++) {
                int s_qs1, e_qs1, e_qs2 = 0;
                uint64_t c_qs = 0;
                
                s_qs1 = get_time_mili();
                c_qs = random_quick_sort(v_rqs, 0, n-1, distr_i, gen);
                e_qs1 = get_time_mili();
                
                for(auto i:v_rqs){
                    cout<<i<<' ';
                }
                cout<<"comps "<<c_qs<< '\n';
            }

            for(int i=0; i< ITERATIONS; i++){
                shuffle(v_rqs.begin(), v_rqs.end(), default_random_engine(get_time_mili()));
                int s_qs1, e_qs1, e_qs2 = 0;
                uint64_t c_qs = 0;
                
                s_qs1 = get_time_mili();
                c_qs = random_quick_sort(v_rqs, 0, n-1, distr_i, gen);
                e_qs1 = get_time_mili();
                
                for(auto i:v_rqs){
                    cout<<i<<' ';
                }
                cout<<"comps "<<c_qs<< '\n';
            }

            break;
        }
        break;

        default: cout << "Invalid input\n";
    }

    outfile.close();
    return 0;
}