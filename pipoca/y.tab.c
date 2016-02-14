#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20090221

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
#ifdef YYPARSE_PARAM_TYPE
#define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
#else
#define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
#endif
#else
#define YYPARSE_DECL() yyparse(void)
#endif /* YYPARSE_PARAM */

extern int YYPARSE_DECL();

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "pipoca.y"
#include <stdio.h>
#include "lib/node.h"
int yylineno;
int floatfound = 0;
#line 10 "pipoca.y"
typedef union {char *s; double real,exp; int i; Node *n;} YYSTYPE;
#line 41 "y.tab.c"
#define NOT 257
#define AND 258
#define OR 259
#define IF 260
#define THEN 261
#define ELSE 262
#define ENDIF 263
#define WHILE 264
#define DO 265
#define DONE 266
#define UNTIL 267
#define BREAK 268
#define CONTINUE 269
#define GOTO 270
#define REAL 271
#define INTEGER 272
#define CONST 273
#define VAR 274
#define INIT 275
#define EXTERN 276
#define END 277
#define MOREOREQUAL 278
#define LESSOREQUAL 279
#define NOTEQUAL 280
#define OPATR 281
#define PLUSONE 282
#define MINUSONE 283
#define PRINTLN 284
#define POT 285
#define STARTBLOCK 286
#define ENDBLOCK 287
#define NEWLINE 288
#define ENDENDBLOCK 289
#define ID 290
#define STRING 291
#define REALN 292
#define EXP 293
#define INT 294
#define INIT2 295
#define INIT3 296
#define EXTERN2 297
#define MULTIIDS 298
#define CONST2 299
#define FUNC 300
#define UNALLOCVECTOR 301
#define FUNC2 302
#define IDVEC 303
#define IDVECINT 304
#define IDVECID 305
#define EXPP 306
#define FUNCCALL 307
#define IDVECA 308
#define PLUSONEA 309
#define MINUSONEA 310
#define MEMRESERV 311
#define MEMRESERVP 312
#define SSM 313
#define LISTEXP 314
#define LISTEXP2 315
#define LISTEXP3 316
#define LISTEXP4 317
#define DECL 318
#define INITN 319
#define CONSTN 320
#define DEC 321
#define INTS 322
#define EXP4 323
#define PRINT 324
#define PRINTP 325
#define PRINTM 326
#define PRINTSM 327
#define PRINTINT 328
#define PRINTID 329
#define PRINTSTRING 330
#define PRINTFUNCCALL 331
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    2,    3,    4,    5,
    5,    5,    5,    6,    7,    7,    8,    8,    9,    9,
    9,   10,   10,   10,   11,   11,   11,   11,   11,   12,
   12,   12,   12,   13,   13,   13,   14,   14,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   16,   16,   16,   16,   17,   17,   18,   18,   18,   19,
   19,   19,   19,   19,   19,   19,   19,   20,   20,   20,
   23,   23,   21,   21,   24,   22,   25,   26,   26,   26,
   26,   26,   27,   27,   28,   28,   28,   28,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   28,   28,
   28,   28,   28,   29,   30,   30,   30,   30,   30,   30,
   30,   30,   30,   30,   30,   30,   31,   32,   32,   32,
   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
   32,   33,   33,   34,   35,   35,   36,   36,   36,   36,
   36,   36,   36,   37,   37,   37,   37,   38,   38,
};
static const short yylen[] = {                            2,
    1,    0,    2,    1,    1,    1,    1,    5,    3,    1,
    2,    3,    4,    3,    1,    3,    3,    5,    1,    1,
    1,   10,   10,    9,    0,    1,    3,    5,    3,    1,
    3,    5,    3,    0,    1,    3,    1,    3,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    2,    2,    2,
    2,    2,    3,    3,    4,    3,    0,    1,    1,    1,
    3,    4,    4,    3,    5,    6,    6,    8,    8,    8,
    6,    1,    6,    1,    2,    2,    2,    1,    5,    3,
    5,    3,    1,    3,    1,    1,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    6,    6,    2,    3,    1,    2,    4,    4,    2,    2,
    2,    2,    1,    2,    2,    2,    6,    1,    1,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    1,    1,    3,    3,    3,    1,    3,    6,    3,
    3,    3,    5,    1,    1,    3,    3,    1,    1,
};
static const short yydefred[] = {                         2,
    0,    0,    0,    0,    0,    0,    7,    0,    3,    4,
    5,    6,    0,    0,    0,   15,    0,    0,    0,    0,
    0,   14,    0,    0,    0,    0,    0,  159,  158,    0,
    0,    0,    0,    0,    0,    0,   85,   86,  123,    0,
    0,    0,    0,   16,  124,  119,  120,  121,  122,    0,
    0,  125,  126,    0,    0,    0,  116,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  113,    0,    0,    0,    0,   10,    8,
  143,    0,    0,    0,  129,  128,  142,    0,    0,    0,
    0,    0,    0,  114,    0,    0,    0,    0,    0,    0,
    0,  106,  105,  108,  107,  110,  109,   98,   97,   88,
   87,   90,   89,   92,   91,   94,   93,   96,   95,  100,
   99,  102,  101,  104,  103,    0,    0,   11,    9,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  117,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   12,
  144,  140,  141,    0,  136,  137,  134,  135,  130,  131,
  132,  133,  138,  139,    0,   79,   81,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   44,   39,
   40,   41,    0,    0,   42,   43,    0,    0,    0,    0,
    0,   13,  112,  111,    0,    0,    0,   51,    0,   52,
    0,    0,    0,   58,   59,    0,    0,    0,    0,    0,
   50,   45,   46,   47,   48,   49,   77,    0,    0,    0,
  118,    0,    0,    0,    0,    0,   53,   54,    0,    0,
   56,    0,    0,   84,  154,    0,  155,    0,   24,  146,
    0,    0,  151,  145,   22,   23,    0,    0,    0,   20,
   19,   17,   21,    0,    0,   55,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   61,    0,  156,
  157,    0,    0,    0,    0,    0,    0,   18,   63,   62,
    0,  127,  149,    0,    0,    0,    0,    0,   65,    0,
    0,   68,   74,    0,    0,   69,   72,   70,   67,   66,
    0,   76,    0,   75,    0,    0,    0,    0,    0,    0,
   73,   71,
};
static const short yydgoto[] = {                          1,
    2,    9,   10,  251,   78,   11,   17,  203,  252,   12,
   33,   34,   88,   89,  178,  179,  180,  206,  233,  181,
  292,  293,  296,  297,  182,  183,  184,   36,   37,   38,
  185,   84,   85,   86,  186,  187,  236,   39,
};
static const short yysindex[] = {                         0,
    0, -100, -276, -271, -259, -234,    0,   33,    0,    0,
    0,    0,   45,   50, -213,    0,  -40,  141,  141,  141,
    9,    0, -229, -184, -179, -166,   75,    0,    0, -256,
  179, -160,   95,  100, -142,  723,    0,    0,    0,   99,
  105,   21, -140,    0,    0,    0,    0,    0,    0,  -30,
  179,    0,    0,   79,  -98,  678,    0, -132,  272,  295,
  295,  308,  308,  308,  308,  308,  308,  308,  308,  308,
  308,  308,  308,    0, -126, -123, -198,  -26,    0,    0,
    0,    0,   94,   60,    0,    0,    0,  128,  130, -142,
   94,  295,  295,    0,  -87,  107,  295,  723,  723,  723,
  123,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -80,  -69,    0,    0,   24,
   67,   94,  -99,   94,   94,   94,   94,   94,    0,  295,
  687,  714,  259,  -12,  678,   94,  259,  259, -198,    0,
    0,    0,    0,  308,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  723,    0,    0,  179,  179,  -76,
 -277, -265,  -61,  -94,  127,  193,  -49,  -37,    0,    0,
    0,    0, -142,  -67,    0,    0,  -28,    0,   96,    1,
   37,    0,    0,    0, -208, -210,  -42,    0,  -41,    0,
  -16,   -4,   -9,    0,    0,  -39,  331, -199,  188,   -3,
    0,    0,    0,    0,    0,    0,    0,    8, -220,   10,
    0,   19,   44,   46,   51,  259,    0,    0,  -84,  -61,
    0,  198,  -38,    0,    0,  267,    0,  260,    0,    0,
  303,  302,    0,    0,    0,    0,   63,   65,   73,    0,
    0,    0,    0,  310,  -81,    0,   78, -163,   94,  179,
 -199,  259,  259,  103,  -84,  282,  286,    0,  289,    0,
    0,   15,  344,  267,  109,  147,  179,    0,    0,    0,
  -68,    0,    0,  -83, -182, -183,  294,  300,    0,  106,
  114,    0,    0,  125,  129,    0,    0,    0,    0,    0,
  132,    0,  133,    0,  259,  259,  185,  223,  134,  156,
    0,    0,
};
static const short yyrindex[] = {                         0,
    0,  425,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  387,  387,  387,
    0,    0,    0,    0,    0,    0,  642,    0,    0,    0,
    0,    0,    0,    0,  -20,  529,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  391,    0,    0,  575,    0,  -55,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   -2,    0,    0,    0,    0,    0,    0,    0,   82,
    0,    0,    0,    0,    0,  651,    0,   91,  538,  562,
  575,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  603,    0,    0,    0,    0,    0,    0,    0,
  -25,  -19,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  101,    0,    0,    0,    0,    0,
    0,    0,    0, -160,  614,  -17,    0,    0,    0,    0,
    0,    0,  152,    0,    0,    0,    0,  111,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   20,    0,    0,    0,  -13,    0,    0,    0,    0,
  -11,    2,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  391,
    0,    0,    0,    0,    0,    0,    0,    0,   34,    0,
    0,    0,    0,    4,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
    0,    0,    0,  422,    0,    0,    0,  214,  181,    0,
  305,    0,  187,    0, -104,  -92,  236,    0,    0,  393,
    0,  139,  165,  142,  602,  -18,  248,   28,  981,  993,
  640,  -74,   59,  366,  706,    0,  195,  893,
};
#define YYTABLESIZE 1158
static const short yytable[] = {                         35,
   35,   35,   31,   23,  220,  257,   42,   30,  131,   83,
  198,  268,   55,   13,  219,  147,  199,  130,   14,  152,
   26,  148,  200,   30,  289,  147,   32,   83,  201,  152,
   15,  148,   90,   52,  150,   28,  153,   29,   27,  230,
   31,   31,  190,  191,  150,   30,  153,   60,   61,   60,
   61,  138,  224,  177,  225,   16,  136,  135,   56,  134,
   44,  137,   82,   60,   32,   77,  129,   21,  149,  241,
  242,  189,   18,  243,   60,   61,   31,   64,  294,  294,
  188,   30,  295,  295,   19,  211,   98,   99,  100,   20,
  235,  177,   28,   28,   29,   29,  138,  211,  211,   42,
   32,  136,  135,  138,  134,   45,  137,  151,  136,  135,
   46,  134,   31,  137,   51,   60,   61,   30,   51,  141,
  142,  249,   35,   47,  145,   37,  270,  177,   28,   57,
   29,   29,  138,   83,   33,   58,   32,  136,  135,   75,
  134,   36,  137,   59,   38,   76,   51,   80,   31,  195,
  196,   28,  133,   30,   32,   95,  211,  275,  276,   92,
   93,  126,   51,  177,  127,   50,   51,  165,  139,   91,
    3,    4,   32,  140,    5,    6,  204,  205,  290,  291,
   31,  154,  211,  211,  272,   30,   31,    7,  221,    8,
  152,   30,  155,  157,  159,  161,  163,  144,  143,  177,
  307,  308,   78,   78,   32,  147,  250,   28,  266,   29,
   32,  197,  267,  146,  211,  211,  148,   91,   31,   24,
  217,  287,  168,   30,   31,  288,  169,  170,  202,   30,
  171,  172,   80,   80,  208,  173,  174,  177,   82,   82,
  209,   90,   32,  226,   25,   26,  227,   22,   32,  256,
  232,  210,  175,  176,   28,  218,   29,   24,  286,   81,
  168,   28,   31,   29,  169,  170,  147,   30,  171,  172,
  152,  228,  148,  173,  174,  177,  229,   81,  231,   28,
  238,   29,   25,   26,  239,  150,   32,  153,  255,  222,
  175,  176,   28,   24,   29,  240,  168,  244,   31,  132,
  169,  170,  282,   30,  171,  172,  245,   60,  258,  173,
  174,   97,   28,  177,   29,   28,   30,   29,   25,   26,
  259,   64,   32,   40,   41,  223,  175,  176,   28,   24,
   29,  246,  168,  247,   97,   32,  169,  170,  248,   30,
  171,  172,  260,  261,  132,  173,  174,   97,  262,  177,
  263,  132,   30,  265,   25,   26,   48,   49,   32,  264,
   48,   49,  175,  176,   28,   24,   29,  269,  168,  277,
   31,   32,  169,  170,  279,   30,  171,  172,  280,  281,
  132,  173,  174,   81,  283,   28,  299,   29,   48,   49,
   25,   26,  300,  301,   32,  284,  291,   24,  175,  176,
   28,  302,   29,   24,   48,   49,  168,  207,   48,   49,
  169,  170,  303,  212,  171,  172,  304,  305,  306,  173,
  174,  295,   25,   26,    1,  212,  212,   25,   25,   26,
   27,   34,   28,  285,   29,   24,  175,  176,   28,   83,
   29,   24,   43,  254,  168,  278,  273,  311,  169,  170,
  298,  312,  171,  172,  234,  274,    0,  173,  174,    0,
   25,   26,    0,    0,    0,    0,   25,   26,   54,    0,
   28,  309,   29,    0,  175,  176,   28,    0,   29,   24,
    0,    0,  168,    0,  212,    0,  169,  170,    0,    0,
  171,  172,    0,    0,    0,  173,  174,  153,    0,  156,
  158,  160,  162,  164,   25,   26,    0,    0,    0,  310,
  212,  212,  175,  176,   28,   24,   29,    0,  168,    0,
    0,    0,  169,  170,    0,    0,  171,  172,   24,    0,
    0,  173,  174,    0,    0,    0,    0,    0,    0,    0,
   25,   26,  212,  212,    0,    0,    0,    0,  175,  176,
   28,   24,   29,   25,   26,    0,    0,    0,    0,    0,
    0,   96,    0,   28,   24,   29,    0,    0,    0,   78,
  213,    0,   78,    0,    0,    0,   25,   26,   80,    0,
    0,   80,  213,  213,   54,    0,   28,   24,   29,   25,
   26,    0,    0,    0,    0,    0,    0,  101,    0,   28,
    0,   29,   82,    0,    0,   82,    0,    0,    0,    0,
    0,  115,   25,   26,    0,  115,  115,  115,  115,  115,
  175,  115,   28,    0,   29,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  115,  115,  115,  115,    0,  118,
    0,  213,    0,  118,  118,  118,  118,  118,    0,  118,
  115,    0,    0,    0,    0,  115,  115,    0,  115,    0,
  115,    0,  118,  118,  118,  118,    0,  213,  213,    0,
    0,    0,    0,  115,  115,  115,  115,    0,  115,    0,
    0,    0,  115,  115,  115,  115,  115,  115,  115,    0,
    0,  115,  115,  115,  115,  115,    0,  115,    0,  213,
  213,  115,  115,  115,  115,    0,    0,    0,    0,    0,
  115,  115,  115,  115,   70,    0,    0,    0,   94,   68,
   67,    0,   66,   70,   69,    0,    0,  166,   68,   67,
    0,   66,    0,   69,    0,    0,    0,   71,   73,   72,
   74,    0,    0,    0,    0,    0,   71,   73,   72,   74,
   70,    0,    0,    0,  167,   68,   67,    0,   66,   70,
   69,    0,    0,    0,   68,   67,    0,   66,    0,   69,
    0,    0,    0,   71,   73,   72,   74,    0,    0,  214,
    0,    0,   71,   73,   72,   74,   78,   78,    0,   78,
   78,  214,  214,   78,   78,   80,   80,    0,   80,   80,
    0,    0,   80,   80,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   78,  215,    0,   82,
   82,    0,   82,   82,    0,   80,   82,   82,    0,  215,
  215,    0,  115,  115,    0,  115,  115,    0,    0,  115,
  115,    0,    0,    0,    0,    0,    0,    0,    0,   82,
  214,    0,  115,  115,  115,    0,    0,    0,    0,  115,
  118,  118,  115,  118,  118,    0,    0,  118,  118,    0,
    0,  115,  115,    0,    0,    0,  214,  214,    0,    0,
  118,  118,  118,  216,    0,    0,    0,  118,  215,    0,
  118,  115,  115,  115,    0,  216,  216,    0,  115,  115,
  115,  115,    0,    0,    0,    0,    0,    0,  214,  214,
    0,    0,    0,    0,  215,  215,    0,    0,    0,  115,
  115,  115,   53,    0,    0,    0,  115,    0,  115,  115,
  115,    0,    0,    0,   79,  115,    0,    0,    0,    0,
    0,    0,   87,    0,    0,    0,  215,  215,    0,    0,
    0,    0,    0,    0,  216,   62,   63,   64,    0,    0,
    0,    0,   65,    0,   62,   63,   64,    0,    0,  128,
    0,   65,    0,    0,    0,   87,    0,    0,    0,    0,
  216,  216,    0,   87,    0,    0,    0,    0,    0,    0,
    0,   62,   63,   64,    0,    0,    0,    0,   65,    0,
   62,   63,   64,    0,    0,    0,    0,   65,    0,    0,
    0,    0,  216,  216,    0,    0,    0,    0,    0,    0,
    0,    0,  150,    0,   87,    0,   87,   87,   87,   87,
   87,    0,    0,    0,    0,    0,   87,    0,   87,    0,
    0,  192,  102,  104,  106,  108,  110,  112,  114,  116,
  118,  120,  122,  124,  103,  105,  107,  109,  111,  113,
  115,  117,  119,  121,  123,  125,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  237,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  253,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  193,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  194,    0,    0,    0,
  271,   87,    0,  237,    0,    0,    0,  253,
};
static const short yycheck[] = {                         18,
   19,   20,   40,   44,   33,   44,   91,   45,   83,   40,
  288,   93,   31,  290,   43,   33,  294,   44,  290,   33,
   41,   33,  288,   44,   93,   43,   64,   40,  294,   43,
  290,   43,   51,  290,   33,  292,   33,  294,   41,   44,
   40,   44,  147,  148,   43,   45,   43,  258,  259,  258,
  259,   37,  261,   91,  265,  290,   42,   43,   31,   45,
  290,   47,   93,   44,   64,   45,   93,  281,   45,  290,
  291,  146,   40,  294,  258,  259,   40,   44,  262,  262,
   93,   45,  266,  266,   40,  178,   59,   60,   61,   40,
  290,   91,  292,  292,  294,  294,   37,  190,  191,   91,
   64,   42,   43,   37,   45,  290,   47,   41,   42,   43,
  290,   45,   40,   47,   40,  258,  259,   45,   40,   92,
   93,  226,   41,  290,   97,   44,  290,   91,  292,  290,
  294,   41,   37,   40,   44,   41,   64,   42,   43,   41,
   45,   41,   47,   44,   44,   41,   40,  288,   40,  168,
  169,   41,   93,   45,   44,  288,  249,  262,  263,  258,
  259,  288,   40,   91,  288,   91,   40,  140,   41,   91,
  271,  272,   64,   44,  275,  276,  271,  272,  262,  263,
   40,  281,  275,  276,  259,   45,   40,  288,   93,  290,
  132,   45,  134,  135,  136,  137,  138,   91,  286,   91,
  305,  306,  258,  259,   64,  286,  291,  292,  290,  294,
   64,  288,  294,   91,  307,  308,  286,   91,   40,  257,
  288,  290,  260,   45,   40,  294,  264,  265,  290,   45,
  268,  269,  258,  259,   42,  273,  274,   91,  258,  259,
  290,  260,   64,  286,  282,  283,  288,  288,   64,  288,
  290,  289,  290,  291,  292,  284,  294,  257,  277,  290,
  260,  292,   40,  294,  264,  265,  284,   45,  268,  269,
  284,  288,  284,  273,  274,   91,  281,  290,  288,  292,
   93,  294,  282,  283,  288,  284,   64,  284,   91,  289,
  290,  291,  292,  257,  294,  288,  260,  288,   40,  285,
  264,  265,  288,   45,  268,  269,  288,  288,   42,  273,
  274,   40,  292,   91,  294,  292,   45,  294,  282,  283,
   61,  288,   64,   19,   20,  289,  290,  291,  292,  257,
  294,  288,  260,  288,   40,   64,  264,  265,  288,   45,
  268,  269,   40,   42,  285,  273,  274,   40,  286,   91,
  286,  285,   45,   44,  282,  283,  282,  283,   64,  287,
  282,  283,  290,  291,  292,  257,  294,  290,  260,  267,
   40,   64,  264,  265,   93,   45,  268,  269,   93,   91,
  285,  273,  274,  290,   41,  292,   93,  294,  282,  283,
  282,  283,   93,  288,   64,  287,  263,  257,  290,  291,
  292,  288,  294,  257,  282,  283,  260,  281,  282,  283,
  264,  265,  288,  178,  268,  269,  288,  286,  286,  273,
  274,  266,  282,  283,    0,  190,  191,   41,  282,  283,
  290,   41,  292,  287,  294,  257,  290,  291,  292,  288,
  294,  257,   21,  230,  260,  265,  260,  309,  264,  265,
  286,  310,  268,  269,  207,  261,   -1,  273,  274,   -1,
  282,  283,   -1,   -1,   -1,   -1,  282,  283,  290,   -1,
  292,  287,  294,   -1,  290,  291,  292,   -1,  294,  257,
   -1,   -1,  260,   -1,  249,   -1,  264,  265,   -1,   -1,
  268,  269,   -1,   -1,   -1,  273,  274,  132,   -1,  134,
  135,  136,  137,  138,  282,  283,   -1,   -1,   -1,  287,
  275,  276,  290,  291,  292,  257,  294,   -1,  260,   -1,
   -1,   -1,  264,  265,   -1,   -1,  268,  269,  257,   -1,
   -1,  273,  274,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  282,  283,  307,  308,   -1,   -1,   -1,   -1,  290,  291,
  292,  257,  294,  282,  283,   -1,   -1,   -1,   -1,   -1,
   -1,  290,   -1,  292,  257,  294,   -1,   -1,   -1,   41,
  178,   -1,   44,   -1,   -1,   -1,  282,  283,   41,   -1,
   -1,   44,  190,  191,  290,   -1,  292,  257,  294,  282,
  283,   -1,   -1,   -1,   -1,   -1,   -1,  290,   -1,  292,
   -1,  294,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,   37,  282,  283,   -1,   41,   42,   43,   44,   45,
  290,   47,  292,   -1,  294,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   60,   61,   62,   63,   -1,   37,
   -1,  249,   -1,   41,   42,   43,   44,   45,   -1,   47,
   37,   -1,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,
   47,   -1,   60,   61,   62,   63,   -1,  275,  276,   -1,
   -1,   -1,   -1,   60,   61,   62,   63,   -1,   37,   -1,
   -1,   -1,   41,   42,   43,   44,   45,   37,   47,   -1,
   -1,   41,   42,   43,   44,   45,   -1,   47,   -1,  307,
  308,   60,   61,   62,   63,   -1,   -1,   -1,   -1,   -1,
   60,   61,   62,   63,   37,   -1,   -1,   -1,   41,   42,
   43,   -1,   45,   37,   47,   -1,   -1,   41,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,   60,   61,   62,
   63,   -1,   -1,   -1,   -1,   -1,   60,   61,   62,   63,
   37,   -1,   -1,   -1,   41,   42,   43,   -1,   45,   37,
   47,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   60,   61,   62,   63,   -1,   -1,  178,
   -1,   -1,   60,   61,   62,   63,  258,  259,   -1,  261,
  262,  190,  191,  265,  266,  258,  259,   -1,  261,  262,
   -1,   -1,  265,  266,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  288,  178,   -1,  258,
  259,   -1,  261,  262,   -1,  288,  265,  266,   -1,  190,
  191,   -1,  258,  259,   -1,  261,  262,   -1,   -1,  265,
  266,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  288,
  249,   -1,  278,  279,  280,   -1,   -1,   -1,   -1,  285,
  258,  259,  288,  261,  262,   -1,   -1,  265,  266,   -1,
   -1,  258,  259,   -1,   -1,   -1,  275,  276,   -1,   -1,
  278,  279,  280,  178,   -1,   -1,   -1,  285,  249,   -1,
  288,  278,  279,  280,   -1,  190,  191,   -1,  285,  258,
  259,  288,   -1,   -1,   -1,   -1,   -1,   -1,  307,  308,
   -1,   -1,   -1,   -1,  275,  276,   -1,   -1,   -1,  278,
  279,  280,   30,   -1,   -1,   -1,  285,   -1,  278,  279,
  280,   -1,   -1,   -1,   42,  285,   -1,   -1,   -1,   -1,
   -1,   -1,   50,   -1,   -1,   -1,  307,  308,   -1,   -1,
   -1,   -1,   -1,   -1,  249,  278,  279,  280,   -1,   -1,
   -1,   -1,  285,   -1,  278,  279,  280,   -1,   -1,   77,
   -1,  285,   -1,   -1,   -1,   83,   -1,   -1,   -1,   -1,
  275,  276,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  278,  279,  280,   -1,   -1,   -1,   -1,  285,   -1,
  278,  279,  280,   -1,   -1,   -1,   -1,  285,   -1,   -1,
   -1,   -1,  307,  308,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  130,   -1,  132,   -1,  134,  135,  136,  137,
  138,   -1,   -1,   -1,   -1,   -1,  144,   -1,  146,   -1,
   -1,  149,   62,   63,   64,   65,   66,   67,   68,   69,
   70,   71,   72,   73,   62,   63,   64,   65,   66,   67,
   68,   69,   70,   71,   72,   73,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  208,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  229,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  154,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  154,   -1,   -1,   -1,
  258,  259,   -1,  261,   -1,   -1,   -1,  265,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 331
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,0,0,"'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NOT","AND","OR","IF","THEN","ELSE","ENDIF",
"WHILE","DO","DONE","UNTIL","BREAK","CONTINUE","GOTO","REAL","INTEGER","CONST",
"VAR","INIT","EXTERN","END","MOREOREQUAL","LESSOREQUAL","NOTEQUAL","OPATR",
"PLUSONE","MINUSONE","PRINTLN","POT","STARTBLOCK","ENDBLOCK","NEWLINE",
"ENDENDBLOCK","ID","STRING","REALN","EXP","INT","INIT2","INIT3","EXTERN2",
"MULTIIDS","CONST2","FUNC","UNALLOCVECTOR","FUNC2","IDVEC","IDVECINT","IDVECID",
"EXPP","FUNCCALL","IDVECA","PLUSONEA","MINUSONEA","MEMRESERV","MEMRESERVP",
"SSM","LISTEXP","LISTEXP2","LISTEXP3","LISTEXP4","DECL","INITN","CONSTN","DEC",
"INTS","EXP4","PRINT","PRINTP","PRINTM","PRINTSM","PRINTINT","PRINTID",
"PRINTSTRING","PRINTFUNCCALL",
};
static const char *yyrule[] = {
"$accept : pipoca",
"pipoca : file",
"file :",
"file : file decl",
"decl : init",
"decl : extern",
"decl : func",
"decl : NEWLINE",
"init : INIT ID OPATR init2 NEWLINE",
"init2 : '[' init3 ']'",
"init3 : intorreal",
"init3 : '-' intorreal",
"init3 : init3 ',' intorreal",
"init3 : init3 ',' '-' intorreal",
"extern : EXTERN extern2 NEWLINE",
"extern2 : ID",
"extern2 : extern2 ',' ID",
"const2 : ID OPATR const",
"const2 : ID ',' const2 ',' const",
"const : init2",
"const : STRING",
"const : intorreal",
"func : REAL ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE",
"func : INTEGER ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE",
"func : ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE",
"listexp3 :",
"listexp3 : exp5",
"listexp3 : ID '[' ']'",
"listexp3 : listexp4 ',' ID '[' ']'",
"listexp3 : listexp4 ',' exp",
"listexp4 : exp5",
"listexp4 : ID '[' ']'",
"listexp4 : listexp4 ',' ID '[' ']'",
"listexp4 : listexp4 ',' exp",
"listexp :",
"listexp : exp5",
"listexp : listexp2 ',' exp",
"listexp2 : exp5",
"listexp2 : listexp2 ',' exp",
"func2 : dec",
"func2 : ints",
"func2 : exp4",
"func2 : memreserv",
"func2 : print",
"func2 : breakcontinue",
"func2 : func2 dec",
"func2 : func2 ints",
"func2 : func2 exp4",
"func2 : func2 memreserv",
"func2 : func2 print",
"func2 : func2 breakcontinue",
"breakcontinue : BREAK NEWLINE",
"breakcontinue : CONTINUE NEWLINE",
"breakcontinue : BREAK INT NEWLINE",
"breakcontinue : CONTINUE INT NEWLINE",
"dec : VAR type var NEWLINE",
"dec : CONST const2 NEWLINE",
"type :",
"type : REAL",
"type : INTEGER",
"var : ID",
"var : ID '[' ']'",
"var : ID '[' INT ']'",
"var : ID '[' ID ']'",
"var : var ',' ID",
"var : var ',' ID '[' ']'",
"var : var ',' ID '[' INT ']'",
"var : var ',' ID '[' ID ']'",
"ints : IF exp5 THEN NEWLINE STARTBLOCK func2 ENDBLOCK elseif",
"ints : WHILE exp5 DO NEWLINE STARTBLOCK func2 ENDBLOCK elsecycle",
"ints : DO NEWLINE STARTBLOCK func2 ENDBLOCK UNTIL exp5 elsecycle",
"elsecycle : ELSE NEWLINE STARTBLOCK func2 ENDBLOCK endelsecycle",
"elsecycle : endelsecycle",
"elseif : ELSE NEWLINE STARTBLOCK func2 ENDBLOCK endelseif",
"elseif : endelseif",
"endelsecycle : DONE NEWLINE",
"endelseif : ENDIF NEWLINE",
"exp4 : exp6 NEWLINE",
"exp5 : exp",
"exp5 : '(' exp5 AND exp ')'",
"exp5 : exp5 AND exp",
"exp5 : '(' exp5 OR exp ')'",
"exp5 : exp5 OR exp",
"exp6 : exp5",
"exp6 : ID OPATR exp6",
"exp : exp2",
"exp : exp3",
"exp : exp '-' exp3",
"exp : exp '-' exp2",
"exp : exp '+' exp3",
"exp : exp '+' exp2",
"exp : exp '*' exp3",
"exp : exp '*' exp2",
"exp : exp '/' exp3",
"exp : exp '/' exp2",
"exp : exp '%' exp3",
"exp : exp '%' exp2",
"exp : exp POT exp3",
"exp : exp POT exp2",
"exp : exp '<' exp3",
"exp : exp '<' exp2",
"exp : exp '>' exp3",
"exp : exp '>' exp2",
"exp : exp '=' exp3",
"exp : exp '=' exp2",
"exp : exp MOREOREQUAL exp3",
"exp : exp MOREOREQUAL exp2",
"exp : exp LESSOREQUAL exp3",
"exp : exp LESSOREQUAL exp2",
"exp : exp NOTEQUAL exp3",
"exp : exp NOTEQUAL exp2",
"exp : ID '[' memreserv2 ']' OPATR exp3",
"exp : ID '[' memreserv2 ']' OPATR exp2",
"exp : exp '?'",
"exp2 : '(' exp ')'",
"exp3 : ID",
"exp3 : '@' ID",
"exp3 : ID '(' listexp ')'",
"exp3 : ID '[' memreserv2 ']'",
"exp3 : PLUSONE ID",
"exp3 : MINUSONE ID",
"exp3 : ID PLUSONE",
"exp3 : ID MINUSONE",
"exp3 : intorreal",
"exp3 : NOT ID",
"exp3 : '-' ID",
"exp3 : '-' intorreal",
"memreserv : '[' ID ']' '=' memreserv2 NEWLINE",
"memreserv2 : memreserv4",
"memreserv2 : memreserv3",
"memreserv2 : memreserv2 '*' memreserv3",
"memreserv2 : memreserv2 '*' memreserv4",
"memreserv2 : memreserv2 '/' memreserv3",
"memreserv2 : memreserv2 '/' memreserv4",
"memreserv2 : memreserv2 '+' memreserv3",
"memreserv2 : memreserv2 '+' memreserv4",
"memreserv2 : memreserv2 '-' memreserv3",
"memreserv2 : memreserv2 '-' memreserv4",
"memreserv2 : memreserv2 '%' memreserv3",
"memreserv2 : memreserv2 '%' memreserv4",
"memreserv2 : memreserv2 POT memreserv3",
"memreserv2 : memreserv2 POT memreserv4",
"memreserv3 : intorreal",
"memreserv3 : ID",
"memreserv4 : '(' memreserv2 ')'",
"print : print2 '!' NEWLINE",
"print : print2 PRINTLN NEWLINE",
"print2 : STRING",
"print2 : print2 '+' ID",
"print2 : print2 '+' ID '(' listexp ')'",
"print2 : print2 '+' STRING",
"print2 : print2 '+' INT",
"print2 : STRING '*' print3",
"print2 : print2 '+' STRING '*' print3",
"print3 : ID",
"print3 : intorreal",
"print3 : print3 '*' ID",
"print3 : print3 '*' intorreal",
"intorreal : INT",
"intorreal : REALN",

};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static unsigned yystacksize;
#line 258 "pipoca.y"
yywrap() {

  return 1;

}
char **yynames = (char**)yyname;
#line 735 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    yystate = 0;
    *yyssp = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yyssp = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yyssp = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 22 "pipoca.y"
	{evaluate(yyvsp[0].n); freeNode(yyvsp[0].n);}
break;
case 2:
#line 25 "pipoca.y"
	{yyval.n = subNode(DECL,0);}
break;
case 3:
#line 26 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1); }
break;
case 4:
#line 28 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 5:
#line 29 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 6:
#line 30 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 7:
#line 31 "pipoca.y"
	{yyval.n = 0;}
break;
case 8:
#line 33 "pipoca.y"
	{yyval.n = subNode(INIT, 2, strNode(ID, yyvsp[-3].s), yyvsp[-1].n);}
break;
case 9:
#line 36 "pipoca.y"
	{yyval.n = yyvsp[-1].n;}
break;
case 10:
#line 39 "pipoca.y"
	{yyval.n = subNode(INITN, 1, yyvsp[0].n);}
break;
case 11:
#line 40 "pipoca.y"
	{yyval.n = subNode(INITN, 1, subNode('-', 1, yyvsp[0].n));}
break;
case 12:
#line 41 "pipoca.y"
	{yyval.n = addNode(yyvsp[-2].n, yyvsp[0].n, yyvsp[-2].n->value.sub.num);}
break;
case 13:
#line 42 "pipoca.y"
	{yyval.n = addNode(yyvsp[-3].n, subNode('-', 1, yyvsp[0].n), yyvsp[-3].n->value.sub.num);}
break;
case 14:
#line 45 "pipoca.y"
	{yyval.n = yyvsp[-1].n;}
break;
case 15:
#line 48 "pipoca.y"
	{yyval.n = subNode(EXTERN, 1, strNode(ID, yyvsp[0].s));}
break;
case 16:
#line 49 "pipoca.y"
	{yyval.n = addNode(yyvsp[-2].n, strNode(ID, yyvsp[0].s), yyvsp[-2].n->value.sub.num);}
break;
case 17:
#line 52 "pipoca.y"
	{yyval.n = subNode(CONSTN, 1, subNode(OPATR, 2, strNode(ID, yyvsp[-2].s), yyvsp[0].n));}
break;
case 18:
#line 53 "pipoca.y"
	{yyval.n = addNode(yyvsp[-2].n, subNode(OPATR, 2, strNode(ID, yyvsp[-4].s), yyvsp[0].n), yyvsp[-2].n->value.sub.num);}
break;
case 19:
#line 56 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 20:
#line 57 "pipoca.y"
	{yyval.n = strNode(STRING, yyvsp[0].s);}
break;
case 21:
#line 58 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 22:
#line 61 "pipoca.y"
	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
break;
case 23:
#line 62 "pipoca.y"
	{yyval.n = subNode(FUNC, 3, strNode(ID, yyvsp[-8].s), yyvsp[-6].n, yyvsp[-2].n);}
break;
case 24:
#line 63 "pipoca.y"
	{yyval.n = subNode(FUNC, 3, strNode(ID, yyvsp[-8].s), yyvsp[-6].n, yyvsp[-2].n);}
break;
case 25:
#line 66 "pipoca.y"
	{yyval.n = 0;}
break;
case 26:
#line 67 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 27:
#line 68 "pipoca.y"
	{yyval.n = subNode(UNALLOCVECTOR, 1, strNode(ID, yyvsp[-2].s));}
break;
case 28:
#line 69 "pipoca.y"
	{yyval.n = subNode(LISTEXP3, 2, yyvsp[-4].n, subNode(UNALLOCVECTOR, 1, strNode(ID, yyvsp[-2].s)));}
break;
case 29:
#line 70 "pipoca.y"
	{yyval.n = subNode(LISTEXP3, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 30:
#line 73 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 31:
#line 74 "pipoca.y"
	{yyval.n = subNode(UNALLOCVECTOR, 1, strNode(ID, yyvsp[-2].s));}
break;
case 32:
#line 75 "pipoca.y"
	{yyval.n = subNode(LISTEXP4, 2, yyvsp[-4].n, subNode(UNALLOCVECTOR, 1, strNode(ID, yyvsp[-2].s)));}
break;
case 33:
#line 76 "pipoca.y"
	{yyval.n = subNode(LISTEXP4, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 35:
#line 80 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 36:
#line 81 "pipoca.y"
	{yyval.n = subNode(LISTEXP, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 37:
#line 84 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 38:
#line 85 "pipoca.y"
	{yyval.n = subNode(LISTEXP2, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 39:
#line 88 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 40:
#line 89 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 41:
#line 90 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 42:
#line 91 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 43:
#line 92 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 44:
#line 93 "pipoca.y"
	{yyval.n = subNode(FUNC2, 1, yyvsp[0].n);}
break;
case 45:
#line 94 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 46:
#line 95 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 47:
#line 96 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 48:
#line 97 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 49:
#line 98 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 50:
#line 99 "pipoca.y"
	{yyval.n = addNode(yyvsp[-1].n, yyvsp[0].n, -1);}
break;
case 51:
#line 102 "pipoca.y"
	{yyval.n = subNode(BREAK, 1, intNode(INT, 1));}
break;
case 52:
#line 103 "pipoca.y"
	{yyval.n = subNode(CONTINUE, 1, intNode(INT, 1));}
break;
case 53:
#line 104 "pipoca.y"
	{yyval.n = subNode(BREAK, 1, intNode(INT, yyvsp[-1].i));}
break;
case 54:
#line 105 "pipoca.y"
	{yyval.n = subNode(CONTINUE, 1, intNode(INT, yyvsp[-1].i));}
break;
case 55:
#line 108 "pipoca.y"
	{yyval.n = yyvsp[-1].n;}
break;
case 56:
#line 109 "pipoca.y"
	{yyval.n = subNode(CONST, 1, yyvsp[-1].n);}
break;
case 58:
#line 113 "pipoca.y"
	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
break;
case 59:
#line 114 "pipoca.y"
	{yyval.n = 0;}
break;
case 60:
#line 117 "pipoca.y"
	{yyval.n = subNode(VAR, 1, strNode(ID, yyvsp[0].s));}
break;
case 61:
#line 118 "pipoca.y"
	{yyval.n = subNode(VAR, 1, strNode(IDVEC, yyvsp[-2].s));}
break;
case 62:
#line 119 "pipoca.y"
	{yyval.n = subNode(VAR, 1, subNode(IDVECINT, 2, strNode(ID, yyvsp[-3].s), intNode(INT, yyvsp[-1].i)));}
break;
case 63:
#line 120 "pipoca.y"
	{yyval.n = subNode(VAR, 1, subNode(IDVECID, 2, strNode(ID, yyvsp[-3].s), strNode(ID, yyvsp[-1].s)));}
break;
case 64:
#line 121 "pipoca.y"
	{yyval.n = addNode(yyvsp[-2].n, strNode(ID, yyvsp[0].s), -1);}
break;
case 65:
#line 122 "pipoca.y"
	{yyval.n = addNode(yyvsp[-4].n, strNode(IDVEC, yyvsp[-2].s), -1);}
break;
case 66:
#line 123 "pipoca.y"
	{yyval.n = addNode(yyvsp[-5].n, subNode(IDVECINT, 2, strNode(ID, yyvsp[-3].s), intNode(INT, yyvsp[-1].i)), -1);}
break;
case 67:
#line 124 "pipoca.y"
	{yyval.n = addNode(yyvsp[-5].n, subNode(IDVECID, 2, strNode(ID, yyvsp[-3].s), strNode(ID, yyvsp[-1].s)), -1);}
break;
case 68:
#line 127 "pipoca.y"
	{yyval.n = subNode(IF, 3, yyvsp[-6].n, yyvsp[-2].n, yyvsp[0].n);}
break;
case 69:
#line 128 "pipoca.y"
	{yyval.n = subNode(WHILE, 3, yyvsp[-6].n, yyvsp[-2].n, yyvsp[0].n);}
break;
case 70:
#line 129 "pipoca.y"
	{yyval.n = subNode(DO, 3, yyvsp[-4].n, yyvsp[-1].n, yyvsp[0].n);}
break;
case 71:
#line 132 "pipoca.y"
	{yyval.n = subNode(ELSE, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 72:
#line 133 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 73:
#line 136 "pipoca.y"
	{yyval.n = subNode(ELSE, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 74:
#line 137 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 75:
#line 140 "pipoca.y"
	{yyval.n = 0;}
break;
case 76:
#line 143 "pipoca.y"
	{yyval.n = 0;}
break;
case 77:
#line 146 "pipoca.y"
	{yyval.n = yyvsp[-1].n;}
break;
case 78:
#line 149 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 79:
#line 150 "pipoca.y"
	{yyval.n = subNode(AND, 2, yyvsp[-3].n, yyvsp[-1].n);}
break;
case 80:
#line 151 "pipoca.y"
	{yyval.n = subNode(AND, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 81:
#line 152 "pipoca.y"
	{yyval.n = subNode(OR, 2, yyvsp[-3].n, yyvsp[-1].n);}
break;
case 82:
#line 153 "pipoca.y"
	{yyval.n = subNode(OR, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 83:
#line 156 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 84:
#line 157 "pipoca.y"
	{yyval.n = subNode(OPATR, 2, strNode(ID, yyvsp[-2].s), yyvsp[0].n);}
break;
case 85:
#line 160 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 86:
#line 161 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 87:
#line 162 "pipoca.y"
	{yyval.n = subNode('-', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 88:
#line 163 "pipoca.y"
	{yyval.n = subNode('-', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 89:
#line 164 "pipoca.y"
	{yyval.n = subNode('+', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 90:
#line 165 "pipoca.y"
	{yyval.n = subNode('+', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 91:
#line 166 "pipoca.y"
	{yyval.n = subNode('*', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 92:
#line 167 "pipoca.y"
	{yyval.n = subNode('*', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 93:
#line 168 "pipoca.y"
	{yyval.n = subNode('/', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 94:
#line 169 "pipoca.y"
	{yyval.n = subNode('/', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 95:
#line 170 "pipoca.y"
	{yyval.n = subNode('%', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 96:
#line 171 "pipoca.y"
	{yyval.n = subNode('%', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 97:
#line 172 "pipoca.y"
	{yyval.n = subNode(POT, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 98:
#line 173 "pipoca.y"
	{yyval.n = subNode(POT, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 99:
#line 174 "pipoca.y"
	{yyval.n = subNode('<', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 100:
#line 175 "pipoca.y"
	{yyval.n = subNode('<', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 101:
#line 176 "pipoca.y"
	{yyval.n = subNode('>', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 102:
#line 177 "pipoca.y"
	{yyval.n = subNode('>', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 103:
#line 178 "pipoca.y"
	{yyval.n = subNode('=', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 104:
#line 179 "pipoca.y"
	{yyval.n = subNode('=', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 105:
#line 180 "pipoca.y"
	{yyval.n = subNode(MOREOREQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 106:
#line 181 "pipoca.y"
	{yyval.n = subNode(MOREOREQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 107:
#line 182 "pipoca.y"
	{yyval.n = subNode(LESSOREQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 108:
#line 183 "pipoca.y"
	{yyval.n = subNode(LESSOREQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 109:
#line 184 "pipoca.y"
	{yyval.n = subNode(NOTEQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 110:
#line 185 "pipoca.y"
	{yyval.n = subNode(NOTEQUAL, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 111:
#line 186 "pipoca.y"
	{yyval.n = subNode(OPATR, 2, subNode(IDVECA, 2, strNode(ID, yyvsp[-5].s), yyvsp[-3].n), yyvsp[0].n);}
break;
case 112:
#line 187 "pipoca.y"
	{yyval.n = subNode(OPATR, 2, subNode(IDVECA, 2, strNode(ID, yyvsp[-5].s), yyvsp[-3].n), yyvsp[0].n);}
break;
case 113:
#line 188 "pipoca.y"
	{yyval.n = subNode('?', 1, yyvsp[-1].n);}
break;
case 114:
#line 191 "pipoca.y"
	{yyval.n = subNode(EXPP, 1, yyvsp[-1].n);}
break;
case 115:
#line 194 "pipoca.y"
	{yyval.n = strNode(ID, yyvsp[0].s);}
break;
case 116:
#line 195 "pipoca.y"
	{yyval.n = subNode('@', 1, strNode(ID, yyvsp[0].s));}
break;
case 117:
#line 196 "pipoca.y"
	{yyval.n = subNode(FUNCCALL, 2, strNode(ID, yyvsp[-3].s), yyvsp[-1].n);}
break;
case 118:
#line 197 "pipoca.y"
	{yyval.n = subNode(IDVECA, 2, strNode(ID, yyvsp[-3].s), yyvsp[-1].n);}
break;
case 119:
#line 198 "pipoca.y"
	{yyval.n = subNode(PLUSONE, 1, strNode(ID, yyvsp[0].s));}
break;
case 120:
#line 199 "pipoca.y"
	{yyval.n = subNode(MINUSONE, 1, strNode(ID, yyvsp[0].s));}
break;
case 121:
#line 200 "pipoca.y"
	{yyval.n = subNode(PLUSONEA, 1, strNode(ID, yyvsp[-1].s));}
break;
case 122:
#line 201 "pipoca.y"
	{yyval.n = subNode(MINUSONEA, 1, strNode(ID, yyvsp[-1].s));}
break;
case 123:
#line 202 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 124:
#line 203 "pipoca.y"
	{yyval.n = subNode(NOT, 1, strNode(ID, yyvsp[0].s));}
break;
case 125:
#line 204 "pipoca.y"
	{yyval.n = subNode('-', 1, strNode(ID, yyvsp[0].s));}
break;
case 126:
#line 205 "pipoca.y"
	{yyval.n = subNode('-', 1, yyvsp[0].n);}
break;
case 127:
#line 208 "pipoca.y"
	{yyval.n = subNode(MEMRESERV, 2, strNode(ID, yyvsp[-4].s), yyvsp[-1].n);}
break;
case 128:
#line 211 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 129:
#line 212 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 130:
#line 213 "pipoca.y"
	{yyval.n = subNode('*', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 131:
#line 214 "pipoca.y"
	{yyval.n = subNode('*', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 132:
#line 215 "pipoca.y"
	{yyval.n = subNode('/', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 133:
#line 216 "pipoca.y"
	{yyval.n = subNode('/', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 134:
#line 217 "pipoca.y"
	{yyval.n = subNode('+', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 135:
#line 218 "pipoca.y"
	{yyval.n = subNode('+', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 136:
#line 219 "pipoca.y"
	{yyval.n = subNode('-', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 137:
#line 220 "pipoca.y"
	{yyval.n = subNode('-', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 138:
#line 221 "pipoca.y"
	{yyval.n = subNode('%', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 139:
#line 222 "pipoca.y"
	{yyval.n = subNode('%', 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 140:
#line 223 "pipoca.y"
	{yyval.n = subNode(POT, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 141:
#line 224 "pipoca.y"
	{yyval.n = subNode(POT, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 142:
#line 227 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 143:
#line 228 "pipoca.y"
	{yyval.n = strNode(ID, yyvsp[0].s);}
break;
case 144:
#line 231 "pipoca.y"
	{yyval.n = subNode(MEMRESERVP, 1, yyvsp[-1].n);}
break;
case 145:
#line 234 "pipoca.y"
	{yyval.n = subNode('!', 1, yyvsp[-2].n);}
break;
case 146:
#line 235 "pipoca.y"
	{yyval.n = subNode(PRINTLN, 1, yyvsp[-2].n);}
break;
case 147:
#line 238 "pipoca.y"
	{yyval.n = strNode(PRINTSTRING, yyvsp[0].s);}
break;
case 148:
#line 239 "pipoca.y"
	{yyval.n = subNode(PRINTP, 2, yyvsp[-2].n, strNode(PRINTID, yyvsp[0].s));}
break;
case 149:
#line 240 "pipoca.y"
	{yyval.n = subNode(PRINTP, 2, yyvsp[-5].n, subNode(PRINTFUNCCALL, 2, strNode(PRINTID, yyvsp[-3].s), yyvsp[-1].n));}
break;
case 150:
#line 241 "pipoca.y"
	{yyval.n = subNode(PRINTP, 2, yyvsp[-2].n, strNode(PRINTSTRING, yyvsp[0].s));}
break;
case 151:
#line 242 "pipoca.y"
	{yyval.n = subNode(PRINTP, 2, yyvsp[-2].n, intNode(PRINTINT, yyvsp[0].i));}
break;
case 152:
#line 243 "pipoca.y"
	{yyval.n = subNode(PRINTSM, 2, strNode(PRINTSTRING, yyvsp[-2].s), yyvsp[0].n);}
break;
case 153:
#line 244 "pipoca.y"
	{yyval.n = subNode(SSM, 3, yyvsp[-4].n, strNode(PRINTSTRING, yyvsp[-2].s), yyvsp[0].n);}
break;
case 154:
#line 247 "pipoca.y"
	{yyval.n = strNode(ID, yyvsp[0].s);}
break;
case 155:
#line 248 "pipoca.y"
	{yyval.n = yyvsp[0].n;}
break;
case 156:
#line 249 "pipoca.y"
	{yyval.n = subNode(PRINTM, 2, yyvsp[-2].n, strNode(ID, yyvsp[0].s));}
break;
case 157:
#line 250 "pipoca.y"
	{yyval.n = subNode(PRINTM, 2, yyvsp[-2].n, yyvsp[0].n);}
break;
case 158:
#line 253 "pipoca.y"
	{yyval.n = intNode(INT, yyvsp[0].i);}
break;
case 159:
#line 254 "pipoca.y"
	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
break;
#line 1548 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = (short) yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
