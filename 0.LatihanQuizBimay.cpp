#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char date[20];
	int itemQty;
	char itemName[20];
	int status;
	struct node *next, *prev;
}*head = NULL, *current, *tail = NULL;

int count1 = 0;
int count2 = 0;
int count3 = 0;

void newNode(char date[], int qty, char name[], int status){
	current = (struct node*)malloc(sizeof (struct node));
	strcpy (current->date,date);
	strcpy (current->itemName,name);
	current->itemQty = qty;
	current->status = status;
	current->next = current->prev = NULL;
}

void countData (char name[], int qty){
	if (strcmp(name,"100D")==0){
		count1 += qty;
	}else if (strcmp(name,"500D")==0){
		count2 += qty;
	}if (strcmp(name,"1000D")==0){
		count3 += qty;
	}
}

void pushData(char date[], int qty, char name[], int statuss){
	newNode(date, qty, name, statuss);
	
	if (head==NULL){
		head = tail = current;
	}else{
		struct node *search = head;
		while (search!=NULL){
			if (head==search && statuss > search->status){
				//push head
				current->next = head;
				head->prev = current;
				head = current;
			}else if (search->next != NULL){
				if (search->next->status < statuss){
					//push mid
					current->next = search->next;
					current->prev = search;
					search->next->prev = current;
					search->next = current;
					break;
				}
			}
			search = search->next;
		}
		
		if (search == NULL){
			//pushtail
			tail->next = current;
			current->prev = tail;
			tail = current;
		}
	}
}

void print(){
	struct node *search = head;
	while (search!=NULL){
			if (search->status == 3){
				printf ("100D Stock : %d\n",count1);
				while (search != NULL && search->status == 3){
					printf ("  %s : %d item (%s)\n",search->itemName, search->itemQty, search->date);
					search = search->next;
				}
			}else if (search->status == 2){
				printf ("500D Stock : %d\n",count2);
				while (search != NULL && search->status == 2){
					printf ("  %s : %d item (%s)\n",search->itemName, search->itemQty, search->date);
					search = search->next;
				}
			}else if (search->status == 1){
				printf ("1000D Stock : %d\n",count3);
//				struct node *search2 = head;
				while (search != NULL && search->status == 1){
					printf ("  %s : %d item (%s)\n",search->itemName, search->itemQty, search->date);
					search = search->next;
				}
//				search = search->next;
			}
	}
}

void pop(char del[]){
	struct node *search = head;
	while (search!=NULL){
		if (strcmp (del, search->itemName)==0){
			current->next->prev = search->next->prev;
			if (head!=NULL){
				if (strcmp(del,"100D")==0){
					count1 -= current->itemQty;
				}else if (strcmp(del,"500D")==0){
					count2 -= current->itemQty;
				}else if (strcmp(del,"1000D")==0){
					count3 -= current->itemQty;
				}
				head = head->next;
				free (head->prev);
			}
			search = search->next;
		}
	}
	//5 7 8 100 200
}

int main(){
	int jumlah;
	char date[20], name[20];
	int qty;
	scanf ("%d",&jumlah);
	for (int i=0; i<jumlah; i++){
		scanf ("%s %s %d",date,name,&qty);
		int statuss;
		if (strcmp(name,"100D")==0){
			statuss = 3;
		}else if (strcmp(name,"500D")==0){
			statuss = 2;
		}else if (strcmp(name,"1000D")==0){
			statuss = 1;
		}
		pushData(date,qty,name,statuss);
		countData(name,qty);
	}
	print();
	char del[20];
	scanf ("%s",del);
	pop (del);
	print();
}

//5
//1-3-2024 100D 3
//1-2-2024 100D 4
//1-3-2024 500D 10
//1-4-2024 1000D 90
//1-5-2024 500D 8
