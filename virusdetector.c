#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct menu_option {
    const char* description;
    void (*action)();
}; 
typedef struct virus {
unsigned short SigSize;
char virusName[16];
unsigned char* sig;
} virus;
typedef struct link link;
struct link {
    link *nextVirus;
    virus *vir;
};
link *SignaturesList= NULL; 
void detect_viruses() {
    char filename[100];
    printf("Enter suspected file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // remove newline

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }
    unsigned char buffer[10000];
    int size = fread(buffer, 1, 10000, file);
    fclose(file);

    for (link *curr = SignaturesList; curr != NULL; curr = curr->nextVirus) {
        virus *v = curr->vir;

        for (int i = 0; i <= size - v->SigSize; i++) {
            if (memcmp(buffer + i, v->sig, v->SigSize) == 0) {
                printf("Virus found at byte %d\n", i);
                printf("Virus name: %s\n", v->virusName);
                 printf("Virus signature size: %d\n\n", v->SigSize);
            }
        }
    }
}
void neutralize_virus(char *fileName, int signatureOffset){
    unsigned char fix = 0xC3;
    FILE* file= fopen(fileName, "r+b");
    if(file!=NULL){
        fseek(file, signatureOffset, SEEK_SET);
        fwrite(&fix, 1,1,file);
        fclose(file);
    }
    else{
        printf("file not found exception\n");
    }

}

void fix_file(){ 
    char filename[100];
    printf("Enter suspected file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // remove newline

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }
    unsigned char buffer[10000];
    int size = fread(buffer, 1, 10000, file);
    fclose(file);

    for (link *curr = SignaturesList; curr != NULL; curr = curr->nextVirus) {
        virus *v = curr->vir;

        for (int i = 0; i <= size - v->SigSize; i++) {
            if (memcmp(buffer + i, v->sig, v->SigSize) == 0) {
                printf("Virus found at byte %d\n", i);
                neutralize_virus(filename, i);

            }
        }
    }
}

void ai_analysis()     { printf("Not implemented yet\n"); }
void quit()            { printf("Quitting...\n"); exit(0); }

link* list_append(link* virus_list, virus* data){
    link* pointer= virus_list;
    link* newlink = malloc(sizeof(link));
    if (!newlink) return virus_list; // or NULL
    newlink->vir = data;
    newlink->nextVirus = NULL;
    if(virus_list==NULL){
        return newlink;
    }
    while(virus_list->nextVirus != NULL){ 
        virus_list= virus_list->nextVirus;
    }
    virus_list->nextVirus=newlink;
    return pointer;   
}
virus* readsignature(FILE* input){
    virus* v = malloc(sizeof(virus));
    if (v == NULL) return NULL;
    if (fread(&v->SigSize, 1, 2, input) != 2) {
        free(v);
        return NULL; 
    }
    fread(v->virusName, 1, 16, input);
    v->sig = malloc(v->SigSize);
    fread(v->sig, 1, v->SigSize, input);
    return v;
}

void printSignature(virus* virus, FILE* output){
    fprintf(output, "%s", virus->virusName);
    fprintf(output, " %d\n", virus->SigSize);
    for (int i = 0; i < virus->SigSize; i++) {
    fprintf(output, "%02X ", virus->sig[i]);
    }
    fprintf(output, "\n");
}
void list_print(link *virus_list, FILE* stream){
    while(virus_list!=NULL){
        printSignature(virus_list->vir, stream);
        fprintf(stream, "\n");
        virus_list= virus_list->nextVirus;
    }
}
void LoadSignature(){
    char filename[100];
    printf("Enter signatures file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Remove newline
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }
    char magic[4];
    if (fread(magic, 1, 4, file) != 4) {
        printf("Cannot read magic number\n");
        fclose(file);
        return;
    }
    int isBigEndian;
    if (memcmp(magic, "VIRL", 4) == 0) {
        isBigEndian = 0;
    } else if (memcmp(magic, "VIRB", 4) == 0) {
        isBigEndian = 1;}
    else {
        printf("Invalid file format\n");
        fclose(file);
        return;
    }
    // Read viruses one by one
    while (1) {
        virus* v = readsignature(file);
        if (!v) break; // End of file
        if (isBigEndian) {
        v->SigSize = (v->SigSize >> 8) | (v->SigSize << 8);
        }
        SignaturesList = list_append(SignaturesList, v);
    }   
    fclose(file);
    printf("Signatures loaded successfully.\n");
}

void PrintSignatures() {
    if (!SignaturesList) {
        printf("No signatures\n");
        return;
    }
    FILE* file = fopen("all_viruses.txt", "w");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }
    list_print(SignaturesList, file);
    fclose(file);
}


void list_free(link *virus_list){
    while(virus_list != NULL){
        link* next = virus_list->nextVirus;
        free(virus_list->vir->sig);
        free(virus_list->vir);
        free(virus_list);
        virus_list = next;
    }
}



int main(int argc, char** argv){
    struct menu_option menu_options[] = {
    {"Load signatures", LoadSignature},
    {"Print signatures", PrintSignatures},
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