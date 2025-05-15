#ifndef NOTE_H
#define NOTE_H

#define MAX_TITLE_LENGTH 50
#define MAX_CONTENT_LENGTH 1000
#define MAX_NOTES 100

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    int id;
} Note;

extern Note notes[MAX_NOTES];
extern int note_count;

void init_notes();
int add_note(const char* title, const char* content);
void list_notes();
int delete_note(int id);
Note* get_note(int id);

#endif
