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

    outfile << "n, maximum load, rounds\n";
    for(int n : N) {
        random_device rd;   // seeding the
        mt19937 gen(rd());  // randomizer
        uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1
        for(int i = 0; i < ITERATIONS; i++) {
            vector<int> rem;

            for(int i = 0; i < n; i++) {    // reset all parameters
                clients[i] = false;
                bins[i] = 0;
            }

            int rounds = 0;
            int max_load = -1;
            int received = 0;

            while(received < n) { // loop until all clients satisfied
                for(int i = 0; i < n; i++) { // start of next round
                    bin_this_round[i] = false;
                }

                for(int i = 0; i < n; i++) { // iterate through clients
                    if(clients[i]) continue;

                    int choice = distr_i(gen);
                    if(!bin_this_round[choice]) {
                        clients[i] = true;
                        received++;
                        bin_this_round[choice] = true;
                        bins[choice]++;
                        max_load = max(max_load, bins[choice]);
                    }
                } 
                
                rounds++;
                rem.push_back(n - received);
            }

            outfile << n << ", " << max_load << ", " << rounds;
            for(int r : rem) {
                outfile << ", " << r; 
            } 
            outfile << '\n';
        }
    }

    return 0;
}