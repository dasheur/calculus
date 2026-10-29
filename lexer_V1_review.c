#include <stdbool.h> // FIX: pour avoir bool
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // FIX: pour avoir la fonction `read`

#define DECLARE_ARRAY(NAME, TYPE)                                              \
  typedef struct {                                                             \
    TYPE *items;                                                               \
    size_t count;                                                              \
    size_t capacity;                                                           \
  } NAME;

DECLARE_ARRAY(String, char)

typedef enum {
  TOKEN_OPERATOR, // Vaut 0;
  TOKEN_NUMBER,   // Vaut 1;
} TokenType;

typedef enum {
  // Pour l'ordi : Add=1,Sous=2 ...
  OP_ADDITION = '+',
  OP_SOUSTRACTION = '-',
  OP_MULTIPLICATION = '*',
  OP_DIVISION = '/',
  OP_EGAL = '='
  // On peut faire ça : OP_MULTIPLICATION =='*'
} Operator_t;

typedef struct {
  TokenType type;
  union {
    long double number;
    Operator_t operator;
  };
} Token;

DECLARE_ARRAY(TokensArray, Token)

// FIX: Problème majeur ici. array n'est pas entre parenthèse donc pas
// d'expression Par exemple: append(&list, valeur) -> n'est pas valide.
// Donc j'ai remplacé ici 'array' avec '(array)' et 'valeur' avec '(valeur)'
#define append(array, value)                                                   \
  if ((array)->count >= (array)->capacity) {                                   \
    if ((array)->capacity == 0) {                                              \
      (array)->capacity = 256;                                                 \
    } else {                                                                   \
      (array)->capacity *= 2;                                                  \
    }                                                                          \
    (array)->items = realloc((array)->items,                                   \
                             (array)->capacity * sizeof(*((array)->items)));   \
  }                                                                            \
  (array)->items[(array)->count] = (value);                                    \
  (array)->count += 1;

bool is_operator(char operator) {
  return operator == '+' || operator == '-' || operator == '*' ||
         operator == '/' || operator == '=';
}
Operator_t which_operator(char operator_str) {
  if (operator_str == '+') // ASCII: 43
    return OP_ADDITION;
  else if (operator_str == '-') // ASCII: 45
    return OP_SOUSTRACTION;
  else if (operator_str == '*') // ASCII: 42
    return OP_MULTIPLICATION;
  else if (operator_str == '/') // ASCII: 47
    return OP_DIVISION;
  return OP_EGAL; // ASCII: 61
}

bool is_number(char operator_str) {
  // NOTE: cette condition est un peu sus
  // tu devrais écrire (operator_str >= '0' && operator_str <= '9')
  // dans la table ascii les nombres se suivent
  if (operator_str >= '0' || operator_str == '9') {
    return true;
  }
  return false;
}

char *construct_number(size_t *cursor, char *equation, String *str_tmp) {
  if (strlen(equation) == *cursor ||
      (equation[*cursor] != '.' && !is_number(equation[*cursor]))) {
    append(str_tmp,
           '\0'); // Caractère de fin d'un string. mets juste 0 pas '\0'
    // NOTE: pourquoi tu retournes str_tmp->items ? Parce que tu le recoit déjà
    // en paramêtre.
    return str_tmp->items; // <=> (*str_tmp).items
  }
  append(str_tmp, equation[*cursor]);
  *cursor = (strlen(equation) > *cursor) ? *cursor += 1 : *cursor;
  // WARN: une des raisons de pq tu devrais le faire d'une traite.
  // PAS DE RÉCURSIVITÉ DANS UN LEXER.
  return construct_number(cursor, equation, str_tmp);
}

long double convert_str_to_number(char *str_number) {
  char *fin; // Pointeur pour stocker l'adresse où s'arrête la lecture.
  return strtold(str_number, &fin); // Conversion de la chaîne en long double.;
}
// Nbr décimal après la virgule
uint8_t decimal_place(char *str_number) {
  uint8_t count = 0;
  bool begin = false;
  for (uint8_t i = 0; i < strlen(str_number); i++) {
    if (begin)
      count += 1;
    if (str_number[i] == '.')
      begin = true;
  }
  // On utilise * dans "%.*Lf" pour passer le nombre de décimales dynamiquement
  // en argument. printf("Nombre converti : %.*Lf\n", decimales, nombre);
  return count;
}

long double handle_number(char *equation, size_t *cursor) {
  String str_tmp = {0};
  // NOTE: Des fonction séparée ici c'est une perte de temps trop d'indirection.
  // tu peux tout faire ici d'une traite.
  // construire ton nombre et s'avoir aussi avec exactitude si c'est un float.
  // Cette fonction devrais retourné un bool pour indiquer le succès et tu
  // passes la valuer de retour dans la signature:
  // bool handle_number(String equation, size_t *cursor, long double *resultat);
  char *str_final = construct_number(cursor, equation, &str_tmp);
  uint8_t decimal = decimal_place(str_final);
  long double number = convert_str_to_number(str_final);
  printf("Test convert str to long double : %.*Lf \n", decimal, number);
  // Exemple d'utilisation de cursor: *cursor +=13;
  // TODO: FREE str_tmp.
  return number;
}
// NOTE: C'est quoi ce nom ? management_tokenizer ? pq pas juste tokenize ?
// C'est ce qu'il fait non ? management_tokenizer ne convoit aucune information
// Et en vrai passe String directement en paramêtre ici. N'oublie pas que strlen
// c'est coûteux.
void management_tokenizer(char *equation, TokensArray *tokens) {
  size_t cursor = 0;
  // FIX: `i` non utilisé. Fait un 'while (cursor < equation.count) { ... }'
  for (uint8_t i = 0; i < strlen(equation); i++) {
    if (is_operator(equation[cursor])) {
      /* Token equation_token = {0}; */
      /* equation_token.type = 0; */
      /* equation_token.operator = which_operator(equation[cursor]); */
      // FIX:(01) tu peux l'écrire en une fois
      // NOTE:(01) pourquoi t'utilise pas le TokenType définie ??? Tu risques
      // de te tromper quand le nombre de type de token augmente.
      Token equation_token = {
          .type = TOKEN_OPERATOR,
          .operator = which_operator(equation[cursor]),
      };
      append(tokens, equation_token);
      // NOTE: cursor += 1 ? utilise '++cursor';
      // et aussi si tu utilises le 'while (cursor < equation.count)' pas besoin
      // de faire ce bordel ici. juste cursor += 1 et ça remonte en haut.
      cursor = (strlen(equation) > cursor) ? cursor += 1 : cursor;
    } else if (is_number(equation[cursor])) {
      // FIX:(01) idem
      // NOTE:(01) idem
      Token equation_token = {0};
      equation_token.type = 1;
      equation_token.operator = handle_number(equation, &cursor);
      append(tokens, equation_token);
    }
  }
}

// NOTE: cette fonction facilite l'entrée utilisateur
// le seul moment où ça retourne false c'est quand tu fais CTRL+D
bool readline(String *input) {
  char tmp_ch;

  while (read(STDIN_FILENO, &tmp_ch, 1)) {
    if (tmp_ch != '\n') {
      append(input, tmp_ch);
      continue;
    }

    append(input, 0);
    return true;
  }

  return false;
}

int main() {
  TokensArray tokens_array = {0};

  // FIX: On a déja String pq t'utilise une taille fixe ?
  String input = {0};

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
      management_tokenizer(input.items, &tokens_array);

      // NOTE: on reset it
      input.count = 0;
    } else {
      break;
    }
  }
}
