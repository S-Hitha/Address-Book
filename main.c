#include "contact.h"
#define GREEN "\033[1;32m"
#define RED "\033[31m"
#define LIGHT_BLUE "\033[1;34m"
#define RESET "\033[0m"
int main()
{
	int choice=0;
	AddressBook A1;
	A1.contactCount=0;
	initialize(&A1);	
	do{
	printf(RED"Address Book Menu:\n"RESET);
	printf(GREEN "1. Create contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n5. List all contacts\n6. Save contacts\n7. Exit\n" RESET);
	printf(LIGHT_BLUE"Enter your choice: "RESET);
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			{
			createContact(&A1);
			break;
			}
		case 2:
			{
			searchContact(&A1);
			break;
			}
		case 3:
			{
			editContact(&A1);
			break;
			}
		case 4:
			{
			deleteContact(&A1);
			break;
			}  
		case 5:
			{
			listContacts(&A1);
			break;
			}
		case 6:
			{
			saveContact(&A1);
			break;
			} 
		case 7:
			{
			break;
			}
		defualt:
			printf(LIGHT_BLUE"Choose the correct option: "RESET);
	}
	}while(choice!=7);
	return 0;
}

