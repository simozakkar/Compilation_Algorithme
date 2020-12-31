bison -d -o syntaxeY.c syntaxe.y
flex -olexique.c lexique.l
gcc -o compiler syntaxeY.c lexique.c
compiler CodeTest.txt