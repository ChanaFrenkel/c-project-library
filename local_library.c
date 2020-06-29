#include "local_library.h"

Book g_books[] = {
{1001, "Sun Don't Shine", 40, ADULT},
{1002, "Irma la dos", -100, DOCUMENTARY},
{1003, "Starship Troopers: Invasion", -68, KIDS},
{1004, "Year of the Jellyfish", 5, ADULT},
{1005, "After Life", -95, DOCUMENTARY},
{1006, "Rest Stop", 20, HIGHSCHOOL},
{1007, "Wuthering Heights", 56, KIDS},
{1008, "New Adventures of Pippi Longstocking", 11, HIGHSCHOOL},
{1009, "She Does Not Drink, Smoke or xxxxxxxx", 23, KIDS},
{1010, "F.I.S.T.", 97, HIGHSCHOOL},
{1011, "Cruise", -97, HIGHSCHOOL},
{1012, "Letter to Elia, A", 54, KIDS},
{1013, "To Be and to Have", -57, ADULT},
{1014, "Get Hard", -66, HIGHSCHOOL},
{1015, "A Nation's Battle for Life", 51, ADULT},
{1016, "Place Called Chiapas", 76, COMICS},
{1017, "A Drama of the Wilderness", 55, COMICS},
{1018, "Ladies Man", 46, ADULT},
{1019, "Film Geek", -100, COMICS},
{1020, "Raining Stones", -83, DOCUMENTARY}
};

size_t g_books_len=sizeof(g_books)/sizeof(Book);  /*for main*/

const Book* first_book()
{
	return g_books;
}

size_t get_book_number()
{
	return (sizeof(g_books)/sizeof(Book));
}

char* get_name(unsigned int internal_number)
{
	size_t i;
	for(i=0;i<get_book_number();++i)
		if((g_books[i]).m_internal_number==internal_number)
			return (g_books[i]).m_name;
	return NULL;
}
