/*
 *	messages header file
 */
 
#ifndef __MESSAGES__
#define __MESSAGES__


void message(const char *msg);
void error(const char *msg);
void warning(const char *msg);
void fatal(const char *msg);
void bug(const char *msg);
char *strsave(const char *s);


#endif
