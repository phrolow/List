#include "list.h"

void ListDump_(list *list, const char *func, const char *file, size_t line) {
    FILE *fp = NULL;

    fp = fopen(LOGPATH, "a");

    fprintf(fp, "%s at %s(%llu)\n", func, file, line);
    fprintf(fp, "List[%p] (ok) at %s at %s(%llu) {\n", list, list->info.func, list->info.file, list->info.line);
    fprintf(fp, "\tsize = %llu\n", list->size);
    fprintf(fp, "\tdata[%p] {\n", list->data);

    for(size_t i = 0; i < list->size; i++) {
        fprintf(fp, "\t\t");

        /* if(i < list->size)
            fprintf(fp, "*"); */

        fprintf(fp, "[%llu] = %d", i, list->data[i]);

        if(list->data[i] == POISON)
            fprintf(fp, " (POISON)");

        fprintf(fp, "\n");
    }

    fprintf(fp, "\t}\n}\n");

    fclose(fp);

    return;
}

int ListCheck_(list *list, const char* func, const char* file, size_t line) {
    int err = ALL_RIGHT;

    err |= CHECK(list->data, NULL_DATA);

    err |= CHECK(list->size < BIG_SIZE && list->size > 0, BAD_SIZE);

    perror_(err, file, func, line);

    return err;
}

void CleanLogs() {
    fclose(fopen(LOGPATH, "w"));
}

void perror_(int err, const char* file, const char* func, size_t line) {
    FILE* fp =  NULL;
    char *bin = NULL;

    fp = fopen(LOGPATH, "a");
    bin = (char*) calloc(8 + 1, sizeof(char));

    if(err)
        fprintf(fp, "ERROR 0b%s in %s at %s(%llu)\n\n", itoa(err, bin, 2), func, file, line);
    else
        fprintf(fp, "(OK)\n\n");

    fclose(fp);
    free(bin);

    return;
}