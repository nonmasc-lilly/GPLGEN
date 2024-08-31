/*
*   GPLGEN, a GNU GPL comment/LICENCE file generator (main.c)
*   Copyright (C) 2024 Lilly H. St Claire
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
#include "gpl.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 2
#define OPTION_NUM    4


static void gpl_licence(const char *path);
static void gpl_regular(const char *path, const char *name, const char *author, const char *year, const char *desc,
    const char *remark_type, bool subname);
static void help();
static void parse_config(const char *config_path, char **options);
static void write_config(const char *config_path, const char *name, const char *author, const char *year,
    const char *desc);

int main(int argc, char **argv) {
    uint32_t i;
    char *eptr;
    const char *name, *author, *year, *desc, *config_path, *remark_type;
    bool subname, config, dontwrite;
    name="__GPLGEN__NONAMEPROVIDED";
    author="__GPLGEN__NOAUTHORPROVIDED";
    year="__GPLGEN__NOYEARPROVIDED";
    desc="__GPLGEN__NODESCRIPTIONPROVIDED";
    remark_type = "C";
    config_path = "";
    config = false;
    dontwrite = false;
    subname = false;
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
        case 'c':
            l_config: config = true; config_path = argv[++i]; break;
        case 'u':
            l_useconfig: config_path = argv[++i]; break;
        case 'r':
            l_remark: remark_type = argv[++i]; break;
        case '-':
            if(!strcmp(argv[i]+2, "licence")) goto l_license;
            else if(!strcmp(argv[i]+2, "project")) goto l_project;
            else if(!strcmp(argv[i]+2, "copyyear")) goto l_year;
            else if(!strcmp(argv[i]+2, "author")) goto l_author;
            else if(!strcmp(argv[i]+2, "desc")) goto l_description;
            else if(!strcmp(argv[i]+2, "subname")) goto l_subname;
            else if(!strcmp(argv[i]+2, "help")) goto l_help;
            else if(!strcmp(argv[i]+2, "config")) goto l_config;
            else if(!strcmp(argv[i]+2, "useconfig")) goto l_useconfig;
            else if(!strcmp(argv[i]+2, "dontwrite")) dontwrite=true;
            else if(!strcmp(argv[i]+2, "remark")) goto l_remark;
            break;
        }
    }
    if(*config_path && !config && !dontwrite) {
        char *options[OPTION_NUM];
        parse_config(config_path, options);
        gpl_regular(argv[argc-1], options[0], options[1], options[2], options[3], remark_type, subname);
        for(i=0; i<OPTION_NUM; i++) {
            free(options[i]);
        }
    } else {
        if(config)     write_config(config_path, name, author, year, desc);
        if(!dontwrite) gpl_regular(argv[argc-1], name, author, year, desc, remark_type, subname);
    }
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

    puts("\nOPTIONS:");
    puts("\t'-l' or '--licence': generate a licence file and exit");
    puts("\t'-p <name>' or '--project <name>': set the project name to <name>");
    puts("\t'-y <year>' or '--copyyear <year>': set the project copyright year to <year>");
    puts("\t'-a <name>' or '--author <name>': set the author name to <name>");
    puts("\t'-d <desc>' or '--desc <desc>': set the description to <desc>");
    puts("\t'-s' or '--subname': append '(<filename>)' to the description line");
    puts("\t'-c <cfile>' or '--config <cfile>': create a config file (<cfile>) with properties of other passed arguments");
    puts("\t'-u <cfile>' or '--useconfig <cfile>': use a config file (<cfile>) in place of other passed arguments");
    puts("\t'--dontwrite': dont write an output file (will still write licence/config files)");
    puts("\t'-r <type>' or '--remark <type>': sets the language of the remark, types are as follows:");
    puts("\t\tC      : C style comments ('/* */')");
    puts("\t\tC++    : C++ style comments ('//')");
    puts("\t\tPython : Python style comments ('#')");
    puts("\t\tVBasic : Visual Basic style comments (''')");
    puts("\t\tOcaml  : Ocaml style comments ('(* *)')");
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
        const char *remark_type, bool subname) {
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
    for(i=0; i<CM__MAX; i++) {
        if(!strcmp(GPL_COMMENT_TYPE_REP[i],remark_type)) break;
    }
    if(i == CM__MAX) {
        printf("REMARK TYPE ERROR\n");
        exit(1);
    }
    GPLGENFP(fp, i, name, desc, snv, year, author);
    if(subname) free(snv);
    fclose(fp);
}

static void parse_config(const char *config_path, char **options) {
    FILE *fp;
    uint32_t i;
    char c;
    fp = fopen(config_path, "r");
    if(!fp) {
        printf("Error: could not open config file %s for parsing\n", config_path);
        exit(4);
    }
    for(i=0; i<OPTION_NUM; i++) {
        options[i] = calloc(1,1);
        while((c = getc(fp)) != '\n') {
            if(c == EOF) {
                printf("Error: not enough lines for config file %s\n", config_path);
                exit(7);
            }
            options[i] = realloc(options[i], strlen(options[i])+2);
            options[i][strlen(options[i])] = c;
            options[i][strlen(options[i])+1] = 0;
        }
        if(!(*(options[i]))) {
            printf("Error: empty line in config file %s\n", config_path);
            exit(5);
        }
    }
    fclose(fp);
}

static void write_config(const char *config_path, const char *name, const char *author, const char *year,
        const char *desc) {
    FILE *fp;
    fp = fopen(config_path, "w");
    if(!fp) {
        printf("Error: config file %s cannot be opened for writing\n", config_path);
        exit(6);
    }
    fprintf(fp, "%s\n%s\n%s\n%s\n", name, author, year, desc);
    fclose(fp);
}
