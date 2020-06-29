#include "books.h"
#include <stdio.h> /*for printf*/
#include <string.h> /*for strcmp,strlen*/
#include <ctype.h> /*for isdigit */
#define MAXINPUT 20

extern Book g_books[];
extern size_t g_books_len;
extern void test();

size_t check_input(char *input)
{
	size_t length,i,res=0; 

	while(1)
	{
		scanf ("%s", input);
		length = strlen (input);
		for(i=0;i<length; ++i)
        		if (!isdigit(input[i]))
        		{
				printf ("Entered input is not a number. please try again\n");
				break;
        		}
		if(i==length)
		{
			for(i=0;i<length;++i)
				res=(res)*10+(size_t)(input[i]-'0');
			return res;
		}
	}
}

void print_books_names()
{
	size_t i;
	printf("the books in library are:\n");

	for(i=0;i< g_books_len;++i)
		printf("\t\t%s\n",(g_books[i]).m_name);
	printf("\n\n");
}

int is_book(unsigned int internal_number)
{
	unsigned int i;
	for(i=0;i<20;++i)
		if((g_books[i]).m_internal_number==internal_number)
			return E_OK;
	return E_ERROR;
}

ErrorCode add_new_book_copy(BookCopy *bookCopy,unsigned int internal_number)
{
	if(is_book(internal_number))
		return E_ERROR;

	init_copy(bookCopy,internal_number);
	return E_OK;
}

ErrorCode is_book_cpoy(BookCopy arr[],long int serial_number,long int *res,unsigned int len)
{
	long int i;

	/*for(i=0;i<sizeof(arr)/sizeof(BookCopy);++i)*/
	for(i=0;i<len;++i)
		if((arr[i]).m_serial_number==serial_number)
		{
			*res=i;
			return E_OK;
		}

	return E_ERROR;
}

void to_borrow_copy(BookCopy arr[],unsigned int len)
{
	char input[MAXINPUT]="";
	long int serial_number,res;
	printf("please enter the serial number of the bookyou would like : \n");
	serial_number=(long int)(check_input(input));
	 
	if(is_book_cpoy(arr,serial_number,&res,len))
	{
		printf("sorry, but there is no such a book in the library\n");
		return;
	}
	if(borrow_copy(&arr[res],1))
		printf("sorry, but the book  is already borrowed\n");
	printf("The book was successfully borrowed\n\n");
	++(arr[res].m_borrowing_times);
} 

void to_return_copy(BookCopy arr[],unsigned int len)
{
	char input[MAXINPUT]="";
	long int serial_number,res;
	printf("please enter the serial number of the bookyou would like : \n");
	serial_number=(long int)(check_input(input));
	 
	if(is_book_cpoy(arr,serial_number,&res,len))
	{
		printf("sorry, but there is no such a book in the library\n");
		return;
	}
	if(borrow_copy(&arr[res],0))
		printf("sorry, but the book  is already return\n");
	else 
	{
	update_attributes(arr);
	printf("The book was successfully returned\n\n");
	}
} 

int borrowing_stage(BookCopy arr[],unsigned int len)
{
	char choice[MAXINPUT];
	printf("for Borrow a book-copy press 1\nfor Return a book-copy press 2\nto Exit press 9\n");
	scanf("%s",choice);

	while(strcmp(choice,"9"))
	{
		if(!strcmp(choice,"1"))
			to_borrow_copy(arr,len);
		else if(!strcmp(choice,"2"))
			to_return_copy(arr,len);
		else printf("you entered a rong number please enter again:\n");
	printf("for Borrow a book-copy press 1\nfor Return a book-copy press 2\nto Exit press 9\n");
	scanf("%s",choice);
	}
	printf("goodbye!!\n");	


	return 0;

}

void add_len(BookCopy arr[],unsigned int len)
{
	char input[MAXINPUT]="";
	unsigned int i,internal_number;
	for(i=0;i<len;++i)
	{
		printf("please enter the internal_number: \n");
		internal_number=(unsigned int)(check_input(input));
		while(add_new_book_copy(&arr[i],internal_number))
		{
			printf("there is no such a book in the library. please enter again: \n");
			internal_number=(unsigned int)(check_input(input));
		}
		printf("the copy book added sucssefully:\n");
		printCopy(&arr[i]);
	printf("\n\n");
	}
}



int main()
{
	char input[MAXINPUT]="";
	unsigned int len,i=0;
	BookCopy *ptr,*arr,*tmp;

	print_books_names();
	printf("please enter how many Book-copies to allocate\n");
	len=(unsigned int)(check_input(input));
	arr=malloc(len*sizeof(BookCopy*)+len*sizeof(BookCopy));
	if(arr)
	{
		ptr=arr;
		tmp=arr+len*sizeof(BookCopy*);
		/*while(i++<len && ptr++=tmp+=sizeof(BookCopy));*/
		for(i=0; i<len; ++i,++ptr,tmp+=sizeof(BookCopy))
			ptr=tmp;
		add_len(arr,len);
		borrowing_stage(arr,len);
		free(arr);
		test();
		return 0;
	}			
	return 1;
}
