#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 4

/* Structure representing an In-Core Inode */
typedef struct Inode {
    int inode_number;
    int ref_count;   /* Number of active processes using this inode */
    int link_count;  /* Number of directory entries pointing to this file */
    int modified;    /* 1 = file changed/accessed, 0 = unchanged */
    int locked;      /* 1 = busy/locked, 0 = unlocked */
    struct Inode *hash_next;
    struct Inode *free_next;
} Inode;

Inode *hash_table[HASH_SIZE] = {NULL};
Inode *free_list = NULL;

/* Simple hash function */
int hash(int inode_number) {
    return inode_number % HASH_SIZE;
}

/* Helper function to insert an inode into the mock hash table */
void insert_hash(Inode *inode) {
    int index = hash(inode->inode_number);
    inode->hash_next = hash_table[index];
    hash_table[index] = inode;
}

/* Initialize system with mock inodes */
void init_system() {
    // Inode 10: Normal file in use by 2 processes
    Inode *i1 = (Inode *)malloc(sizeof(Inode));
    i1->inode_number = 10; i1->ref_count = 2; i1->link_count = 1; i1->modified = 0; i1->locked = 0; i1->free_next = NULL;
    insert_hash(i1);

    // Inode 20: File modified by 1 process, ready to be closed
    Inode *i2 = (Inode *)malloc(sizeof(Inode));
    i2->inode_number = 20; i2->ref_count = 1; i2->link_count = 1; i2->modified = 1; i2->locked = 0; i2->free_next = NULL;
    insert_hash(i2);

    // Inode 30: File was deleted (link_count = 0) but 1 process still had it open
    Inode *i3 = (Inode *)malloc(sizeof(Inode));
    i3->inode_number = 30; i3->ref_count = 1; i3->link_count = 0; i3->modified = 0; i3->locked = 0; i3->free_next = NULL;
    insert_hash(i3);
}

/* Simulate the iput() algorithm */
void iput(int inode_number) {
    int index = hash(inode_number);
    Inode *current = hash_table[index];

    /* Find the inode in the in-core table */
    while (current != NULL) {
        if (current->inode_number == inode_number) {
            printf("\n--- Executing iput() for Inode %d ---\n", inode_number);

            /* 1. Lock inode if not already locked */
            if (current->locked == 0) {
                current->locked = 1;
                printf("Action: Inode locked.\n");
            }

            /* 2. Decrement inode reference count */
            current->ref_count--;
            printf("Action: Reference count decremented to %d.\n", current->ref_count);

            /* 3. If reference count reaches 0 */
            if (current->ref_count == 0) {
                printf("Notice: Reference count is 0. Processing release...\n");

                /* If link count is 0, the file was deleted */
                if (current->link_count == 0) {
                    printf("  -> Link count is 0. File has no names!\n");
                    printf("  -> [Simulated] Freeing disk blocks for file...\n");
                    printf("  -> [Simulated] Setting file type to 0...\n");
                    printf("  -> [Simulated] Freeing disk inode (ifree)...\n");
                }

                /* If modified, update disk */
                if (current->modified == 1) {
                    printf("  -> Inode or file data was modified. Updating disk inode...\n");
                    current->modified = 0; // Reset flag after saving
                }

                /* Put on free list */
                current->free_next = free_list;
                free_list = current;
                printf("Action: Inode placed on the free list.\n");
                
                /* Wake up waiting processes */
                printf("System: Waking up any processes waiting for a free inode.\n");
            } else {
                printf("Action: Reference count > 0. Keeping inode in memory.\n");
            }

            /* 4. Release inode lock */
            current->locked = 0;
            printf("Action: Inode lock released.\n");
            printf("-------------------------------------\n");
            return;
        }
        current = current->hash_next;
    }
    printf("\nError: Inode %d not found in memory.\n", inode_number);
}

/* Helper function to display the current state of the Hash Table */
void display_inode_table() {
    printf("\n=== Current In-Core Inode Table ===\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Hash Queue %d: ", i);
        Inode *temp = hash_table[i];
        if (temp == NULL) printf("EMPTY");
        while (temp != NULL) {
            printf("[Inode: %d, Ref: %d, Links: %d, Mod: %d] -> ", 
                   temp->inode_number, temp->ref_count, temp->link_count, temp->modified);
            temp = temp->hash_next;
        }
        printf("\n");
    }
    
    printf("\nFree List: ");
    Inode *f_temp = free_list;
    if (f_temp == NULL) printf("EMPTY\n");
    while (f_temp != NULL) {
        printf("[Inode: %d] -> ", f_temp->inode_number);
        f_temp = f_temp->free_next;
    }
    printf("\n===================================\n");
}

int main() {
    init_system();
    int choice, inode_num;

    while(1) {
        printf("\n1. Call iput()\n2. Display Inode Table\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Inode number to release: ");
            scanf("%d", &inode_num);
            iput(inode_num);
        } else if (choice == 2) {
            display_inode_table();
        } else {
            break;
        }
    }
    return 0;
}
