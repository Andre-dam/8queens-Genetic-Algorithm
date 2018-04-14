//#include <iostream>
//#include <cstdlib>
#include <bits/stdc++.h>
//#include <vector>
//#include <time.h>

#define DIM 8
#define GEN 100

using namespace std;

class Chromosome{
	
public:
	std::vector<int> permutations;
	Chromosome();
	void displayPermutation();
	void printBoard();
	int check();
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
	cout <<"Permutations: ";
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

bool Compare(Chromosome i, Chromosome j){ return (i.check()<i.check());}

int main(){
	srand (time(NULL));

	Chromosome* test;
	long int aux,i=0;

	Chromosome geracao[GEN];
	printf("\n");

	for(int i=GEN-1;i>0;i--){
		int rand_position = rand()%(i+1); //Gera a posicao
		//Faz a troca
		Chromosome aux = geracao[rand_position];
		geracao[rand_position] = geracao[i];
		geracao[i] = aux;
	}

	Chromosome selecao[5];

	for (int i = 0; i < 5; i++)
	{
		selecao[i] = geracao[i];
	}




		for (int i = 0; i < 5; i++)
	{
		printf("%d\n", selecao[i].check());
	}
	printf("\n");

	Chromosome aux1;

   for (int i = 0; i < 5-1; i++)  {    
       // Last i elements are already in place   
       for (int j = 0; j < 5-i-1; j++){ 
           if (selecao[j].check() > selecao[j+1].check()){
           		aux1 = selecao[j];
           		selecao[j] = selecao[j+1];
           		selecao[j+1] = aux1;
            }
        }
    }


	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", selecao[i].check());
	}

	Chromosome son1,son2;

	son1 = selecao[0];
	son2 = selecao[1];

	bool son1_[8];
	bool son2_[8];

	for (int i = 0; i < 8; ++i)
	{
		son1_[i] = false;
		son2_[i] = false;
	}



	printf("cross\n");

	son1.displayPermutation();
	son2.displayPermutation();

	if((1+rand()%10)!=10){
		int pos = 1+rand()%6;
		printf("pos: %d\n",pos );
		for (int i = 0; i < pos; ++i)
		{
			son1_[son1.permutations[i]] = true;
			son2_[son2.permutations[i]] = true;
		}

		int i=pos;
		int j=pos;

		do{
			if(i<8){
				if(son1_[selecao[1].permutations[i]]){
					son1.permutations[j] = selecao[1].permutations[i];
					i++;
					j++;
				}else{
					i++;
				}
			}else{
				for (int k = 0; k < pos; ++k)
				{
					son1.permutations[j] = selecao[0].permutations[k];
					j++;
				}
			}

		}while(j<7);
		i=pos;
		j=pos;


		do{
			if(i<8){
				if(son2_[selecao[0].permutations[i]]){
					son2.permutations[j] = selecao[0].permutations[i];
					i++;
					j++;
				}else{
					i++;
				}
			}else{
				for (int k = 0; k < pos; ++k)
				{
					son2.permutations[j] = selecao[1].permutations[k];
					j++;
				}
			}

		}while(j<7);
	}
	son1.displayPermutation();
	son2.displayPermutation();
	selecao[0].displayPermutation();
	selecao[1].displayPermutation();
	
	/*
	while(true){
		system("clear");
		i++;
		cout<<"Number of iterations :"<<i<<endl;
		test = new Chromosome();
		test->displayPermutation();
		aux = test->check();
		cout <<"checks: "<<aux;
		test->printBoard();
		if(!aux) break;
		cout<<endl<<endl;
	}*/
	return 0;
}