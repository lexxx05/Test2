#include <stdio.h>
#include <stdlib.h>

struct tree{
	int value;
	struct tree *left, *right;
}*root = NULL;

struct tree* newNode(int value){
	struct tree* node = (struct tree*)malloc(sizeof(struct tree));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}

struct tree* insert(struct tree* cur, int value){
	if (cur == NULL){
		cur = newNode(value);
		return cur;
	}else if (cur->value != value){
		if (value < cur->value){
			cur->left = newNode(value);
		}else{
			cur->right = newNode(value);
		}
	}
	return cur;
}

void printInorder(struct tree* cur){
	if (cur == NULL){
		return;
	}
	printInorder(cur->left);
	printf ("%d ",cur->value);
	printInorder(cur->right);
}

void printPreorder (struct tree* cur){
	if (cur == NULL){
		return;
	}
	printf ("%d ", cur->value);
	printPreorder(cur->left);
	printPreorder(cur->right);
}

void printPostorder(struct tree* cur){
	if (cur == NULL){
		return;
	}
	printPostorder(cur->left);
	printPostorder(cur->right);
	printf ("%d ", cur->value);
}

int count(struct tree* cur){
	if(cur == NULL){
		return 0;
	}
	return (1 + count(cur->left) + count(cur->right));
}

int height(struct tree* cur){
	if(cur == NULL){
		return 0;
	}
	int leftHeight = height(cur->left);
	int rightHeight = height(cur->right);
	
	int maxHeight = 0;
	if(leftHeight < rightHeight){
		maxHeight = rightHeight;
	}else{
		maxHeight = leftHeight;
	}
	
	return (1+maxHeight);
}

int min(struct tree* cur){
	if (cur == NULL){
		return 0;
	}
	//dia bakal ke kiri terus buat cari yang minimum sampai anak kirinya kosong
	//kalo ga ada lagi, dia akan return value yg skrg
	if (cur->left == NULL){
		return cur->value;
	}
	//kalo belom ketemu, dia akan terus cari ke bawah kiri terus sampe ujung kena basecase
	return min(cur->left);
}

int max (struct tree* cur){
	if (cur == NULL){
		return 0;
	}
	if (cur->right == NULL){
		return cur->value;
	}
	return max(cur->right);
}

int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		puts ("Binary Search Tree");
		puts ("---------------------------\n");
		
		printf ("Current Tree (Infix Order):\n");
		if (count(root) == 0) printf ("There is no node yet...");
		else printInorder(root);
		
		puts ("\n");
		
		puts ("1. Insert");
		puts ("2. Delete");
		puts ("3. View Prefix");
		puts ("4. View Postfix");
		puts ("5. Search");
		puts ("6. View Details");
		puts ("7. Exit");
		
		printf ("\n>> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			system ("cls");
			int temp;
			printf ("Input a value to insert a new node: ");
			scanf ("%d", &temp); getchar();
			root = insert(root, temp);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 2){
			system ("cls");
			int temp;
			printf ("Input a value to delete: ");
			scanf ("%d", &temp); getchar();
			root = pop (root, temp);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 3){
			system ("cls");
			printf ("Prefix Order:\n\n");
			printPreorder(root);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 4){
			system ("cls");
			printf ("Postfix Order:\n\n");
			printPostorder(root);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 5){
			
			system ("cls");
			
			printf ("Current Tree:\n");
			if (count(root) == 0) printf ("There is no node yet...");
			else printInfix(root);
			
			puts("\n");
			
			int temp;
			printf ("Input a value to search: ");
			scanf ("%d", &temp); getchar();
			search (root, temp);
			
			printf ("\n\nPress enter to continue...");
			getchar();
			
		}
		
		else if (action == 6){
			printDetails();
		}
		
		else if (action == 7){
			break;
		}
		
	}
	
	while (true);
	
	system ("cls");
	printf ("Thank youu...\n");
	
	return 0;
}

