#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// int proccess(){

// }


int main() {
    char buff[100];  
    int n = 100;

    system("clear");

    while (1) {
        printf("\n$ > ");
        
        // Read input
        if (fgets(buff, n, stdin) == NULL) {
            continue;  // handle input error
        }

        // Remove trailing newline
        buff[strcspn(buff, "\n")] = '\0';

        // Skip empty input
        if (buff[0] == '\0') {
            continue;
        }

        // Exit condition
        if (strcmp(buff, "exit") == 0) {
            break;
        }

        // Otherwise, unknown command
        printf("%s: Command Not Found.\n", buff);
    }

    return 0;
}