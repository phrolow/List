#include "list.h"

void ListDump_(list *list, const char *func, const char *file, size_t line) {
    FILE *fp;

    fp = fopen(HTMLPATH, "a");

    fprintf(fp, "<pre>\n");
    fprintf(fp, "%s at %s(%llu)\n", func, file, line);
    fprintf(fp, "List[%p] (%s at %s(%llu)) {\n", list, list->info.func, list->info.file, list->info.line);
    fprintf(fp, "\tsize = %llu\n", list->size);
    fprintf(fp, "\thappy: %d\n}\n\n", list->happy);
    fprintf(fp, "</pre>\n\n");

    fclose(fp);
}

void ListGraphDump(list *list) {
    FILE *fp = NULL;
    char *cmdbuf = NULL;
    int i = 0;

    fp = fopen(DOTPATH, "w");

    fprintf(fp, "digraph structs {\n");

    fprintf(fp, "\tnode [color=black, shape=box, style=\"filled\"];\n");
    fprintf(fp, "\trankdir=LR;\n");
    fprintf(fp, "\thead [fillcolor=\"#42AAFF\",     label=\"Head = %d\"];\n", list->Head);
    fprintf(fp, "\ttail  [fillcolor=\"#42AAFF\",     label=\"Tail = %d\"];\n", list->Tail);
    fprintf(fp, "\tfree  [fillcolor=\"#42AAFF\",     label=\"free = %d\"];\n", list->free);
    fprintf(fp, "\tsorted [fillcolor=\"#E34234\",    label=\"happy = %d\"];\n", list->happy);
    fprintf(fp, "\tsize   [fillcolor=\"#E34234\",    label=\"size = %llu\"];\n", list->size);
    fprintf(fp, "\tnode [color=black, shape=record, style=\"filled\"];\n\n");

    fprintf(fp, "\tedge [style=invis, constraint=true];\n");

    for(i = 0; i < list->size; i++) {
        fprintf(fp, "\tnode%d [fillcolor=\"#5035DE\",label=\" %d | { <p> %d | %d | <n> %d}\"];\n", i, i, list->prev[i], list->data[i], list->next[i]);
        if(i)
            fprintf(fp, "\tnode%d->node%d;\n", i, i - 1);
    }

    i = list->Head;

    fprintf(fp, "\tedge [style=solid, constraint=false];\n");

    do {
        fprintf(fp, "\tnode%d->node%d\n", i, list->next[i]);

        i = list->next[i];
    } while(list->next[i]);

    fprintf(fp, "\tedge [style=bold, constraint=false];\n");
    fprintf(fp, "\thead->node%d;\n", list->Head);
    fprintf(fp, "\ttail->node%d;\n", list->Tail);
    fprintf(fp, "\tfree->node%d;\n", list->free);
    fprintf(fp, "}");

    fclose(fp);

    cmdbuf = (char*)calloc(0x200, sizeof(char));
    sprintf(cmdbuf, "dot %s -T png -o graph%d.png", DOTPATH, NGDUMP);

    system(cmdbuf);

    free(cmdbuf);

    fp = fopen(HTMLPATH, "a");

    fprintf(fp, "<img src=\"graph%d.png\">\n", NGDUMP);

    fclose(fp);

    NGDUMP++;

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
    fclose(fopen(HTMLPATH, "w"));
    fclose(fopen(DOTPATH, "w"));
    fclose(fopen(PNGPATH, "wb"));
}

void perror_(int err, const char* file, const char* func, size_t line) {
    FILE* fp =  NULL;
    char *bin = NULL;

    fp = fopen(HTMLPATH, "a");
    bin = (char*) calloc(8 + 1, sizeof(char));

    if(err)
        fprintf(fp, "ERROR 0b%s in %s at %s(%llu)\n\n", itoa(err, bin, 2), func, file, line);
    else
        fprintf(fp, "(OK)\n\n");

    fclose(fp);
    free(bin);

    return;
}