#include "test.h"
#include <stdio.h> /*for printf*/
#define NUM 4
static BookCopy *s_bookcopy[NUM];

void test()
{
	unsigned int i;	
	for(i=0;i<NUM;++i)
	{
		s_bookcopy[i]=create_copy(1001+i);
		if(!(s_bookcopy[i]))
			return;
	}

	s_bookcopy[1]->m_attributes=COVER+INDEXING+MISSING_PAGES+BAR_CODE+SPINE_BROKEN+STAINED_PAGES;
	s_bookcopy[2]->m_attributes=s_bookcopy[3]->m_attributes=COVER+INDEXING+BAR_CODE+SPINE_BROKEN;

	printf("%s\n",test_is_librarian_required()?"oops! there is a problem with is_librarian_required":"hurray!\n is_librarian_required is working");
	printf("%s\n",test_is_bookbinder_required()?"oops! there is a problem with is_bookbinder_required":"hurray!\n is_bookbinder_required is working");
	printf("%s\n",test_is_repairable()?"oops! there is a problem with is_repairable":"hurray!\n is_repairable is working");
	printf("%s\n",test_is_ok()?"oops! there is a problem with is_ok":"hurray!\n is_ok is working");
	printf("%s\n",test_is_useless()?"oops! there is a problem with is_useless":"hurray!\n is_useless is working");
	printf("%s\n",test_are_in_same_condition()?"oops! there is a problem with are_in_same_condition":"hurray!\n are_in_same_condition is working");

	free_arry(s_bookcopy,NUM);																	
}

ErrorCode test_is_librarian_required()
{
	int i;
	Boolean arr[NUM]={0,1,1,1};
	for(i=0;i<NUM;++i)
		if(is_librarian_required(s_bookcopy[i])!=arr[i])
			return E_ERROR;
	return E_OK;
}

ErrorCode test_is_bookbinder_required()
{
	int i;
	Boolean arr[NUM]={0,1,1,1};
	for(i=0;i<NUM;++i)
		if(is_bookbinder_required(s_bookcopy[i])!=arr[i])
			return E_ERROR;
	return E_OK;
}

ErrorCode test_is_repairable()
{
	int i;
	Boolean arr[NUM]={1,0,1,1};
	for(i=0;i<NUM;++i)
		if(is_repairable(s_bookcopy[i])!=arr[i])
			return E_ERROR;
	return E_OK;
}
ErrorCode test_is_ok()
{
	int i;
	Boolean arr[NUM]={1,0,0,0};
	for(i=0;i<NUM;++i)
		if(is_ok(s_bookcopy[i])!=arr[i])
			return E_ERROR;
	return E_OK;
}

ErrorCode test_is_useless()
{
	int i;
	Boolean arr[NUM]={0,1,1,1};
	for(i=0;i<NUM;++i)
		if(is_useless(s_bookcopy[i])!=arr[i])
			return E_ERROR;
	return E_OK;
}
 
ErrorCode test_are_in_same_condition()
{
	int i;
	Boolean arr[NUM-1]={0,0,1};
	for(i=0;i<NUM-1;++i)
		if(are_in_same_condition(s_bookcopy[i],s_bookcopy[i+1])!=arr[i])
			return E_ERROR;
	return E_OK;
}
