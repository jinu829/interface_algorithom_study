#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 리스트 분할 함수: L을 크기 k인 L1과 나머지 L2로 분할
// O(1)의 공간만을 사용하라는 조건을 지키기 위하여, 새로운 연결리스트를 생성하는 대신, 
// 기존 연결리스트의 k번째 노드와 (k+1)번째 노드 사이의 링크를 끊고,
// L2(새로운 header포인터)가 (k+1)번째 노드를 가리키게 하는 식으로 분할을 진행함.
void partition(Node* L, int k, Node** L1, Node** L2) {
    *L1 = L;
    Node* p = L;
    for (int i = 1; i < k; i++) {
        p = p->next;
    }
    *L2 = p->next; //k+1번째 노드에 새로운 header붙여주기
    p->next = NULL; //k -> k+1링크 끊기
}

// 리스트 합병 함수: 정렬된 두 연결리스트 L1, L2를 합병함.
// tmp라는 공간 하나만 생성해서(O(1)조건 만족), L1, L2연결리스트의 원소들을 하나씩 비교하면서 작은 친구부터 tmp뒤로 줄세우기 진행.
Node* merge(Node* L1, Node* L2) {
    Node tmp;
    Node* p = &tmp;

    while (L1 != NULL && L2 != NULL) {
        if (L1->data <= L2->data) {
            p->next = L1;
            L1 = L1->next;
        } 
        else {
            p->next = L2;
            L2 = L2->next;
        }
        p = p->next;
    }

    if (L1 != NULL) {
        p->next = L1;
    } 
    if (L2 != NULL) {
        p->next = L2;
    }

    return tmp.next;
}

// 합병 정렬 함수(mergeSort) : 교안에 있는 의사코드 내용과 똑같이 작성하면 됨.
// 배열을 사용할 시 실습문제에 있는 의사코드를 사용해도 괜찮으나, 본 문제에서는
// 단일연결리스트를 사용해야 하기에 교안에 있는 mergeSort알고리즘이 구현하기 더 좋습니다.
Node* mergeSort(Node* L, int size) {
    Node *L1 = NULL, *L2 = NULL;
    int k = size / 2;

    if (size > 1){
        // L을 크기 k와 (size - k)로 분할
        partition(L, k, &L1, &L2);

        // 재귀 호출
        L1 = mergeSort(L1, k);
        L2 = mergeSort(L2, size - k);

        // 정렬된 두 리스트 합병
        return merge(L1, L2);
    }
    return L;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    Node* head = NULL;
    Node* tail = NULL;
    Node* p = NULL;

    //연결리스트 제작
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        Node* newNode = createNode(val);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } 
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    //제작된 연결리스트를 합병 정렬으로 정렬
    head = mergeSort(head, n);

    //정렬된 연결리스트 출력
    p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    //연결리스트 free
    p = head;
     while (p != NULL) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }

    return 0;
}