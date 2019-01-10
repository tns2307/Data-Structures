#include <stdio.h>
#include <stdlib.h>

struct Data{
	int price;
	int total;
	struct Data *next;
}*head, *tail, *curr;

struct Data* createNode(int price, int total){
	struct Data *temp = (struct Data*)malloc(sizeof(struct Data));
	temp->price = price;
	temp->total = total;
	temp->next = NULL;
	return temp;
}

void push(int price, int total){
	struct Data *temp = createNode(price, total);
	if (head==NULL){
		head=tail=temp;
	}
	else if (temp->price < head->price){
		temp->next=head;
		head=temp;
	}
	else if (temp->price > tail->price){
		tail->next=temp;
		tail=temp;
	}
	else{
		struct Data *prev;
		curr=head;
		while(curr->price < temp->price){
			prev=curr;
			curr=curr->next;
		}
		
		if(curr->price == temp->price){
			curr->total += temp->total;
		}
		else{
			prev->next = temp;
			temp->next = curr;
		}
	}
}

void pop(){
	if(head!=NULL){
		curr=head;
		head=head->next;
		free(curr);
	}
}

void popAll(){
	while(head!=NULL){
		pop();
	}
}

void view(){
	if(head!=NULL){
		curr=head;
		while(curr!=NULL){
			printf("%5d %5d\n", curr->price, curr->total);
			curr=curr->next;
		}
	}
	printf("\n");
}

int main(){
	int menu, price, lot;
	do{
		system("cls");
		printf(" Offer List\n");
		printf("===========\n");
		printf("Price   Lot\n");
		view();
		printf("1. Add New Offer\n");
		printf("2. Buy All Lot in Lowest\n");
		printf("3. Exit\n");
		do{
			printf("Input [1-3] : ");
			scanf("%d", &menu); getchar();	
		}while(menu<1||menu>3);
		printf("\n");
		switch(menu){
			case 1:
				do{
					printf("Offer price [100-10000 must be multiple of 10]: ");
					scanf("%d", &price); getchar();	
				}while(price<100||price>10000||price%10!=0);
				
				do{
					printf("Lot [1-10000] : ");
					scanf("%d", &lot); getchar();
				}while(lot<1||lot>10000);
				
				push(price, lot);
				break;
			case 2:
				pop();
				break;
			case 3:
				popAll();
				break;
		}	
	}while(menu!=3);
	
	return 0;
}
