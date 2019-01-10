#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
	char name[100];
	int duration;
	struct Data *next;
}*head, *tail, *curr;

struct Data *createNode(char name[], int duration){
	struct Data *temp = (struct Data*)malloc(sizeof(struct Data));
	strcpy(temp->name, name);
	temp->duration = duration;
	temp->next=NULL;
	return temp;
}

void push(char name[], int duration){
	struct Data *temp = createNode(name, duration);
	if(head==NULL){
		head=tail=temp;
	}
	else if(strcmp(temp->name, head->name) < 0){
		temp->next=head;
		head=temp;
	}
	else if(strcmp(temp->name, tail->name) > 0){
		tail->next=temp;
		tail=temp;
	}
	else{
		struct Data *prev;
		curr=head;
		while(strcmp(curr->name, temp->name) < 0){
			prev=curr;
			curr=curr->next;
		}
		if(strcmp(curr->name, temp->name) == 0){
			curr->duration=temp->duration;
		}
		else{
			prev->next=temp;
			temp->next=curr;
		}
	}
}

void pop(){
	if(head!=NULL){
		if(head->next==NULL){
			free(head);
			head=tail=NULL;
		}
		else{
			curr=head;
			while(curr->next!=tail){
				curr=curr->next;
			}
			free(curr->next);
			tail=curr;
			tail->next=NULL;
		}
	}
}

void view(){
	printf("Movie Title      :  Duration (minutes)\n");
	if(head!=NULL){
		curr=head;
		while(curr!=NULL){
			printf("%-20s %d\n", curr->name, curr->duration);
			curr=curr->next;
		}
	}
	printf("\n");
}

int main(){
	int menu, duration, length;
	char name[100];
	do{
		system("cls");
		view();
		printf("XXI Movie Center\n");
		printf("================\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Exit\n");
		do{
			printf("Input your choice : ");
			scanf("%d", &menu); getchar();	
		}while(menu<1||menu>3);	
		printf("\n");
		switch(menu){
			case 1:
				do{
					printf("Input the movie title [min. 3 characters]: ");
					scanf("%[^\n]", &name); getchar();
					length = strlen(name);	
				}while(length<3);
				do{
					printf("Input the movie duration [must be a multiple of 30]: ");
					scanf("%d", &duration); getchar();
				}while(duration%30!=0);
				push(name, duration);
				break;
			case 2:
				pop();
				break;
		}
	}while(menu!=3);
	
	return 0;
}
