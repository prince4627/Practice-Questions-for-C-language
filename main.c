#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct contacts
{
	int index;
	char first_name[15];
	char last_name[15];
	char mobile_number[10];
	char emailId[50];
}contacts;

typedef struct node
{
	contacts data;
	struct node *next, *prev;
}node;

void home();
void main_menu(node *head);
void main_menu_choice(int choice, node *head);
void print(contacts x);
void displayAll(node *head);
void search_menu(node *head);
void search_menu_choice(int choice, node *head);
void search_firstName(node *head);
void search_lastName(node *head);
void search_contactNumber(node *head);
void search_emailId(node *head);
/*void sort(node *head);
void copy(node *str2, node *str1);*/
void edit(node *head);
void quit(node *head);
node *insert(node *head, contacts x);
node *delete(node *head);

contacts read()
{
	contacts x;
	printf("Enter Index\n");
	scanf("%d", &x.index);
	printf("Enter First Name \n");
	scanf("%s", x.first_name);
	printf("Enter Last Name \n");
	scanf("%s", x.last_name);
	printf("Enter Mobile Name \n");
	scanf("%s", x.mobile_number);
	printf("Enter Email ID \n");
	scanf("%s", x.emailId);
	return x;
}

void home()
{
	system("cls"); 

	printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                  Phone Book                   |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");

	printf(" \n Press any key to continue:");
	getch();
}

void main_menu(node *head)
{
	system("cls");

	printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                   Main Menu                   |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        1. Add New Contact                     |\n");
	printf("\t\t|        2. List All Contact                    |\n");
	printf("\t\t|        3. Edit A Contact                      |\n");
	printf("\t\t|        4. Delete A Contact                    |\n");
	printf("\t\t|        5. Search A Contact                    |\n");
	printf("\t\t|        6. Exit                                |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");

	int choice;
	printf("Enter a Choice\n");
	scanf("%d", &choice);
	main_menu_choice(choice, head);
}

void main_menu_choice(int choice, node *head)
{
	contacts x;

	switch (choice)
	{
		case 1: insert(head, x); break;
		case 2: displayAll(head); break;
		case 3: edit(head); break;
		case 4: delete(head); break;
		case 5: search_menu(head); break;
		case 6: quit(head); break;
	}
}

void print(contacts x)
{
	printf("\n %d. %s %s \t %s \t %s", x.index, x.first_name, x.last_name, x.mobile_number, x.emailId);
}

node *insert(node *head, contacts x)
{
	system("cls");
	printf("Add A New Contact\n");
	node *p, *q;
	p=(node *)malloc(sizeof(node));
	x = read();
	q=head;
	p->data=x;
	p->next=NULL;
	if (head==NULL)
	{
		head = p;
		head->prev=NULL;
	} 
	else		
	{	
		while (q->next!=NULL)
				q=q->next;
		q->next=p;
		p->prev=q;
	}

	//sort(head);

	FILE *filePointer;
	filePointer = fopen("contacts.txt", "w") ;

	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x = p->data;
			fprintf(filePointer, "%d. %s \t %s \t %s \t %s \n", x.index, x.first_name, x.last_name, x.mobile_number, x.emailId);
		}
	}

	fclose(filePointer);
	
	printf(" \nContact Added Successfully \n\n");
	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}
	
void displayAll(node *head)
{
	system("cls");
	node *p;
	printf("All Contacts \n\n");
	
	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x = p->data;
			print(x);
		}
	}

	printf("\n \n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

node *delete(node *head)
{
	node *p, *q;

	printf("\n");
	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x=p->data;
			print(x);
		}
	}

	int index;
	if(head == NULL)
	{
		printf("\n No Contacts");
		printf("\n Press any key for the Main Menu\n");
		getch();
		main_menu(head);
	}
	else
	{ 
		printf("\n Enter The Index of The Contact you want to delete:");
		scanf("%d", &index);
		for (p=head; p!=NULL && p->data.index != index; p=p->next);
			if (p->data.index != index)
			{
				printf("Contact Not Found\n");
				printf("\n Press any key for the Main Menu\n");
				getch();
				main_menu(head);
			}
		if (p==head)
		{
			head=head->next;
			if (head != NULL)
				head->prev=NULL;
			free(p);
		}

		else if (p->next == NULL)
		{
			q = p;
			p = p->prev;
			p->next = NULL;
			free(q);
		}

		else 
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
			free(p);
		}

	FILE *filePointer;
	filePointer = fopen("contacts.txt", "w") ;

	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x = p->data;
			fprintf(filePointer, "%d. %s \t %s \t %s \t %s \n", x.index, x.first_name, x.last_name, x.mobile_number, x.emailId);
		}
	}

	fclose(filePointer);

	printf("\n Contact Deleted Successfully. \nPress any key for the Main Menu\n");
	getch();
	main_menu(head);
	}
}

void edit(node *head)
{
	system("cls");
	printf("Edit a Contact\n");
	int index;
	node *p;
	printf("\n");

	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x=p->data;
			print(x);
		}
	}

	printf(" \n Enter Index of Contact");
	scanf("%d", &index);
	for (p=head; p!=NULL && p->data.index != index; p=p->next);
	{	
		if (p!=NULL)
			{
				printf("Enter a new Record \n");
				p->data=read();
				printf("Contact Modified\n");
			}
		else
			printf("Wrong Index\n");
	}

	//sort(head);

	FILE *filePointer;
	filePointer = fopen("contacts.txt", "w") ;

	if (head != NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			contacts x = p->data;
			fprintf(filePointer, "%d. %s \t %s \t %s \t %s \n", x.index, x.first_name, x.last_name, x.mobile_number, x.emailId);
		}
	}

	fclose(filePointer);

	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

void search_menu(node *head)
{
	system("cls");

	printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                    SEARCH                     |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        Search VIA:                            |\n");
	printf("\t\t|        1. First Name                          |\n");
	printf("\t\t|        2. Last Name                           |\n");
	printf("\t\t|        3. Contact Number                      |\n");
	printf("\t\t|        4. Email ID                            |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");

	int choice;
	printf("Enter a Choice\n");
	scanf("%d", &choice);
	search_menu_choice(choice, head);
}

void search_menu_choice(int choice, node *head)
{
	contacts x;

	switch (choice)
	{
		case 1: search_firstName(head); break;
		case 2: search_lastName(head); break;
		case 3: search_contactNumber(head); break;
		case 4: search_emailId(head); break;
		default: printf("Enter valid choice\n");
	}
}

void search_firstName(node *head)
{
	node *p;
	printf("Enter First Name:\n");
	char firstName[15];
	scanf("%s", firstName);
	if(head == NULL)
	{
		printf("\n No Contacts");
		main_menu(head);
	}
	else
	{ 
		for (p=head; p!=NULL && (strcmp(p->data.first_name, firstName) == 1); p=p->next);
			if (strcmp(p->data.first_name, firstName) == 1)
			{
				printf("Contact Not Found\n");
				main_menu(head);
			}
		contacts x = p->data;
		print(x);
	}

	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

void search_lastName(node *head)
{
	node *p;
	printf("Enter Last Name:\n");
	char lastName[15];
	scanf("%s", lastName);
	if(head == NULL)
	{
		printf("\n No Contacts");
		main_menu(head);
	}
	else
	{ 
		for (p=head; p!=NULL && (strcmp(p->data.last_name, lastName) == 1); p=p->next);
			if (strcmp(p->data.last_name, lastName) == 1)
			{
				printf("Contact Not Found\n");
				main_menu(head);
			}
		contacts x = p->data;
		print(x);
	}

	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

void search_contactNumber(node *head)
{
	node *p;
	printf("Enter Contact Number:\n");
	char contactNumber[10];
	scanf("%s", contactNumber);
	if(head == NULL)
	{
		printf("\n No Contacts");
		main_menu(head);
	}
	else
	{ 
		for (p=head; p!=NULL && (strcmp(p->data.mobile_number, contactNumber) == 1); p=p->next);
			if (strcmp(p->data.mobile_number, contactNumber) == 1)
			{
				printf("Contact Not Found\n");
				main_menu(head);
			}
		contacts x = p->data;
		print(x);
	}

	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

void search_emailId(node *head)
{
	node *p;
	printf("Enter Contact Number:\n");
	char emailId[50];
	scanf("%s", emailId);
	if(head == NULL)
	{
		printf("\n No Contacts");
		main_menu(head);
	}
	else
	{ 
		for (p=head; p!=NULL && (strcmp(p->data.emailId, emailId) == 1); p=p->next);
			if (strcmp(p->data.emailId, emailId) == 1)
			{
				printf("Contact Not Found\n");
				main_menu(head);
			}
		contacts x = p->data;
		print(x);
	}

	printf("\n Press any key for the Main Menu\n");
	getch();
	main_menu(head);
}

/*void sort(node *head)
{
	node *p, *q, *temp;
	temp = (node *)malloc(sizeof(node));

	if (head->next!=NULL)
	{
		for (p=head; p!=NULL; p=p->next)
		{
			for (q=head; q->next==NULL; q=q->next)
			{
				if (strcmp(p->data.first_name, q->data.first_name) > 0)
				{
					copy(temp, p);
					copy(p, q);
					copy(q, temp);
				}
			}
		}
	}
}

void copy(node *str2, node *str1)
{	
	strcmp(str2->data.index, str1->data.index);
	strcmp(str2->data.first_name, str1->data.first_name);
	strcmp(str2->data.last_name, str1->data.last_name);
	strcmp(str2->data.mobile_number, str1->data.mobile_number);
	strcmp(str2->data.emailId, str1->data.emailId);
}*/

void quit(node *head)
{
	system("cls");

	printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|          Do You Really Want To Exit           |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|         YES (1)                NO(2)          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");

	int choice;
	printf("Enter a Choice\n");
	scanf("%d", &choice);
	
	if (choice == 1)
		exit(0);
	else if (choice == 2)
		main_menu(head);
	else
		printf("Enter a Valid Choice\n");
}

int main()
{
	node *head=NULL;
	home();
	main_menu(head);
	return 0;
}
