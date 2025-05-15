#include "../include/note.h"
#include <stdio.h>
#include <string.h>

Note notes[MAX_NOTES];
int note_count = 0;

void init_notes() {
    note_count = 0;
}

int add_note(const char *title, const char *content) {
    if (note_count >= MAX_NOTES) {
        printf("ERROR: Failed to add note, maximum number of notes reached\n");
        return -1;
    }

    int id = note_count;
    notes[id].id = id;

    strncpy(notes[id].title, title, MAX_TITLE_LENGTH - 1);
    notes[id].title[MAX_TITLE_LENGTH - 1] = '\0';

    strncpy(notes[id].content, content, MAX_CONTENT_LENGTH - 1);
    notes[id].content[MAX_CONTENT_LENGTH - 1] = '\0';

    note_count++;
    return id;
}

void list_notes() {
    if (note_count == 0) {
        printf("No notes available.\n");
        return;
    }

    printf("\n===== Notes =====\n");
    for (int i = 0; i < note_count; i++) {
        printf("[%d] %s\n", notes[i].id, notes[i].title);
    }
    printf("==================\n\n");
}

int delete_note(int id) {
    if (id < 0 || id >= note_count) {
        return -1;
    }

    for (int i = id; i < note_count - 1; i++) {
        notes[i] = notes[i + 1];
        notes[i].id = i;
    }

    note_count--;
    return 0;
}

Note* get_note(int id) {
    if (id < 0 || id >= note_count) {
        return NULL;
    }
    return &notes[id];
}
