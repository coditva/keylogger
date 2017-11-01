#include <fcntl.h>
#include <stdio.h>

#define EVENT_FILE_PATH "/dev/input/event0"

int main(int argc, char *argv[])
{
    int event_fd = open(EVENT_FILE_PATH, O_RDONLY);
    if (event_fd == -1) {
        fprintf(stderr, "Could not open file\n");
    } else {
        printf("File opened\n");
    }
    return 0;
}
