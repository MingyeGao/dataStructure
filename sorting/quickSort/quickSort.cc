///快速排序

#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

void quickSort(vector<int> &input, int start, int end){
    if(start >= end) return;

    int base = input[end];
    int baseIndex = end;
    int frontIndex = start;
    int backIndex = end;
    while(frontIndex < backIndex){
        while(input[frontIndex] <= base && frontIndex <backIndex){
            frontIndex++;
        }
        if(frontIndex < backIndex){
            swap(input[frontIndex], input[baseIndex]);
            baseIndex = frontIndex;
        }

        while(input[backIndex] >= base && backIndex > frontIndex){
            backIndex--;
        }

        if(backIndex > frontIndex){
            swap(input[backIndex], input[baseIndex]);
            baseIndex = backIndex;
        }
        
    }

    input[baseIndex] = base;

    quickSort(input, start, baseIndex-1);
    quickSort(input, baseIndex+1, end);
}

int main(){
    vector<int> input(20, 0);
    for(int i = 0; i < 20; ++i){
        input[i] = random()%50;
    }

    quickSort(input, 0, 19);

    for(int i = 0; i < input.size(); ++i){
        printf("%d, ", input[i]);
    }
    printf("\n");
}