#include <stdio.h>
    #include <stdlib.h>
    #define HASH_SIZE 4
    #define BUFFER_COUNT 6

    typedef struct Buffer{
        int block_number;
        int busy;
        int valid;
        int delayed_write;
        struct Buffer *hash_next;
        struct Buffer *free_next;
    }Buffer;

    Buffer *hash_table[HASH_SIZE];
    Buffer *free_list=NULL;

    int hash(int block_number){
        return block_number%HASH_SIZE;
    }

    void initialize_buffer(Buffer *buffer,int block_number){
        buffer->block_number=block_number;
        buffer->busy=0;
        buffer->valid=0;
        buffer->delayed_write=0;
        buffer->hash_next=NULL;
        buffer->free_next=NULL;
    }

    void insert_into_hash(Buffer *buffer){
        int index=hash(buffer->block_number);
        buffer->hash_next=hash_table[index];
        hash_table[index]=buffer;
    }

    void remove_from_hash(Buffer *buffer){
        int index=hash(buffer->block_number);
        Buffer *current=hash_table[index];
        Buffer *previous=NULL;
        while(current!=NULL){
            if(current==buffer){
                if(previous==NULL)
                    hash_table[index]=current->hash_next;
                else
                    previous->hash_next=current->hash_next;
                current->hash_next=NULL;
                return;
            }
            previous=current;
            current=current->hash_next;
        }
    }

    void insert_into_free_list(Buffer *buffer){
        Buffer *current;
        buffer->free_next=NULL;
        if(free_list==NULL){
            free_list=buffer;
            return;
        }
        current=free_list;
        while(current->free_next!=NULL)
            current=current->free_next;
        current->free_next=buffer;
    }

    void remove_from_free_list(Buffer *buffer){
        Buffer *current=free_list;
        Buffer *previous=NULL;
        while(current!=NULL){
            if(current==buffer){
                if(previous==NULL)
                    free_list=current->free_next;
                else
                    previous->free_next=current->free_next;
                current->free_next=NULL;
                return;
            }
            previous=current;
            current=current->free_next;
        }
    }

    Buffer *search_buffer(int block_number){
        int index=hash(block_number);
        Buffer *current=hash_table[index];
        while(current!=NULL){
            if(current->block_number==block_number)
                return current;
            current=current->hash_next;
        }
        return NULL;
    }

    void write_delayed_buffer(Buffer *buffer){
        printf("Writing delayed buffer B%d to disk...\n",buffer->block_number);
        buffer->delayed_write=0;
        buffer->valid=1;
    }

    Buffer *getblk(int block_number){
        Buffer *buffer;
        while(1){
            buffer=search_buffer(block_number);
            if(buffer!=NULL){
                if(buffer->busy){
                    printf("Buffer B%d is busy.\n",block_number);
                    printf("Process is sleeping...\n");
                    buffer->busy=0;
                    printf("Buffer B%d becomes free.\n",block_number);
                    continue;
                }
                buffer->busy=1;
                remove_from_free_list(buffer);
                printf("Buffer found in hash queue and is free.\n");
                return buffer;
            }
            if(free_list==NULL){
                printf("Free list is empty.\n");
                printf("Process is sleeping...\n");
                return NULL;
            }
            buffer=free_list;
            remove_from_free_list(buffer);
            if(buffer->delayed_write){
                printf("Buffer B%d has delayed write.\n",buffer->block_number);
                write_delayed_buffer(buffer);
                insert_into_free_list(buffer);
                continue;
            }
            remove_from_hash(buffer);
            buffer->block_number=block_number;
            buffer->busy=1;
            buffer->valid=0;
            buffer->delayed_write=0;
            insert_into_hash(buffer);
            return buffer;
        }
    }

    void display_hash_queues(){
        int i;
        Buffer *current;
        for(i=0;i<HASH_SIZE;i++){
            printf("Hash[%d]: ",i);
            current=hash_table[i];
            while(current!=NULL){
                printf("B%d -> ",current->block_number);
                current=current->hash_next;
            }
            printf("NULL\n");
        }
    }

    void display_free_list(){
        Buffer *current=free_list;
        printf("Free List: ");
        while(current!=NULL){
            printf("B%d -> ",current->block_number);
            current=current->free_next;
        }
        printf("NULL\n");
    }

    void initialize_buffer_cache(){
        int i;
        Buffer *buffer;
        for(i=0;i<HASH_SIZE;i++)
            hash_table[i]=NULL;
        for(i=0;i<BUFFER_COUNT;i++){
            buffer=malloc(sizeof(Buffer));
            if(buffer==NULL){
                printf("Memory allocation failed.\n");
                exit(1);
            }
            initialize_buffer(buffer,i);
            insert_into_hash(buffer);
            insert_into_free_list(buffer);
        }
    }

    int main(){
        int block_number;
        Buffer *buffer;
        initialize_buffer_cache();
        display_hash_queues();
        display_free_list();
        printf("Enter block number to get: ");
        scanf("%d",&block_number);
        buffer=getblk(block_number);
        if(buffer!=NULL)
            printf("Buffer B%d successfully allocated.\n",buffer->block_number);
        else
            printf("Unable to allocate buffer.\n");
        display_hash_queues();
        display_free_list();
        return 0;
    }
