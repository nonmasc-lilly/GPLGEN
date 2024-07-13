/*
*   GPLGEN, a GNU GPL comment/LICENCE file generator 2024
*   Copyright (C) Lilly H. St Claire (main.c)
*
*            This program is free software: you can redistribute it and/or modify
*            it under the terms of the GNU General Public License as published by
*            the Free Software Foundation, either version 3 of the License, or (at
*            your option) any later version.
*
*            This program is distributed in the hope that it will be useful, but
*            WITHOUT ANY WARRANTY; without even the implied warranty of
*            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*            General Public License for more details.
*
*            You should have received a copy of the GNU General Public License
*            along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 1

static void gpl_licence(const char *path);
static void gpl_regular(const char *path, const char *name, const char *author, const char *year, const char *desc,
    bool subname);
static void help();

int main(int argc, char **argv) {
    uint32_t i;
    char *eptr;
    const char *name, *author, *year, *desc;
    bool subname;
    name="__GPLGEN__NONAMEPROVIDED";
    author="__GPLGEN__NOAUTHORPROVIDED";
    year="__GPLGEN__NOYEARPROVIDED";
    desc="";
    if(argc < 2) {
        printf("Error: Usage: %s [OPTIONS] <filename>\n");
        help();
        exit(3);
    }
    for(i=1; i<argc; i++) {
        if(argv[i][0] == '-') switch(argv[i][1]) {
        case 'l':
            l_license: gpl_licence(argv[argc-1]); exit(0); break;
        case 'p':
            l_project: name = argv[++i]; break;
        case 'y':
            l_year: strtol(argv[++i], &eptr, 10);
            if(*eptr) {
                printf("Error: year is not a number\n");
                exit(2);
            }
            year = argv[i]; break;
        case 'a':
            l_author: author = argv[++i]; break;
        case 'd':
            l_description: desc = argv[++i]; break;
        case 's':
            l_subname: subname = true; break;
        case 'h':
            l_help: help(); exit(0);
        case '-':
            if(!strcmp(argv[i]+2, "licence")) goto l_license;
            else if(!strcmp(argv[i]+2, "project")) goto l_project;
            else if(!strcmp(argv[i]+2, "copyyear")) goto l_year;
            else if(!strcmp(argv[i]+2, "author")) goto l_author;
            else if(!strcmp(argv[i]+2, "desc")) goto l_description;
            else if(!strcmp(argv[i]+2, "subname")) goto l_subname;
            else if(!strcmp(argv[i]+2, "help")) goto l_help;
            break;
        }
    }
    gpl_regular(argv[argc-1], name, author, year, desc, subname);
    return 0;
}

static void help() {
    printf("GPLGEN V%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    puts("GPLGEN, a GNU GPL disclaimer/LICENCE file generator Copyright (C) 2024 Lilly H. St Claire");
    puts("This program comes with ABSOLUTELY NO WARRANTY, not even the");
    puts("implied warranty fo MERCHANTABILITY or FITNESS FOR A PARTICULAR");
    puts("PURPOSE.");
    puts("This is free software, and you are welcome to redistribute it");
    puts("under the conditions of the GNU General Public Licence.");
    puts("For more information, see: <https://www.gnu.org/licenses/>");
}

static void gpl_licence(const char *path) {
    FILE *fp;
    fp = fopen(path, "w");
    if(!fp) {
        printf("Error: could not open %s for writing\n", path);
        exit(1);
    }
    fwrite(GPL_LICENCE_STRING, 1, strlen(GPL_LICENCE_STRING), fp);
    fclose(fp);
}

static void gpl_regular(const char *path, const char *name, const char *author, const char *year, const char *desc,
        bool subname) {
    FILE *fp;
    char *snv;
    uint32_t i;
    snv = "";
    fp = fopen(path, "w");
    if(!fp) {
        printf("Error: could not open %s for writing\n", path);
        exit(1);
    }
    if(subname) {
        for(i=strlen(path); i && path[i-1] != '/' && path[i-1] != '\\'; i--);
        snv = malloc(strlen(path+i)+3);
        sprintf(snv, "(%s)", path+i);
    }
    fprintf(fp, GPL_COMMENT_FORMAT_STRING, name, desc, year, author, snv);
    if(subname) free(snv);
    fclose(fp);
}

