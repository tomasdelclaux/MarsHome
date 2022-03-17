#include <iostream>
#include <vector>
using namespace std;

const vector<int> INPUT = {1,1,1,1,-2,1,4};

// TODO BRUTE FORCE CONTIGUOUS SUBARRAY 1D
// LET i be the beginning of the maximum contiguous subarray
// LET j be the end of the maximum contiguous subarray
// Need to go through all the combinations of subarrays(i,j), where i>=0 and i<n, and j>=i and j<n.
vector<int> bruteForce(vector<int> input){
    int sum;
    int maxSum=0;
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
    return vector<int>(input.begin() + start, input.begin()+end+1);
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
    std::cout << "Welcome to Mars" << std::endl;
    auto res = bruteForce(INPUT);
    for(auto r:res){
        cout<<r<<" ";
    }
    return 0;
}
