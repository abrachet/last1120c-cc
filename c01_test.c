/*
    Alex Brachet
*/

char_a 65; /* A */

main(argc, argv)
int argv[];
{
    extern putchar;
    extern char_a;

    putchar(char_a);
    putchar('\n');

    return(0);
}
