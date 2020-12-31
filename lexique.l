%option yylineno
%option noyywrap
%{
/*Réalisé par: EZ-ZAKKAR Mohammed && ELmoumny Azddine && Aalloul Outmane && AMAACH Amine SMI-S6*/
#include <string.h>
#include "syntaxeY.h"
char valIdentif[50];
char valtype[50];
char  strval[50];
char val[50];
%}
nbr [0-9]
lettre [A-Za-z]
SP  [!-+:-@[-`‘-”]
%%


[" "\t\n]                               { /* rien */ }

[-|+]?{nbr}+                                  { /*  yylval= atoi(yytext); */strcpy(val,yytext); return ENTIER; };
[-|+]?{nbr}+"."{nbr}+                         { /* valReel = atof(yytext); */strcpy(val,yytext); return REEL; };
"'"{lettre}"'"                          { strcpy(val,yytext); return CHAR; };
"\""({lettre}|" "|{nbr}|{SP})*"\""      { strcpy(val,yytext); return STRING; };
{lettre}({lettre}|{nbr})*"["{nbr}*"]"   { strcpy(valIdentif, yytext);strcpy(strval, yytext);strcpy(val, yytext); return ARRAY; };
"vaut"                                  { return VAUT; };
"ENTIER"|"entier"                       { strcpy(valtype, "int"); return ENTIERTYPE; };
"REEL"|"reel"                           { strcpy(valtype, "float"); return REELTYPE; };
"CHAR"|"char"                           { strcpy(valtype, "char"); return CHARTYPE; };
"STRING"|"string"                       { strcpy(valtype, "char *"); return STRINGTYPE; };
"Break"|"break"                         { return BREAK; };

"CONST"|"const"                         { return CONST; };
"VAR"|"var"                             { return VAR; };
"TantQue"|"tantque"                     { return WHILE; };
"FinTantQue"|"fintantque"               { return FINWH; };
"Faire"|"faire"                         { return DO; };
"Si"|"si"                               { return SI; };
"Sinon"|"sinon"                         { return SINON; };
"Alors"|"alors"                         { return ALORS; };
"FinSi"|"finsi"                         { return FINSI; };
"Cas"|"cas"                             { return SWITCH; };
"FinCas"|"fincas"                       { return FINSW; };
"REP"|"rep"                             { return REP; };
"JUS"|"jus"                             { return JUS; };
"Pour"|"pour"                           { return POUR; };
"FinPour"|"finpour"                     { return FINPOUR; };
"Renvoyer"|"renvoyer"                   { return RETURN; };

"=="                                    { return EGAL; };
"<>"                                    { return DIFF; };
"="                                     { return AFFECT; };
"+"                                     { return PLUS;};
"*"                                     { return MUL;};
"/"                                     { return DIV;};
"-"                                     { return SSTRA;};
"%"                                     { return MOD;};
"ET"                                    { return ET;};
"OU"                                    { return OU;};
">"                                     { return Sup;};
"<"                                     { return Inf;};
">="                                    { return SupEQ;};
"<="                                    { return InfEQ;};

";"                                     { return PTVIRG;};

"Lire"|"lire"                           { return INPUT;};
"Ecrire"|"ecrire"                       { return OUTPUT;};

"Fonction"|"fonction"                   { return FUN;};
"Procedure"|"procedure"                 { return PROC;};

"Algorithme"|"algorithme"	            { return Algo;};
"Debut"|"debut"                         { return Debut ; };
"Fin"|"fin"                             { return Fin; };

{lettre}({lettre}|{nbr})*               { strcpy(valIdentif, yytext);strcpy(strval, yytext);strcpy(val, yytext);  return IDENTIF; };
"{"({lettre}|{nbr}|\n|" "|\t|{SP})*"}"	{ strcpy(valIdentif, yytext);return Comment;};
.                                       { return yytext[0]; };

%%

/* int valNombre;
int yylval;
float valReel; */

/* 
int yywrap(void) {
    return 1;
} */