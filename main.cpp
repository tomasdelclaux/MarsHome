#include <iostream>
#include <vector>
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
vector<int> maxContSubArr(vector<int> input){}

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
    auto res = bruteForce(INPUT1);
    assert(res[0]==0);
    assert(res[1]==0);
    assert(res[2]==-1);
    return 0;
}
