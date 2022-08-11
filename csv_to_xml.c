#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char* nme; // name
    int age; // age
    char* occ; // occupation
    char* tmp; // temporary
};

// Program to filter adults from CSV file and convert to XML
int main(int argc, char** argv) {
    // Output data variable
    struct Person* data[100];

    // Read file
    char* filename = argv[1];
    FILE* f = fopen(argv[1], "r");

    // Read lines
    char line[100];
    int n = 0;
    int header = 1;
    while (fgets(line, 10000, f)) {
        // Create person struct
        struct Person* p = malloc(1000);
        p->nme = malloc(1000);
        p->occ = malloc(1000);
        p->tmp = malloc(1000);

        // CSV has 3 fields: name, birth year, occupation
        strcpy(p->nme, strtok(line, ","));
        strcpy(p->tmp, strtok(NULL, ","));
        strcpy(p->occ, strtok(NULL, ","));

        // Age = current year - birth year
        p->age = 2021 - atoi(p->tmp);

        if (header) {
            header = 0;
            goto skip;
        } else {
            // Adult check
            if (p->age >= 18) {
                data[n] = malloc(1000);
                data[n] = p;
                // printf("%s\n", p->nme);
            } else {
                goto skip;
            }
        }

        n += 1;

        skip: ;
    }

    // Convert to XML
    char* xml = malloc(10000);
    strcat(xml, "<adults>");
    for (int i = 0; i < n; i += 1) {
        strcat(xml, "<adult>");
        strcat(xml, "<name>");
        strcat(xml, data[i]->nme);
        strcat(xml, "</name>");
        strcat(xml, "<age>");
        char number[100];
        sprintf(number, "%d", data[i]->age);
        strcat(xml, number);
        strcat(xml, "</age>");
        strcat(xml, "<occupation>");
        strcat(xml, data[i]->occ);
        strcat(xml, "</occupation>");
        strcat(xml, "</adult>");
    }
    strcat(xml, "</adults>");

    // Write file
    FILE* g = fopen(argv[2], "w");
    fputs(xml, g);

    return 0;
}
