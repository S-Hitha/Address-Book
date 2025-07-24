#include "contact.h"
#define LIGHT_BLUE "\033[1;34m"
#define RED "\033[31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define PINK "\033[95m"
#define RESET "\033[0m"

void listContacts(AddressBook *addressBook) 
{
	for(int i=0;i<100;i++)
		printf("-");
	printf("\n");
	printf(RED"%-6s %-20s %-25s %-30s\n","SL.NO","NAME","PHONE NUMBER","EMAIL_ID"RESET);
	
	for(int i=0;i<100;i++)
		printf("-");
	printf("\n");
	for(int i=0;i<addressBook->contactCount;i++)
	{
		printf(PURPLE"%-6d %-20s"RESET,i+1,addressBook->contacts[i].name);
	   	printf(BLUE"%-25s"RESET,addressBook->contacts[i].phone);
	   	printf(PINK"%-30s"RESET,addressBook->contacts[i].email);
	   	printf("\n");
    	}
	for(int i=0;i<100;i++)
		printf("-");
	printf("\n");
}  

void initialize(AddressBook *addressBook) 
{
	addressBook->contactCount=0;
	FILE *file=fopen("contact.txt","r");
	{
		if((file != NULL))
		{
			fclose(file);
			loadContact(addressBook);
		}
		else
		{
			populate_contacts(addressBook);
		}
	}	
}

void createContact(AddressBook *addressBook) 
{
	while(1)
	{
	printf("Enter the name: ");
	getchar();
	scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].name);
	if(checkname(addressBook))
		continue;
	else
		break;
	}
	while(1)
	{
	printf("Enter the phone number: ");
	getchar();
	scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].phone);
	if(checkphone(addressBook))
		continue;
	else
		break;
	}
	while(1)
	{
	printf("Enter the email id: ");
	getchar();
	scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].email);
	if(checkemail(addressBook))
		continue;
	else
		break;
	}
	if(checkcontact(addressBook))
	{
		printf("\n");
		printf(YELLOW "Contact already exists\n"RESET);

	}
	else
	{
		printf("\n");
		printf(YELLOW "Contact created successfully\n"RESET);
		printf("\n");
		addressBook->contactCount++;
	}
}

int checkname(AddressBook *addressBook)
{
	char *name=addressBook->contacts[addressBook->contactCount].name;
	for(int i=0;name[i]!=0;i++)
	{
		if(!((name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z') || name[i] ==' '))
		{
			printf(LIGHT_BLUE "Invalid name\n"RESET);
			return 1;
		}
	}
	return 0;
}

int checkphone(AddressBook *addressBook)
{
	char *phone=addressBook->contacts[addressBook->contactCount].phone;
	int len = strlen(phone);
	if(len !=10)
	{
		printf(LIGHT_BLUE "Invalid phone number\n"RESET);
		return 1;
	}
	for(int i=0;i<len;i++)
	{
		if(phone[i] < '0' || phone[i] > '9')
		{
			printf(LIGHT_BLUE"Invalid phone number\n"RESET);
			return 1;
		}
	}
	return 0;
}

int checkemail(AddressBook *addressBook)
{
	char *email=addressBook->contacts[addressBook->contactCount].email;
	int count1=0;
	int count2=0;
	for(int i=0;email[i]!=0;i++)
	{
		if(email[i] == '@')
			count1++;
		if(email[i] == '.')
			count2++;
	}
	if(count1!=1 || count2!=1)
	{
		printf(LIGHT_BLUE"Invalid email id\n"RESET);
		return 1;
	}
	return 0;
}

int checkcontact(AddressBook *addressBook)
{
	char *name=addressBook->contacts[addressBook->contactCount].name;
	char *phone=addressBook->contacts[addressBook->contactCount].phone;
	char *email=addressBook->contacts[addressBook->contactCount].email;

	for(int i=0;i<addressBook->contactCount;i++)
	{
		if((strcmp(name,addressBook->contacts[i].name)==0) ||
		(strcmp(phone,addressBook->contacts[i].phone)==0) ||
		(strcmp(email,addressBook->contacts[i].email)==0))
		{
		return 1;
		}
	}
	return 0;
}

void searchContact(AddressBook *addressBook) 
{

	int n=0;
	printf("Search by 1.Name 2.Phone 3.Email\n");
	scanf("%d",&n);
	getchar();
	if(n==1)
		search_by_name(addressBook);
	else if(n==2)
		search_by_phone(addressBook);
	else if(n==3)
		search_by_email(addressBook);
	else
	{
		printf("Choose the correct option\n"); 
		searchContact(addressBook);
	}
}

void editContact(AddressBook *addressBook) 
{
	char name[200];
	int flag=0;
	printf(LIGHT_BLUE"Enter the name of the contact you want to edit: "RESET);
	getchar();
	fgets(name,sizeof(name),stdin);
	name[strcspn(name,"\n")]=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(name,addressBook->contacts[i].name)==0)
		{
			printf("Enter new contact details: \n");
			printf(LIGHT_BLUE"Name Phone Email: "RESET);
			scanf("%[^\n] %[^\n] %[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			flag++;
		}
	}
	if(flag==0)
	{
		printf("\n");
		printf(LIGHT_BLUE"Contact not found\n"RESET);
	}
	else
	{
		printf("\n");
		printf(YELLOW"Contact has been edited successfully\n"RESET);
	}
	printf("\n");
}

void deleteContact(AddressBook *addressBook) 
{
	char d_name[200];
	int flag=0;
	printf("Enter the contact you want to delete: \n");
	getchar();
	fgets(d_name,sizeof(d_name),stdin);
	d_name[strcspn(d_name,"\n")]=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(d_name,addressBook->contacts[i].name)==0)
		{
			for(int j=i;j<=addressBook->contactCount;j++)
			{
				strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
				strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
				strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
			}
				printf("\n");
				printf(YELLOW "Contact deleted successfully\n"RESET);
				printf("\n");
				addressBook->contactCount--;
				flag++;
				break;
		}
	}
	if(flag==0)
	{
		printf("\n");
		printf(YELLOW"Contact not found\n"RESET);
	}
}


void search_by_name(AddressBook *addressBook)
{
	char str[100];
	int n=0;

	printf(LIGHT_BLUE"Enter the name: "RESET);
	fgets(str,sizeof(str),stdin);
	str[strcspn(str,"\n")]=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(str,addressBook->contacts[i].name)==0)
		{
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf(RED"%-20s %-25s %-30s \n","NAME","PHONE NUMBER","EMAIL_ID"RESET);
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf("%-20s  %-25s  %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			n=1;
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");

			break;
		}
	}
	if(!n)
		printf(LIGHT_BLUE"Contact not found\n"RESET);
}

void search_by_phone(AddressBook *addressBook)
{
	char str[100];
	int n=0;

	printf(LIGHT_BLUE"Enter the phone number: "RESET);
	fgets(str,sizeof(str),stdin);
	str[strcspn(str,"\n")]=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(str,addressBook->contacts[i].phone)==0)
		{
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf(RED"%-20s %-25s %-30s\n","NAME","PHONE NUMBER","EMAIL_ID"RESET);
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf("%-20s  %-25s  %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			n=1;
 			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");

			break;
		}
	}
	if(!n)
		printf(LIGHT_BLUE"Contact not found"RESET);
}

void search_by_email(AddressBook *addressBook)
{
	char str[100];
	int n=0;

	printf(LIGHT_BLUE"Enter the email id: "RESET);
	fgets(str,sizeof(str),stdin);
	str[strcspn(str,"\n")]=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(str,addressBook->contacts[i].email)==0)
		{
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf(RED"%-20s %-25s %-30s\n","NAME","PHONE NUMBER","EMAIL_ID"RESET);
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");
			printf("%-20s  %-25s  %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			n=1;
			for(int i=0;i<100;i++)
				printf("-");
			printf("\n");

			break;
		}
	}
	if(!n)
		printf(LIGHT_BLUE"Contact not found"RESET);
}

void loadContact(AddressBook *addressBook)
{
	FILE *file=fopen("contact.txt","r");
	if(file == NULL)
	{
		printf(LIGHT_BLUE"Error opening file\n"RESET);
		return;
	}
	char line[200];
	while(fgets(line,sizeof(line),file) && addressBook->contactCount < MAX_CONTACTS)
	{
		char name[50], phone[20], email[50];
		int res=fscanf(file,"%49[^,],%19[^,],%49[^\n]",name, phone, email);
	  	if(res==3)
		{	
			strcpy(addressBook->contacts[addressBook->contactCount].name,name);
			strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
			strcpy(addressBook->contacts[addressBook->contactCount].email,email);
			addressBook->contactCount++;
		}
		else if(res!=3)
			break;
		else
		{
			printf(LIGHT_BLUE"Error reading contacts\n"RESET);
			break;
		}
	}
	fclose(file);
}


void saveContact(AddressBook *addressBook)
{
	FILE *file=fopen("contact.txt","w");
	if(file==NULL)
	{
		printf(LIGHT_BLUE"Error opening file\n"RESET);
		return;
	}

	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(file,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	
	printf("\n");
	printf(YELLOW"All contacts saved successfully\n"RESET);	
	printf("\n");
	fclose(file);
}
