#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/wait.h>


// -------------------- ANSI COLORS & TEXT EFFECTS --------------------

// Text colors
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define GREY        "\033[90m"


// Bright text colors
#define BBLACK      "\033[90m"
#define BRED        "\033[91m"
#define BGREEN      "\033[92m"
#define BYELLOW     "\033[93m"
#define BBLUE       "\033[94m"
#define BMAGENTA    "\033[95m"
#define BCYAN       "\033[96m"
#define BWHITE      "\033[97m"

// Background colors
#define BGBLACK     "\033[40m"
#define BGRED       "\033[41m"
#define BGGREEN     "\033[42m"
#define BGYELLOW    "\033[43m"
#define BGBLUE      "\033[44m"
#define BGMAGENTA   "\033[45m"
#define BGCYAN      "\033[46m"
#define BGWHITE     "\033[47m"

// Bright background colors
#define BGBBLACK    "\033[100m"
#define BGRED_B     "\033[101m"
#define BGGREEN_B   "\033[102m"
#define BGYELLOW_B  "\033[103m"
#define BGBBLUE_B   "\033[104m"
#define BGMAGENTA_B "\033[105m"
#define BGCYAN_B    "\033[106m"
#define BGWHITE_B   "\033[107m"

// Text effects
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define INVERT      "\033[7m"
#define HIDDEN      "\033[8m"
#define STRIKETHROUGH "\033[9m"

// int proccess(){

// }

int main() {
    char buff[100];  
    int n = 100;

    system("clear");

    while (1) {

        // Getting username
        char *username = getenv("USER");
        if (!username) username = "unknown";

        // Getting Hostname
        char hostname[HOST_NAME_MAX + 1]; // +1 for null terminator
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            strcpy(hostname, "unknown");
        }

        // Getting current dir
        char cwd[PATH_MAX];
        char *current_dir = NULL;
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            current_dir = cwd;
        } else {
            current_dir = "unknown";
        }

        // Prompt
        printf(
            BLUE "\n┌─ $ " RESET
            GREY "(" BOLD YELLOW "%s" RESET BRED "@" BOLD YELLOW "%s" RESET GREY ") - " RESET
            GREY "{" BOLD CYAN "%s" RESET GREY "}" RESET BLUE "\n└─> " RESET,
            username, hostname, current_dir
        );
        
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

        // Make a copy of buff to use for error messages
        char original_buff[100];
        strcpy(original_buff, buff);

        // Tokenizing the cmd
        char* token = strtok(buff, " ");

        // --------- BUILT-IN COMMANDs -----------

        // PWD
        if (strcmp(token, "pwd") == 0 ) 
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                 printf("%s\n", cwd);
            }

            else { perror("getcwd() error"); return 1; }
            continue; 
        }
        // LS (manual implementation)
        if (strcmp(token, "ls") == 0) {
            char *dir_to_list = ".";  // list current working directory
            struct dirent *de;

            DIR *dr = opendir(dir_to_list);
            if (dr == NULL) {
                printf("Could not open current directory\n");
                continue;
            }

            while ((de = readdir(dr)) != NULL) {
                // skip . and ..
                if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
                    continue;

                // build full relative path
                char path[PATH_MAX];
                snprintf(path, sizeof(path), "%s/%s", dir_to_list, de->d_name);

                struct stat st;
                if (stat(path, &st) == 0) {
                    if (S_ISDIR(st.st_mode)) {
                        printf(BOLD CYAN"%s/\n"RESET, de->d_name);  // directory
                    } else {
                        printf(BOLD GREEN"%s\n"RESET, de->d_name);   // file
                    }
                } else {
                    printf("%s\n", de->d_name);  // fallback
                }
            }

            closedir(dr);
            continue;
        }


        // ECHO
        if (strcmp(token, "echo") == 0) {
            token = strtok(NULL, " "); // first argument after echo

            if (token == NULL) {
                printf("\n");
                continue;
            }

            // If argument starts with a quote
            if (token[0] == '"') {
                char buffer[1024] = {0};
                strcat(buffer, token + 1); // skip the first quote

                // Keep grabbing tokens until we find the closing quote
                while (token[strlen(token) - 1] != '"') {
                    token = strtok(NULL, " ");
                    if (token == NULL) break; // malformed input

                    strcat(buffer, " ");
                    strcat(buffer, token);
                }

                // Remove the trailing quote if present
                if (buffer[strlen(buffer) - 1] == '"') {
                    buffer[strlen(buffer) - 1] = '\0';
                }

                printf("%s\n", buffer);
            } 
            else {
                // No quotes, just print normally
                printf("%s\n", token);
            }

            continue;
        }

        // CD
        if (strcmp(token, "cd") == 0) {
            char *arg = strtok(NULL, " "); // folder to change to
            if (arg == NULL) arg = getenv("HOME"); // default to HOME
            if (chdir(arg) != 0) {
                perror("chdir failed");
            }
            continue;
        }

        // CLEAR
        if (strcmp(token, "clear") == 0 ) {
            system("clear");
            continue;
        }

        // unknown command
        printf("%s: Command Not Found.\n", original_buff);

    }

    return 0;
}
