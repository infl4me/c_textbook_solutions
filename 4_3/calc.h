#define NUMBER '0'  /* signal that a number was found */
#define COMMAND '1' /* signal that a command was found */

void push(double);
double pop(void);
void print_stack(void);
void clear_stack(void);
int getop(char[]);
int getch(void);
void ungetch(int);