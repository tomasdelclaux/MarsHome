#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

enum Algo { task1, task2, task3_a, task3_b, task4, task5, task6};

// BRUTE FORCE CONTIGUOUS SUBARRAY 1D
// LET i be the beginning of the maximum contiguous subarray
// LET j be the end of the maximum contiguous subarray
// Need to go through all the combinations of subarrays(i,j), where i>=0 and i<n, and j>=i and j<n.
vector<long  int> bruteForce(const vector<int> &input){
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
            if(sum >= maxSum){
                maxSum = sum;
                start = i;
                end = j;
            }
        }
    }
    vector<long int> res;
    res.push_back(start+1);
    res.push_back(end+1);
    res.push_back(maxSum);
    return res;
}

// DP CONTIGUOUS SUBARRAY 1D (square)
vector<long int> maxContSubArr(const vector<int> &input){
    vector<long int> output;
    vector<vector<int>> map;
    for(int i=0; i<input.size(); i++){
        vector<int> v;
        v.reserve(input.size());
        for(int j=0; j<input.size(); j++){
            v.push_back(0);
        }
        map.push_back(v);
    }
    for(int i=0; i<input.size(); i++){
        map[i][i]=input[i];
    }
    int curr_max = input[0];
    int start=0;
    int end=0;
    for(int l=1; l<input.size(); l++){
        for(int j=0; j<=l; j++) {
            map[j][l] = max(map[j][l - 1] + input[l], input[l]);
            if(map[j][l]>=curr_max){
                end = l;
                start = j;
                curr_max=map[j][l];
            }
        }
    }
    output.push_back(start+1);
    output.push_back(end+1);
    output.push_back(curr_max);
    return output;
}


// Part A TOD DOWN
int betterMaxContSubArr_A(const vector<int> &input, int end, vector<int> &mem){
    if(end==0){
        return input[0];
    }
    if(mem[end]>INT_MIN){
        return mem[end];
    }
    else{
        mem[end]= max(input[end], betterMaxContSubArr_A(input, end-1, mem)+input[end]);
        return mem[end];
    }
}

//Part A driver
vector<long int> betterMaxContSubArr_A(const vector<int> &input){
    vector<int> mem;
    vector<long int> output;
    int end, start, backTrack;
    int max_sum = INT_MIN;
    mem.reserve(input.size());
    for(int i=0; i<input.size(); i++){
        mem.push_back(INT_MIN);
    }
    mem[0]= input[0];
    auto dummy = betterMaxContSubArr_A(input, input.size()-1, mem);
    for(int i=0; i<mem.size(); i++){
        if(mem[i]>=max_sum){
            end = i;
            max_sum=mem[i];
        }
    }
    backTrack = max_sum;
    start = end;
    while(true){
        backTrack-=input[start];
        if(backTrack==0){
            break;
        }
        start--;
    }
    output.push_back(start+1);
    output.push_back(end+1);
    output.push_back(max_sum);
    return output;
}

//BOTTOM UP APPROACH
vector<long int> betterMaxContSubArr_B(const vector<int> &input){
    vector<int> sums;
    vector<long int> output;
    int start, end, backTrack;
    int max_sum = INT_MIN;
    sums.reserve(input.size());
    for(int i=0; i<input.size(); i++){
        sums.push_back(0);
    }
    sums[0]=input[0];
    for(int i=1; i<input.size(); i++){
        sums[i] = max(sums[i-1]+input[i], input[i]);
    }
    for(int i=0; i<input.size(); i++){
        if(sums[i]>=max_sum){
            end = i;
            max_sum =sums[i];
        }
    }
    backTrack = max_sum;
    start = end;
    while(true){
        backTrack-=input[start];
        if(backTrack==0){
            break;
        }
        start--;
    }
    output.push_back(start+1);
    output.push_back(end+1);
    output.push_back(max_sum);
    return output;
}


vector<long int> bruteForce2D(const vector<vector<int>> &input, int m, int n){
    int m_sum = INT_MIN;
    int x1,y1,x2,y2;
    vector<long int> output;
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int x = 0; x <= i; x++){
                for(int y = 0; y <= j; y++){
                    int sum_ = 0;
                    for(int si = x; si <= i; si++){
                        for(int sj = y; sj <= j; sj++){
                            sum_ = sum_ + input[si][sj];
                        }
                    }
                    if(sum_ > m_sum){
                        m_sum = sum_;
                        x1 = x + 1;
                        y1 = y + 1;
                        x2 = i + 1;
                        y2 = j + 1;
                    }
                }
            }
        }
    }
    output.push_back(x1);
    output.push_back(y1);
    output.push_back(x2);
    output.push_back(y2);
    output.push_back(m_sum);
    return output;
}

vector<long int> maxSubRect(const vector<vector<int>> &input, int m, int n){
    int max_sum = INT_MIN;
    int sum;
    int x1,y1,x2,y2;
    vector<long int> output;
    //INITIALIZE A VECTOR WITH ZEROES FROM 0-M and 0-N
    vector<vector<int>> map(m+1,vector<int>(n+1,0));

    //CALCULATE THE MAX SUMS OF ALL ELEMENTS ENDING IN ROW I AND COLUMN J
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            map[i][j]=map[i-1][j]+map[i][j-1]-map[i-1][j-1]+input[i-1][j-1];
        }
    }

    for(int rs=1; rs<=m; rs++){
        for(int re=rs; re<=m; re++){
            for(int cs=1; cs<=n; cs++){
                for(int ce=cs; ce<=n; ce++){
                    sum = map[re][ce]-map[rs-1][ce]-map[re][cs-1]+map[rs-1][cs-1];

                    if(sum>max_sum){
                        max_sum= sum;
                        x1 = rs;
                        y1 = cs;
                        x2 = re;
                        y2 = ce;
                    }
                }
            }
        }
    }

    output.push_back(x1);
    output.push_back(y1);
    output.push_back(x2);
    output.push_back(y2);
    output.push_back(max_sum);
    return output;
}

// TODO DP CONTIGUOUS SUBARRAY 1D (pow 3)
vector<long int> betterMaxSubRect(const vector<vector<int>> &input, int m, int n){
    int max_sum = INT_MIN;
    vector<long int> output;
    vector<int> rowSums;
    int x1,y1,x2,y2;
    rowSums.reserve(m);
    for(int i=0; i<m; i++){
        rowSums.push_back(0);
    }
    for(int cs=0; cs<n; cs++){
        for(int i=0; i<m; i++){
            rowSums[i]=0;
        }
        for(int ce=cs; ce<n; ce++){
            for(int i=0; i<m; i++){
                rowSums[i]=rowSums[i]+input[i][ce];
            }

            auto output = betterMaxContSubArr_B(rowSums);

            if(output[2]>max_sum){
                max_sum=output[2];
                x1=output[0];
                x2=output[1];
                y1=cs;
                y2=ce;
            }
        }
    }

    output.push_back(x1);
    output.push_back(y1+1);
    output.push_back(x2);
    output.push_back(y2+1);
    output.push_back(max_sum);
    return output;
}


void experiment(Algo algo){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-32768, 32768);


    ofstream outfile;
    switch(algo){
        case task1:
            outfile.open("../task1.csv");
            for(int size=100; size<=10000; size=size+100){
                cout<<size<<endl;
                vector<int> testInput;
                testInput.reserve(size);
                for(int i=0; i<size; i++){
                    testInput.push_back(distr(gen));
                }
                auto start = chrono::high_resolution_clock::now();
                auto output = bruteForce(testInput);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                outfile<<size<<','<<duration.count()<<endl;
            }
            outfile.close();
            break;
        case task2:
            outfile.open("../task2.csv");
            for(int size=100; size<=10000; size=size+100){
                cout<<size<<endl;
                vector<int> testInput;
                testInput.reserve(size);
                for(int i=0; i<size; i++){
                    testInput.push_back(distr(gen));
                }
                auto start = chrono::high_resolution_clock::now();
                auto output = maxContSubArr(testInput);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                outfile<<size<<','<<duration.count()<<endl;
            }
            outfile.close();
            break;
        case task3_a:
            outfile.open("../task3a.csv");
            for(int size=100; size<=10000; size=size+100){
                cout<<size<<endl;
                vector<int> testInput;
                testInput.reserve(size);
                for(int i=0; i<size; i++){
                    testInput.push_back(distr(gen));
                }
                auto start = chrono::high_resolution_clock::now();
                auto output = betterMaxContSubArr_A(testInput);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                outfile<<size<<','<<duration.count()<<endl;
            }
            outfile.close();
            break;
        case task3_b:
            outfile.open("../task3b.csv");
            for(int size=100; size<=10000; size=size+100){
                cout<<size<<endl;
                vector<int> testInput;
                testInput.reserve(size);
                for(int i=0; i<size; i++){
                    testInput[i]=distr(gen);
                }
                auto start = chrono::high_resolution_clock::now();
                auto output = betterMaxContSubArr_A(testInput);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                outfile<<size<<','<<duration.count()<<endl;
            }
            outfile.close();
            break;
        case task4:
            outfile.open("../task4.csv");
            for(int m=10; m<=500; m=m+10){
                cout<<m<<endl;
                for(int n=10; n<=500; n=n+10){
                    vector<vector<int>> testInput(m,vector<int>(n,0));
                    for(int i=0; i<m; i++){
                        for(int j=0; j<n; j++){
                            testInput[i][j]=distr(gen);
                        }
                    }
                    auto start = chrono::high_resolution_clock::now();
                    auto output = bruteForce2D(testInput,m,n);
                    auto stop = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                    outfile<<m*n<<','<<duration.count()<<endl;
                }
            }
            break;
        case task5:
            break;
        case task6:
            break;
    }
}

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

//    //TEST CASE 1 -- BRUTE FORCE 1D
//    const vector<int> INPUT1 = {-1,-1, -1, -1, -1};
//    auto res1 = bruteForce(INPUT1);
//    assert(res1[0]==0);
//    assert(res1[1]==0);
//    assert(res1[2]==-1);
//

//PROBLEM 1
    const vector<int> INPUT1 = {-1,-1, -1, -1, -1};
    const vector<int> INPUT2 = {19,25,23,-19,24,-9,-31,-22};
    const vector<int> INPUT3 = {7,80,-100, 25,-2};
    const vector<int> INPUT4 = {1,2,3,-1,5,7,-10};
    const vector<int> INPUT5 = {-99,-38,-81,-29,-91,-3,-36,-46};

//TASK 1
    auto output_1 = bruteForce(INPUT1);
    auto output_2 = bruteForce(INPUT2);
    auto output_3 = bruteForce(INPUT3);
    auto output_4 = bruteForce(INPUT4);
    auto output_5 = bruteForce(INPUT5);
    assert(output_1[0]==5);
    assert(output_1[1]==5);
    assert(output_1[2]==-1);
    assert(output_2[0]==1);
    assert(output_2[1]==5);
    assert(output_2[2]==72);
    assert(output_3[0]==1);
    assert(output_3[1]==2);
    assert(output_3[2]==87);
    assert(output_4[0]==1);
    assert(output_4[1]==6);
    assert(output_4[2]==17);
    assert(output_5[0]==6);
    assert(output_5[1]==6);
    assert(output_5[2]==-3);


//TASK 2
    output_1 = maxContSubArr(INPUT1);
    output_2 = maxContSubArr(INPUT2);
    output_3 = maxContSubArr(INPUT3);
    output_4 = maxContSubArr(INPUT4);
    output_5 = maxContSubArr(INPUT5);
    assert(output_1[0]==5);
    assert(output_1[1]==5);
    assert(output_1[2]==-1);
    assert(output_2[0]==1);
    assert(output_2[1]==5);
    assert(output_2[2]==72);
    assert(output_3[0]==1);
    assert(output_3[1]==2);
    assert(output_3[2]==87);
    assert(output_4[0]==1);
    assert(output_4[1]==6);
    assert(output_4[2]==17);
    assert(output_5[0]==6);
    assert(output_5[1]==6);
    assert(output_5[2]==-3);

//TASK 3A
    output_1 = betterMaxContSubArr_A(INPUT1);
    output_2 = betterMaxContSubArr_A(INPUT2);
    output_3 = betterMaxContSubArr_A(INPUT3);
    output_4 = betterMaxContSubArr_A(INPUT4);
    output_5 = betterMaxContSubArr_A(INPUT5);
    assert(output_1[0]==5);
    assert(output_1[1]==5);
    assert(output_1[2]==-1);
    assert(output_2[0]==1);
    assert(output_2[1]==5);
    assert(output_2[2]==72);
    assert(output_3[0]==1);
    assert(output_3[1]==2);
    assert(output_3[2]==87);
    assert(output_4[0]==1);
    assert(output_4[1]==6);
    assert(output_4[2]==17);
    assert(output_5[0]==6);
    assert(output_5[1]==6);
    assert(output_5[2]==-3);

//TASK 3B
    output_1 = betterMaxContSubArr_B(INPUT1);
    output_2 = betterMaxContSubArr_B(INPUT2);
    output_3 = betterMaxContSubArr_B(INPUT3);
    output_4 = betterMaxContSubArr_B(INPUT4);
    output_5 = betterMaxContSubArr_B(INPUT5);
    assert(output_1[0]==5);
    assert(output_1[1]==5);
    assert(output_1[2]==-1);
    assert(output_2[0]==1);
    assert(output_2[1]==5);
    assert(output_2[2]==72);
    assert(output_3[0]==1);
    assert(output_3[1]==2);
    assert(output_3[2]==87);
    assert(output_4[0]==1);
    assert(output_4[1]==6);
    assert(output_4[2]==17);
    assert(output_5[0]==6);
    assert(output_5[1]==6);
    assert(output_5[2]==-3);


//PROBLEM 2
    const vector<vector<int>> INPUT6 = {{21,3,-17,-14},{15,-14,-31,-28},{11,-21,24,-6},{-2,23,-23,23}};
    const vector<vector<int>> INPUT7 = {{0,5,-11,-61},{-41,-88,-24,-65},{53,-18,29,-37},{-38,52,0,5}};
    const vector<vector<int>> INPUT8 = {{-1,-1,-1,-1},{0,0,0,0},{-1,-1,-1,-1},{0,0,0,0}};
    const vector<vector<int>> INPUT9 = {{0,5,-11,-61},{-41,-88,-24,-65},{53,-18,29,-37},{-38,52,0,5}, {50,-2,0,7}};


//TASK4
    auto output_6 = bruteForce2D(INPUT6,4,4);
    auto output_7 = bruteForce2D(INPUT7,4,4);
    auto output_8 = bruteForce2D(INPUT8,4,4);
    auto output_9 = bruteForce2D(INPUT9,5,4);
    assert(output_6[0]==1);
    assert(output_6[1]==1);
    assert(output_6[2]==3);
    assert(output_6[3]==1);
    assert(output_6[4]==47);
    assert(output_7[0]==3);
    assert(output_7[1]==1);
    assert(output_7[2]==4);
    assert(output_7[3]==3);
    assert(output_7[4]==78);
//    for(auto v: output_8){
//        cout<<v<<" ";
//    }
//    cout<<endl;
    assert(output_8[0]==2);
    assert(output_8[1]==1);
    assert(output_8[2]==2);
    assert(output_8[3]==1);
    assert(output_8[4]==0);
//    for(auto v: output_9){
//        cout<<v<<" ";
//    }
//    cout<<endl;
    assert(output_9[0]==3);
    assert(output_9[1]==1);
    assert(output_9[2]==5);
    assert(output_9[3]==3);
    assert(output_9[4]==126);


////TASK5
    output_6 = maxSubRect(INPUT6,4,4);
    output_7 = maxSubRect(INPUT7,4,4);
    output_8 = maxSubRect(INPUT8,4,4);
    output_9 = maxSubRect(INPUT9,5,4);
    assert(output_6[0]==1);
    assert(output_6[1]==1);
    assert(output_6[2]==3);
    assert(output_6[3]==1);
    assert(output_6[4]==47);
    assert(output_7[0]==3);
    assert(output_7[1]==1);
    assert(output_7[2]==4);
    assert(output_7[3]==3);
    assert(output_7[4]==78);
//    for(auto v: output_8){
//        cout<<v<<" ";
//    }
//    cout<<endl;
    assert(output_8[0]==2);
    assert(output_8[1]==1);
    assert(output_8[2]==2);
    assert(output_8[3]==1);
    assert(output_8[4]==0);
    assert(output_9[0]==3);
    assert(output_9[1]==1);
    assert(output_9[2]==5);
    assert(output_9[3]==3);
    assert(output_9[4]==126);
//
//
////TASK6
    output_6 = betterMaxSubRect(INPUT6,4,4);
    output_7 = betterMaxSubRect(INPUT7,4,4);
    output_8 = betterMaxSubRect(INPUT8,4,4);
    output_9 = betterMaxSubRect(INPUT9,5,4);
    assert(output_6[0]==1);
    assert(output_6[1]==1);
    assert(output_6[2]==3);
    assert(output_6[3]==1);
    assert(output_6[4]==47);
    assert(output_7[0]==3);
    assert(output_7[1]==1);
    assert(output_7[2]==4);
    assert(output_7[3]==3);
    assert(output_7[4]==78);
//    for(auto v: output_8){
//        cout<<v<<" ";
//    }
//    cout<<endl;
    assert(output_8[0]==4);
    assert(output_8[1]==1);
    assert(output_8[2]==4);
    assert(output_8[3]==1);
    assert(output_8[4]==0);
    assert(output_9[0]==3);
    assert(output_9[1]==1);
    assert(output_9[2]==5);
    assert(output_9[3]==3);
    assert(output_9[4]==126);

    experiment(task1);
}
