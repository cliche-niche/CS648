#include <bits/stdc++.h>

using namespace std;

#define ITERATIONS 2'000

vector< vector<int> > gen_output(int n, uniform_int_distribution<> (&d), mt19937 (&g)){

    int max_load = 0;
    vector<int> load(n, 0);
    vector< vector<int> > output(ITERATIONS, vector<int> (2, 0));

    for(int reps = 0; reps < ITERATIONS; reps++){
        fill(load.begin(), load.end(), 0);
        max_load = 0;

        for(int client = 0; client < n; client++){
            int server1 = d(g);
            int server2 = d(g);
            while(server2 == server1){
                server2 = d(g);
            }
            int server_of_choice = (load[server1] > load[server2] ? server2 : server1);

            load[server_of_choice]++;
            max_load = max(max_load, load[server_of_choice]);
        }

        output[reps][0] = n;
        output[reps][1] = max_load;
    }

    return output;
}

int main(){

    int n_vals[] = {1'000, 10'000, 100'000, 1'000'000};
    vector< vector< vector<int> > > outputs;
    string filename = "dataQ2.csv";

    ofstream fout(filename);
    fout << "n,max_load\n";
    
    for(auto n : n_vals){
        random_device rd;   // seeding the
        mt19937 gen(rd());  // randomizer
        uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1

        outputs.push_back(gen_output(n, distr_i, gen));
        cout << "Completed iterations for n = " << n << '\n';
    }

    for(const auto (&n_outputs) : outputs){
        for(const auto (&output) : n_outputs){
            fout << output[0] << "," << output[1] << '\n';
        }
    }

    return 0;
}