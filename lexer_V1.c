
Jean
dasheur0x2c3
Invisible
﻿
Jean [NERD], 
 — 
15/10/2026 00:17
Jean [NERD], 
 — 
15/10/2026 21:30
Lexer
Parser
interpreter
Jean [NERD], 
 — 
20/10/2026 01:24
the hollow man book
Jean [NERD], 
 — 
21/10/2026 00:07
https://forebears.io/fr/surnames/simo
Jean [NERD], 
 — 
21/10/2026 13:08
Jean [NERD], 
 — 
22/10/2026 10:43
Jean [NERD], 
 — 
24/10/2026 00:50
Jean [NERD], 
 — 
28/10/2026 15:28
Bible
nivuk :
Proverbes   :  5
Ecclésiaste :  7

Reading  :
AT  : Gen 8
NT : Mat 5

Lien : 
https://www.bible.com/fr/bible/113/JHN.1.NIVUK 
Bible.com
John 1 | NIVUK Bible - Bible App
The Word became flesh  In the beginning was the Word, and the Word was with God, and the Word was God. He was with God in the beginning. Through him all things were made; without him nothing was made
Jean a épinglé 
un message dans ce salon. Voir tous les messages épinglés.
 — 
28/10/2026 15:29
Jean [NERD], 
 — 
29/10/2026 09:57
transmition de système d'erreur.
Jean [NERD], 
 — 
31/10/2026 01:41
Type de fichier joint : spreadsheet
Old_exam.xlsx
29.84 KB
Jean a changé le nom du groupe : 
O. Modifier le groupe
 — 
31/10/2026 13:27
Jean a changé le nom du groupe : 
Inventaire. Modifier le groupe
 — 
31/10/2026 13:27
Jean a changé l'icône du groupe. 
Modifier le groupe
 — 
31/10/2026 13:29
Jean [NERD], 
 — 
31/10/2026 23:55
Mes grands parents 


Lien de parenté 



Grand père ( un fils du Foo )
prince notable de Batoufam mais pas notable du Foo parmi les 9
Ngansop l enfant de Tchouanguep 
 était un prince
Un prince 



Grand père mama :
Soumitanyou  :
Quelqu’un qui se débrouille donne par le Foo
Planteur, fonctionnaire au tant colonial
Batoufam venant de magma

Simo : Dieu de quelqu un



Le nom de mon grand père maternelle ,
Fils d’aucun Foo
Il a ’appelait Lowe
Moebho tiéjegua donne par le Foo
Qui se sont chercher et on eu un héritage 
Avait une plantation 
Cacao et café et bananes 
A eu bcp d argent et de pouvoir.

Mon père appelé ma mère Lowe 
C est l un de ses sœur qui elle a épousée un fils de Foo



Fo metang 11 ème roi des batouffam (1911 à 1924)  prédécesseur de Fo Njike Isaac 12 ème (règne de 1927 à 1954).
Grand père de mon père Jean-Yves Tchouanguep Ngansop.
Le 11 ème roi n'a pas participer aux deux guerres.

Wouebo nono le grand père de ma mère a combattu pour la France à la première et deuxième guerre mondiale.

Je veux changer de nom pour car je ne veux plus être d'une lignée de prince batouffam par amour envers Jésus-Christ. 
Jean a épinglé 
un message dans ce salon. Voir tous les messages épinglés.
 — 
01/11/2026 00:13
Jean a épinglé 
un message dans ce salon. Voir tous les messages épinglés.
 — 
01/11/2026 20:08
Jean [NERD], 
 — 
01/11/2026 23:20
A faire pour changer de nom : 

Il doit obligatoirement s'agir d'une copie intégrale (pas un extrait condensé) délivrée par la mairie camerounaise du lieu de naissance, ou par l'Ambassade du Cameroun si la naissance y avait été enregistrée.
Jean [NERD], 
 — 
Hier à 14:19
Les Âmes de l'Achéron
Les joueurs d'échec August Moritz Retzsch
Allégorie de Satan (Seigneur du monde)
Gerard van Honthorst - Christ before the High Priest
Jean [NERD], 
 — 
Hier à 21:00
Jean [NERD], 
 — 
08:26
Image
Jean [NERD], 
 — 
08:52

#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DECLARE_ARRAY(NAME,TYPE)                            \
typedef struct{                                             \
    TYPE* items;                                            \
    size_t count;                                           \
    size_t capacity ;                                       \
} NAME;

DECLARE_ARRAY(String,char)

typedef enum
{
    TOKEN_OPERATOR, // Vaut 0;
    TOKEN_NUMBER, // Vaut 1;
} TokenType;

typedef enum
{
    // Pour l'ordi : Add=1,Sous=2 ...
    OP_ADDITION       ='+',
    OP_SOUSTRACTION   ='-',
    OP_MULTIPLICATION ='*',
    OP_DIVISION       ='/',
    OP_EGAL           ='='
    // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct
{
    TokenType type;
    union
    {
        long double number;
        Operator_t operator;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                     \
   if((array).count >= (array).capacity)                      \
   {                                                            \
    if((array).capacity == 0)                                  \
    {                                                           \
        (array).capacity = 256;                                \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).capacity *=2;                                  \
    }                                                           \
    (array).items = realloc((array).items,(array).capacity*sizeof(*((array).items))); \
   }                                                            \
   (array).items[(array).count] = (value);                    \
   (array).count +=1;                                          \

bool is_operator(char operator)
{
    return 
        operator == '+' ||
        operator == '-' ||
        operator == '*' ||
        operator == '/' ||
        operator == '=';
}  
Operator_t which_operator(char  operator_str)
{
    if( operator_str =='+' ) // ASCII: 43
        return  OP_ADDITION;
    else if( operator_str =='-' ) // ASCII: 45
        return  OP_SOUSTRACTION;
    else if( operator_str =='*' ) // ASCII: 42
        return  OP_MULTIPLICATION;
    else if( operator_str =='/' ) // ASCII: 47
        return  OP_DIVISION;
    return  OP_EGAL; // ASCII: 61               
} 

bool is_number(char operator_str)
{
    if( operator_str >= '0' &&  operator_str == '9')
    {
        return true;
    }
    return false;
}
/*
char* construct_number(size_t* cursor, char* equation, String* str_tmp)
{
    if(strlen(equation) == *cursor 
       || 
       (
        equation[*cursor] !='.' && !is_number(equation[*cursor])
       ))
    {
        append(str_tmp,'0'); // Caractère de fin d'un string.
... (105 lignes restantes)

message.c
6 Ko
Jean [NERD], 
 — 
13:01
mémoire :
  adresse 0x7f03  →  'a'
  adresse  0x5e10 →  'a','b','\0'

endptr   = 0x7f03        (une adresse, un pointeur)
*endptr  = 'a'           (le caractère, une valeur)

*endptr ne « pointe vers » rien — c'est la valeur qu'on obtient en suivant le pointeur. 
Jean [NERD], 
 — 
13:46

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h> // Pour la fonction read.
#include <errno.h>

#define DECLARE_ARRAY(NAME,TYPE)                            \
typedef struct{                                             \
    TYPE* items;                                            \
    size_t count;                                           \
    size_t capacity ;                                       \
} NAME;

DECLARE_ARRAY(String,char)

typedef enum
{
    TOKEN_OPERATOR, // Vaut 0;
    TOKEN_NUMBER, // Vaut 1;
} TokenType;

typedef enum
{
    // Pour l'ordi : Add=1,Sous=2 ...
    OP_ADDITION       ='+',
    OP_SOUSTRACTION   ='-',
    OP_MULTIPLICATION ='*',
    OP_DIVISION       ='/',
    OP_EGAL           ='='
    // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct
{
    TokenType type;
    union
    {
        long double number;
        Operator_t operator;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                     \
   if((array).count >= (array).capacity)                      \
   {                                                            \
    if((array).capacity == 0)                                  \
    {                                                           \
        (array).capacity = 256;                                \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).capacity *=2;                                  \
    }                                                           \
    (array).items = realloc((array).items,(array).capacity*sizeof(*((array).items))); \
   }                                                            \
   (array).items[(array).count] = (value);                    \
   (array).count +=1;                                          \

bool is_operator(char operator)
{
    return
        operator == '+' ||
        operator == '-' ||
        operator == '*' ||
        operator == '/' ||
        operator == '=';
}
Operator_t which_operator(char  operator_str)
{
    if( operator_str =='+' ) // ASCII: 43
        return  OP_ADDITION;
    else if( operator_str =='-' ) // ASCII: 45
        return  OP_SOUSTRACTION;
    else if( operator_str =='*' ) // ASCII: 42
        return  OP_MULTIPLICATION;
    else if( operator_str =='/' ) // ASCII: 47
        return  OP_DIVISION;
    return  OP_EGAL; // ASCII: 61
}

bool is_number(char operator_str)
{
    if( operator_str >= '0' &&  operator_str == '9')
    {
        return true;
    }
    return false;
}

bool is_convert_str_to_number(char* str_number, long double* resultat )
{
    char* fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
    long double tmp = strtod(str_number,&fin);
    if (fin == str_number) return false; // Aucune conversion n'a eu lieu car ils pointent vers la même adresse.
    else if (errno == ERANGE) return false; // Overflow ou underflow.
    else if (*fin != '\0') return false; // Conversion partielle ex: ex: "3.14abc" → val = 3.14, endptr pointe sur 'a'.
... (84 lignes restantes)

message.c
6 Ko
Jean [NERD], 
 — 
14:29

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h> // Pour la fonction read.
#include <errno.h>

#define DECLARE_ARRAY(NAME,TYPE)                            \
typedef struct{                                             \
    TYPE* items;                                            \
    size_t count;                                           \
    size_t capacity ;                                       \
} NAME;

DECLARE_ARRAY(String,char)

typedef enum
{
    TOKEN_OPERATOR, // Vaut 0;
    TOKEN_NUMBER, // Vaut 1;
} TokenType;

typedef enum
{
    // Pour l'ordi : Add=1,Sous=2 ...
    OP_ADDITION       ='+',
    OP_SOUSTRACTION   ='-',
    OP_MULTIPLICATION ='*',
    OP_DIVISION       ='/',
    OP_EGAL           ='='
    // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct
{
    TokenType type;
    union
    {
        long double number;
        Operator_t operator;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                     \
   if((array).count >= (array).capacity)                      \
   {                                                            \
    if((array).capacity == 0)                                  \
    {                                                           \
        (array).capacity = 256;                                \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).capacity *=2;                                  \
    }                                                           \
    (array).items = realloc((array).items,(array).capacity*sizeof(*((array).items))); \
   }                                                            \
   (array).items[(array).count] = (value);                    \
   (array).count +=1;                                          \

bool is_operator(char operator)
{
    return
        operator == '+' ||
        operator == '-' ||
        operator == '*' ||
        operator == '/' ||
        operator == '=';
}
Operator_t which_operator(char  operator_str)
{
    if( operator_str =='+' ) // ASCII: 43
        return  OP_ADDITION;
    else if( operator_str =='-' ) // ASCII: 45
        return  OP_SOUSTRACTION;
    else if( operator_str =='*' ) // ASCII: 42
        return  OP_MULTIPLICATION;
    else if( operator_str =='/' ) // ASCII: 47
        return  OP_DIVISION;
    return  OP_EGAL; // ASCII: 61
}

bool is_number(char operator_str)
{
    if( operator_str >= '0' &&  operator_str == '9')
    {
        return true;
    }
    return false;
}

bool is_convert_str_to_number(char* str_number, long double* resultat )
{
    char* fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
    long double tmp = strtod(str_number,&fin);
    if (fin == str_number) return false; // Aucune conversion n'a eu lieu car ils pointent vers la même adresse.
    else if (errno == ERANGE) return false; // Overflow ou underflow.
    else if (*fin != '\0') return false; // Conversion partielle ex: ex: "3.14abc" → val = 3.14, endptr pointe sur 'a'.
... (90 lignes restantes)

message.c
6 Ko
Jean [NERD], 
 — 
14:45

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h> // Pour la fonction read.
#include <errno.h>

#define DECLARE_ARRAY(NAME,TYPE)                            \
typedef struct{                                             \
    TYPE* items;                                            \
    size_t count;                                           \
    size_t capacity ;                                       \
} NAME;

DECLARE_ARRAY(String,char)

typedef enum
{
    TOKEN_OPERATOR, // Vaut 0;
    TOKEN_NUMBER, // Vaut 1;
} TokenType;

typedef enum
{
    // Pour l'ordi : Add=1,Sous=2 ...
    OP_ADDITION       ='+',
    OP_SOUSTRACTION   ='-',
    OP_MULTIPLICATION ='*',
    OP_DIVISION       ='/',
    OP_EGAL           ='='
    // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct
{
    TokenType type;
    union
    {
        long double number;
        Operator_t operator;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                     \
   if((array).count >= (array).capacity)                      \
   {                                                            \
    if((array).capacity == 0)                                  \
    {                                                           \
        (array).capacity = 256;                                \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).capacity *=2;                                  \
    }                                                           \
    (array).items = realloc((array).items,(array).capacity*sizeof(*((array).items))); \
   }                                                            \
   (array).items[(array).count] = (value);                    \
   (array).count +=1;                                          \

bool is_operator(char operator)
{
    return
        operator == '+' ||
        operator == '-' ||
        operator == '*' ||
        operator == '/' ||
        operator == '=';
}
Operator_t which_operator(char  operator_str)
{
    if( operator_str =='+' ) // ASCII: 43
        return  OP_ADDITION;
    else if( operator_str =='-' ) // ASCII: 45
        return  OP_SOUSTRACTION;
    else if( operator_str =='*' ) // ASCII: 42
        return  OP_MULTIPLICATION;
    else if( operator_str =='/' ) // ASCII: 47
        return  OP_DIVISION;
    return  OP_EGAL; // ASCII: 61
}

bool is_number(char operator_str)
{
    if( operator_str >= '0' &&  operator_str == '9')
    {
        return true;
    }
    return false;
}

bool is_convert_str_to_number(char* str_number, long double* resultat )
{
    char* fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
    long double tmp = strtod(str_number,&fin);
    if (fin == str_number) return false; // Aucune conversion n'a eu lieu car ils pointent vers la même adresse.
    else if (errno == ERANGE) return false; // Overflow ou underflow.
    else if (*fin != '\0') return false; // Conversion partielle ex: ex: "3.14abc" → val = 3.14, endptr pointe sur 'a'.
... (88 lignes restantes)

message.c
6 Ko
﻿

#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DECLARE_ARRAY(NAME,TYPE)                            \
typedef struct{                                             \
    TYPE* items;                                            \
    size_t count;                                           \
    size_t capacity ;                                       \
} NAME;

DECLARE_ARRAY(String,char)

typedef enum
{
    TOKEN_OPERATOR, // Vaut 0;
    TOKEN_NUMBER, // Vaut 1;
} TokenType;

typedef enum
{
    // Pour l'ordi : Add=1,Sous=2 ...
    OP_ADDITION       ='+',
    OP_SOUSTRACTION   ='-',
    OP_MULTIPLICATION ='*',
    OP_DIVISION       ='/',
    OP_EGAL           ='='
    // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct
{
    TokenType type;
    union
    {
        long double number;
        Operator_t operator;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                     \
   if((array).count >= (array).capacity)                      \
   {                                                            \
    if((array).capacity == 0)                                  \
    {                                                           \
        (array).capacity = 256;                                \
    }                                                           \
    else                                                        \
    {                                                           \
        (array).capacity *=2;                                  \
    }                                                           \
    (array).items = realloc((array).items,(array).capacity*sizeof(*((array).items))); \
   }                                                            \
   (array).items[(array).count] = (value);                    \
   (array).count +=1;                                          \

bool is_operator(char operator)
{
    return 
        operator == '+' ||
        operator == '-' ||
        operator == '*' ||
        operator == '/' ||
        operator == '=';
}  
Operator_t which_operator(char  operator_str)
{
    if( operator_str =='+' ) // ASCII: 43
        return  OP_ADDITION;
    else if( operator_str =='-' ) // ASCII: 45
        return  OP_SOUSTRACTION;
    else if( operator_str =='*' ) // ASCII: 42
        return  OP_MULTIPLICATION;
    else if( operator_str =='/' ) // ASCII: 47
        return  OP_DIVISION;
    return  OP_EGAL; // ASCII: 61               
} 

bool is_number(char operator_str)
{
    if( operator_str >= '0' &&  operator_str == '9')
    {
        return true;
    }
    return false;
}
/*
char* construct_number(size_t* cursor, char* equation, String* str_tmp)
{
    if(strlen(equation) == *cursor 
       || 
       (
        equation[*cursor] !='.' && !is_number(equation[*cursor])
       ))
    {
        append(str_tmp,'0'); // Caractère de fin d'un string.
        return str_tmp->items; // <=> (*str_tmp).items
    }
    append(str_tmp,equation[*cursor]);
    ++*cursor;
    return construct_number(cursor,equation,str_tmp);
}
*/
long double convert_str_to_number(char* str_number)
{
    char* fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
    return strtold(str_number,&fin); // Conversion de la chaîne en long double.;
}
// Nbr décimal après la virgule
uint8_t decimal_place(char* str_number)
{
    uint8_t count = 0;
    bool begin = false;
    for(uint8_t i = 0;i< strlen(str_number); i++)
    {
        if(begin)
            count +=1;
        if(str_number[i] =='.')
            begin = true;
    }
    // On utilise * dans "%.*Lf" pour passer le nombre de décimales dynamiquement en argument.
    // printf("Nombre converti : %.*Lf\n", decimales, nombre);
    return count;
}
/*
long double handle_number(char* equation, size_t* cursor )
{
    String str_tmp={0};
    char* str_final= construct_number(cursor,equation,&str_tmp);
    uint8_t decimal= decimal_place(str_final);
    long double number =  convert_str_to_number(str_final);
    printf("Test convert str to long double : %.*Lf \n",decimal,number);
    // Exemple d'utilisation de cursor: *cursor +=13;
    // TODO FREE str_tmp.
    return number;
}
    */
long double handle_number_bool( char* equation, size_t* cursor )
{
    String str_tmp = {0};
    while (*cursor < strlen(equation))
    {
        if( *cursor == strlen(equation)
        || 
        (
            equation[*cursor] !='.' && !is_number(equation[*cursor])
        ))
        {
            append(str_tmp,'0');
        }
        else
        {
            append(str_tmp,equation[*cursor]);
        }
        ++*cursor;
    }
    uint8_t decimal= decimal_place(str_tmp.items);
    long double number =  convert_str_to_number(str_tmp.items);
    printf("Test convert str to long double : %.*Lf \n",decimal,number);
    // Exemple d'utilisation de cursor: *cursor +=13;
    // TODO FREE str_tmp.
    return number;
}

void tokenize(char* equation,TokensArray* tokens_array)
{
    size_t cursor = 0;
    while(cursor < strlen(equation))
    {
        if(is_operator(equation[cursor]))
        {
            Token equation_token = {
                .type = TOKEN_OPERATOR,
                .operator = which_operator(equation[cursor]),
            };
            append(*tokens_array,equation_token);
            ++cursor;
       }
        else if(is_number(equation[cursor])) 
        {
             Token equation_token = {
                .type = TOKEN_NUMBER,
                .operator = handle_number_bool(equation,&cursor),
            };
            append(*tokens_array,equation_token);
        }
    }
}
int main()
{

    TokensArray tokens_array = {0};
    char equation[256]={};
    printf("Calc : \n");
    scanf("%s",equation);
    printf("COUNT CARAC : %ld \n",strlen(equation));
    // printf("Affiche l'équation : %s \n",equation);
    tokenize(equation,&tokens_array);


}

