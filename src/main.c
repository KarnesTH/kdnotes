#include "../include/main.h"
#include <stdio.h>
#include <string.h>
#include "../include/note.h"
#include "../include/file_ops.h"

#define DEFAULT_FILENAME "notes.txt"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu() {
    printf("\nNOTEBOOK - HOME\n");
    printf("1. New note\n");
    printf("2. Show notes\n");
    printf("3. Read note\n");
    printf("4. Delete note\n");
    printf("5. Save notes\n");
    printf("6. Load notes\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

void create_note() {
    char title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];

    printf("\n=== NEW NOTE ===\n");

    printf("Title: ");
    fgets(title, MAX_TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Content (empty line to finish):\n");

    content[0] = '\0';
    char line[MAX_CONTENT_LENGTH];

    while (1) {
        fgets(line, MAX_CONTENT_LENGTH, stdin);

        if (line[0] == '\n') {
            break;
        }

        if (strlen(content) + strlen(line) < MAX_CONTENT_LENGTH - 1) {
            strcat(content, line);
        } else {
            printf("Warning: Maximum length reached. Content has been truncated.\n");
            break;
        }
    }

    int id = add_note(title, content);
    if (id >= 0) {
        printf("Note successfully created. (ID: %d).\n", id);
    }
}

void read_note() {
    int id;

    printf("\nWhich note do you want to read? ID: ");
    scanf("%d", &id);
    clear_input_buffer();

    Note* note = get_note(id);
    if (note) {
        printf("\n=== Note #%d ===\n", id);
        printf("Title: %s\n", note->title);
        printf("Content:\n%s\n", note->content);
        printf("================\n");
    } else {
        printf("ERROR: Failed to find note with ID %d.\n", id);
    }
}

void delete_note_ui() {
    int id;

    printf("\nWhich note do you want to delete? ID: ");
    scanf("%d", &id);
    clear_input_buffer();

    if (delete_note(id) == 0) {
        printf("Note #%d successfully deleted.\n", id);
    } else {
        printf("ERROR: Failed to find note with ID %d\n", id);
    }
}

int main() {
    init_notes();
    int choice = -1;

    printf("Welcome to your Notebook!\n");

    while (choice != 0) {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 0:
                printf("Goodbye!\n");
                break;

            case 1:
                create_note();
                break;

            case 2:
                list_notes();
                break;

            case 3:
                read_note();
                break;

            case 4:
                delete_note_ui();
                break;

            case 5:
                if (save_notes_to_file(DEFAULT_FILENAME) == 0) {
                    printf("Notes successfully saved to '%s'.\n", DEFAULT_FILENAME);
                }
                break;

            case 6:
                if (load_notes_from_file(DEFAULT_FILENAME) == 0) {
                    printf("Notes successfully loaded from '%s'.\n", DEFAULT_FILENAME);
                }
                break;

            default:
                printf("Invalid option, please try again.\n");
        }
    }

    return 0;
}
