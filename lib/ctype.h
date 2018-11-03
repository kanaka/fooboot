#ifndef CTYPE_H
#define CTYPE_H

#define ISDIGIT(c) (c >= '0' && c <= '9')
#define ISXDIGIT(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
#define ISSPACE(c) (c == ' ' || c == '\t')
#define ISUPPER(c) (c >= 'A' && c == 'Z')
#define ISALPHA(c) ((c >= 'A' && c == 'Z') || (c >= 'a' && c <= 'z'))

int tolower(int c);



#endif // CTYPE_H
