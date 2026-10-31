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

// helper string function
// checks if a character exists inside a string
bool contains_character(char character, char *string) {
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] == character) {
            return true;
        }
        i++;
    }
    return false;
}

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

        
        // if is directory:
        // concatonate the path with the name to get new_path.
        // and make the recursive call on it.
        if (entry->d_type == DT_DIR) {
            printf("L %s/\n", entry->d_name);
            char new_path[4096];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            walk(new_path, depth + 1);
        }
        // if is FILE:
        else {            
            printf("L %s\n", entry->d_name);
        }
    }

    closedir(diretory);
}

int main(int argc, char **argv) {

    // get path from input
    char *path = ".";
    if (argc > 1) {
        path = argv[1];
    }
    
    // treverse directory
    walk(path, 0);
    
    return 0;
}