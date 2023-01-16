#include <bits/stdc++.h>

using namespace std;



void print_map(vector<vector<int>> & vector){
    for(auto i : vector){
        for(auto j : i){
            printf("%d ",j);
        }
        printf("\n");
    }
}

bool cmp(const vector<int> &a,const vector<int> &b){
    return a[0] < b[0];
}

int count_sign(vector<vector<int>> & map, int l){
    int result = 0;
    for(auto temp : map){
        if(temp[0] > l) break;
        result += (l - temp[0])/temp[1];
        if(temp[1]>0)result++;
    }
    return result;
}


int bsearch_map(vector<vector<int>> & map, int k){
    // print_map(map);
    int low = -1, high = map[map.size()-1][0];
    // cout << "low " << low <<" high "<< high <<"\n";
    int mid = 0;
    while(low + 1 < high){
        mid = (low+high)/2;
        if(count_sign(map,mid) >= k) high = mid;
        else low = mid;
    }

    return high;
}

int main(void){
    int testcase_num=0; 
    int city_num = 0; int result_num = 0;
    int l_temp, m_temp, g_temp;
    vector<vector<int>> map;

    scanf("%d",&testcase_num);
    for(int caseidx = 0; caseidx < testcase_num; caseidx++){
        result_num = 0;
        scanf("%d %d",&city_num, &result_num);
        map.assign(city_num*2,vector<int>(2,0));
        //(start or end, between)
        // print_map(map);
        for(int cityidx = 0; cityidx < city_num; cityidx++){
            scanf("%d %d %d",&l_temp,&m_temp,&g_temp);
            map[cityidx * 2][0] = l_temp - m_temp;
            map[cityidx * 2][1] = g_temp;
            map[cityidx * 2 +1][0] = l_temp;
            map[cityidx * 2 +1][1] = -g_temp;
        }
        // print_map(map);
        sort(map.begin(),map.end(),cmp);
        printf("%d\n",bsearch_map(map,result_num));
        // print_map(map);


    }

}