#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ENTRIES 5
#define MAX_INODES 10

/* Structure for a directory entry (maps a name to an inode) */
typedef struct {
    char name[32];
    int inode_number;
} DirEntry;

/* Structure simulating an Inode */
typedef struct {
    int inode_number;
    int is_dir; /* 1 if directory, 0 if regular file */
    DirEntry entries[MAX_ENTRIES];
    int entry_count;
} Inode;

/* Simulated Disk / Inode Table */
Inode inode_table[MAX_INODES];

/* System Environment Variables */
int root_inode = 1;
int current_dir_inode = 2; // Let's pretend the user is currently in "/home" (Inode 2)

/* Simulated iget(): Fetch inode from disk to memory */
Inode* iget(int inode_num) {
    printf("  [System] iget: Fetching Inode %d\n", inode_num);
    return &inode_table[inode_num];
}

/* Simulated iput(): Release inode */
void iput(Inode* inode) {
    printf("  [System] iput: Releasing Inode %d\n", inode->inode_number);
}

/* Initialize our mock file system */
void init_mock_filesystem() {
    // Inode 1: "/" (Root Directory)
    inode_table[1].inode_number = 1;
    inode_table[1].is_dir = 1;
    inode_table[1].entry_count = 3;
    strcpy(inode_table[1].entries[0].name, ".");  inode_table[1].entries[0].inode_number = 1;
    strcpy(inode_table[1].entries[1].name, ".."); inode_table[1].entries[1].inode_number = 1;
    strcpy(inode_table[1].entries[2].name, "home"); inode_table[1].entries[2].inode_number = 2;

    // Inode 2: "/home" (Directory)
    inode_table[2].inode_number = 2;
    inode_table[2].is_dir = 1;
    inode_table[2].entry_count = 3;
    strcpy(inode_table[2].entries[0].name, ".");  inode_table[2].entries[0].inode_number = 2;
    strcpy(inode_table[2].entries[1].name, ".."); inode_table[2].entries[1].inode_number = 1;
    strcpy(inode_table[2].entries[2].name, "file.txt"); inode_table[2].entries[2].inode_number = 3;

    // Inode 3: "/home/file.txt" (Regular File)
    inode_table[3].inode_number = 3;
    inode_table[3].is_dir = 0; // Not a directory
    inode_table[3].entry_count = 0;
}

/* The namei() Algorithm Implementation */
int namei(char* pathname) {
    int working_inode_num;
    char path_copy[256];
    char* component;

    strcpy(path_copy, pathname);

    printf("\n--- Starting namei() for path: '%s' ---\n", pathname);

    /* 1. Determine starting inode based on absolute/relative path */
    if (pathname[0] == '/') {
        printf("Absolute path detected. Starting at ROOT.\n");
        working_inode_num = root_inode;
    } else {
        printf("Relative path detected. Starting at CURRENT DIRECTORY.\n");
        working_inode_num = current_dir_inode;
    }

    /* 2. Split pathname into components */
    component = strtok(path_copy, "/");

    while (component != NULL) {
        printf("\nProcessing component: '%s'\n", component);
        Inode* working_inode = iget(working_inode_num);

        /* 3. Verify working inode is a directory */
        if (!working_inode->is_dir) {
            printf("Error: '%s' is not a directory! Cannot search inside it.\n", component);
            iput(working_inode);
            return -1;
        }

        /* 4. Handle root ".." edge case */
        if (working_inode->inode_number == root_inode && strcmp(component, "..") == 0) {
            printf("Notice: At root directory, '..' maps back to root.\n");
            component = strtok(NULL, "/");
            continue;
        }

        /* 5. Search directory for the component */
        int found_inode = -1;
        for (int i = 0; i < working_inode->entry_count; i++) {
            if (strcmp(working_inode->entries[i].name, component) == 0) {
                found_inode = working_inode->entries[i].inode_number;
                printf("  -> Match found! '%s' is Inode %d\n", component, found_inode);
                break;
            }
        }

        if (found_inode == -1) {
            printf("Error: Component '%s' not found in current directory.\n", component);
            iput(working_inode);
            return -1; // No inode
        }

        /* 6. Release working inode and update for next loop */
        iput(working_inode);
        working_inode_num = found_inode;

        /* Move to next component */
        component = strtok(NULL, "/");
    }

    return working_inode_num;
}

int main() {
    char pathname[256];
    init_mock_filesystem();

    printf("=== Namei() Algorithm Simulator ===\n");
    printf("Available paths in mock FS:\n");
    printf(" - / (Root)\n");
    printf(" - /home\n");
    printf(" - /home/file.txt\n");
    printf("Current working directory is set to: /home (Inode 2)\n\n");

    printf("Enter a pathname to resolve: ");
    scanf("%255s", pathname);

    int final_inode = namei(pathname);

    if (final_inode != -1) {
        printf("\nSUCCESS: The final inode number for '%s' is: %d\n", pathname, final_inode);
    } else {
        printf("\nFAILURE: Path resolution failed.\n");
    }

    return 0;
}
