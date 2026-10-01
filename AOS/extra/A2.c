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

Buffer *hash_table[HASH_SIZE];
Buffer *free_list = NULL;


/* ---------------- HASH FUNCTION ---------------- */

int hash(int block_number)
{
    return block_number % HASH_SIZE;
}


/* ---------------- INITIALIZE BUFFER ---------------- */

void initialize_buffer(Buffer *buffer, int block_number)
{
    buffer->block_number = block_number;
    buffer->busy = 0;
    buffer->valid = 0;
    buffer->delayed_write = 0;

    buffer->data[0] = '\0';

    buffer->hash_next = NULL;
    buffer->free_next = NULL;
}


/* ---------------- INSERT INTO HASH TABLE ---------------- */

void insert_into_hash(Buffer *buffer)
{
    int index = hash(buffer->block_number);

    buffer->hash_next = hash_table[index];
    hash_table[index] = buffer;
}


/* ---------------- REMOVE FROM HASH TABLE ---------------- */

void remove_from_hash(Buffer *buffer)
{
    int index = hash(buffer->block_number);

    Buffer *current = hash_table[index];
    Buffer *previous = NULL;

    while (current != NULL)
    {
        if (current == buffer)
        {
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


/* ---------------- INSERT INTO FREE LIST ---------------- */

void insert_into_free_list(Buffer *buffer)
{
    Buffer *current;

    buffer->free_next = NULL;

    if (free_list == NULL)
    {
        free_list = buffer;
        return;
    }

    current = free_list;

    while (current->free_next != NULL)
        current = current->free_next;

    current->free_next = buffer;
}


/* ---------------- REMOVE FROM FREE LIST ---------------- */

void remove_from_free_list(Buffer *buffer)
{
    Buffer *current = free_list;
    Buffer *previous = NULL;

    while (current != NULL)
    {
        if (current == buffer)
        {
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


/* ---------------- SEARCH BUFFER ---------------- */

Buffer *search_buffer(int block_number)
{
    int index = hash(block_number);

    Buffer *current = hash_table[index];

    while (current != NULL)
    {
        if (current->block_number == block_number)
            return current;

        current = current->hash_next;
    }

    return NULL;
}


/* ---------------- READ FROM DISK ---------------- */

void read_from_disk(Buffer *buffer)
{
    printf("Reading block %d from disk...\n",
           buffer->block_number);

    snprintf(buffer->data,
             sizeof(buffer->data),
             "Data of disk block %d",
             buffer->block_number);

    buffer->valid = 1;
}


/* ---------------- WRITE DELAYED BUFFER ---------------- */

void write_delayed_buffer(Buffer *buffer)
{
    printf("Writing block %d to disk...\n",
           buffer->block_number);

    buffer->delayed_write = 0;
}


/* ---------------- GET BLOCK ---------------- */

Buffer *getblk(int block_number)
{
    Buffer *buffer;

    while (1)
    {
        /* Step 1: Search for the requested block */

        buffer = search_buffer(block_number);

        if (buffer != NULL)
        {
            /*
             * Block already exists in hash table.
             */

            if (buffer->busy)
            {
                printf("Buffer for block %d is busy.\n",
                       block_number);

                printf("Cannot use the buffer right now.\n");

                return NULL;
            }

            /*
             * Buffer exists and is free.
             */

            buffer->busy = 1;

            remove_from_free_list(buffer);

            return buffer;
        }


        /* Step 2: Block is not in hash table */

        if (free_list == NULL)
        {
            printf("Free list is empty.\n");
            return NULL;
        }


        /*
         * Take the first buffer from the free list.
         */

        buffer = free_list;

        remove_from_free_list(buffer);


        /* Step 3: Check delayed write */

        if (buffer->delayed_write)
        {
            printf("Buffer B%d has delayed write.\n",
                   buffer->block_number);

            write_delayed_buffer(buffer);

            /*
             * Put it back into the free list
             * and search again.
             */

            insert_into_free_list(buffer);

            continue;
        }


        /* Step 4: Reuse the buffer */

        remove_from_hash(buffer);

        buffer->block_number = block_number;
        buffer->busy = 1;

        /*
         * New block has not been read from disk yet.
         */

        buffer->valid = 0;
        buffer->delayed_write = 0;

        buffer->data[0] = '\0';

        insert_into_hash(buffer);

        return buffer;
    }
}


/* ---------------- BREAD ---------------- */

Buffer *bread(int block_number)
{
    Buffer *buffer;

    /*
     * Get a buffer for the requested block.
     */

    buffer = getblk(block_number);

    if (buffer == NULL)
        return NULL;


    /*
     * Check whether valid data already
     * exists in the buffer.
     */

    if (buffer->valid)
    {
        printf("CACHE HIT\n");

        return buffer;
    }


    /*
     * Data is not present in the cache.
     */

    printf("CACHE MISS\n");

    read_from_disk(buffer);

    return buffer;
}


/* ---------------- RELEASE BUFFER ---------------- */

void brelse(Buffer *buffer)
{
    if (buffer == NULL)
        return;

    /*
     * Buffer is no longer being used.
     */

    buffer->busy = 0;

    /*
     * Put it back into the free list.
     */

    insert_into_free_list(buffer);
}


/* ---------------- DISPLAY HASH TABLE ---------------- */

void display_hash_table()
{
    int i;

    Buffer *current;

    printf("\nHash Table:\n");

    for (i = 0; i < HASH_SIZE; i++)
    {
        printf("Hash[%d]: ", i);

        current = hash_table[i];

        while (current != NULL)
        {
            printf("B%d -> ",
                   current->block_number);

            current = current->hash_next;
        }

        printf("NULL\n");
    }
}


/* ---------------- DISPLAY FREE LIST ---------------- */

void display_free_list()
{
    Buffer *current = free_list;

    printf("Free List: ");

    while (current != NULL)
    {
        printf("B%d -> ",
               current->block_number);

        current = current->free_next;
    }

    printf("NULL\n");
}


/* ---------------- INITIALIZE BUFFER CACHE ---------------- */

void initialize_buffer_cache()
{
    int i;

    Buffer *buffer;

    for (i = 0; i < HASH_SIZE; i++)
        hash_table[i] = NULL;

    for (i = 0; i < BUFFER_COUNT; i++)
    {
        buffer = malloc(sizeof(Buffer));

        if (buffer == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        initialize_buffer(buffer, i);

        insert_into_hash(buffer);

        insert_into_free_list(buffer);
    }
}


/* ---------------- MAIN ---------------- */

int main()
{
    int block_number;

    Buffer *buffer;

    initialize_buffer_cache();

    printf("===== BUFFER CACHE SIMULATION =====\n");

    display_hash_table();
    display_free_list();


    /*
     * Keep asking for block numbers
     * until the user enters -1.
     */

    do
    {
        printf("\nEnter block number to read (-1 to exit): ");
        scanf("%d", &block_number);

        if (block_number == -1)
            break;


        /*
         * Call bread().
         *
         * bread() calls getblk().
         * Then it checks CACHE HIT/MISS.
         */

        buffer = bread(block_number);


        if (buffer != NULL)
        {
            printf("Data: %s\n",
                   buffer->data);

            /*
             * Release the buffer after use.
             */

            brelse(buffer);
        }
        else
        {
            printf("Unable to get buffer.\n");
        }


        display_hash_table();
        display_free_list();

    } while (block_number != -1);


    printf("\nProgram ended.\n");

    return 0;
}
