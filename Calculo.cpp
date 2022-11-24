#include <stdio.h>
#include <conio.h>  
#include <stdlib.h>
#include <locale.h> 
#include <string.h> 
#include <ctype.h>

// Cálculo: (M1*3+M2*3=M3*4)/10=MA

typedef struct tmateria{
	char nome[50];
	float nota[3], multiNota[3], media, falta;
}Cadastro;

Cadastro aluno[50];

void linha(){
	printf("\n------------------------------");
}

float mediaAtual(int i){
	float media;
	
	for(int j=0;j<2;j++){
		media+=aluno[i].nota[j]*3;
	}
	
	return media/10;
		
}

float notaFaltante (int i){
	return (aluno[i].media-5)*-1;
}

void escreverHistorico (int cont, FILE *notas){
	notas=fopen("Notas.txt", "a");
	for(int i=0; i<=cont; i++){
		fprintf(notas,"Matéria: %s", aluno[i].nome);
		for(int j=0;j<2;j++){
			fprintf(notas,"\nNota do %dº Trimestre:%.1f", j+1, aluno[i].nota[j]);
			fprintf(notas,"\nNota Multiplicada:%.1f",aluno[i].nota[j]*3);
		}
		fprintf(notas,"\nMedia Atual:%.1f",aluno[i].media);
			if(aluno[i].media>5)
				fprintf(notas,"\nParabéns você não está de PFV nessa matéria");
					
			else{
				fprintf(notas,"\nNota Faltante:%.1f",aluno[i].falta);
			}
		fprintf(notas,"\n------------------------------\n");
	}

					
	
	fclose(notas);
	return true;
}

int main(){
	int cont=-1, escolha, opc;
	char SouN;
	FILE *notas;
	
	notas=fopen("Notas.txt", "r");
	if(notas== NULL){
		printf("Erro [404] O arquivo não existe.");
		system("pause");
		return 0;
	}
	fclose(notas);
	
	setlocale(LC_ALL, "portuguese");
	
	do{
		system("cls");
		printf("::::::::::Menu::::::::::");
		printf("\n1-Cadastra\n2-Mostra\n0-Sair\n");
		scanf("%d", &opc);
		switch(opc){
			case 1:{
				cont++;
				system("cls");
				printf("::::::::::Média Anual::::::::::");
				printf("\nDigite o nome da matéria:");
				scanf("%s", &aluno[cont].nome);
		
				for(int i=0;i<2;i++){
					printf("\nDigita a nota do %dºTrimeste:", i+1);
					scanf("%f", &aluno[cont].nota[i]);
				}
				
				aluno[cont].media=mediaAtual(cont);
				
				if(aluno[cont].media<5)
						aluno[cont].falta=notaFaltante(cont);
				
				escreverHistorico(cont, notas);
				
				printf("\nDeseja continuar? S/N");
				SouN=toupper(getche());
		
				if(SouN == 'N') break;
			break;}
			case 2:{
				system("cls");
				printf("::::::::::Médias::::::::::");
				for(int i=0;i<=cont;i++){
					printf("\nMatéria: %s", aluno[i].nome);
					for(int j=0;j<2;j++){
						printf("\nNota do %dº Trimestre:%.1f", j+1, aluno[i].nota[j]);
						printf("\nNota Multiplicada:%.1f",aluno[i].nota[j]*3);
					}
					
					printf("\nMedia Atual:%.1f", aluno[i].media);
					if(aluno[i].media>5)
						printf("\nParabéns você não está de PFV nessa matéria");
					
					else{
						aluno[i].falta=notaFaltante(i);
						printf("\nNota Faltante:%.1f", aluno[i].falta);
					}
					linha();
				}
				system("pause")	;
			break;}
			
		}
	}while(opc != 0);
	
}
