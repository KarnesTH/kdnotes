#include "../include/file_ops.h"
#include <stdio.h>
#include <string.h>
#include "../include/note.h"

int save_notes_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    fprintf(file, "%d\n", note_count);

    for (int i = 0; i < note_count; i++) {
        fprintf(file, "%s\n", notes[i].title);
        fprintf(file, "%s\n", notes[i].content);
    }

    fclose(file);
    return 0;
}

int load_notes_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        return -1;
    }

    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        fclose(file);
        return -1;
    }

    init_notes();

    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    char line[MAX_CONTENT_LENGTH];

    for (int i = 0; i < count; i++) {
        if (!fgets(title, MAX_TITLE_LENGTH, file)) {
            break;
        }
        title[strcspn(title, "\n")] = '\0';

        if (!fgets(content, MAX_CONTENT_LENGTH, file)) {
            break;
        }
        content[strcspn(content, "\n")] = '\0';

        add_note(title, content);
    }

    fclose(file);
    return 0;
}
