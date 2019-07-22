
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IN_TEXT 1
#define IN_EXERCISE 2
#define IN_BEGIN_EXERCISE 3
#define IN_END_EXERCISE 4
#define IN_SECTION_LINE 5
#define IN_APPENDIX 6
#define IN_BEGIN_DOCUMENT 7
#define IN_END_DOCUMENT 8
#define IN_FANCYHEAD 9
#define IN_USEPACKAGE 10

void write_header() {
  printf("\\documentclass[12pt,twoside,a4paper]{article}\n");
  printf("\\input{../gowiz.tex}\n\n");
}

int main() {

  write_header();
  
  char* line;
  size_t n = 0;
  int state = IN_TEXT;

  while (state != IN_END_DOCUMENT && getline(&line, &n, stdin) > 0) {

    if (strstr(line, "\\section{") == line) {
      if (state != IN_APPENDIX) {
	state = IN_SECTION_LINE;
      }
    }

    if (strstr(line, "\\begin{oefening}") == line) {
      state = IN_BEGIN_EXERCISE;
    }

    if (strstr(line, "\\end{oefening}") == line) {
      state = IN_END_EXERCISE;
    }

    if (strstr(line, "\\appendix") ==  line) {
      state = IN_APPENDIX;
    }

    if (strstr(line, "\\begin{document}") == line) {
      state = IN_BEGIN_DOCUMENT;
    }

    if (strstr(line, "\\end{document}") == line) {
      state = IN_END_DOCUMENT;
    }

    if (strstr(line, "\\fancyhead[RO,LE]{") == line) {
      state = IN_FANCYHEAD;
    }

    if (strstr(line, "\\usepackage") == line) {
      state = IN_USEPACKAGE;
    }

    switch (state) {
    case IN_TEXT:
      break;
    case IN_BEGIN_EXERCISE:
      printf("%s", line);
      state = IN_EXERCISE;
      break;
    case IN_END_EXERCISE:
      printf("%s\n", line);
      state = IN_TEXT;
      break;
    case IN_EXERCISE:
      printf("%s", line);
      break;
    case IN_SECTION_LINE:
      printf("\\pagebreak\n");
      printf("%s\n", line);
      state = IN_TEXT;
      break;
    case IN_APPENDIX:
      printf("%s", line);
      break;
    case IN_BEGIN_DOCUMENT:
      printf("%s", line);
      state = IN_TEXT;
      break;
    case IN_END_DOCUMENT:
      printf("%s", line);
      break;
    case IN_USEPACKAGE:
      printf("%s", line);
      state = IN_TEXT;
      break;
    case IN_FANCYHEAD:
      printf("\\pagestyle{fancy}\n");
      printf("\\fancyhead[RO,LE]{");
      printf("Oefeningen %s", strstr(line, "{") + 1);
      printf("\\fancyhead[RE,LO]{}\n\n");
      state = IN_TEXT;
      break;
    }    

    free(line);
    line = NULL;
    n = 0;
  }
}
