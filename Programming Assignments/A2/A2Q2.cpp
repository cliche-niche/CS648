#include <bits/stdc++.h>

using namespace std;

vector< vector<int> > gen_output(int n, uniform_int_distribution<> (&d), mt19937 (&g), int reps = 1'000){

    int max_load = 0, rounds = 0, num_served = 0;
    vector<int> load(n, 0);
    vector<bool> served(n+1, false);
    vector< vector<int> > output(reps, vector<int> (3, 0));
    ofstream outf("A2Q2.csv");

    while(reps--){
        fill(load.begin(), load.end(), 0);
        fill(served.begin(), served.end(), false);
        max_load = 0;
        num_served = 0;

        while(num_served < n){
            fill(load.begin(), load.end(), 0);
            if(num_served == 0){
                for(int client = 1; client <= n; client++){
                    if(!served[client]){
                        int server1 = d(g);
                        int server2 = d(g);
                        while(server2 == server1){
                            server2 = d(g);
                        }
                        int server_of_choice = (load[server1] > load[server2] ? server2 : server1);

                        if(load[server_of_choice] == 0){
                            num_served++;
                            served[client] == true;
                        }
                        load[server_of_choice]++;
                        max_load = max(max_load, load[server_of_choice]);
                    }
                }
            }else{
                for(int client = 1; client <= n; client++){
                    if(!served[client]){
                        int server1 = d(g);
                        int server2 = d(g);
                        while(server2 == server1){
                            server2 = d(g);
                        }
                        int server_of_choice = (load[server1] > load[server2] ? server2 : server1);

                        if(load[server_of_choice] == 0){
                            num_served++;
                            served[client] == true;
                        }
                        load[server_of_choice]++;
                    }
                }
            }
            rounds++;
        }

        output[reps][0] = n;
        output[reps][1] = max_load;
        output[reps][2] = rounds;
    }

    return output;
}

int main(){

    int reps = 2'000;
    int n_vals[] = {1'000, 10'000, 100'000, 1'000'000};
    vector< vector< vector<int> > > outputs;
    string filename = "A2Q2.csv";

    ofstream fout(filename);
    fout << "n,max_load,rounds,\n";
    
    for(auto n : n_vals){
        random_device rd;   // seeding the
        mt19937 gen(rd());  // randomizer
        uniform_int_distribution<> distr_i(0, n-1); // generate a random integer between 0 and n-1

        outputs.push_back(gen_output(n, distr_i, gen, reps));
    }

    for(const auto (&n_outputs) : outputs){
        for(const auto (&output) : n_outputs){
            fout << output[0] << "," << output[1] << "," << output[2] << "," << '\n';
        }
    }
    

    return 0;
}