#include <stdlib.h> /*for size_t*/
/*typedef struct book Book;
typedef struct bookCopy BookCopy;*/

typedef enum
{
	KIDS,
	HIGHSCHOOL,
	ADULT,
	DOCUMENTARY,
	COMICS
}Zone;

typedef enum
{
	False,
	True
}Boolean;

typedef enum
{
	E_OK,
	E_ERROR,
	E_NULL_PTR,
	E_OVERFLOW
}ErrorCode;

typedef enum
{
	COVER=0X1,
	INDEXING=0x2,
	MISSING_PAGES=0x4,
	BAR_CODE=0x8,
	SPINE_BROKEN=0x10,
	STAINED_PAGES=0x20
}Condition;

typedef struct book
{
	unsigned int m_internal_number;
	char *m_name;
	int m_promotion;
	Zone m_zone;
}Book;

typedef struct bookCopy
{
	unsigned int m_internal_number;
	size_t m_serial_number;
	Boolean m_is_borrowed;
	size_t m_borrowing_times;
	int m_attributes ;
	/*Condition m_condition;*/
}BookCopy;


char* get_zone_name(Zone m_zone);
ErrorCode print_book(Book *book);
ErrorCode printCopy(BookCopy *bookcopy);
ErrorCode borrow_copy(BookCopy *bookcopy, Boolean is_borrowing);
ErrorCode init_copy(BookCopy *bookcopy,unsigned int internal_number);
Boolean is_librarian_required(BookCopy *bookcopy);
Boolean is_bookbinder_required(BookCopy *bookcopy);
Boolean is_repairable(BookCopy *bookcopy);
Boolean is_ok(BookCopy *bookcopy);
Boolean is_useless(BookCopy *bookcopy);
Boolean  are_in_same_condition(BookCopy *bookcopy1,BookCopy *bookcopy2);
BookCopy* create_copy(unsigned int internal_number);
void free_arry(BookCopy *bookcopy[],unsigned int size);
ErrorCode update_attributes(BookCopy *bookcopy);
ErrorCode print_attributes(BookCopy *bookcopy);
