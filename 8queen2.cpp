#include <bits/stdc++.h>

#define DIM 8
#define GEN 100
#define QNT_ESCOLHIDOS 2
#define MUT_RATE 4

using namespace std;

class Chromosome{
	
public:
	std::vector<int> permutations;
	Chromosome();
	void displayPermutation();
	void printBoard();
	int check();
	bool operator<(Chromosome& b);
  	void mutation();
};

Chromosome::Chromosome(){	
	for(int i=0;i<DIM;i++){
		this->permutations.push_back(i);
	}

	//Generates a random-permutation using Fisher-Yates algorithm.
	for(int i=DIM-1;i>0;i--){
		int rand_position = rand()%(i+1); //Gera a posicao
		//Faz a troca
		int aux = this->permutations[rand_position];
		this->permutations[rand_position] = this->permutations[i];
		this->permutations[i]=aux;
	}
}

void Chromosome::displayPermutation(){
	cout <<"\tPermutations: ";
	for(int i=0;i < this->permutations.size();i++){
		cout <<this->permutations[i]<<" ";
	}
	cout<<endl;		
}
void Chromosome::printBoard(){
	for(int i=0;i<DIM;i++){
		cout<<endl;
		for(int j=0; j<DIM;j++){
			if(this->permutations[i]==j) cout <<"@ ";
			else cout <<"- ";
		}		
	}
}
int Chromosome::check(){
	int num_checks = 0;
	for(int i=0; i<DIM;i++){
		for(int j=i+1; j<DIM;j++){
			if(this->permutations[j] == (this->permutations[i]+(j-i))) num_checks++;
			if(this->permutations[j] == (this->permutations[i]-(j-i))) num_checks++;
		}
	}
	return num_checks;
}
bool Chromosome::operator<(Chromosome& b){
    return this->check() < b.check();
}
void Chromosome::mutation(){
    printf("\n====================================================\n====================== Mutacao =====================\n====================================================\n");
  	
    if((1+rand()%10)<=MUT_RATE){
		int pos1 = rand()%DIM;
		int pos2;
		do {
		   pos2 = rand()%DIM;
		} while (pos2 == pos1);
        
        int aux = this->permutations[pos1];
        this->permutations[pos1] = this->permutations[pos2];
        this->permutations[pos2] = aux;
      	printf("> Mutacao:\n\t%d <--> %d\n",pos1, pos2);
      	this->displayPermutation();
	}
	else{
		printf("> Nao houve Mutacao<\n");
	}
}


/* void troca (Chromosome *A, Chromosome *B) {
 // printf("(troca entra) Ordena"); 
	Chromosome t;
	t = *A;
	*A = *B;
	*B = t;
	 // printf("(troca sai) Ordena");
}

void Ordena (Chromosome v[], int p, int r) {
	int count = 0;
    if (p < r) {
    	// printf("Ordena %d\n", count++);
		int i = p-1, j = r;
		// printf("Ordena %d\n", count++);
		Chromosome c = v[r];
		// printf("Ordena %d\n", count++);
		while (1) { 
			// printf("(while 1) Ordena %d\n", count++);
		 while (v[++i].check() < c.check()) ;
		 // printf("(while 2) Ordena %d\n", count++);
		 while (c.check() < v[--j].check()) if (j == p) break;
		  // printf("(while 3) Ordena %d\n", count++);
		 if (i > j) break;
		 troca (&v[i], &v[j]);
		}
		troca (&v[i], &v[r]);
		Ordena (v, p, j);
		Ordena (v, i+1, r);
    }
} */

void Cross_over (Chromosome *pai_1, Chromosome *pai_2, Chromosome *filho_1, Chromosome *filho_2){
	printf("\n====================================================\n==================== Cross-over ====================\n====================================================\n");
  	printf("> Pais:\n");
	pai_1->displayPermutation();
	pai_2->displayPermutation();

	bool visitadosFilho_1[DIM];
	bool visitadosFilho_2[DIM];

	for (int i = 0; i < DIM; ++i)
	{
		visitadosFilho_1[i] = false;
		visitadosFilho_2[i] = false;
	}

	if((1+rand()%10)!=10){
		int pos = 1+rand()%(DIM-2);
		printf("> Cross-over na posicao: %d\n",pos );
		for (int i = 0; i < pos; ++i)
		{
			visitadosFilho_1[filho_1->permutations[i]] = true;
			visitadosFilho_2[filho_2->permutations[i]] = true;
		}

		int i=pos;
		int j=pos; // tem que comecar a partir da posicao do array seguinte do corte

		do{
			if(i < DIM){
				if(!visitadosFilho_1[pai_2->permutations[i]]){
					filho_1->permutations[j] = pai_2->permutations[i];
					visitadosFilho_1[pai_2->permutations[i]] = true;
					i++;
					j++;
				}else{
					i++;
				}
			}else{
				for (int k = 0; k < pos; ++k)
				{
					if(!visitadosFilho_1[pai_2->permutations[k]]){
						filho_1->permutations[j] = pai_2->permutations[k];
						j++;
			        }
				}
			}

		}while(j < DIM);

		i=pos;
		j=pos;

		do{
			if(i < DIM){
				if(!visitadosFilho_2[pai_1->permutations[i]]){
					filho_2->permutations[j] = pai_1->permutations[i];
					visitadosFilho_2[pai_1->permutations[i]] = true;
					i++;
					j++;
				}else{
					i++;
				}
			}else{
				for (int k = 0; k < pos; ++k)
				{
					if(!visitadosFilho_2[pai_1->permutations[k]]){
						filho_2->permutations[j] = pai_1->permutations[k];
						j++;
					}
				}
			}

		}while(j < DIM);
	}
	else{
		printf("> Não ocorreu Cross-over <\n");
	}
  	printf("> Filhos:\n");
  	filho_1->displayPermutation();
	filho_2->displayPermutation();
	//printf("====================================================\n");
}

int main(){
srand (time(NULL));
int soma_iterac=0;
int zero_sum=0;

	for(int k=0; k<100;k++){

		Chromosome* test;
		long int aux,i=0;
		Chromosome selecao[QNT_ESCOLHIDOS];
		Chromosome geracao[GEN];
		Chromosome filho_1,filho_2;
		int posicoes[QNT_ESCOLHIDOS];
		int iterac;

		printf("\n");
		
		for(iterac=0; iterac < 10000; iterac++){
			int sum_fit=0;
			printf("\n====================================================\n=================== Iteracao: %d ===================\n====================================================\n",iterac);
			sort(geracao,geracao + GEN);
			int maxfit = geracao[GEN-1].check();
			for(int i=0; i < GEN; i++){
				cout << geracao[i].check() << " ";
			}
			cout << endl;
			if(!geracao[0].check()) break;

		 	for(int i=GEN-1;i>0;i--){
				int rand_position = rand()%(i+1); //Gera a posicao
				//Faz a troca
				Chromosome aux = geracao[rand_position];
				geracao[rand_position] = geracao[i];
				geracao[i] = aux;
			}

			
			for (int i = 0; i < GEN; ++i)
			{			
				sum_fit += geracao[i].check();
			}

			int r1 = rand()%(sum_fit+1);
			int i1=0;
			while(r1>0){
				r1-= (maxfit - geracao[i1].check()+1);
				i1++;
			}
			selecao[0] = geracao[i1-1];
			int i2=0;
			do {
				int r2 = rand()%(sum_fit+1);
				i2=0;
				while(r2>0){
					r2-= (maxfit - geracao[i2].check()+1);
					i2++;
				}
				selecao[1] = geracao[i2-1];
			} while (i1-1 == i2);


			printf("2 selecionados:\n");
			for (int i = 0; i < QNT_ESCOLHIDOS; i++){
				printf("%d ", selecao[i].check());
			}
			printf("\n\n");


			sort(selecao,selecao + QNT_ESCOLHIDOS);
			//Ordena(selecao, 0, QNT_ESCOLHIDOS-1);

		 		printf("5 selecionados ordenado:\n");
			for (int i = 0; i < 2; i++)
			{
				printf("%d ", selecao[i].check());
			}
			printf("\n\n"); 
			

			filho_1 = selecao[0];
			filho_2 = selecao[1];

			Cross_over (&selecao[0], &selecao[1], &filho_1, &filho_2);
			
			filho_1.mutation();
			filho_2.mutation();


			//sort(geracao,geracao + GEN);
			//Ordena(geracao, 0, GEN-1);

			printf("\n> Selecao de sobreviventes <\n\n");
			printf("%d %d\n", geracao[GEN-2].check(), geracao[GEN-1].check());
				
			if(filho_1.check() < filho_2.check()){
				if(filho_1.check() < geracao[GEN-2].check()){
					geracao[GEN-2] = filho_1;
					if(filho_2.check() < geracao[GEN-1].check()){
						geracao[GEN-1] = filho_2;
					}
				}else if(filho_1.check() < geracao[GEN-1].check()){
					geracao[GEN-1] = filho_1;
				}
			}else{
				if(filho_2.check() < geracao[GEN-2].check()){
					geracao[GEN-2] = filho_2;
					if(filho_1.check() < geracao[GEN-1].check()){
						geracao[GEN-1] = filho_1;
					}
				}else if(filho_2.check() < geracao[GEN-1].check()){
					geracao[GEN-1] = filho_2;
				}
			}
			printf("%d %d\n", geracao[GEN-2].check(), geracao[GEN-1].check());
			
		}
		if(iterac==0) zero_sum++;
		cout << "Melhor individuo:"<< endl;
		geracao[0].displayPermutation();
		cout << "Check: "<< geracao[0].check() << endl;	
	
		soma_iterac += iterac;

	}

	printf("qtdzero: %d media:%f\n media_real: %f",zero_sum, soma_iterac/100.0, soma_iterac/(100.0-zero_sum) );

	return 0;
}