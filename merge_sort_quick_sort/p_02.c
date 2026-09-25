#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 범위 [l, r] 중 무작위 인덱스를 피벗으로 선택
int findPivot(int *L, int l, int r) {
    return l + rand() % (r - l + 1);
}


void inPlacePartition(int *L, int l, int r, int k, int* a, int* b) {
    int pivotVal = L[k];
    int i = l + 1;
    int eq_start = l;
    int eq_end = l;
    int gt_start = r + 1;

    // 피벗을 맨 앞(l)으로 이동
    swap(&L[k], &L[l]);

    // 맨 앞은 pivot으로 채웠으므로, 그 다음 부분부터 검사 시작.
    // 계속해서 i - 1인덱스에 피벗이 오게 하도록 함!!
    while (i < gt_start) {
        if (L[i] < pivotVal) { // pivot보다 값이 작다면 피벗이 모여있는 부분의 바로 앞으로 이동시키고, pivot묶음이 있는 인덱스 좌표를 하나씩 올림.
            swap(&L[i], &L[eq_start]);
            eq_start++;
            eq_end++;
            i++;
        } 
        else if (L[i] == pivotVal) { //i - 1부분이 피벗인데, i부분도 피벗 -> 그냥 피벗 끝 범위를 하나 더 늘리면 됨.
            eq_end++;
            i++;
        }
        else { //L[i] > pivotVal : 피벗보다 값이 크다면 기존에 만들어놨었던 피벗보다 큰 원소들 묶음(gt)의 한칸 앞쪽이랑 원소 스위칭
            gt_start--;
            swap(&L[i], &L[gt_start]);
        }
    }

    // (a, b) ← inPlacePartition(L, l, r, k) 의사코드에는 이렇게 되어있는데, a, b둘 모두를 한번의 함수 호출로 할당하려면 어떻게 해야 할까?
    // 기존의 return방식으로는 불가능(C언어에서는 지원 X). 따라서 이렇게 포인터로 변수의 주소를 받고, 그 주소가 가리키는 변수의 값을 바꾸는 식으로 해야 한다.
    *a = eq_start;
    *b = eq_end;
}

// 퀵 정렬 함수
//교안의 inPlaceQuickSort와 구조가 거의 비슷함.
void inPlaceQuickSort(int *L, int l, int r) {
    int k;
    int a, b; //피벗이 하나만 있지 않기 때문에(중복 가능) 피벗들을 한곳으로 모았을 때 첫 번째 인덱스와 마지막 인덱스를 저장함.

    if (l >= r) {
        return;
    }
    // 무작위 피벗 선택
    k = findPivot(L, l, r);

    // 분할 (a, b 계산)
    inPlacePartition(L, l, r, k, &a, &b);

    // 재귀 호출 (피벗과 같은 값 a ~ b는 제외)
    inPlaceQuickSort(L, l, a - 1);
    inPlaceQuickSort(L, b + 1, r);
}

int main() {
    int n;
    int* arr;

    srand(time(NULL)); // 무작위 random값 받기 위한 기본 설정
    scanf("%d", &n);
    
    //배열 원소 할당
    arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    //퀵 정렬을 통해 오름차순 정렬 진행.
    inPlaceQuickSort(arr, 0, n - 1);

    //정렬한 후 배열에 있는 값들 출력
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //메모리 해제
    free(arr);
    return 0;
}