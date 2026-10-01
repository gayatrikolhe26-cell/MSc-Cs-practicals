#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 4
#define INODES_PER_BLOCK 8
#define START_BLOCK 2
#define INODE_SIZE 64 /* Assume each disk inode is 64 bytes */

/* Structure representing an In-Core Inode */
typedef struct Inode {
    int inode_number;
    int ref_count;
    int locked; /* 1 = busy/locked, 0 = free */
    struct Inode *hash_next;
    struct Inode *free_next;
} Inode;

Inode *hash_table[HASH_SIZE] = {NULL};
Inode *free_list = NULL;

/* Simple hash function */
int hash(int inode_number) {
    return inode_number % HASH_SIZE;
}

/* Initialize the free list with some dummy blank inodes */
void init_system() {
    for (int i = 0; i < 3; i++) {
        Inode *new_inode = (Inode *)malloc(sizeof(Inode));
        new_inode->inode_number = 0; // 0 means unassigned
        new_inode->ref_count = 0;
        new_inode->locked = 0;
        new_inode->hash_next = NULL;
        
        // Insert at beginning of free list
        new_inode->free_next = free_list;
        free_list = new_inode;
    }
}

/* Simulate the iget() algorithm */
Inode* iget(int inode_number) {
    int index = hash(inode_number);
    Inode *current = hash_table[index];

    printf("\n--- Executing iget() for Inode %d ---\n", inode_number);

    /* 1. Search the hash queue */
    while (current != NULL) {
        if (current->inode_number == inode_number) {
            printf("Found Inode %d in hash queue.\n", inode_number);
            
            /* If busy, simulate sleeping */
            if (current->locked == 1) {
                printf("Status: BUSY. Process goes to sleep waiting for inode...\n");
                printf("Status: Woken up! Inode is now free.\n");
            }
            
            /* Mark busy and increment reference count */
            current->locked = 1;
            current->ref_count++;
            printf("Action: Inode locked. Reference count is now %d.\n", current->ref_count);
            return current;
        }
        current = current->hash_next;
    }

    /* 2. Inode not found in cache. Allocate from free list */
    printf("Inode %d not found in memory. Allocating from free list...\n", inode_number);
    if (free_list == NULL) {
        printf("Error: Free list is empty!\n");
        return NULL;
    }

    /* Remove from free list */
    Inode *new_inode = free_list;
    free_list = free_list->free_next;

    /* Initialize the new inode */
    new_inode->inode_number = inode_number;
    new_inode->locked = 1;
    new_inode->ref_count = 1;

    /* 3. Calculate Logical Block Number and Byte Offset */
    int block_number = ((inode_number - 1) / INODES_PER_BLOCK) + START_BLOCK;
    int byte_offset = ((inode_number - 1) % INODES_PER_BLOCK) * INODE_SIZE;

    printf("Reading from simulated disk...\n");
    printf(" -> Logical Block Number: %d\n", block_number);
    printf(" -> Byte Offset inside block: %d bytes\n", byte_offset);

    /* 4. Insert into hash queue */
    new_inode->hash_next = hash_table[index];
    hash_table[index] = new_inode;
    printf("Action: Inode inserted into hash queue and locked.\n");

    return new_inode;
}

/* Helper function to display the current state of the Hash Table */
void display_hash_table() {
    printf("\n=== Current In-Core Inode Table ===\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Hash Queue %d: ", i);
        Inode *temp = hash_table[i];
        if (temp == NULL) {
            printf("EMPTY");
        }
        while (temp != NULL) {
            printf("[Inode: %d, Ref: %d, Busy: %d] -> ", temp->inode_number, temp->ref_count, temp->locked);
            temp = temp->hash_next;
        }
        printf("\n");
    }
    printf("===================================\n");
}

int main() {
    init_system();
    int choice, inode_num;

    while(1) {
        printf("\n1. Call iget()\n2. Display Inode Table\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Inode number to fetch: ");
            scanf("%d", &inode_num);
            iget(inode_num);
        } else if (choice == 2) {
            display_hash_table();
        } else {
            break;
        }
    }
    return 0;
}
