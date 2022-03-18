#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <cassert>
using namespace std;


// TODO BRUTE FORCE CONTIGUOUS SUBARRAY 1D
// LET i be the beginning of the maximum contiguous subarray
// LET j be the end of the maximum contiguous subarray
// Need to go through all the combinations of subarrays(i,j), where i>=0 and i<n, and j>=i and j<n.
vector<long  int> bruteForce(vector<int> input){
    int sum;
    int maxSum=input[0];
    int start=0;
    int end=0;
    for(int i=0; i<input.size(); i++){
        for(int j=i; j<input.size(); j++){
            sum=0;
            for(int z=i; z<=j; z++){
                sum+= input[z];
            }
            if(sum > maxSum){
                maxSum = sum;
                start = i;
                end = j;
            }
        }
    }
    vector<long int> res;
    res.push_back(start);
    res.push_back(end);
    res.push_back(maxSum);
    return res;
}

// TODO DP CONTIGUOUS SUBARRAY 1D (square)
int maxContSubArr(vector<int> input){
    vector<vector<int>> map;
    for(int i=0; i<input.size(); i++){
        vector<int> v;
        for(int j=0; j<input.size(); j++){
            v.push_back(0);
        }
        map.push_back(v);
    }
    for(int i=0; i<input.size(); i++){
        map[i][i]=input[i];
    }
    int curr_max = input[0];
    int start, end;
    for(int l=1; l<input.size(); l++){
        for(int j=0; j<=l; j++) {
            map[j][l] = max(map[j][l - 1] + input[l], input[l]);
            if(map[j][l]>curr_max){
                start = j;
                end = l;
                curr_max=map[j][l];
            }
        }
    }
    return curr_max;
}

// TODO DP CONTIGUOUS SUBARRAY 1D (linear)
vector<int> betterMaxContSubArr(vector<int> input){}


// TODO BRUTE FORCE CONTIGUOUS SUBARRAY 2D
vector<vector<int>> bruteForce(vector<vector<int>> input){}

// TODO DP CONTIGUOUS SUBARRAY 2D (pow 4)
vector<vector<int>> maxSubRect(vector<vector<int>> input){}

// TODO DP CONTIGUOUS SUBARRAY 1D (pow 3)
vector<vector<int>> betterMaxSubRect(vector<vector<int>> input){}


int main() {
    // PROGRAM1 INTERFACE
//    int size;
//    int num;
//    cout << "Welcome to Mars" << std::endl;
//    cout<<"Enter size of array: ";
//    cin>>size;
//    vector<int> input(size, 0);
//    int i=0;
//    while(i<size){
//        cin>>num;
//        input[i]=num;
//        i++;
//    }
//    for(auto r: input){
//        cout<<r<<" ";
//    }

    //TEST CASE 1 -- BRUTE FORCE 1D
    const vector<int> INPUT1 = {-1,-1, -1, -1, -1};
    auto res1 = bruteForce(INPUT1);
    assert(res1[0]==0);
    assert(res1[1]==0);
    assert(res1[2]==-1);

    //TEST CASE 2 -- DP
    const vector<int> INPUT2 = {7,80, -100, 25, -2};
    const vector<int> INPUT3 = {1,2,3,-1,5,7,-10};
    int res2 = maxContSubArr(INPUT2);
    assert(res2==87);
    res2= maxContSubArr(INPUT3);
    assert(res2==17);
    return 0;
}
