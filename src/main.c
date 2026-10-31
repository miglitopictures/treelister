// study practice: a recursive directory viewer
// hand written in C by miglito.

// inspired by the simple design proposed by Hayyoth (https://hayyoth.org/)
// in the first 78 seconds of this video -> https://www.youtube.com/watch?v=tiMHtc6l7xM
/*
    - get user
    - walk(path)
        - if is directory, walk() it with recurssion
        - if is file, print name
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h> // DIRectory ENTry... ok
#include <sys/stat.h>

// traverses the directory specified by `path` printing its entries
// if a entry is a directory, recursively call walk() on it.
void walk(char *path, int depth) {

    DIR *diretory = opendir(path);
    if (diretory == NULL) return;

    struct dirent *entry = NULL;
    while (true) {
        
        entry = readdir(diretory);
        if (entry == NULL) { break; }
        
        // skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // add spacing based on "depth"
        for (int i = 0; i < depth; i++) { printf("  "); }

        // get new_path by concatonating path with the name 
        char new_path[4096];
        snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);

        // if is DIRECTORY:
        if (entry->d_type == DT_DIR) {
            printf("\x1B[1;33mL %s/\x1B[0m\n", entry->d_name);
            walk(new_path, depth + 1); // make the recursive call on it.
        }
        // if is FILE:
        else {
            // get file info with stat() and use `bitwise AND` (&) on `st_mode`
            // to check if is executable file, print it diferently.
            struct stat file_info;
            if (stat(new_path, &file_info) == 0 && (file_info.st_mode & S_IXUSR)) {  // S_IXUSR - execute/search permission, owner 
                printf("L \x1B[36m%s\x1B[0m\n", entry->d_name);
            }
            else {
                printf("L %s\n", entry->d_name);
            }
        }
    }

    closedir(diretory);
}

int main(int argument_count, char **arguments) {

    // get path from input
    char *path = ".";
    if (argument_count > 1) {
        path = arguments[1];
    }

    // print path
    printf("%s/\n", path);
    
    // treverse directory
    walk(path, 0);
    
    return 0;
}