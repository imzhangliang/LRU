#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echoing
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply new settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Get file status flags
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    // Make stdin non-blocking
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    while (1) {
        ch = getchar(); // Read from stdin

        if (ch != EOF) {
            printf("Key pressed: %c\n", ch); // Print the character
            break; // Exit the loop
        }
        // Add any other processing here
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
