#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 4
#define BUFFER_COUNT 6

typedef struct Buffer {
    int block_number;
    int busy;
    int valid;
    int delayed_write;
    char data[100];

    struct Buffer *hash_next;
    struct Buffer *free_next;
} Buffer;


/* Hash table and free list */
Buffer *hash_table[HASH_SIZE];
Buffer *free_list = NULL;


/* Hash function */
int hash(int block_number) {
    return block_number % HASH_SIZE;
}


/* Initialize a buffer */
void initialize_buffer(Buffer *buffer, int block_number) {
    buffer->block_number = block_number;
    buffer->busy = 0;
    buffer->valid = 0;
    buffer->delayed_write = 0;

    buffer->hash_next = NULL;
    buffer->free_next = NULL;
}


/* Insert buffer into hash table */
void insert_into_hash(Buffer *buffer) {
    int index = hash(buffer->block_number);

    buffer->hash_next = hash_table[index];
    hash_table[index] = buffer;
}


/* Remove buffer from hash table */
void remove_from_hash(Buffer *buffer) {
    int index = hash(buffer->block_number);

    Buffer *current = hash_table[index];
    Buffer *previous = NULL;

    while (current != NULL) {

        if (current == buffer) {

            if (previous == NULL)
                hash_table[index] = current->hash_next;
            else
                previous->hash_next = current->hash_next;

            current->hash_next = NULL;
            return;
        }

        previous = current;
        current = current->hash_next;
    }
}


/* Insert buffer into free list */
void insert_into_free_list(Buffer *buffer) {

    Buffer *current;

    buffer->free_next = NULL;

    if (free_list == NULL) {
        free_list = buffer;
        return;
    }

    current = free_list;

    while (current->free_next != NULL)
        current = current->free_next;

    current->free_next = buffer;
}


/* Remove buffer from free list */
void remove_from_free_list(Buffer *buffer) {

    Buffer *current = free_list;
    Buffer *previous = NULL;

    while (current != NULL) {

        if (current == buffer) {

            if (previous == NULL)
                free_list = current->free_next;
            else
                previous->free_next = current->free_next;

            current->free_next = NULL;
            return;
        }

        previous = current;
        current = current->free_next;
    }
}


/* Search for a buffer in hash table */
Buffer *search_buffer(int block_number) {

    int index = hash(block_number);

    Buffer *current = hash_table[index];

    while (current != NULL) {

        if (current->block_number == block_number)
            return current;

        current = current->hash_next;
    }

    return NULL;
}


/* Simulate reading a block from disk */
void read_from_disk(Buffer *buffer) {

    printf("Reading block %d from disk...\n",
           buffer->block_number);

    sprintf(buffer->data,
            "Data of disk block %d",
            buffer->block_number);

    buffer->valid = 1;
}


/* Get a buffer for a block */
Buffer *getblk(int block_number) {

    Buffer *buffer;

    while (1) {

        /* Check if block already exists in buffer cache */
        buffer = search_buffer(block_number);

        if (buffer != NULL) {

            if (buffer->busy) {

                /* Simplified handling of busy buffer */
                buffer->busy = 0;
                continue;
            }

            buffer->busy = 1;

            remove_from_free_list(buffer);

            return buffer;
        }


        /* No buffer for this block exists */
        if (free_list == NULL)
            return NULL;


        /* Take a buffer from free list */
        buffer = free_list;

        remove_from_free_list(buffer);


        /* Handle delayed write */
        if (buffer->delayed_write) {

            buffer->delayed_write = 0;
            buffer->valid = 1;

            insert_into_free_list(buffer);

            continue;
        }


        /* Reuse the buffer for the new block */
        remove_from_hash(buffer);

        buffer->block_number = block_number;
        buffer->busy = 1;
        buffer->valid = 0;

        insert_into_hash(buffer);

        return buffer;
    }
}


/* Read a block */
Buffer *bread(int block_number) {

    Buffer *buffer;

    buffer = getblk(block_number);

    if (buffer == NULL)
        return NULL;

    /* If data is not valid, read it from disk */
    if (!buffer->valid)
        read_from_disk(buffer);

    return buffer;
}


/* Release a buffer */
void brelse(Buffer *buffer) {

    if (buffer == NULL)
        return;

    buffer->busy = 0;

    insert_into_free_list(buffer);
}


/* Read block and next block (read-ahead) */
Buffer *breada(int block_number) {

    Buffer *buffer;
    Buffer *read_ahead_buffer;

    int next_block = block_number + 1;


    /* Read requested block */
    buffer = bread(block_number);

    if (buffer == NULL)
        return NULL;


    /* Check whether next block is already cached */
    read_ahead_buffer = search_buffer(next_block);


    if (read_ahead_buffer == NULL) {

        /* Get a buffer for next block */
        read_ahead_buffer = getblk(next_block);

        if (read_ahead_buffer != NULL) {

            /* Read next block from disk */
            read_from_disk(read_ahead_buffer);

            /* Release read-ahead buffer */
            brelse(read_ahead_buffer);
        }
    }

    return buffer;
}


/* Main function */
int main() {

    int i;
    int block_number;

    Buffer *buffer;


    /* Initialize hash table */
    for (i = 0; i < HASH_SIZE; i++)
        hash_table[i] = NULL;


    /* Create buffers */
    for (i = 0; i < BUFFER_COUNT; i++) {

        buffer = malloc(sizeof(Buffer));

        initialize_buffer(buffer, i);

        insert_into_hash(buffer);

        insert_into_free_list(buffer);
    }


    /*
       Keep asking the user for block numbers
       until -1 is entered.
    */
    do {

        printf("\nEnter block number (-1 to exit): ");
        scanf("%d", &block_number);


        if (block_number == -1)
            break;


        /* Read requested block and next block */
        buffer = breada(block_number);


        if (buffer != NULL) {

            printf("Block %d is ready.\n",
                   buffer->block_number);

            printf("Data: %s\n",
                   buffer->data);

            /* Release the buffer */
            brelse(buffer);
        }

        else {

            printf("No free buffer available.\n");
        }


    } while (1);


    return 0;
}
