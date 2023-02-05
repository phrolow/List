#include "../list.h"

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
    const char *color = NULL;
    int i = 0;

    fp = fopen(DOTPATH, "w");

    fprintf(fp, "digraph structs {\n");

    fprintf(fp, "\tnode [color=black, shape=box, style=\"filled\"];\n");
    fprintf(fp, "\trankdir=LR;\n");
    fprintf(fp, "\thead [fillcolor=\"%s\",     label=\"Head = %d\"];\n", COLOR_HTF, list->Head);
    fprintf(fp, "\ttail  [fillcolor=\"%s\",     label=\"Tail = %d\"];\n", COLOR_HTF, list->Tail);
    fprintf(fp, "\tfree  [fillcolor=\"%s\",     label=\"free = %d\"];\n", COLOR_HTF, list->free);
    fprintf(fp, "\tsorted [fillcolor=\"%s\",    label=\"happy = %d\"];\n", COLOR_PARAM, list->happy);
    fprintf(fp, "\tsize   [fillcolor=\"%s\",    label=\"size = %llu\"];\n", COLOR_PARAM, list->size);
    fprintf(fp, "\tnode [color=black, shape=record, style=\"filled\"];\n\n");

    fprintf(fp, "\tedge [style=invis, constraint=true];\n");

    for(i = 0; i < list->size; i++) {
        if(!i) {
            color = COLOR_ZERO_NODE;
        }
        else if(list->prev[i] == -1) {
            color = COLOR_FREE_NODE;
        }
        else {
            color = COLOR_NODE;
        }

        fprintf(fp, "\tnode%d [fillcolor=\"%s\",label=\" %d | { <p> PREV %d | %c | <n> NEXT %d}\"];\n", i, color, i, list->prev[i], list->data[i], list->next[i]);
        if(i)
            fprintf(fp, "\tnode%d->node%d;\n", i, i - 1);
    }

    i = list->Head;

    fprintf(fp, "\tedge [style=solid, constraint=false];\n");

    for(int i = 0; i < list->size; i++) {
        fprintf(fp, "\tnode%d->node%d\n", i, list->next[i]);
    }

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

void CleanLogs() {
    fclose(fopen(HTMLPATH, "w"));
    fclose(fopen(DOTPATH, "w"));
    fclose(fopen(PNGPATH, "wb"));
}

void perror_(err_t err, const char* file, const char* func, size_t line) {
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