#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

#define DIM 8

using namespace std;

class Chromosome{
	std::vector<int> permutations;
public:
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

int main(){
	srand (time(NULL));

	Chromosome* test;
	long int aux,i=0;
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
	}
	return 0;
}