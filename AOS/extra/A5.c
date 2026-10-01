#include <stdio.h>
#include <stdlib.h>

/* Structure representing a buffer node in a linked list */
struct Buffer {
    int block_no;
    int is_busy;
    struct Buffer* next;
};

/* Global pointer for the free list */
struct Buffer* free_list = NULL;

/* Function to simulate brelse algorithm */
void brelse(struct Buffer* b) {
    printf("\n--- Executing brelse() --- \n");

    /* 1. Wakeup waiting processes */
    printf("1. Waking up processes waiting for ANY free buffer...\n");
    printf("   Waking up processes waiting for block %d...\n", b->block_no);

    /* 2. Update buffer status & Release busy buffer */
    b->is_busy = 0;
    printf("2. Buffer status updated: Busy = %d (Released)\n", b->is_busy);

    /* 3. Insert into free list (Inserting at the head for simplicity) */
    b->next = free_list;
    free_list = b;
    printf("3. Buffer inserted into the free list.\n");
    printf("--------------------------\n");
}

/* Helper function to display the current free list */
void display_free_list() {
    struct Buffer* temp = free_list;
    printf("Current Free List: ");
    if (temp == NULL) {
        printf("EMPTY\n");
        return;
    }
    while (temp != NULL) {
        printf("[Block %d] -> ", temp->block_no);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    /* Allocate memory for a new buffer */
    struct Buffer* b = (struct Buffer*)malloc(sizeof(struct Buffer));
    b->next = NULL;

    printf("=== Buffer Release (brelse) Simulator ===\n");
    
    /* Take user input to set up the busy buffer */
    printf("Enter block number: ");
    scanf("%d", &b->block_no);
    
    printf("Enter busy status (1 for busy): ");
    scanf("%d", &b->is_busy);

    printf("\nStatus Before brelse():\n");
    printf("Block = %d, Busy = %d\n", b->block_no, b->is_busy);
    display_free_list();

    /* Execute the algorithm */
    if (b->is_busy == 1) {
        brelse(b);
    } else {
        printf("\nBuffer is already free. No need to call brelse().\n");
    }

    /* Show final state */
    printf("\nStatus After brelse():\n");
    printf("Block = %d, Busy = %d\n", b->block_no, b->is_busy);
    display_free_list();

    return 0;
}
