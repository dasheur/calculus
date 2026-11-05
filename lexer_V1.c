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
        Operator_t operator;
        long double number;
    };
} Token;

DECLARE_ARRAY(TokensArray,Token)

#define append(array,value)                                       \
   if((array)->count >= (array)->capacity)                        \
   {                                                              \
    if((array)->capacity == 0)                                    \
    {                                                             \
        (array)->capacity = 256;                                  \
    }                                                             \
    else                                                          \
    {                                                             \
        (array)->capacity *=2;                                    \
    }                                                             \
    (array)->items = realloc((array)->items,(array)->capacity*sizeof(*((array)->items))); \
   }                                                              \
   (array)->items[(array)->count] = (value);                      \
   (array)->count +=1;                                            \

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
    if( operator_str >= '0' &&  operator_str <= '9')
    {
        return true;
    }
    return false;
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

bool is_convert_str_to_number(char* str_number, long double* resultat )
{
    char* fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
    long double tmp = strtod(str_number,&fin);
    if (fin == str_number) return false; // Aucune conversion n'a eu lieu car ils pointent vers la même adresse.
    else if (errno == ERANGE) return false; // Overflow ou underflow.
    else if (*fin != '\0') return false; // Conversion partielle ex: ex: "3.14abc" → val = 3.14, endptr pointe sur 'a'.
    *resultat = tmp;
    return true;

}

bool handle_number_bool( char* equation, size_t* cursor, long double* resultat )
{
    String str_tmp = {0}; 
    while (*cursor < strlen(equation))
    {
        if( equation[*cursor] !='.' && !is_number(equation[*cursor]) )
        {
            append(&str_tmp,0);
            break;
        }
        else if(is_number(equation[*cursor]) || equation[*cursor] =='.')
        {
            append(&str_tmp,equation[*cursor]);
        }
        ++*cursor;
    }
    if ( is_convert_str_to_number(str_tmp.items,resultat) ) return true;
    // TODO FREE str_tmp.
    return false;
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
            append(tokens_array,equation_token);
            ++cursor;
            printf("Value Data OP     :%c \n",equation_token.operator);
            printf("Value Data OP TAB :%c \n",tokens_array->items[tokens_array->count-1].operator);
            printf("Value Data OP COUNT:%ld \n",tokens_array->count);
       }
       else if(is_number(equation[cursor]))
       {
            long double resultat= 0;
            if(!handle_number_bool(equation,&cursor, &resultat)) printf("ERREUR TOKEN NUMBER");
            else
            {
                Token equation_token = {
                    .type = TOKEN_NUMBER,
                    .number = resultat,
                };
                append(tokens_array,equation_token);
                printf("Value Data NUM      :%Lf \n",equation_token.number);
                printf("Value Data NUM TAB  :%Lf \n",tokens_array->items[tokens_array->count-1].number);
                printf("Value Data NUM COUNT:%ld \n",tokens_array->count);
            }
        }
    }
}

// NOTE: cette fonction facilite l'entrée utilisateur
// le seul moment où ça retourne false c'est quand tu fais CTRL+D
bool readline(String *input) {
  char tmp_ch;

  while (read(STDIN_FILENO, &tmp_ch, 1)) {
    if (tmp_ch != '\n') {
        if(tmp_ch !=' ') // evite la boucle infinie avec par ex: 1 1 1
        {
            append(input, tmp_ch);
        }
        continue;
    }

    append(input, 0);
    return true;
  }

  return false;
}

int main()
{

    TokensArray tokens_array = {0};
    String input = {0};
    // char equation[256]={};
    //printf("Calc : \n");
    //scanf("%2s",equation);
    //tokenize(equation,&tokens_array);
    
    for (;;) {
        printf("Calc : ");
        // NOTE: ça c'est pour afficher le printf directement.
        // Le `printf` a un buffer. Comme ça, ça fait pas trop de syscall - il
        // affiche directement quand il y a une nouvelle ligne à la fin du texte. Ou
        // le runtime de C flush tout quand la fonction retourne.
        // fflush - force la vidange du buffer dans la console.
        fflush(stdout);
        if (readline(&input)) {
            // NOTE: Le strlen marche ici parce que le readline ajoute un 0 après le
            // texte d'entrée.
            printf("COUNT CARAC : %lu \n", strlen(input.items));
            tokenize(input.items, &tokens_array);

            // NOTE: on reset it
            input.count = 0;
        } 
        else 
        {
            break;
        }
    } 
}