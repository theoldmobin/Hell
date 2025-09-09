#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
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





void printHelp(){
        printf(BOLD RED "\n  ================== HELL COMMANDS HELP ==================\n" RESET);
        printf(BOLD BRED "  pwd" RESET "       - Print current working directory\n");
        printf(BOLD BRED "  ls" RESET "        - List files and directories\n");
        printf(BOLD BRED "  cd" RESET "        - Change directory (default HOME)\n");
        printf(BOLD BRED "  echo/ec" RESET "   - Print text to the terminal\n");
        printf(BOLD BRED "  whoami/wmi" RESET " - Show current user\n");
        printf(BOLD BRED "  clear/clr/cls" RESET " - Clear the terminal screen\n");
        printf(BOLD BRED "  mkdir/mdr" RESET " - Create a new directory\n");
        printf(BOLD BRED "  rmdir/rmd" RESET " - Remove an empty directory\n");
        printf(BOLD BRED "  rm" RESET "        - Remove a file\n");
        printf(BOLD BRED "  touch/tch" RESET " - Create an empty file or update timestamp\n");
        printf(BOLD BRED "  exit" RESET "       - Exit the shell\n");
        printf(BOLD BRED "  help" RESET "       - Show this help message\n");
        printf(BOLD RED "  =======================================================\n\n" RESET);
}



// Function to convert color names to ANSI escape sequences
void process_color_names(char *str) {
    // Create a temporary buffer
    char temp[2048] = {0};
    char *src = str;
    char *dst = temp;
    
    while (*src) {
        // Check for color names

        // Basic Colors
        if (strncmp(src, "RED", 3) == 0) {
            strcpy(dst, RED);
            dst += strlen(RED);
            src += 3;
        }
        else if (strncmp(src, "GREEN", 5) == 0) {
            strcpy(dst, GREEN);
            dst += strlen(GREEN);
            src += 5;
        }
        else if (strncmp(src, "YELLOW", 6) == 0) {
            strcpy(dst, YELLOW);
            dst += strlen(YELLOW);
            src += 6;
        }
        else if (strncmp(src, "BLUE", 4) == 0) {
            strcpy(dst, BLUE);
            dst += strlen(BLUE);
            src += 4;
        }
        else if (strncmp(src, "MAGENTA", 7) == 0) {
            strcpy(dst, MAGENTA);
            dst += strlen(MAGENTA);
            src += 7;
        }
        else if (strncmp(src, "CYAN", 4) == 0) {
            strcpy(dst, CYAN);
            dst += strlen(CYAN);
            src += 4;
        }
        else if (strncmp(src, "WHITE", 5) == 0) {
            strcpy(dst, WHITE);
            dst += strlen(WHITE);
            src += 5;
        }
        else if (strncmp(src, "GREY", 4) == 0) {
            strcpy(dst, GREY);
            dst += strlen(GREY);
            src += 4;
        }

        // Bright Colors
        else if (strncmp(src, "BRED", 4) == 0) {
            strcpy(dst, BRED);
            dst += strlen(BRED);
            src += 4;
        }
        else if (strncmp(src, "BGREEN", 6) == 0) {
            strcpy(dst, BGREEN);
            dst += strlen(BGREEN);
            src += 6;
        }
        else if (strncmp(src, "BYELLOW", 7) == 0) {
            strcpy(dst, BYELLOW);
            dst += strlen(BYELLOW);
            src += 7;
        }
        else if (strncmp(src, "BBLUE", 5) == 0) {
            strcpy(dst, BBLUE);
            dst += strlen(BBLUE);
            src += 5;
        }
        else if (strncmp(src, "BMAGENTA", 8) == 0) {
            strcpy(dst, BMAGENTA);
            dst += strlen(BMAGENTA);
            src += 8;
        }
        else if (strncmp(src, "BCYAN", 5) == 0) {
            strcpy(dst, BCYAN);
            dst += strlen(BCYAN);
            src += 5;
        }
        else if (strncmp(src, "BWHITE", 6) == 0) {
            strcpy(dst, BWHITE);
            dst += strlen(BWHITE);
            src += 6;
        }

        // Background Colors
        else if (strncmp(src, "BGBLUE", 6) == 0) {
            strcpy(dst, BGBLUE);
            dst += strlen(BGBLUE);
            src += 6;
        }
        else if (strncmp(src, "BGYELLOW", 8) == 0) {
            strcpy(dst, BGYELLOW);
            dst += strlen(BGYELLOW);
            src += 8;
        }
        else if (strncmp(src, "BGRED", 5) == 0) {
            strcpy(dst, BGRED);
            dst += strlen(BGRED);
            src += 5;
        }
        else if (strncmp(src, "BGRED", 5) == 0) {
            strcpy(dst, BGRED);
            dst += strlen(BGRED);
            src += 5;
        }

        // Text formats
        else if (strncmp(src, "BOLD", 4) == 0) {
            strcpy(dst, BOLD);
            dst += strlen(BOLD);
            src += 4;
        }
        else if (strncmp(src, "UNDERLINE", 9) == 0) {
            strcpy(dst, UNDERLINE);
            dst += strlen(UNDERLINE);
            src += 9;
        }
        else if (strncmp(src, "RESET", 5) == 0) {
            strcpy(dst, RESET);
            dst += strlen(RESET);
            src += 5;
        }
        else {
            // Copy regular characters
            *dst++ = *src++;
        }
    }
    
    // Copy the processed string back to the original
    strcpy(str, temp);
}

// Helper function to convert escape sequences to actual characters
void process_escape_sequences(char *str) {
    char temp[2048] = {0};
    char *src = str;
    char *dst = temp;
    
    while (*src) {
        if (*src == '\\') {
            src++;
            switch (*src) {
                case '0': 
                    if (src[1] == '3' && src[2] == '3') {
                        *dst++ = '\033';
                        src += 3;
                    } else {
                        *dst++ = '\\';
                    }
                    break;
                case 'n': *dst++ = '\n'; src++; break;
                case 't': *dst++ = '\t'; src++; break;
                case 'r': *dst++ = '\r'; src++; break;
                default: 
                    *dst++ = '\\';
                    *dst++ = *src++;
                    break;
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    
    // Copy the processed string back to the original
    strcpy(str, temp);
}




int main() {
    char buff[1024];  

    // Get absolute path to config file
    char configPath[PATH_MAX];
    if (realpath("../prompt.config", configPath) == NULL) {
        perror("Error resolving config file path");
        exit(EXIT_FAILURE);
    }

    system("clear");

    while (1) {

               // Get username, hostname, current dir
        char *username = getenv("USER");
        if (!username) username = "unknown";

        char hostname[HOST_NAME_MAX + 1];
        if (gethostname(hostname, sizeof(hostname)) != 0) strcpy(hostname, "unknown");

        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) strcpy(cwd, "unknown");

        char prompt[1024];
        char configPrompt[2048] = {0}; // Larger buffer for processing
        char ch;
        
        // Use absolute path to config file
        FILE *fptr = fopen(configPath, "r");
        if (!fptr) {
            perror("Error opening config file");
            exit(EXIT_FAILURE);
        }

        // Read file with bounds checking
        int i;
        for (i = 0; i < sizeof(configPrompt) - 1 && (ch = fgetc(fptr)) != EOF; i++) {
            configPrompt[i] = ch;
        }
        configPrompt[i] = '\0';
        fclose(fptr);

        // Parse the format string from configPrompt
        char *formatStart = strchr(configPrompt, '"');
        if (formatStart) {
            formatStart++; // Skip the first quote
            char *formatEnd = strrchr(formatStart, '"');
            if (formatEnd) {
                *formatEnd = '\0'; // Terminate at the closing quote
            }
        } else {
            formatStart = configPrompt;
        }

        // Process color names and text effects
        process_color_names(formatStart);
        
        // Process escape sequences in the format string
        process_escape_sequences(formatStart);

        // Build prompt with the required variables
        snprintf(prompt, sizeof(prompt), formatStart, username, hostname, cwd);

        // Read input using readline
        char *input = readline(prompt);
        if (!input) continue;


        // Skip empty input
        if (strlen(input) == 0) { free(input); continue; }

        // Add to history
        add_history(input);

        strncpy(buff, input, sizeof(buff)-1);
        buff[sizeof(buff)-1] = '\0';
        free(input);

        // Exit condition
        if (strcmp(buff, "exit") == 0) break;

        // Make a copy for errors
        char original_buff[1024];
        strcpy(original_buff, buff);

        // Tokenize
        char *token = strtok(buff, " ");

        // --------- BUILT-IN COMMANDs -----------

        // PWD
         if (strcmp(token, "pwd") == 0) {
            char cwd2[PATH_MAX];
            if (getcwd(cwd2, sizeof(cwd2))) printf("%s\n", cwd2);
            else perror("getcwd() error");
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
        if (strcmp(token, "echo") == 0 || strcmp(token, "ec") == 0) {
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

        //WHOAMI
        if (strcmp(token, "whoami") == 0 || strcmp(token, "wmi") == 0) {
            printf("%s",username);
            continue;
        }


        // CLEAR
        if (strcmp(token, "clear") == 0  || strcmp(token, "clr") == 0 || strcmp(token, "cls") == 0){
            system("clear");
            continue;
        }
        
        //RM
        if(strcmp(token, "rm")==0){
            token = strtok(NULL, " "); // To find second token
            if(token == NULL){
                continue;
            }
            remove(token);
            continue;
        }

        // RMDIR
        if (strcmp(token, "rmdir") == 0 || strcmp(token, "rmd") == 0) {
            struct stat st = {0};
            token = strtok(NULL, " "); // To find second token


            if (token == NULL){
                continue;
            }
            if (stat(token, &st) == 0 && S_ISDIR(st.st_mode)) {
                char dir_path[PATH_MAX];
                snprintf(dir_path, sizeof(dir_path), "%s/%s", cwd, token);
                if (rmdir(dir_path) == 0) {
                    printf(YELLOW"Directory removed: %s\n"RESET, dir_path);
                }
            }
                else{
                    printf(BRED"Directory '%s' Does not exist."RESET,token);
                }
                continue;
        }



        // MKDIR
        if (strcmp(token, "mkdir") == 0 || strcmp(token, "mdr") == 0) {
            struct stat st = {0};
            token = strtok(NULL, " "); // To find second token

            if(token == NULL){
                continue;
            }

            if (stat(token, &st) == -1) {
                mkdir(token, 0700);
            }
            else{
                printf(BRED"Directory '%s' Already exist."RESET,token);
            }
            continue;
        }

        // TOUCH
        if (strcmp(token, "touch") == 0 || strcmp(token, "tch") == 0) {
            token = strtok(NULL, " "); // filename

            if (token == NULL) {
                printf("touch: missing file operand\n");
                continue;
            }

            char file_name[1024]; // buffer for filename
            snprintf(file_name, sizeof(file_name), "%s", token);

            FILE *fp = fopen(file_name, "a"); // open for append, creates if not exists
            if (fp == NULL) {
                perror("touch");
                continue;
            }

            fclose(fp);
            continue;
    }
        
    if (strcmp(token, "help") == 0 ) {
        
        printHelp();
        continue;
    }
        // unknown command
        printf("%s: Command Not Found.\n", original_buff);

    }

    return 0;
}
