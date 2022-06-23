#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE_OF_TREE = 100000;

class FenwickTree
{
    //It is a 1-based index Fenwick Tree.
private:
    int arr[MAX_SIZE_OF_TREE+5] = {0};
public:
    FenwickTree();
    void updateElementByValue(int index, int value);
    int getPrefixSum(int index);
    int getSum(int l, int r);
    int getLowerBoundIndex(int value);
    ~FenwickTree();
};

FenwickTree::FenwickTree()
{
    memset(arr, 0, sizeof(arr));
}

FenwickTree::~FenwickTree()
{
    //dtor
}

void FenwickTree::updateElementByValue(int index, int value){

    //value: the value by which the element at index has to be increased. NOT the new value to store at index.

    int i = index;
    while(i < MAX_SIZE_OF_TREE){
        arr[i] += value;
        i = i + (i & (-i));
    }
}

int FenwickTree::getPrefixSum(int index){
    
    int sum = 0;
    int i = index;
    
    while(i > 0){
        sum += arr[i];
        i = i - (i & (-i));
    }

    return sum;
}

int FenwickTree::getSum(int left, int right){
    if(left == 1) return getPrefixSum(right);
    else return getPrefixSum(right) - getPrefixSum(left-1);
}

int FenwickTree::getLowerBoundIndex(int value){
    
    //Using Binary Lifting

    int ptr = 0, prevsum = 0;
    for(int i = log2(MAX_SIZE_OF_TREE); i>= 0; i--){
        if(arr[ptr + (1<<i)] + prevsum < value){
            prevsum += arr[ptr + (1<<i)];
            ptr += (1<<i);
        }
    }

    return ptr+1;
}

int main(){
    //Driver function

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    FenwickTree ft = FenwickTree();
    for(int i = 0; i < 10; i++){
        ft.updateElementByValue(i+1, a[i]);
    }

    for(int i = 0; i < 10; i++){
        //increasing the value of each element in the array by 1
        ft.updateElementByValue(i+1, 1);
        a[i]++;
    }

    for(int i = 0; i < 10; i++){
        cout << "Prefix sum upto index " << i+1 << " is " << ft.getPrefixSum(i+1) << endl;
    }

    cout << "Lower bound of 30 is at index " << ft.getLowerBoundIndex(30) << endl;
    cout << "Sum from index 5 to 8 is " << ft.getSum(5, 8) << endl;
}
