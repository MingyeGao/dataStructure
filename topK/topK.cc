#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

void heapify(vector<int> &heap, int index);

vector<int> topK(vector<int> &input, int k){
    vector<int> heap = vector<int>(k, INT_MIN);
    for(int i = 0; i < input.size(); ++i){
        if(input[i] > heap[0]){
            heap[0] = input[i];
            heapify(heap, 0);
        }
    }

    return heap;
}

void heapify(vector<int> &heap, int index){
    int heapSize = heap.size();

    if(2*index + 1 >= heapSize){
        return;
    }

    if(2*index + 1 == (heapSize-1)){
        if(heap[index] > heap[heapSize-1]){
            swap(heap[index], heap[heapSize]);
        }
        return;
    }

    int lchildIndex = 2*index + 1;
    int rchildIndex = 2*index + 2;
    int smallerIndex = heap[lchildIndex]<heap[rchildIndex]?lchildIndex:rchildIndex;
    if(heap[index] > heap[smallerIndex]){
        swap(heap[index], heap[smallerIndex]);
        heapify(heap, smallerIndex);
    }


}

int main(){
    vector<int> input;
    for(int i = 0; i < 10; ++i){
        input.push_back(i);
    }

    vector<int> result;
    result = topK(input, 3);

    for(auto i : result){
        printf("%d, ", i);
    }
    printf("\n");
}