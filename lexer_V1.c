#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DECLARE_ARRAY(NAME,TYPE) \
typedef struct{ \
    TYPE* items; \
    size_t count; \
    size_t capacity ; \
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

#define append(array,value)\
   if(array->count >= array->capacity) \
   { \
    if(array->capacity == 0) \
    {\
        array->capacity = 256; \
    }\
    else\
    {\
        array->capacity *=2; \
    }\
    array->items = realloc(array->items,array->capacity*sizeof(*(array->items))); \
   } \
   array->items[array->count] = value; \
   array->count +=1; \

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
    if( operator_str >= '0' ||  operator_str == '9')
    {
        return true;
    }
    return false;
}

char* construct_number(size_t* cursor, char* equation, String* str_tmp)
{
    if(strlen(equation) == *cursor 
       || 
       (
        equation[*cursor] !='.' && !is_number(equation[*cursor])
       ))
    {
        append(str_tmp,'\0'); // Caractère de fin d'un string.
        return str_tmp->items; // <=> (*str_tmp).items
    }
    append(str_tmp,equation[*cursor]);
    *cursor = (strlen(equation) > *cursor ) ? *cursor +=1  : *cursor;
    return construct_number(cursor,equation,str_tmp);
}

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
void management_tokenizer(char* equation,TokensArray* tokens_array)
{
    size_t cursor = 0;
    for( uint8_t i = 0; i< strlen(equation);i++ )
    {
        if(is_operator(equation[cursor]))
        {
            Token equation_token ={0};
            equation_token.type = 0;
            equation_token.operator = which_operator(equation[cursor]);
            append(tokens_array,equation_token);
            cursor = (strlen(equation) > cursor) ? cursor += 1 : cursor;
        }
        else if(is_number(equation[cursor])) 
        {
            Token equation_token ={0};
            equation_token.type = 1;
            equation_token.operator = handle_number(equation,&cursor);
            append(tokens_array,equation_token);
        }
    }
}
int main()
{
    TokensArray tokens_array={0};

    char equation[256]="";
    printf("Calc : \n");
    scanf("%255s",equation);
    printf("COUNT CARAC : %d \n",strlen(equation));
    // printf("Affiche l'équation : %s \n",equation);
    management_tokenizer(equation,&tokens_array);


}