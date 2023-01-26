#include "../list.h"

void ListDump_(list *list, const char *func, const char *file, size_t line) {
    fprintf(HTML, "<pre>\n");
    fprintf(HTML, "%s at %s(%llu)\n", func, file, line);
    fprintf(HTML, "List[%p] (%s at %s(%llu)) {\n", list, list->info.func, list->info.file, list->info.line);
    fprintf(HTML, "\tsize = %llu\n", list->size);
    fprintf(HTML, "\thappy: %d\n}\n\n", list->happy);
    fprintf(HTML, "</pre>\n\n");
}

void ListGraphDump(list *list) {
    char *cmdbuf = NULL;
    const char *color = NULL;
    int i = 0;

    fprintf(DOTFILE, "digraph structs {\n");

    fprintf(DOTFILE, "\tnode [color=black, shape=box, style=\"filled\"];\n");
    fprintf(DOTFILE, "\trankdir=LR;\n");
    fprintf(DOTFILE, "\thead [fillcolor=\"%s\",     label=\"Head = %d\"];\n", COLOR_HTF, list->Head);
    fprintf(DOTFILE, "\ttail  [fillcolor=\"%s\",     label=\"Tail = %d\"];\n", COLOR_HTF, list->Tail);
    fprintf(DOTFILE, "\tfree  [fillcolor=\"%s\",     label=\"free = %d\"];\n", COLOR_HTF, list->free);
    fprintf(DOTFILE, "\tsorted [fillcolor=\"%s\",    label=\"happy = %d\"];\n", COLOR_PARAM, list->happy);
    fprintf(DOTFILE, "\tsize   [fillcolor=\"%s\",    label=\"size = %llu\"];\n", COLOR_PARAM, list->size);
    fprintf(DOTFILE, "\tnode [color=black, shape=record, style=\"filled\"];\n\n");

    fprintf(DOTFILE, "\tedge [style=invis, constraint=true];\n");

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

        fprintf(DOTFILE, "\tnode%d [fillcolor=\"%s\",label=\" %d | { <p> %d | %d | <n> %d}\"];\n", i, color, i, list->prev[i], list->data[i], list->next[i]);
        if(i)
            fprintf(DOTFILE, "\tnode%d->node%d;\n", i, i - 1);
    }

    i = list->Head;

    fprintf(DOTFILE, "\tedge [style=solid, constraint=false];\n");

    for(int i = 0; i < list->size; i++) {
        fprintf(DOTFILE, "\tnode%d->node%d\n", i, list->next[i]);
    }

    fprintf(DOTFILE, "\tedge [style=bold, constraint=false];\n");
    fprintf(DOTFILE, "\thead->node%d;\n", list->Head);
    fprintf(DOTFILE, "\ttail->node%d;\n", list->Tail);
    fprintf(DOTFILE, "\tfree->node%d;\n", list->free);
    fprintf(DOTFILE, "}");

    cmdbuf = (char*)calloc(0x200, sizeof(char));
    sprintf(cmdbuf, "dot %s -T png -o graph.png", DOTPATH);

    system(cmdbuf);

    free(cmdbuf);

    fprintf(HTML, "<img src=\"graph.png\">\n");

    return;
}

void perror_(err_t err, const char* file, const char* func, size_t line) {
    char *bin = NULL;

    bin = (char*) calloc(8 + 1, sizeof(char));

    if(err)
        fprintf(HTML, "ERROR 0b%s in %s at %s(%llu)\n\n", itoa(err, bin, 2), func, file, line);
    else
        fprintf(HTML, "(OK)\n\n");

    free(bin);

    return;
}

void CloseLogs() {
    fclose(DOTFILE);
    fclose(HTML);
}