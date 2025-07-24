#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void populate_contacts(AddressBook *addressBook);
void search_by_name(AddressBook *addressBook);
void search_by_phone(AddressBook *addressBook);
void search_by_email(AddressBook *addressBook);
int checkcontact(AddressBook *addressBook);
int checkname(AddressBook *addressBook);
int checkphone(AddressBook *addressBook);
int checkemail(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);
void loadContact(AddressBook *addressBook);
#endif
