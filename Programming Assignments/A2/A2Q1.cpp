#include <bits/stdc++.h>
#include <chrono>

#define ITERATIONS 2000
#define MAX_N (int)(1e6 + 5)

using namespace std;


int bins[MAX_N];
bool bin_this_round[MAX_N];
bool clients[MAX_N];

int main() {
    int N[] = {(int)1e3, (int)1e4, (int)1e5, (int)1e6};

    ofstream outfile("dataQ1.csv");

    outfile << "n,max_load\n";
    for(int n : N) {
        random_device rd;   // seeding the
        mt19937 gen(rd());  // randomizer
        uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
        for(int i = 0; i < ITERATIONS; i++) {
            int max_load = 0;
            for(int i = 0; i < n; i++) {
                bins[i] = 0;        // reset all bins 
                max_load = 0;       // reset load
            }
            for(int i = 0; i < n; i++) {
                int choice = distr_i(gen);  // each user chooses a random bin
                bins[choice]++;
                max_load = max(max_load, bins[choice]);
            }

            outfile << n << ", " << max_load << endl;
        }
    }

    return 0;
}