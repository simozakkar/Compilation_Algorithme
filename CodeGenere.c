#include"headerFile.h"
int main(){

	int A , B = -6 , Som , P = -66;
	int i = +6 , k[4];
	const char str1[40] = "Hello ";
	const char str2[40] = "World !";
	const int s;
	char str3[30];

	printf("A:");
	scanf("%d",&A);
	printf("B:");
	scanf("%d",&B);
	A=A+B-3+3;
	Som=somme(A,B);
	Afficher(Som);
	scanf("%d%d",&P,&i);
	strcpy(str3,"");
	strcat(str3,str1);
	strcat(str3,str2);
	printf("%s",str3);
	scanf("%s",str3);
	printf("%s",str3);
	P=4;
	switch(P){
		case 1:
		case 5:
	printf("La somme de A et B est impaire");
			break;
		case 2:
	printf("La somme de A et B est impaire");
			break;
		default :
	printf("La somme de A et B est paire");
			break;
	}
	if(Som>10){
	printf("La somme de A et B est %d>10\n",Som);
	}else {
	printf("La somme de A et B est %d<10\n",Som);
	}
	do{
	scanf("%d",&i);
	}while(i>5);
	for(i= 0 ; i<10 ; i++){
	printf("HI\n");
	}
	while(i>9){
	printf("i>9");
	i=8;
	}
	return 0;
}