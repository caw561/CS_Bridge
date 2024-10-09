#include <iostream>
#include <vector>
using namespace std;

vector<int> divideAndConquer(vector<int> v, int start, int end)
{
    int min,max;
    int v_size = (end - start)+1;
    if(v_size==1){
        min = v[start];
        max = v[start];
    }
    else if(v_size==2){
        if(v[start]>=v[end]){
            min = v[end];
            max = v[start];
        }
        else{
            min = v[start];
            max = v[end];
        }
    }
    else{
        int mid = (v_size/2)+start;
        vector<int> temp1, temp2;
        temp1 = divideAndConquer(v, start, mid);
        temp2 = divideAndConquer(v, mid+1, end);

        if(temp1[0]>=temp2[0]){
            min = temp2[0];
        }
        else{
            min = temp1[0];
        }
        if(temp1[1]>=temp2[1]){
            max = temp1[1];
        }
        else{
            max = temp2[1];
        }
    }
    vector<int> MinMax = {min,max};
    return MinMax;
}

int main()
{
    vector<int> v = {1,7,6,8,4,1,-6,9,10,10,-8};
    vector<int> min_max;
    min_max = divideAndConquer(v, 0, v.size()-1);

    for(int i:min_max){
        cout<<i<<endl;
    }

    return 0;
}

