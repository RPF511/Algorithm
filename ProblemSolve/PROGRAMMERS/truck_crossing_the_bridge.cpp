#include <string>
#include <vector>
#include <iostream>

using namespace std;

void printvector(const vector<int> &v){
    cout << "[";
    for(int i : v){
        cout << i << " ";
    }
    cout <<"]"<< endl;
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int time = 1;
    vector<int> data;
    int end = 1;
    int current_truck = 0;
    data.push_back(0);
    data.push_back(0);
    
    
    while(current_truck<truck_weights.size()){
        if((data[time] + truck_weights[current_truck]) <= weight){
            for(int i = 0; i < bridge_length; ++i){
                if((time+i) > end){
                    ++end;
                    data.push_back(truck_weights[current_truck]);
                }
                else{
                    data[time+i] += truck_weights[current_truck];
                }
            }
            ++current_truck;
        }
        if(time == end){
            ++end;
            data.push_back(0);
        }
        // cout << "i : "<<current_truck<< " ,t : " <<time;
        printvector(data);
        ++time;
    }
    
    
    return data.size();
}



/*
0
0 7 7
*/