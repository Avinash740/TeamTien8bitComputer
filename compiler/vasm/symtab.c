/* Maintain symbol table for vasm.c					*/

#include <stdio.h>
#include "gvars.h"

/* Given a character string containing a symbol, this routine searches
   the symbol table to see if the symbol is already there.  If it is, a
   pointer to that location is returned.  If it is not already in the table,
   it is added and a pointer to that location is returned.
									*/
add_symbol(symbol)
char	*symbol;	/* symbol to be added				*/
{
	int	hash_val;	/* resulting value of hashing symbol	*/
	int	ptr;		/* pointer to symbol in sym_table[]	*/
	int	found;		/* flag indicating that symbol is in table */

	/* find the hash value and the corresponding pointer for symbol	*/
	hash_val = hash(symbol);
	ptr = hash_table[hash_val];

	/* check if already in table, if not add it to table		*/
	if (ptr == NULL_PTR)	/* not in table				*/
		ptr = insert_sym(symbol,hash_val);	/* insert it	*/
	else	{	/* search the linked list pointed to by ptr	*/
		found = NO;
		while ( (ptr != NULL_PTR) && (found == NO) )
			{
			if (mystrcmp(symbol,sym_table[ptr].name) == 0) /* match */
				found = YES;
			else	ptr = sym_table[ptr].link;
			}
		if (found == NO)	/* not in table			*/
			ptr = insert_sym(symbol,hash_val);
		}

/*
printf("	'%s' hashes to %d, stored in location %d\n",
	symbol,hash_val,ptr);
*/
	/* return the pointer						*/
	return(ptr);
}








/* Insert the given symbol at the head of the linked list.  The hash
   table pointer will now point to the symbol just added.  Other symbols
   in the linked list will follow this new symbol.
   Returns a pointer to sym_table[] that contains the new symbol.	*/

insert_sym(symbol,hash_val)
char	*symbol;	/* symbol to be inserted			*/
int	hash_val;	/* location in hash_table to take new pointer	*/
{
	int	ptr;	/* pointer to sym_table[] containing symbol	*/

	/* get a free location in sym_table[]				*/
	ptr = next_free_ptr;
	next_free_ptr++;
	if (next_free_ptr >= MAX_SYM_TABLE)
		err_exit("symbol table overflow",SYM_TABLE_OFLW);

	/* add new symbol to table, setting appropriate pointers in list */
	mystrcpy(sym_table[ptr].name,symbol);	/* copy symbol to ~.name */
	sym_table[ptr].link = hash_table[hash_val];
	hash_table[hash_val] = ptr;

	/* initialize some other variables in the symbol structure	*/
	sym_table[ptr].value = UN_INIT_LABEL;	/* Used to mark
                                                   uninitialized labels */

	return(ptr);
}








/* Given string s[], return integer hash value.
   0 <= hash_val < MAX_HASH_TABLE					*/

hash(s)
char	s[];		/* string to be hashed				*/
{
	int	i;	/* index into string				*/
	int	sum;	/* accumulated hash value to return		*/

	/* init local vars						*/
	i = 0;
	sum = 271828;		/* some "random" seed value		*/

	/* scan string accumulating sum, and shifting left if i is odd	*/
	while (s[i] != '\0')		/* not end of string		*/
		{
		sum += ((int) s[i]) << (8 * (i & 1));
		i++;
		}

	/* do some more "randomization" of sum				*/
	sum = (sum * 314159269) + 453806245;
	sum = abs(sum) % MAX_HASH_TABLE;

	return(sum);
}









/* Copy string t to string s.  (From C book, p. 100)			*/

mystrcpy(s, t)
char	s[];	/* destination string					*/
char	t[];	/* source string					*/
{
	int	i;

	i = 0;
	while ((s[i] = t[i]) != '\0')
		{
		i++;
		if (i >= MAX_NAME_LEN)
			{
			fprintf(stderr,"'%s'   ",t);
			err_exit("variable name too long",NAME_LEN_OFLW);
			}
		}
}









/* Compare string s and string t.  Return <0 if s<t, 0 if s==t, >0 if s>t
   (From C book, p. 102)						*/

mystrcmp(s, t)
char	*s, *t;
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return(0);
	return(*s - *t);
}
