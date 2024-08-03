#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "log_utils.h"

void log_message(const char *message) {
    FILE *log_fp = fopen("logs/server_log.txt", "a");
    if (log_fp == NULL) {
        perror("Failed to open log file");
        exit(1);
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline character

    fprintf(log_fp, "[%s] %s\n", timestamp, message);
    fclose(log_fp);
}

