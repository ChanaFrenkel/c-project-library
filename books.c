#include <stdio.h> /*for printf*/
#include "books.h"

static char *s_zone_name[]={"KIDS","HIGHCHOOL" ,"ADULT" ,"DOCUMENTARY" ,"COMICS"};
static char *s_is_borrowed[]={"not_borrowed","borrowed"};
static char *s_attributes[]={"COVER     ","INDEXING","MISSING_PAGES","BAR_CODE","SPINE_BROKEN","STAINED_PAGES"};

char* get_zone_name(Zone m_zone)
{
	return s_zone_name[m_zone];
}

ErrorCode  print_book(Book *book)
{
	if(book)
	{
		printf("book name: %s\ninternal number: %u\npromotion: %d\nzone: %s\n",book->m_name,book->m_internal_number,book->m_promotion,get_zone_name(book->m_zone));
			return E_OK;
	}
	return E_NULL_PTR;
}

ErrorCode printCopy(BookCopy *bookcopy)
{
	if(bookcopy)
	{
		printf("internal number: %u\nserial number %ld\nis borrowed: %s\nborrowing times: %ld\n", bookcopy->m_internal_number, bookcopy->m_serial_number, s_is_borrowed[bookcopy->m_is_borrowed],bookcopy->m_borrowing_times);
		print_attributes(bookcopy);
		return E_OK;
	}
	return E_NULL_PTR;
}

ErrorCode borrow_copy(BookCopy *bookcopy, Boolean is_borrowing)
{
	if(!bookcopy)
		return E_NULL_PTR;
	if (is_borrowing == bookcopy->m_is_borrowed)
		return E_ERROR;
	bookcopy->m_is_borrowed = !bookcopy->m_is_borrowed;
	
	return E_OK;
}

ErrorCode init_copy(BookCopy *bookcopy,unsigned int internal_number)
{
	static size_t s_serial=10000;
	if(!bookcopy)
		return E_NULL_PTR;
	if(s_serial>1000000000)
		return E_OVERFLOW;
	bookcopy->m_internal_number=internal_number;
	bookcopy->m_serial_number=s_serial;
	bookcopy->m_is_borrowed=0;
	bookcopy->m_borrowing_times=0;
	bookcopy->m_attributes=0;
	++s_serial;
	return E_OK;
}

Boolean is_librarian_required(BookCopy *bookcopy)
{
	return(((COVER+INDEXING+BAR_CODE) & bookcopy->m_attributes)?True:False);
}

Boolean is_bookbinder_required(BookCopy *bookcopy)
{
	return(((MISSING_PAGES+SPINE_BROKEN+STAINED_PAGES) & bookcopy->m_attributes)?True:False);
}

Boolean is_repairable(BookCopy *bookcopy)
{
	return((!((MISSING_PAGES+STAINED_PAGES) & bookcopy->m_attributes))?True:False);
}

Boolean is_ok(BookCopy *bookcopy)
{
	return((!(0 | bookcopy->m_attributes))?True:False);
}

Boolean is_useless(BookCopy *bookcopy)
{
	unsigned int count = 0;
	int attributes=bookcopy->m_attributes; 
    	while (attributes) 
	{ 
        	attributes &= (attributes - 1); 
        	++count; 
	}
	return(count>=4);
}

Boolean  are_in_same_condition(BookCopy *bookcopy1,BookCopy *bookcopy2)
{
	return ((!(bookcopy1->m_attributes ^ bookcopy2->m_attributes))?True:False);
}

BookCopy* create_copy(unsigned int internal_number)
{
	BookCopy *bookcopy=malloc(sizeof(BookCopy));

	if(bookcopy)
		init_copy(bookcopy,internal_number);
	return bookcopy;
}
void free_arry(BookCopy *bookcopy[],unsigned int size)
{
	unsigned int i;
	for (i=0;i<size;++i)
	{
		free(bookcopy[i]);
		bookcopy[i]=NULL;
	}
}

ErrorCode update_attributes(BookCopy *bookcopy)
{
	int i=0,res=0,attributes=0,condition=1;
	
	if(!bookcopy)
		return E_NULL_PTR;
	printf("please fill in the state of the book\nfor ok press 0 for not ok press 1\n");
	printf("1.cover:  2.indexing: 3.missing_pages: 4.bar_code: 5.spine_broken: 6. stained_pages :\n");

	for(i=0;i<6;++i,condition*=2)
	{
		printf("%d.:",i+1);
		scanf("%d",&res ); 
		if(res)
			attributes+=condition;
	}
	bookcopy->m_attributes=attributes;
	return E_OK;  
}
 
ErrorCode print_attributes(BookCopy *bookcopy)
{
	int i,condition=1;
	if(!bookcopy)
		return E_NULL_PTR;
	printf("the attributes are:\n");
	for(i=0;i<6;++i,condition*=2)
		printf("\t%s:\t %s\n",s_attributes[i],(bookcopy->m_attributes&condition)?"not ok":"ok");
	return E_OK;	
}
