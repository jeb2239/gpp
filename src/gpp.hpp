/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if you have the <fnmatch.h> header file. */
#define HAVE_FNMATCH_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `pclose' function. */
#define HAVE_PCLOSE 1

/* Define to 1 if you have the `popen' function. */
#define HAVE_POPEN 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "gpp"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "tristan@logological.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GPP"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GPP 2.26-SNAPSHOT"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gpp"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.26-SNAPSHOT"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "2.26-SNAPSHOT"

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
#ifdef WIN_NT /* WIN NT settings */
#define popen _popen
#define pclose _pclose
#define my_strdup _strdup
#define my_strcasecmp _stricmp
#define SLASH '\\'
#define DEFAULT_CRLF 1
#else /* UNIX settings */
#define SLASH '/'
#define DEFAULT_CRLF 0
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_FNMATCH_H
#include <fnmatch.h>
#endif
#include <time.h>

#define STACKDEPTH 50
#define MAXARGS 100
#define MAXINCL 128 /* max # of include dirs */

#define MAX_GPP_NUM_SIZE 15
#define MAX_GPP_DATE_SIZE 1024

typedef struct MODE {
  char *mStart;      /* before macro name */
  char *mEnd;        /* end macro without arg */
  char *mArgS;       /* start 1st argument */
  char *mArgSep;     /* separate arguments */
  char *mArgE;       /* end last argument */
  char *mArgRef;     /* how to refer to arguments in a def */
  char quotechar;    /* quote next char */
  char *stackchar;   /* characters to stack */
  char *unstackchar; /* characters to unstack */
} MODE;

/* translation for delimiters :
   \001 = \b = ' ' = one or more spaces    \201 = \!b = non-space
   \002 = \w = zero or more spaces
   \003 = \B = one or more spaces or \n    \203 = \!B = non-space nor \n
   \004 = \W = zero or more spaces or \n
   \005 = \a = alphabetic (a-z, A-Z)       \205 = \!a = non-alphabetic
   \006 = \A = alphabetic or space/\n      \206 = \!A
   \007 = \# = numeric (0-9)               \207 = \!#
   \010 = \i = identifier (a-zA-Z0-9_)     \210 = \!i
   \011 = \t, \012 = \n                    \211 = \!t, \212 = \!n
   \013 = \o = operator (+-*\/^<>=`~:.?@#&!%|) \213 = \!o
   \014 = \O = operator or ()[]{}              \214 = \!O
*/
/*                   st        end   args   sep    arge ref  quot  stk  unstk*/
struct MODE CUser = (MODE){"", "", "(", ",", ")", "#", '\\', "(", ")"};
struct MODE CMeta =
    (MODE){"#", "\n", "\001", "\001", "\n", "#", '\\', "(", ")"};
struct MODE KUser = (MODE){"", "", "(", ",", ")", "#", 0, "(", ")"};
struct MODE KMeta =
    (MODE){"\n#\002", "\n", "\001", "\001", "\n", "#", 0, "", ""};
struct MODE Tex = (MODE){"\\", "", "{", "}{", "}", "#", '@', "{", "}"};
struct MODE Html = (MODE){"<#", ">", "\003", "|", ">", "#", '\\', "<", ">"};
struct MODE XHtml = (MODE){"<#", "/>", "\003", "|", "/>", "#", '\\', "<", ">"};

#define DEFAULT_OP_STRING (unsigned char *)"+-*/\\^<>=`~:.?@#&!%|"
#define PROLOG_OP_STRING (unsigned char *)"+-*/\\^<>=`~:.?@#&"
#define DEFAULT_OP_PLUS (unsigned char *)"()[]{}"
#define DEFAULT_ID_STRING                                                      \
  (unsigned char *)"\005\007_" /* or equiv. "A-Za-z0-9_" */

/* here we assume that longs are at least 32 bit... if not, change this ! */
#define LOG_LONG_BITS 5
#define CHARSET_SUBSET_LEN (256 >> LOG_LONG_BITS)
typedef unsigned long *CHARSET_SUBSET;

CHARSET_SUBSET DefaultOp, DefaultExtOp, PrologOp, DefaultId;

typedef struct COMMENT {
  char *start;  /* how the comment/string starts */
  char *end;    /* how it ends */
  char quote;   /* how to prevent it from ending */
  char warn;    /* a character that shouldn't be in there */
  int flags[3]; /* meta, user, text */
  struct COMMENT *next;
} COMMENT;

#define OUTPUT_TEXT 0x1  /* what's inside will be output */
#define OUTPUT_DELIM 0x2 /* the delimiters will be output */
#define PARSE_MACROS 0x4 /* macros inside will be parsed */
#define FLAG_IGNORE 0x40

#define FLAG_STRING (OUTPUT_TEXT | OUTPUT_DELIM)
#define FLAG_COMMENT 0

#define FLAG_META 0
#define FLAG_USER 1
#define FLAG_TEXT 2

/* Some stuff I removed because it made for some impossible situations :

 #define PARSE_COMMENTS  0x8
   comments inside comments will not be parsed because nesting comments is
   too complicated (syntax conflicts, esp. to find a comment's end)
   -- of course, unless the comment is ignored.

 #define MACRO_FRIENDLY  0x20
   a comment-end is to be processed even if an unfinished macro call has
   started inside the comment, otherwise it's too hard do decide in advance
   where a comment ends. In particular foo('bar((((') is valid.

 #define PREVENT_DELIM   0x10
   all comments will prevent macro delimitation, i.e. foo('bar) is invalid.
   -- of course, unless the comment is ignored.
   Too bad, #define foo '...    terminates only at following "'".
   Unless one adds quotechars like in #define foo \' ...

 ALSO NOTE : comments are not allowed before the end of the first argument
 to a meta-macro. E.g. this is legal :   #define foo <* blah *> 3
 This is not legal :                     #define <* blah *> foo 3
 If a comment occurs here, the behavior depends on the actual meta-macro :
 most will yield an error and stop gpp (#define, #undef, #ifdef/ifndef,
 #defeval, #include, #mode) ; #exec, #if and #eval should be ok ;
 #ifeq will always fail while #ifneq will always succeed ;
*/

typedef struct SPECS {
  struct MODE User, Meta;
  struct COMMENT *comments;
  struct SPECS *stack_next;
  int preservelf;
  CHARSET_SUBSET op_set, ext_op_set, id_set;
} SPECS;

struct SPECS *S;

typedef struct MACRO {
  char *username, *macrotext, **argnames;
  int macrolen, nnamedargs;
  struct SPECS *define_specs;
  int defined_in_comment;
} MACRO;

struct MACRO *macros;
int nmacros, nalloced;
char *includedir[MAXINCL];
int nincludedirs;
int execallowed;
int dosmode;
int autoswitch;
/* must be a format-like string that has % % % in it.
 The first % is replaced with line number, the second with "filename", and
 the third with 1, 2 or blank
 Can also use ? instead of %.
 */
char *include_directive_marker = NULL;
short WarningLevel = 2;

/* controls if standard dirs, like /usr/include, are to be searched for
 #include and whether the current dir is to be searched first or last. */
int NoStdInc = 0;
int NoCurIncFirst = 0;
int CurDirIncLast = 0;
int file_and_stdout = 0;
char *IncludeFile = NULL;

typedef struct OUTPUTCONTEXT {
  char *buf;
  int len, bufsize;
  FILE *f;
} OUTPUTCONTEXT;

typedef struct INPUTCONTEXT {
  char *buf;
  char *malloced_buf; /* what was actually malloc-ed (buf may have shifted) */
  int len, bufsize;
  int lineno;
  char *filename;
  FILE *in;
  int argc;
  char **argv;
  char **namedargs;
  struct OUTPUTCONTEXT *out;
  int eof;
  int in_comment;
  int ambience; /* FLAG_TEXT, FLAG_USER or FLAG_META */
  int may_have_args;
} INPUTCONTEXT;

struct INPUTCONTEXT *C;

int commented[STACKDEPTH], iflevel;
/* commented = 0: output, 1: not output,
 2: not output because we're in a #elif and we've already gone through
 the right case (so #else/#elif can't toggle back to output) */

void ProcessContext(void); /* the main loop */

int findIdent(const char *b, int l);
void delete_macro(int i);

/* various recent additions */
void usage(void);
void display_version(void);
void bug(const char *s);
void warning(const char *s);
void getDirname(const char *fname, char *dirname);
FILE *openInCurrentDir(const char *incfile);
char *ArithmEval(int pos1, int pos2);
void replace_definition_with_blank_lines(const char *start, const char *end,
                                         int skip);
void replace_directive_with_blank_line(FILE *file);
void write_include_marker(FILE *f, int lineno, char *filename,
                          const char *marker);
void construct_include_directive_marker(char **include_directive_marker,
                                        const char *includemarker_input);
void escape_backslashes(const char *instr, char **outstr);
void DoInclude(char *file_name);

/*
 ** strdup() and my_strcasecmp() are not ANSI C, so here we define our own
 ** versions in case the compiler does not support them
 */
#if !HAVE_STRDUP
inline char *my_strdup(const char *s);
inline char *my_strdup(const char *s) {
  size_t len = strlen(s) + 1;
  char *newstr = malloc(len);
  return newstr ? (char *)memcpy(newstr, s, len) : NULL;
}
#else
#undef my_strdup
#define my_strdup strdup
#endif
#if !HAVE_STRCASECMP
int my_strcasecmp(const char *s, const char *s2) {
  do {
    char c1 = tolower(*s);
    char c2 = tolower(*s2);
    if (c1 > c2)
      return 1;
    if (c1 < c2)
      return -1;
  } while (*s++ && *s2++);
  return 0;
}
#else
#undef my_strcasecmp
#define my_strcasecmp strcasecmp
#endif

void bug(const char *s) {
  fprintf(stderr, "%s:%d: error: %s\n", C->filename, C->lineno, s);
  exit(EXIT_FAILURE);
}

void warning(const char *s) {
  fprintf(stderr, "%s:%d: warning: %s\n", C->filename, C->lineno, s);
}

struct SPECS *CloneSpecs(const struct SPECS *Q) {
  struct SPECS *P;
  struct COMMENT *x, *y;

  P = (SPECS *)malloc(sizeof *P);
  if (P == NULL)
    bug("Out of memory.");
  memcpy(P, Q, sizeof(struct SPECS));
  P->stack_next = NULL;
  if (Q->comments != NULL)
    P->comments = (COMMENT *)malloc(sizeof *(P->comments));
  for (x = Q->comments, y = P->comments; x != NULL; x = x->next, y = y->next) {
    memcpy(y, x, sizeof(struct COMMENT));
    y->start = my_strdup(x->start);
    y->end = my_strdup(x->end);
    if (x->next != NULL)
      y->next = (COMMENT *)malloc(sizeof *(y->next));
  }
  return P;
}

void FreeComments(struct SPECS *Q) {
  struct COMMENT *p;

  while (Q && Q->comments != NULL) {
    p = Q->comments;
    Q->comments = p->next;
    free(p->start);
    free(p->end);
    free(p);
  }
}

void PushSpecs(const struct SPECS *X) {
  struct SPECS *P;

  P = CloneSpecs(X);
  P->stack_next = S;
  S = P;
}

void PopSpecs(void) {
  struct SPECS *P;

  P = S;
  S = P->stack_next;
  FreeComments(P);
  free(P);
  if (S == NULL)
    bug("#mode restore without #mode save");
}

void display_version(void) {
  fprintf(stderr, PACKAGE_STRING "\n");
  fprintf(stderr, "Copyright (C) 1996-2001 Denis Auroux\n");
  fprintf(stderr, "Copyright (C) 2003-2017 Tristan Miller\n");
  fprintf(stderr, "This is free software; see the source for copying "
                  "conditions.  There is NO\n"
                  "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
                  "PARTICULAR PURPOSE.\n");
}

void usage(void) {
  fprintf(stderr, "Usage : gpp [-{o|O} outfile] [-I/include/path] [-Dname=val "
                  "...] [-z] [-x] [-m]\n");
  fprintf(stderr, "            [-n] [-C | -T | -H | -X | -P | -U ... [-M ...]] "
                  "[+c<n> str1 str2]\n");
  fprintf(stderr,
          "            [+s<n> str1 str2 c] [long options] [infile]\n\n");
  fprintf(stderr, "      default:    #define x y           macro(arg,...)\n");
  fprintf(stderr,
          " -C : maximum cpp compatibility (includes -n, +c, +s, ...)\n");
  fprintf(stderr,
          " -T : TeX-like    \\define{x}{y}         \\macro{arg}{...}\n");
  fprintf(stderr, " -H : HTML-like   <#define x|y>         <#macro arg|...>\n");
  fprintf(stderr,
          " -X : XHTML-like  <#define x|y/>        <#macro arg|.../>\n");
  fprintf(stderr, " -P : prolog compatible cpp-like mode\n");
  fprintf(stderr, " -U : user-defined syntax (specified in 9 following args; "
                  "see manual)\n");
  fprintf(stderr, " -M : user-defined syntax for meta-macros (specified in 7 "
                  "following args)\n\n");
  fprintf(stderr, " -o : output to outfile\n");
  fprintf(stderr, " -O : output to outfile and stdout\n");
  fprintf(stderr, " -z : line terminator is CR-LF (MS-DOS style)\n");
  fprintf(stderr, " -x : enable #exec built-in macro\n");
  fprintf(stderr,
          " -m : enable automatic mode switching upon including .h/.c files\n");
  fprintf(stderr,
          " -n : send LF characters serving as macro terminators to output\n");
  fprintf(stderr,
          " +c : use next 2 args as comment start and comment end sequences\n");
  fprintf(stderr,
          " +s : use next 3 args as string start, end and quote character\n\n");
  fprintf(stderr, " Long options:\n");
  fprintf(stderr, " --include file : process file before infile\n");
  fprintf(
      stderr,
      " --nostdinc : don't search standard directories for files to include\n");
  fprintf(stderr, " --nocurinc : don't search the current directory for files "
                  "to include\n");
  fprintf(stderr, " --curdirinclast : search the current directory last\n");
  fprintf(stderr, " --warninglevel n : set warning level\n");
  fprintf(stderr, " --includemarker formatstring : keep track of #include "
                  "directives in output\n\n");
  fprintf(stderr, " --version : display version information and exit\n");
  fprintf(stderr, " -h, --help : display this message and exit\n\n");
}

void write_include_marker(FILE *f, int lineno, char *filename,
                          const char *marker);

void DoInclude(char *file_name);
void ProcessContext(void);
int gpp_main(int argc, char **argv);