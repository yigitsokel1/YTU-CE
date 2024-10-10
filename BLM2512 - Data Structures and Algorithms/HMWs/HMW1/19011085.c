#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 25

typedef struct Node {
    int value;
    struct Node** next;  
} Node;

typedef struct FastLinkedList {
    Node* header;  
    int level;     
} FastLinkedList;


Node* createNode(int value, int level) {
	int i;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = (Node**)malloc(sizeof(Node*) * (level + 1));
    for (i = 0; i <= level; i++) {
        newNode->next[i] = NULL;
    }
    return newNode;
}

FastLinkedList* initializeList() {
    FastLinkedList* list = (FastLinkedList*)malloc(sizeof(FastLinkedList));
    list->header = createNode(-1, MAX_LEVEL); 
    list->level = 0;
    return list;
}


int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}


void insertValue(FastLinkedList* list, int value) {
    Node* update[MAX_LEVEL + 1];
    Node* current = list->header;
    int i;
    
    for (i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
        update[i] = current;
    }
    
    current = current->next[0];
    
    if (current == NULL || current->value != value) {
        int newLevel = randomLevel();
        
        if (newLevel > list->level) {
            for (i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }
        
        Node* newNode = createNode(value, newLevel);
        for (i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
}


void searchValue(FastLinkedList* list, int value) {
    Node* current = list->header;
    int i;
    
    for (i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
    }
    
    current = current->next[0];
    
    if (current != NULL && current->value == value) {
        printf("Found value %d\n", value);
    } else {
        printf("Value %d not found\n", value);
    }
}


void deleteValue(FastLinkedList* list, int value) {
    Node* update[MAX_LEVEL + 1];
    Node* current = list->header;
    int i;
    
    for (i = list->level; i >= 0; i--) {
        while (current->next[i] != NULL && current->next[i]->value < value) {
            current = current->next[i];
        }
        update[i] = current;
    }
    
    current = current->next[0];
    
    if (current != NULL && current->value == value) {
        for (i = 0; i <= list->level; i++) {
            if (update[i]->next[i] != current) {
                break;
            }
            update[i]->next[i] = current->next[i];
        }
        free(current->next);
        free(current);
        
        while (list->level > 0 && list->header->next[list->level] == NULL) {
            list->level--;
        }
    }
}

void printList(FastLinkedList* list) {
	int i;
    for (i = list->level; i >= 0; i--) {
        Node* current = list->header->next[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next[i];
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));
    
    FastLinkedList* list = initializeList();
    
    insertValue(list, 3);
    insertValue(list, 6);
    insertValue(list, 7);
    insertValue(list, 9);
    insertValue(list, 12);
    
    printList(list);
    
    searchValue(list, 6);
    searchValue(list, 7);
    
    deleteValue(list, 7);
    
    printList(list);
    
    return 0;
}

