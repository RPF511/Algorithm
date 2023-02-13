#include <bits/stdc++.h>

using namespace std;

void print_vector(vector<int> &data){
    for(int i : data){
        cout << i << " ";
    }
    cout << "\n";
}

int get_result_ex(vector<int> &data, int housenum){
    int result = 0;
    int i = 0;
    for(; i < data.size() ; i++){
        int cur_data = data[i];
        housenum -= cur_data;
        result += cur_data * (i+1);

        if(housenum <= 0){
            result += housenum * (i+1);
            housenum = 0;
            break;
        }
    }
    result += (i + housenum/2)*(i + housenum/2 + 1) - i * (i + 1);
    if(housenum % 2) result += i + housenum/2 + 1;
    return result;
}
long long get_count(vector<int> &data, int num, int & idx){
    long long result = 0;
    int i = idx;
    for(; i< data.size() ;  i++){
        int dest = 2 * num -1;
        if(data[i] == dest){
            result++;
        }
        if(data[i] > dest) break;
    }
    result += 2 * (data.size() - i);
    idx = i;
    return result+2;
}

long long get_result(vector<int> &data, int housenum){
    int size = data.size();
    long long result = 0;
    int cur_num = 1;
    int cur_idx = 0;
    while(1){
        int temp_count = get_count(data, cur_num, cur_idx);
        // cout << "temp count " << cur_num << " : " << temp_count <<  " cur_idx : "<<cur_idx << "\n";
        housenum -= temp_count;
        result += temp_count * cur_num;

        if(housenum <= 0){
            result += housenum * cur_num;
            housenum = 0;
            break;
        }

        cur_num++;
    }
    return result;
}

int main(void){
    int N, K, temp;
    vector<int> data;
    vector<int> dif_data;
    cin >> N >> K ;
    for(int i =0; i<N ; i++){
        cin >> temp;
        data.push_back(temp);
    }
    sort(data.begin(),data.end());
    // print_vector(data);
    for(int i =0 ; i< data.size() - 1 ; i++){
        dif_data.push_back(data[i+1] - data[i] -1);
    }
    sort(dif_data.begin(),dif_data.end());
    // print_vector(dif_data);
    // data.clear();
    // data.resize(dif_data[0] / 2 + 1, 2);
    // print_vector(data);

    // for(int cur_dif : dif_data){
    //     int i = 0;
    //     for(; i < cur_dif / 2 ; i++){
    //         data[i] += 2;
    //     }
    //     if(cur_dif % 2) data[i] += 1;
    // }
    // print_vector(data);

    // for(int i = 1 ; i <K ;  i++){
    //     cout << i << " "<<get_result(dif_data,i) << "\n";
    // }

    cout << get_result(dif_data,K) << "\n";

    return 0;
}