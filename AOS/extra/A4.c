#include <stdio.h>
    #include <stdlib.h>
    #define HASH_SIZE 4
    #define BUFFER_COUNT 6

    typedef struct Buffer{
        int block_number;
        int busy;
        int valid;
        int delayed_write;
        char data[100];
        struct Buffer *hash_next;
        struct Buffer *free_next;
    }Buffer;

    Buffer *hash_table[HASH_SIZE];
    Buffer *free_list=NULL;

    int hash(int block_number){return block_number%HASH_SIZE;}

    void initialize_buffer(Buffer *buffer,int block_number){
        buffer->block_number=block_number;
        buffer->busy=0;
        buffer->valid=0;
        buffer->delayed_write=0;
        buffer->data[0]='\0';
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
        Buffer *current=hash_table[index],*previous=NULL;
        while(current!=NULL){
            if(current==buffer){
                if(previous==NULL) hash_table[index]=current->hash_next;
                else previous->hash_next=current->hash_next;
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
        if(free_list==NULL){free_list=buffer;return;}
        current=free_list;
        while(current->free_next!=NULL) current=current->free_next;
        current->free_next=buffer;
    }

    void remove_from_free_list(Buffer *buffer){
        Buffer *current=free_list,*previous=NULL;
        while(current!=NULL){
            if(current==buffer){
                if(previous==NULL) free_list=current->free_next;
                else previous->free_next=current->free_next;
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
            if(current->block_number==block_number) return current;
            current=current->hash_next;
        }
        return NULL;
    }

    void write_to_disk(Buffer *buffer){
        printf("Writing block %d to disk...\n",buffer->block_number);
        printf("Data written: %s\n",buffer->data);
        buffer->valid=1;
    }

    Buffer *getblk(int block_number){
        Buffer *buffer;
        while(1){
            buffer=search_buffer(block_number);
            if(buffer!=NULL){
                if(buffer->busy){buffer->busy=0;continue;}
                buffer->busy=1;
                remove_from_free_list(buffer);
                return buffer;
            }
            if(free_list==NULL) return NULL;
            buffer=free_list;
            remove_from_free_list(buffer);
            if(buffer->delayed_write){
                write_to_disk(buffer);
                buffer->delayed_write=0;
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

    void brelse(Buffer *buffer){
        if(buffer==NULL) return;
        buffer->busy=0;
        insert_into_free_list(buffer);
    }

    void bwrite(Buffer *buffer){
        if(buffer==NULL) return;
        write_to_disk(buffer);
        buffer->delayed_write=0;
        brelse(buffer);
    }

    int main(){
        int i,block_number;
        Buffer *buffer;
        for(i=0;i<HASH_SIZE;i++) hash_table[i]=NULL;
        for(i=0;i<BUFFER_COUNT;i++){
            buffer=malloc(sizeof(Buffer));
            initialize_buffer(buffer,i);
            insert_into_hash(buffer);
            insert_into_free_list(buffer);
        }
        printf("Enter block number: ");
        scanf("%d",&block_number);
        buffer=getblk(block_number);
        if(buffer!=NULL){
            printf("Enter data to write: ");
            scanf(" %99[^\n]",buffer->data);
            buffer->valid=1;
            buffer->delayed_write=1;
            bwrite(buffer);
        }
        return 0;
    }
