%{/*-------- syntaxe.y -----------*/
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
%}
%token ENTIERTYPE BREAK REEL CHAR STRING ENTIER CONST VAR IDENTIF FINWH WHILE DO SI 
%token SINON ALORS FINSI SWITCH FINSW REP JUS POUR FINPOUR EGAL DIFF AFFECT PLUS MUL 
%token DIV SSTRA MOD ET OU Sup Inf SupEQ InfEQ OUTPUT INPUT FUN PROC TAB Debut Fin Algo 
%token Comment PTVIRG  VAUT ARRAY  REELTYPE CHARTYPE STRINGTYPE RETURN

%start code // z de notre grammaire
%%
code :
    {
    LC=fopen("headerFile.h","w");
    fprintf(LC,"#include<stdio.h>\n#include<string.h>\n#include<stdlib.h>");
    }
    FUNCTIONS 
    Algo IDENTIF {
    fclose(LC);
    strcat(valIdentif, ".c");
    LC=fopen(valIdentif,"w");
    fprintf(LC,"#include\"headerFile.h\"\nint main(){\n\n");
    } PTVIRG declaration  
    Debut 
    {PARTIE_INST=1;}
    listInstr 
    Fin
    {
    PARTIE_INST=0;
    fprintf(LC,"\n\treturn 0;\n}");
    fclose(LC);
    /* aff(); */
    }
;
FUNCTIONS : 
                    | FUNCTIONS FUN IDENTIF {strcpy(FUN_list[++i_tab_FUN][1],"F");strcpy(FUN_list[i_tab_FUN][0],valIdentif);strcpy(dec,valIdentif);strcat(dec,"(");} 
                        '(' {FUN_ARG_ZONE=1;} Arglist {FUN_ARG_ZONE=0;} ')'
                        ':'type {
                            fprintf(LC,"\n%s %s){\n",valtype,dec);
                            if(!strcmp(valtype,"int"))strcat(FUN_list[i_tab_FUN][1],"d");
                            else if(!strcmp(valtype,"float"))strcat(FUN_list[i_tab_FUN][1],"f");
                                else strcat(FUN_list[i_tab_FUN][1],"c");
                        }
                        declaration  
                        Debut 
                        {PARTIE_INST=1;}
                        listInstr 
                        Fin {PARTIE_INST=0;
                            fprintf(LC,"\n}");
                            i_tab=-1;
                        }
                    | FUNCTIONS PROC {PROC_ZONE=1;} IDENTIF {strcpy(FUN_list[++i_tab_FUN][1],"P");strcpy(FUN_list[i_tab_FUN][0],valIdentif);strcpy(dec,valIdentif);strcat(dec,"(");} 
                        '(' {FUN_ARG_ZONE=1;} Arglist {FUN_ARG_ZONE=0;} ')'
                        {
                            fprintf(LC,"\nvoid %s){\n",dec);
                        }
                        declaration  
                        Debut 
                        {PARTIE_INST=1;}
                        listInstr 
                        Fin {PARTIE_INST=0;
                            fprintf(LC,"\n}");
                            i_tab=-1;
                            PROC_ZONE=0;
                        }
;
varArg : IDENTIF
       | ARRAY
;
Arg : varArg         {add_idn(valIdentif);}
    | Arg ',' varArg {add_idn(valIdentif);}
;
Arglist : Arg ':' type                                {add_type_idn(valtype);}
        | Arglist ','{strcat(dec,",");} Arg ':' type  {add_type_idn(valtype);}
;
declaration : 
            | declaration VAR {typeVAR=0;} listdec  
            | declaration CONST {typeVAR=1;} listdec  
;

listdec : 
        | listdec namelist ':' type PTVIRG {
        if(typeVAR) fprintf(LC ,"\tconst %s %s;\n",valtype,dec);
        else fprintf(LC ,"\t%s %s;\n",valtype,dec);
        add_type_idn(valtype);
    }
;
namelist : variable {
                    strcpy(dec,valIdentif);
                    add_idn(valIdentif);
                    if(DEC_AFF){
                        strcat(dec," = ");
                        strcat(dec,val);
                        DEC_AFF=0;
                    }
    }
    | namelist ','{strcat(dec," , ");} variable {
            strcat(dec,valIdentif);
            add_idn(valIdentif);
            if(DEC_AFF){
                strcat(dec," = ");
                strcat(dec,val);
                DEC_AFF=0;
            }
    }
;
variable : ARRAY
         | IDENTIF
         | IDENTIF AFFECT VALUE {DEC_AFF = 1;}
         | ARRAY AFFECT VALUE {DEC_AFF = 1;}
;
listInstr : 
            | listInstr IDENTIF '(' {isFUNCTION(valIdentif);fprintf(LC,"\n\t%s(",valIdentif);} explist ')' {fprintf(LC,")");} PTVIRG {fprintf(LC,";");}
            | listInstr IDENTIF AFFECT {CHECK_STR_AFF();} exp PTVIRG {if(!AFF_STR)fprintf(LC,";");AFF_STR=0;}
            | listInstr ARRAY AFFECT {fprintf(LC,"\n\t%s=",valIdentif);isDeclared(valIdentif);} exp PTVIRG {fprintf(LC,";");}
            | listInstr PTVIRG
            | listInstr RETURN ReturnList PTVIRG {fprintf(LC,"\n\treturn %s;",val);if(PROC_ZONE){yyerror("can't use renvoyer !!");exit(-1);}}
            | listInstr OUTPUT {OUTPUT_ZON=1;} '(' {fprintf(LC,"\n\tprintf(\"");} valuelist ')' {add_tab_op_idn();{OUTPUT_ZON=0;} }
            | listInstr INPUT '('{fprintf(LC,"\n\tscanf(\"");} valuelist ')'{add_tab_op_idn();}
            | listInstr Comment {add_COMMENT(valIdentif);}
            | listInstr SI '(' {fprintf(LC,"\n\tif(");} exp ')' ALORS {fprintf(LC,"){");} listInstr suiteCondition
            | listInstr WHILE '('{fprintf(LC,"\n\twhile(");} exp ')' DO {fprintf(LC,"){");} listInstr FINWH {fprintf(LC,"\n\t}")}
            | listInstr REP {fprintf(LC,"\n\tdo{");} listInstr JUS '(' {fprintf(LC,"\n\t}while(");} exp ')'{fprintf(LC,");")}
            | listInstr SWITCH IDENTIF {fprintf(LC,"\n\tswitch(%s){",valIdentif);} VAUT suiteSwitch FINSW {fprintf(LC,"\n\t}");}
            | listInstr POUR IDENTIF {fprintf(LC,"\n\tfor(%s=",valIdentif);strcpy(dec,valIdentif);} ValuePour {fprintf(LC," %s ;",valIdentif);} '_' ValuePour {fprintf(LC," %s<%s ; %s++){",dec,valIdentif,dec);} listInstr FINPOUR {fprintf(LC,"\n\t}");}
;
ReturnList : ENTIER 
            | REEL     
            | STRING   
            | CHAR         
            | IDENTIF
            | ARRAY 
;   
ValuePour : IDENTIF
          | ENTIER {strcpy(valIdentif,val);}
;
ValuelistSW : {fprintf(LC,"\n\t\tcase ")} VALUE {fprintf(LC,":")}
            | ValuelistSW ',' {fprintf(LC,"\n\t\tcase ")} VALUE {fprintf(LC,":")}
;
Case : ValuelistSW ':' listInstr BREAK {fprintf(LC,"\n\t\t\tbreak;")}
      | Case ValuelistSW ':' listInstr BREAK {fprintf(LC,"\n\t\t\tbreak;")}
suiteSwitch : Case
            | Case SINON {fprintf(LC,"\n\t\tdefault :");} ':' listInstr BREAK {fprintf(LC,"\n\t\t\tbreak;")}
;
suiteCondition : FINSI {fprintf(LC,"\n\t}")}
              | SINON {fprintf(LC,"\n\t}else {");} listInstr FINSI {fprintf(LC,"\n\t}")}
;
type :ENTIERTYPE
    | REELTYPE
    | STRINGTYPE {yyerror("erreur : unknown type name << string >> ,try with VAR name[M] : CHAR");exit(-1);}
    | CHARTYPE
    | IDENTIF    {yyerror("erreur : unknown type name << ");printf("%s >>",valIdentif);exit(-1);}
;

VALUE : ENTIER {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);}}
    | REEL     {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);}}
    | STRING   {if(PARTIE_INST){
                    if(!AFF_STR)fprintf(LC,"%s",val);
                    else if(AFF_STR)fprintf(LC,"\n\tstrcat(%s,%s);",IDN_AFF_STR,val);
                }
            }
    | CHAR     {if(PARTIE_INST && !AFF_STR)fprintf(LC,"%s",val);else if(AFF_STR){yyerror(strError);exit(-1);}}    
;
exp : VALUE    {if(OPR_NULL){if(strchr(val,'+') || strchr(val,'-'))OPR_NULL=0;else{yyerror("syntaxe error");exit(-1);}}}
    | IDENTIF  {isDeclared(valIdentif);if(OPR_NULL){yyerror("syntaxe error");exit(-1);} if(!AFF_STR)fprintf(LC,"%s",valIdentif);else AFF_STR_IDN();}
    | ARRAY    {isDeclared(valIdentif);if(OPR_NULL){yyerror("syntaxe error");exit(-1);}if(!AFF_STR)fprintf(LC,"%s",valIdentif);}      
    | exp opr exp 
    | exp OU {if(!AFF_STR)fprintf(LC," || ");else{yyerror(strError);exit(-1);}} exp 
    | exp ET {if(!AFF_STR)fprintf(LC," && ");else{yyerror(strError);exit(-1);}} exp 
    | exp CMP {if(AFF_STR){yyerror(strError);exit(-1);}} exp
    | '(' {if(!AFF_STR)fprintf(LC,"(");} exp ')' {if(!AFF_STR)fprintf(LC,")");}
    | IDENTIF '(' {isFUNCTION(valIdentif);if(!AFF_STR)fprintf(LC,"%s(",valIdentif);} explist ')' {if(!AFF_STR)fprintf(LC,")");}
;

explist : exp            
        | explist ',' {if(!AFF_STR)fprintf(LC,",");} exp 
;
opr : {OPR_NULL=1;}
    | PLUS   {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"+");}
    | SSTRA  {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"-");      else{yyerror(strError);exit(-1);}}
    | DIV    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"/");      else{yyerror(strError);exit(-1);}}
    | MOD    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"%c",'%'); else{yyerror(strError);exit(-1);}}
    | MUL    {OPR_NULL=0;if(!AFF_STR)fprintf(LC,"*");      else{yyerror(strError);exit(-1);}}   
;
CMP : Sup   {if(!AFF_STR)fprintf(LC,">"); }
    | Inf   {if(!AFF_STR)fprintf(LC,"<"); }
    | SupEQ {if(!AFF_STR)fprintf(LC,">=");}
    | InfEQ {if(!AFF_STR)fprintf(LC,"<=");}
    | EGAL  {if(!AFF_STR)fprintf(LC,"==");}
    | DIFF  {if(!AFF_STR)fprintf(LC,"!=");}
;
valuelist : ARRAY                 {type_idn(valIdentif);}
          | IDENTIF               {type_idn(valIdentif);}
          | STRING                {if(OUTPUT_ZON)add_str_OUTPUT(val);
                                   else {
                                       yyerror("syntaxe error : can't add string to Lire");
                                       printf("\n\t\t\tLire(..%s",val);
                                       exit(-1);
                                   }}
          | valuelist ',' IDENTIF {type_idn(valIdentif);}
          | valuelist ',' ARRAY   {type_idn(valIdentif);}
          | valuelist ',' STRING  {if(OUTPUT_ZON)add_str_OUTPUT(val);
                                   else {
                                       yyerror("syntaxe error : can't add string to Lire ");
                                       printf("\n\t\t\tLire(..%s",val);
                                       exit(-1);
                                   }}
;

%%
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