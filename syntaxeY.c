
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "syntaxe.y"
/*-------- syntaxe.y -----------*/
  /*Réalisé par: EZ-ZAKKAR Mohammed && ELmoumny Azddine && Aalloul Outmane && AMAACH Amine SMI-S6*/
    #include <stdio.h>
    #include<stdlib.h>
    #include<string.h>
    FILE * LC;
    extern FILE* yyin; //file pointer by default points to terminal
    int yylex(void); // defini dans lexiqueL.c, utilise par yyparse()
    void yyerror(const char * msg); // definie dans syntaxe.y, utilise par notre code pour .
    int yylineno;// notre compteur de lignes
    /* extern int yylval; | AFFECT {fprintf(LC,"=");if(NOT_START_EXP){yyerror("Errore : ");exit(-1);}}*/
    /* extern float valReel; */
    extern char valIdentif[];
    extern char valtype[];
    extern char strval[];
    extern char val[];
    char _help1[20];
    char IDN_AFF_STR[20];
    int NOT_START_EXP=-1;
    char dec[50];
    int typeVAR=1;
    int OPR_NULL=0;
    int DEC_AFF=0;
    int AFF_STR=0;
    int PARTIE_INST=0;
    char listIdentifs[20][3][20];//table to add variable name ,type and (TAB or NOTTAB)
    char FUN_list[10][2][20];
    int i_tab_FUN = -1;
    int i_tab=-1;
    int nbr_idntf_add = 0;
    char tab_op_idn[10][20];
    int i_tab_op=-1;
    int OUTPUT_ZON = 0;
    int FUN_ARG_ZONE = 0;
    int PROC_ZONE = 0;
    char nameFile[20];
    const char * strError = " errore : " ;
    const char * msgErrore=" errore : undefined identifier" ;
    const char * ErroreFun=" errore : undefined Function";
    int isFUNCTION(char * string){
        for(int i=0;i<=i_tab_FUN;i++){
            if(!strcmp(string,FUN_list[i][0])){
                return 1;
            }
        }
        yyerror(ErroreFun);printf(" '%s(..'",string);
        exit(-1);
    }
    int isDeclared(char * string){ //check if the varible is declared or not
        for(int i=0;i<=i_tab;i++){
            strcpy(strval,listIdentifs[i][0]);//to not change value IDNTIF in the listIdentifs table with the function strtok
            strcpy(dec,string);
            if(!strcmp(strtok(dec,"["),strtok(strval,"["))){
                /* if(strlen) */
                if(!strchr(string,'[') && strchr(listIdentifs[i][0],'[')){
                    if(!strcmp(listIdentifs[i][1],"int") || !strcmp(listIdentifs[i][1],"float")){
                        yyerror("erreur : assignment to expression with array type");printf("\n\t%s",string);
                        exit(-1);
                    }
                }else if(strchr(string,'[') && !strchr(listIdentifs[i][0],'[')){
                    if(strcmp(listIdentifs[i][1],"char *")){
                        yyerror("erreur : subscripted value is neither array nor pointer nor vector");printf("\n\t%s",string);
                        exit(-1);
                    }
                }
                return 1;
            }
        }
        yyerror(msgErrore);printf(" '%s'",string);
        exit(-1);
    }
    int add_idn(char * string){//add IDNETIF in the listIdentifs table , with check error if the IDENTIF is declared 
        for(int i=0;i<=i_tab;i++){
            strcpy(strval,listIdentifs[i][0]);//to not change value IDNTIF in the listIdentifs table with the function strtok
            strcpy(_help1,string);
            if(!strcmp(strtok(_help1,"["),strtok(strval,"["))){
                yyerror("erreur : redeclaration of << ");printf("%s >>",valIdentif);
                exit(-1);
            }
        }
        strcpy(listIdentifs[++i_tab][0],string);
        if(strchr(string,'['))strcpy(listIdentifs[i_tab][2],"TAB");
        else strcpy(listIdentifs[i_tab][2],"NOTTAB");
        nbr_idntf_add++;
        return 1;
    }
    int add_type_idn(char * string){// add varible type in the listIdentifs[i][1] table
        for(int i=nbr_idntf_add-1;i>=0;i--) {
            if(!strcmp("char",string)){
                if(strchr(listIdentifs[i_tab-i][0],'[')) strcpy(listIdentifs[i_tab-i][1],"char *");
                else strcpy(listIdentifs[i_tab-i][1],string);
            }
            else strcpy(listIdentifs[i_tab-i][1],string);
            if(FUN_ARG_ZONE){
                if(!strcmp(listIdentifs[i_tab-i][1],"char *")){strcat(dec,"char");strcat(FUN_list[i_tab_FUN][1],"s");}
                else{
                    strcat(dec,listIdentifs[i_tab-i][1]);
                    if(!strcmp(listIdentifs[i_tab-i][1],"char"))strcat(FUN_list[i_tab_FUN][1],"c");
                    else if(!strcmp(listIdentifs[i_tab-i][1],"int"))strcat(FUN_list[i_tab_FUN][1],"d");
                        else strcat(FUN_list[i_tab_FUN][1],"f");
                }
                strcat(dec," ");
                strcat(dec,listIdentifs[i_tab-i][0]);
                if(i)strcat(dec,",");
            }
        }
        nbr_idntf_add=0;
        return 0;
    }
    int type_idn(char * string){
        isDeclared(string);
        strcpy(tab_op_idn[++i_tab_op],string);
        for(int i=0; i<=i_tab; i++){
            strcpy(strval,listIdentifs[i][0]);
            if(!strcmp(strtok(string,"["),strtok(strval,"["))){
                if(!strcmp(listIdentifs[i][1],"int"))
                    fprintf(LC,"%cd",'%');
                else if(!strcmp(listIdentifs[i][1],"float"))
                        fprintf(LC,"%cf",'%');
                    else if(!strcmp(listIdentifs[i][1],"char *"))
                            {
                                if(strchr(tab_op_idn[i_tab_op],'['))fprintf(LC,"%cc",'%');
                                else fprintf(LC,"%cs",'%');
                            }
                        else if(!strcmp(listIdentifs[i][1],"char"))
                                fprintf(LC,"%cc",'%');
                return 1;
            } 
        }
    }
    int CHECK_STR_AFF(){
        isDeclared(valIdentif);
        for(int i=0;i<=i_tab;i++){
            strcpy(strval,listIdentifs[i][0]);
            strcpy(_help1,valIdentif);
            if(!strcmp(strtok(_help1,"["),strtok(strval,"["))){
                if(!strcmp(listIdentifs[i][1],"char *")){
                    AFF_STR=1;
                    fprintf(LC,"\n\tstrcpy(%s,\"\");",valIdentif);
                    strcpy(IDN_AFF_STR,valIdentif);
                }
                else fprintf(LC,"\n\t%s=",valIdentif);
            }
        }
    }
    void AFF_STR_IDN(){
        for(int i=0;i<=i_tab;i++){
            strcpy(strval,listIdentifs[i][0]);
            strcpy(_help1,valIdentif);
            if(!strcmp(strtok(_help1,"["),strtok(strval,"["))){
                if(!strcmp(listIdentifs[i][1],"char *"))fprintf(LC,"\n\tstrcat(%s,%s);",IDN_AFF_STR,valIdentif);
                else {
                    yyerror(strError);exit(-1);
                }
            }
        }
    }
    int add_tab_op_idn(){
        fprintf(LC,"\"",tab_op_idn[0]);
        for(int i=0; i <= i_tab_op ; i++){
            if(OUTPUT_ZON) fprintf(LC,",%s",tab_op_idn[i]);
            else {
                strcpy(dec,tab_op_idn[i]);
                for(int j=0;j<=i_tab;j++){
                    strcpy(strval,listIdentifs[j][0]);
                    if(!strcmp(strtok(dec,"["),strtok(strval,"["))){
                        if(!strcmp(listIdentifs[j][1],"char *")){
                            if(!strchr(tab_op_idn[i],'['))
                                fprintf(LC,",%s",tab_op_idn[i]);
                            else fprintf(LC,",&%s",tab_op_idn[i]);
                        }else fprintf(LC,",&%s",tab_op_idn[i]);
                    }
                }
            }
            
        }
        fprintf(LC,");");
        i_tab_op=-1;
    }
    int add_str_OUTPUT(char * string){
            for(int i=1 ; i<strlen(string)-1 ; i++)
                fprintf(LC,"%c",string[i]);
    }
    int add_COMMENT(char * string){
        fprintf(LC,"%s","/*");
        for(int i=1 ; i<strlen(string)-1 ; i++)
                fprintf(LC,"%c",string[i]);
        fprintf(LC,"%s","*/");
    }
    void aff(){
        for(int i=0;i<=i_tab;i++){
            printf("%s %s %s\n",listIdentifs[i][0],listIdentifs[i][1],listIdentifs[i][2]);}
    }


/* Line 189 of yacc.c  */
#line 269 "syntaxeY.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENTIERTYPE = 258,
     BREAK = 259,
     REEL = 260,
     CHAR = 261,
     STRING = 262,
     ENTIER = 263,
     CONST = 264,
     VAR = 265,
     IDENTIF = 266,
     FINWH = 267,
     WHILE = 268,
     DO = 269,
     SI = 270,
     SINON = 271,
     ALORS = 272,
     FINSI = 273,
     SWITCH = 274,
     FINSW = 275,
     REP = 276,
     JUS = 277,
     POUR = 278,
     FINPOUR = 279,
     EGAL = 280,
     DIFF = 281,
     AFFECT = 282,
     PLUS = 283,
     MUL = 284,
     DIV = 285,
     SSTRA = 286,
     MOD = 287,
     ET = 288,
     OU = 289,
     Sup = 290,
     Inf = 291,
     SupEQ = 292,
     InfEQ = 293,
     OUTPUT = 294,
     INPUT = 295,
     FUN = 296,
     PROC = 297,
     TAB = 298,
     Debut = 299,
     Fin = 300,
     Algo = 301,
     Comment = 302,
     PTVIRG = 303,
     VAUT = 304,
     ARRAY = 305,
     REELTYPE = 306,
     CHARTYPE = 307,
     STRINGTYPE = 308,
     RETURN = 309
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 365 "syntaxeY.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   530

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNRULES -- Number of states.  */
#define YYNSTATES  237

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,    56,     2,     2,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    59,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    18,    19,    20,    21,
      22,    23,    24,    42,    43,    44,    45,    46,    47,    48,
      65,    67,    69,    71,    75,    79,    80,    87,    88,    89,
      94,    95,   100,   101,   107,   109,   110,   115,   117,   119,
     123,   127,   128,   129,   130,   139,   140,   147,   148,   155,
     158,   163,   164,   165,   173,   174,   181,   184,   185,   186,
     197,   198,   199,   210,   211,   212,   222,   223,   231,   232,
     233,   234,   246,   248,   250,   252,   254,   256,   258,   260,
     262,   263,   266,   267,   272,   277,   283,   285,   286,   293,
     295,   296,   301,   303,   305,   307,   309,   311,   313,   315,
     317,   319,   321,   323,   325,   329,   330,   335,   336,   341,
     342,   347,   348,   353,   354,   360,   362,   363,   368,   369,
     371,   373,   375,   377,   379,   381,   383,   385,   387,   389,
     391,   393,   395,   397,   401,   405
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      61,     0,    -1,    -1,    -1,    -1,    62,    65,    46,    11,
      63,    48,    81,    44,    64,    88,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    41,    11,    66,    55,    67,
      79,    68,    56,    57,   116,    69,    81,    44,    70,    88,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    42,
      71,    11,    72,    55,    73,    79,    74,    56,    75,    81,
      44,    76,    88,    45,    -1,    11,    -1,    50,    -1,    77,
      -1,    78,    58,    77,    -1,    78,    57,   116,    -1,    -1,
      79,    58,    80,    78,    57,   116,    -1,    -1,    -1,    81,
      10,    82,    84,    -1,    -1,    81,     9,    83,    84,    -1,
      -1,    84,    85,    57,   116,    48,    -1,    87,    -1,    -1,
      85,    58,    86,    87,    -1,    50,    -1,    11,    -1,    11,
      27,   117,    -1,    50,    27,   117,    -1,    -1,    -1,    -1,
      88,    11,    55,    89,   124,    56,    90,    48,    -1,    -1,
      88,    11,    27,    91,   118,    48,    -1,    -1,    88,    50,
      27,    92,   118,    48,    -1,    88,    48,    -1,    88,    54,
     106,    48,    -1,    -1,    -1,    88,    39,    93,    55,    94,
     128,    56,    -1,    -1,    88,    40,    55,    95,   128,    56,
      -1,    88,    47,    -1,    -1,    -1,    88,    15,    55,    96,
     118,    56,    17,    97,    88,   114,    -1,    -1,    -1,    88,
      13,    55,    98,   118,    56,    14,    99,    88,    12,    -1,
      -1,    -1,    88,    21,   100,    88,    22,    55,   101,   118,
      56,    -1,    -1,    88,    19,    11,   102,    49,   112,    20,
      -1,    -1,    -1,    -1,    88,    23,    11,   103,   107,   104,
      59,   107,   105,    88,    24,    -1,     8,    -1,     5,    -1,
       7,    -1,     6,    -1,    11,    -1,    50,    -1,    11,    -1,
       8,    -1,    -1,   109,   117,    -1,    -1,   108,    58,   110,
     117,    -1,   108,    57,    88,     4,    -1,   111,   108,    57,
      88,     4,    -1,   111,    -1,    -1,   111,    16,   113,    57,
      88,     4,    -1,    18,    -1,    -1,    16,   115,    88,    18,
      -1,     3,    -1,    51,    -1,    53,    -1,    52,    -1,    11,
      -1,     8,    -1,     5,    -1,     7,    -1,     6,    -1,   117,
      -1,    11,    -1,    50,    -1,   118,   126,   118,    -1,    -1,
     118,    34,   119,   118,    -1,    -1,   118,    33,   120,   118,
      -1,    -1,   118,   127,   121,   118,    -1,    -1,    55,   122,
     118,    56,    -1,    -1,    11,    55,   123,   124,    56,    -1,
     118,    -1,    -1,   124,    58,   125,   118,    -1,    -1,    28,
      -1,    31,    -1,    30,    -1,    32,    -1,    29,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    25,    -1,    26,
      -1,    50,    -1,    11,    -1,     7,    -1,   128,    58,    11,
      -1,   128,    58,    50,    -1,   128,    58,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   203,   203,   208,   215,   203,   225,   226,   227,   227,
     228,   236,   226,   242,   242,   243,   243,   244,   249,   242,
     257,   258,   260,   261,   263,   264,   264,   266,   267,   267,
     268,   268,   271,   272,   278,   287,   287,   297,   298,   299,
     300,   302,   303,   303,   303,   304,   304,   305,   305,   306,
     307,   308,   308,   308,   309,   309,   310,   311,   311,   311,
     312,   312,   312,   313,   313,   313,   314,   314,   315,   315,
     315,   315,   317,   318,   319,   320,   321,   322,   324,   325,
     327,   327,   328,   328,   330,   331,   332,   333,   333,   335,
     336,   336,   338,   339,   340,   341,   342,   345,   346,   347,
     352,   354,   355,   356,   357,   358,   358,   359,   359,   360,
     360,   361,   361,   362,   362,   365,   366,   366,   368,   369,
     370,   371,   372,   373,   375,   376,   377,   378,   379,   380,
     382,   383,   384,   390,   391,   392
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ENTIERTYPE", "BREAK", "REEL", "CHAR",
  "STRING", "ENTIER", "CONST", "VAR", "IDENTIF", "FINWH", "WHILE", "DO",
  "SI", "SINON", "ALORS", "FINSI", "SWITCH", "FINSW", "REP", "JUS", "POUR",
  "FINPOUR", "EGAL", "DIFF", "AFFECT", "PLUS", "MUL", "DIV", "SSTRA",
  "MOD", "ET", "OU", "Sup", "Inf", "SupEQ", "InfEQ", "OUTPUT", "INPUT",
  "FUN", "PROC", "TAB", "Debut", "Fin", "Algo", "Comment", "PTVIRG",
  "VAUT", "ARRAY", "REELTYPE", "CHARTYPE", "STRINGTYPE", "RETURN", "'('",
  "')'", "':'", "','", "'_'", "$accept", "code", "$@1", "$@2", "$@3",
  "FUNCTIONS", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "$@12", "$@13", "$@14", "varArg", "Arg", "Arglist", "$@15",
  "declaration", "$@16", "$@17", "listdec", "namelist", "$@18", "variable",
  "listInstr", "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25",
  "$@26", "$@27", "$@28", "$@29", "$@30", "$@31", "$@32", "$@33", "$@34",
  "$@35", "ReturnList", "ValuePour", "ValuelistSW", "$@36", "$@37", "Case",
  "suiteSwitch", "$@38", "suiteCondition", "$@39", "type", "VALUE", "exp",
  "$@40", "$@41", "$@42", "$@43", "$@44", "explist", "$@45", "opr", "CMP",
  "valuelist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    40,    41,    58,    44,    95
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    62,    63,    64,    61,    65,    66,    67,    68,
      69,    70,    65,    71,    72,    73,    74,    75,    76,    65,
      77,    77,    78,    78,    79,    80,    79,    81,    82,    81,
      83,    81,    84,    84,    85,    86,    85,    87,    87,    87,
      87,    88,    89,    90,    88,    91,    88,    92,    88,    88,
      88,    93,    94,    88,    95,    88,    88,    96,    97,    88,
      98,    99,    88,   100,   101,    88,   102,    88,   103,   104,
     105,    88,   106,   106,   106,   106,   106,   106,   107,   107,
     109,   108,   110,   108,   111,   111,   112,   113,   112,   114,
     115,   114,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   119,   118,   120,   118,   121,
     118,   122,   118,   123,   118,   124,   125,   124,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   127,   127,   127,
     128,   128,   128,   128,   128,   128
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    11,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,    16,
       1,     1,     1,     3,     3,     0,     6,     0,     0,     4,
       0,     4,     0,     5,     1,     0,     4,     1,     1,     3,
       3,     0,     0,     0,     8,     0,     6,     0,     6,     2,
       4,     0,     0,     7,     0,     6,     2,     0,     0,    10,
       0,     0,    10,     0,     0,     9,     0,     7,     0,     0,
       0,    11,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     0,     4,     4,     5,     1,     0,     6,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     5,     1,     0,     4,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,     0,     0,    13,     0,     7,     0,
       3,     0,    14,     0,     8,     0,    27,     0,    15,     0,
      20,    21,    22,     0,     9,     0,    30,    28,     4,     0,
       0,    25,     0,    16,    32,    32,    41,    92,    96,    93,
      95,    94,    24,    23,     0,     0,     0,    31,    29,     0,
       0,     0,    17,    38,    37,     0,    34,     0,     0,     0,
       0,    63,     0,    51,     0,     5,    56,    49,     0,     0,
       0,    10,    27,     0,     0,     0,    35,    45,    42,    60,
      57,    66,    41,    68,     0,    54,    47,    73,    75,    74,
      72,    76,    77,     0,    26,    27,     0,    98,   100,    99,
      97,    39,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,     0,     0,    50,     0,    18,    33,    36,
     102,   103,   111,   101,   118,   118,     0,   118,   118,    80,
       0,    79,    78,    69,     0,   132,   131,   130,     0,   118,
      11,    41,   113,     0,   128,   129,   119,   123,   121,   120,
     122,   107,   105,   124,   125,   126,   127,    46,     0,   109,
      43,   116,     0,     0,     0,     0,    80,     0,    64,     0,
       0,    55,     0,    48,    41,     0,     0,   118,     0,     0,
     104,     0,     0,     0,    61,    58,    41,    82,    81,    87,
       0,    67,     0,     0,    53,   135,   133,   134,     0,    19,
       0,   112,   108,   106,   110,    44,   118,    41,    41,     0,
       0,     0,    41,   118,    70,    12,   114,     0,     0,    84,
      83,    41,     0,    65,    41,    62,    90,    89,    59,     0,
      85,     0,    41,    88,    71,     0,    91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    36,     4,    11,    17,    32,    95,
     174,     9,    15,    25,    46,    72,   141,    22,    23,    24,
      44,    19,    35,    34,    47,    55,   104,    56,    49,   106,
     182,   105,   114,    84,   134,   113,   108,   208,   107,   207,
      82,   192,   109,   111,   169,   224,    93,   133,   164,   165,
     210,   166,   167,   211,   228,   232,    42,   123,   125,   179,
     178,   181,   143,   176,   126,   183,   158,   159,   138
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
    -103,     8,  -103,  -103,    65,     5,  -103,     9,  -103,    33,
    -103,   -28,  -103,   -15,  -103,    11,  -103,    -4,  -103,    21,
    -103,  -103,  -103,    16,    -7,    -4,  -103,  -103,  -103,    32,
      -4,  -103,    35,    -7,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,    -4,    43,    49,    -1,    -1,   154,
      37,    32,  -103,    51,    82,    71,  -103,   -18,    62,    69,
     124,  -103,   129,  -103,    88,  -103,  -103,  -103,   122,    91,
      32,  -103,  -103,   126,   126,    32,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,    98,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,   107,  -103,  -103,    77,  -103,  -103,  -103,
    -103,  -103,  -103,   110,    -1,    64,    64,    64,    64,   112,
     192,    47,  -103,     7,    64,  -103,    79,  -103,  -103,  -103,
     108,  -103,  -103,  -103,   450,   344,     6,   392,   406,  -103,
     111,  -103,  -103,  -103,     7,  -103,  -103,  -103,    24,   471,
    -103,  -103,  -103,    64,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,    64,  -103,
    -103,  -103,   158,   151,   113,   126,    22,   156,  -103,   115,
      57,  -103,    18,  -103,  -103,   205,    64,   421,    64,    64,
     492,    64,   134,    64,  -103,  -103,  -103,  -103,  -103,  -103,
     121,  -103,    64,    47,  -103,  -103,  -103,  -103,   243,  -103,
      90,  -103,   492,   492,   492,  -103,   358,  -103,  -103,     0,
     126,   127,  -103,   435,  -103,  -103,  -103,   256,   141,  -103,
    -103,  -103,    13,  -103,  -103,  -103,  -103,  -103,  -103,    97,
    -103,   294,  -103,  -103,  -103,   317,  -103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,   153,   142,   160,
    -103,   -50,  -103,  -103,   152,  -103,  -103,    86,   -82,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,     3,    26,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,    52,   -72,  -102,  -103,
    -103,  -103,  -103,  -103,    30,  -103,  -103,  -103,    63
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -118
static const yytype_int16 yytable[] =
{
     110,   101,   102,   124,   219,   127,   128,    20,     3,    77,
      53,    57,   139,    58,   135,    59,     8,   230,   136,    60,
      10,    61,    96,    62,    57,   195,    58,    14,    59,   196,
      26,    27,    60,    16,    61,    37,    62,    78,   189,    63,
      64,   177,   -86,    38,    12,   116,    21,    66,    67,    54,
      68,    31,    63,    64,    69,   131,   180,   137,   132,   175,
      66,    67,   160,    68,   161,    28,    18,    69,   197,    97,
      98,    99,   100,    29,    30,   120,   202,   203,    73,   204,
     171,   206,   172,    39,    40,    41,    26,    27,    26,    27,
     213,    45,   198,   188,    70,    30,    87,    88,    89,    90,
      51,   233,    91,    71,   209,    52,     5,     6,    57,    74,
      58,     7,    59,   194,   121,   172,    60,    79,    61,   122,
      62,   117,    94,   140,    80,   217,   218,   103,    75,    76,
     222,    97,    98,    99,   100,    81,    63,    64,   220,   229,
      83,    92,   231,    85,    66,    67,   216,    68,   161,    86,
     235,    69,    57,   112,    58,   115,    59,   226,   118,   227,
      60,   129,    61,   142,    62,    57,   168,    58,   185,    59,
     186,   187,   184,    60,   193,    61,   191,    62,   212,   187,
      63,    64,   205,    43,   221,    33,    50,    48,    66,    67,
     119,    68,   190,    63,    64,    69,   214,   170,     0,    65,
       0,    66,    67,    57,    68,    58,   200,    59,    69,     0,
       0,    60,     0,    61,   130,    62,    57,     0,    58,     0,
      59,     0,     0,     0,    60,     0,    61,     0,    62,     0,
       0,    63,    64,     0,     0,     0,     0,     0,     0,    66,
      67,     0,    68,     0,    63,    64,    69,     0,     0,     0,
     199,     0,    66,    67,    57,    68,    58,     0,    59,    69,
       0,     0,    60,     0,    61,     0,    62,    57,   225,    58,
       0,    59,     0,     0,     0,    60,     0,    61,     0,    62,
       0,     0,    63,    64,     0,     0,     0,     0,   215,     0,
      66,    67,     0,    68,     0,    63,    64,    69,     0,     0,
       0,     0,     0,    66,    67,    57,    68,    58,     0,    59,
      69,     0,     0,    60,     0,    61,     0,    62,   234,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,     0,
      58,     0,    59,    63,    64,   236,    60,     0,    61,     0,
      62,    66,    67,     0,    68,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,     0,     0,     0,    66,    67,     0,    68,     0,   144,
     145,    69,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   144,   145,     0,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,     0,     0,
    -115,     0,  -115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -117,     0,  -117,   144,   145,     0,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   144,   145,     0,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   144,   145,   162,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     144,   145,   163,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   144,   145,   201,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
       0,   223,     0,     0,     0,     0,   144,   145,   157,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       0,     0,     0,     0,     0,     0,     0,   144,   145,   173,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156
};

static const yytype_int16 yycheck[] =
{
      82,    73,    74,   105,     4,   107,   108,    11,     0,    27,
      11,    11,   114,    13,     7,    15,    11,     4,    11,    19,
      11,    21,    72,    23,    11,     7,    13,    55,    15,    11,
       9,    10,    19,    48,    21,     3,    23,    55,    16,    39,
      40,   143,    20,    11,    11,    95,    50,    47,    48,    50,
      50,    58,    39,    40,    54,     8,   158,    50,    11,   141,
      47,    48,    56,    50,    58,    44,    55,    54,    50,     5,
       6,     7,     8,    57,    58,    11,   178,   179,    27,   181,
      56,   183,    58,    51,    52,    53,     9,    10,     9,    10,
     192,    56,   174,   165,    57,    58,     5,     6,     7,     8,
      57,     4,    11,    51,   186,    56,    41,    42,    11,    27,
      13,    46,    15,    56,    50,    58,    19,    55,    21,    55,
      23,    44,    70,    44,    55,   207,   208,    75,    57,    58,
     212,     5,     6,     7,     8,    11,    39,    40,   210,   221,
      11,    50,   224,    55,    47,    48,    56,    50,    58,    27,
     232,    54,    11,    55,    13,    48,    15,    16,    48,    18,
      19,    49,    21,    55,    23,    11,    55,    13,    17,    15,
      57,    58,    14,    19,    59,    21,    20,    23,    57,    58,
      39,    40,    48,    30,    57,    25,    44,    35,    47,    48,
     104,    50,   166,    39,    40,    54,   193,   134,    -1,    45,
      -1,    47,    48,    11,    50,    13,   176,    15,    54,    -1,
      -1,    19,    -1,    21,    22,    23,    11,    -1,    13,    -1,
      15,    -1,    -1,    -1,    19,    -1,    21,    -1,    23,    -1,
      -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    50,    -1,    39,    40,    54,    -1,    -1,    -1,
      45,    -1,    47,    48,    11,    50,    13,    -1,    15,    54,
      -1,    -1,    19,    -1,    21,    -1,    23,    11,    12,    13,
      -1,    15,    -1,    -1,    -1,    19,    -1,    21,    -1,    23,
      -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    48,    -1,    50,    -1,    39,    40,    54,    -1,    -1,
      -1,    -1,    -1,    47,    48,    11,    50,    13,    -1,    15,
      54,    -1,    -1,    19,    -1,    21,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,
      13,    -1,    15,    39,    40,    18,    19,    -1,    21,    -1,
      23,    47,    48,    -1,    50,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    50,    -1,    25,
      26,    54,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      56,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    58,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    25,    26,    56,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      25,    26,    56,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    25,    26,    56,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    25,    26,    48,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    48,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,    65,    41,    42,    46,    11,    71,
      11,    66,    11,    63,    55,    72,    48,    67,    55,    81,
      11,    50,    77,    78,    79,    73,     9,    10,    44,    57,
      58,    58,    68,    79,    83,    82,    64,     3,    11,    51,
      52,    53,   116,    77,    80,    56,    74,    84,    84,    88,
      78,    57,    56,    11,    50,    85,    87,    11,    13,    15,
      19,    21,    23,    39,    40,    45,    47,    48,    50,    54,
      57,   116,    75,    27,    27,    57,    58,    27,    55,    55,
      55,    11,   100,    11,    93,    55,    27,     5,     6,     7,
       8,    11,    50,   106,   116,    69,    81,     5,     6,     7,
       8,   117,   117,   116,    86,    91,    89,    98,    96,   102,
      88,   103,    55,    95,    92,    48,    81,    44,    48,    87,
      11,    50,    55,   117,   118,   118,   124,   118,   118,    49,
      22,     8,    11,   107,    94,     7,    11,    50,   128,   118,
      44,    76,    55,   122,    25,    26,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    48,   126,   127,
      56,    58,    56,    56,   108,   109,   111,   112,    55,   104,
     128,    56,    58,    48,    70,    88,   123,   118,   120,   119,
     118,   121,    90,   125,    14,    17,    57,    58,   117,    16,
     108,    20,   101,    59,    56,     7,    11,    50,    88,    45,
     124,    56,   118,   118,   118,    48,   118,    99,    97,    88,
     110,   113,    57,   118,   107,    45,    56,    88,    88,     4,
     117,    57,    88,    56,   105,    12,    16,    18,   114,    88,
       4,    88,   115,     4,    24,    88,    18
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 203 "syntaxe.y"
    {
    LC=fopen("headerFile.h","w");
    fprintf(LC,"#include<stdio.h>\n#include<string.h>\n#include<stdlib.h>");
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 208 "syntaxe.y"
    {
    fclose(LC);
    strcat(valIdentif, ".c");
    LC=fopen(valIdentif,"w");
    fprintf(LC,"#include\"headerFile.h\"\nint main(){\n\n");
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 215 "syntaxe.y"
    {PARTIE_INST=1;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 218 "syntaxe.y"
    {
    PARTIE_INST=0;
    fprintf(LC,"\n\treturn 0;\n}");
    fclose(LC);
    /* aff(); */
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 226 "syntaxe.y"
    {strcpy(FUN_list[++i_tab_FUN][1],"F");strcpy(FUN_list[i_tab_FUN][0],valIdentif);strcpy(dec,valIdentif);strcat(dec,"(");;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 227 "syntaxe.y"
    {FUN_ARG_ZONE=1;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 227 "syntaxe.y"
    {FUN_ARG_ZONE=0;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 228 "syntaxe.y"
    {
                            fprintf(LC,"\n%s %s){\n",valtype,dec);
                            if(!strcmp(valtype,"int"))strcat(FUN_list[i_tab_FUN][1],"d");
                            else if(!strcmp(valtype,"float"))strcat(FUN_list[i_tab_FUN][1],"f");
                                else strcat(FUN_list[i_tab_FUN][1],"c");
                        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 236 "syntaxe.y"
    {PARTIE_INST=1;;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 238 "syntaxe.y"
    {PARTIE_INST=0;
                            fprintf(LC,"\n}");
                            i_tab=-1;
                        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 242 "syntaxe.y"
    {PROC_ZONE=1;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 242 "syntaxe.y"
    {strcpy(FUN_list[++i_tab_FUN][1],"P");strcpy(FUN_list[i_tab_FUN][0],valIdentif);strcpy(dec,valIdentif);strcat(dec,"(");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 243 "syntaxe.y"
    {FUN_ARG_ZONE=1;;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 243 "syntaxe.y"
    {FUN_ARG_ZONE=0;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 244 "syntaxe.y"
    {
                            fprintf(LC,"\nvoid %s){\n",dec);
                        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 249 "syntaxe.y"
    {PARTIE_INST=1;;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 251 "syntaxe.y"
    {PARTIE_INST=0;
                            fprintf(LC,"\n}");
                            i_tab=-1;
                            PROC_ZONE=0;
                        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 260 "syntaxe.y"
    {add_idn(valIdentif);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 261 "syntaxe.y"
    {add_idn(valIdentif);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 263 "syntaxe.y"
    {add_type_idn(valtype);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 264 "syntaxe.y"
    {strcat(dec,",");;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 264 "syntaxe.y"
    {add_type_idn(valtype);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 267 "syntaxe.y"
    {typeVAR=0;;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 268 "syntaxe.y"
    {typeVAR=1;;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 272 "syntaxe.y"
    {
        if(typeVAR) fprintf(LC ,"\tconst %s %s;\n",valtype,dec);
        else fprintf(LC ,"\t%s %s;\n",valtype,dec);
        add_type_idn(valtype);
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 278 "syntaxe.y"
    {
                    strcpy(dec,valIdentif);
                    add_idn(valIdentif);
                    if(DEC_AFF){
                        strcat(dec," = ");
                        strcat(dec,val);
                        DEC_AFF=0;
                    }
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 287 "syntaxe.y"
    {strcat(dec," , ");;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 287 "syntaxe.y"
    {
            strcat(dec,valIdentif);
            add_idn(valIdentif);
            if(DEC_AFF){
                strcat(dec," = ");
                strcat(dec,val);
                DEC_AFF=0;
            }
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 299 "syntaxe.y"
    {DEC_AFF = 1;;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 300 "syntaxe.y"
    {DEC_AFF = 1;;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 303 "syntaxe.y"
    {isFUNCTION(valIdentif);fprintf(LC,"\n\t%s(",valIdentif);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 303 "syntaxe.y"
    {fprintf(LC,")");;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 303 "syntaxe.y"
    {fprintf(LC,";");;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 304 "syntaxe.y"
    {CHECK_STR_AFF();;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 304 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,";");AFF_STR=0;;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 305 "syntaxe.y"
    {fprintf(LC,"\n\t%s=",valIdentif);isDeclared(valIdentif);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 305 "syntaxe.y"
    {fprintf(LC,";");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 307 "syntaxe.y"
    {fprintf(LC,"\n\treturn %s;",val);if(PROC_ZONE){yyerror("can't use renvoyer !!");exit(-1);};}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 308 "syntaxe.y"
    {OUTPUT_ZON=1;;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 308 "syntaxe.y"
    {fprintf(LC,"\n\tprintf(\"");;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 308 "syntaxe.y"
    {add_tab_op_idn();{OUTPUT_ZON=0;} ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 309 "syntaxe.y"
    {fprintf(LC,"\n\tscanf(\"");;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 309 "syntaxe.y"
    {add_tab_op_idn();;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 310 "syntaxe.y"
    {add_COMMENT(valIdentif);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 311 "syntaxe.y"
    {fprintf(LC,"\n\tif(");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 311 "syntaxe.y"
    {fprintf(LC,"){");;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 312 "syntaxe.y"
    {fprintf(LC,"\n\twhile(");;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 312 "syntaxe.y"
    {fprintf(LC,"){");;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 312 "syntaxe.y"
    {fprintf(LC,"\n\t}");}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 313 "syntaxe.y"
    {fprintf(LC,"\n\tdo{");;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 313 "syntaxe.y"
    {fprintf(LC,"\n\t}while(");;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 313 "syntaxe.y"
    {fprintf(LC,");");}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 314 "syntaxe.y"
    {fprintf(LC,"\n\tswitch(%s){",valIdentif);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 314 "syntaxe.y"
    {fprintf(LC,"\n\t}");;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 315 "syntaxe.y"
    {fprintf(LC,"\n\tfor(%s=",valIdentif);strcpy(dec,valIdentif);;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 315 "syntaxe.y"
    {fprintf(LC," %s ;",valIdentif);;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 315 "syntaxe.y"
    {fprintf(LC," %s<%s ; %s++){",dec,valIdentif,dec);;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 315 "syntaxe.y"
    {fprintf(LC,"\n\t}");;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 325 "syntaxe.y"
    {strcpy(valIdentif,val);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 327 "syntaxe.y"
    {fprintf(LC,"\n\t\tcase ");}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 327 "syntaxe.y"
    {fprintf(LC,":");}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 328 "syntaxe.y"
    {fprintf(LC,"\n\t\tcase ");}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 328 "syntaxe.y"
    {fprintf(LC,":");}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 330 "syntaxe.y"
    {fprintf(LC,"\n\t\t\tbreak;");}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 331 "syntaxe.y"
    {fprintf(LC,"\n\t\t\tbreak;");}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 333 "syntaxe.y"
    {fprintf(LC,"\n\t\tdefault :");;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 333 "syntaxe.y"
    {fprintf(LC,"\n\t\t\tbreak;");}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 335 "syntaxe.y"
    {fprintf(LC,"\n\t}");}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 336 "syntaxe.y"
    {fprintf(LC,"\n\t}else {");;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 336 "syntaxe.y"
    {fprintf(LC,"\n\t}");}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 340 "syntaxe.y"
    {yyerror("erreur : unknown type name << string >> ,try with VAR name[M] : CHAR");exit(-1);;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 342 "syntaxe.y"
    {yyerror("erreur : unknown type name << ");printf("%s >>",valIdentif);exit(-1);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 345 "syntaxe.y"
    {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);};}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 346 "syntaxe.y"
    {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);};}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 347 "syntaxe.y"
    {if(PARTIE_INST){
                    if(!AFF_STR)fprintf(LC,"%s",val);
                    else if(AFF_STR)fprintf(LC,"\n\tstrcat(%s,%s);",IDN_AFF_STR,val);
                }
            ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 352 "syntaxe.y"
    {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);};}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 354 "syntaxe.y"
    {if(OPR_NULL){if(strchr(val,'+') || strchr(val,'-'))OPR_NULL=0;else{yyerror("syntaxe error");exit(-1);}};}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 355 "syntaxe.y"
    {isDeclared(valIdentif);if(OPR_NULL){yyerror("syntaxe error");exit(-1);} if(!AFF_STR)fprintf(LC,"%s",valIdentif);else AFF_STR_IDN();;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 356 "syntaxe.y"
    {isDeclared(valIdentif);if(OPR_NULL){yyerror("syntaxe error");exit(-1);}if(!AFF_STR)fprintf(LC,"%s",valIdentif);;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 358 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC," || ");else{yyerror(strError);exit(-1);};}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 359 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC," && ");else{yyerror(strError);exit(-1);};}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 360 "syntaxe.y"
    {if(AFF_STR){yyerror(strError);exit(-1);};}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 361 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,"(");;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 361 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,")");;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 362 "syntaxe.y"
    {isFUNCTION(valIdentif);if(!AFF_STR)fprintf(LC,"%s(",valIdentif);;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 362 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,")");;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 366 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,",");;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 368 "syntaxe.y"
    {OPR_NULL=1;;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 369 "syntaxe.y"
    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"+");;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 370 "syntaxe.y"
    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"-");      else{yyerror(strError);exit(-1);};}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 371 "syntaxe.y"
    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"/");      else{yyerror(strError);exit(-1);};}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 372 "syntaxe.y"
    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"%c",'%'); else{yyerror(strError);exit(-1);};}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 373 "syntaxe.y"
    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"*");      else{yyerror(strError);exit(-1);};}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 375 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,">"); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 376 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,"<"); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 377 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,">=");;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 378 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,"<=");;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 379 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,"==");;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 380 "syntaxe.y"
    {if(!AFF_STR)fprintf(LC,"!=");;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 382 "syntaxe.y"
    {type_idn(valIdentif);;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 383 "syntaxe.y"
    {type_idn(valIdentif);;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 384 "syntaxe.y"
    {if(OUTPUT_ZON)add_str_OUTPUT(val);
                                   else {
                                       yyerror("syntaxe error : can't add string to Lire");
                                       printf("\n\t\t\tLire(..%s",val);
                                       exit(-1);
                                   };}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 390 "syntaxe.y"
    {type_idn(valIdentif);;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 391 "syntaxe.y"
    {type_idn(valIdentif);;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 392 "syntaxe.y"
    {if(OUTPUT_ZON)add_str_OUTPUT(val);
                                   else {
                                       yyerror("syntaxe error : can't add string to Lire ");
                                       printf("\n\t\t\tLire(..%s",val);
                                       exit(-1);
                                   };}
    break;



/* Line 1455 of yacc.c  */
#line 2642 "syntaxeY.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 400 "syntaxe.y"

void yyerror( const char * msg){
    /* system("CLS"); */
    printf("(%s) line %d : %s",nameFile, yylineno, msg);
}
int main(int argc,char ** argv){
    if(argc > 1) {
        strcpy(nameFile,argv[1]);
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return (1);
        }
        
    }// vérifier résultat !!!
    /* yyparse(); */
    if(!yyparse())printf("Expression correct\n");
    return(0);
}
