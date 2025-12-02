#include <stdio.h>
#include <stdio.h>
#include <string.h>
void load_signatures() { printf("Not implemented yet\n"); }
void print_signatures(){ printf("Not implemented yet\n"); }
void detect_viruses()  { printf("Not implemented yet\n"); }
void fix_file()        { printf("Not implemented yet\n"); }
void ai_analysis()     { printf("Not implemented yet\n"); }
void quit()            { printf("Quitting...\n"); exit(0); }

struct menu_option {
    const char* description;
    void (*action)();
};
typedef struct virus {
unsigned short SigSize;
char virusName[16];
unsigned char* sig;
} virus;

virus* readsignature(FILE* input){

}
void printSignature(virus* virus, FILE* output){
    fprintf(output, "%s", virus->virusName);
    fprintf(output, " %d\n", virus->SigSize);
    for (int i = 0; i < virus->SigSize; i++) {
    fprintf(output, "%02X ", virus->sig[i]);
    }
    fprintf(output, "\n");
}

int main(int argc, char** argv){

    struct menu_option menu_options[] = {
    {"Load signatures", load_signatures},
    {"Print signatures", print_signatures},
    {"Detect viruses", detect_viruses},
    {"Fix file", fix_file},
    {"AI analysis of file", ai_analysis},
    {"Quit", quit},
    {NULL, NULL} 
};

    int menu_length = 0;
    char input[100];
    int base_len_input= 100;
    while (menu_options[menu_length].description != NULL)
        menu_length++;
    while (1) {
            printf("Select operation from the following menu:\n");
            for (int i = 0; i < menu_length; i++) {
                printf("%d) %s\n", i + 1, menu_options[i].description);
            }
            fgets(input, base_len_input, stdin);
            char* endptr;
            long choice = strtol(input, &endptr, 10)-1;
            if (choice >= 0 && choice < menu_length) {
                menu_options[choice].action();   
            }
    }
}