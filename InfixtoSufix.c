#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Postfix{
    char data;
    struct Postfix *ant;
}post;
typedef struct Operators{
    char data;
    struct Operators *ant;
}ops;
typedef struct Result{
    int data;
    struct Result *ant;
}res;

void central_operations(void);
void Data_controler(char);
void cad_reverse(int, char *);
int isoperator(char);
int hierarchy(char);
void push_ops(char);
char pop_ops(void);
void push_post(char);
void pop_post(void);
void change_post(void);
void push_new_post(char);
void display_post(int);
void evaluate(void);
int operation(int, int, char);
void push_digits_eval(int);
int pop_digits_eval(void);

post *top_post = NULL;//Pointer to stack 1
ops *top_ops = NULL;
post *top_change_post = NULL;
char * pointer_reverse = NULL;
res *top_digits_eval = NULL;

int main(){
    ops *Optors;
    Optors = (ops*)malloc(sizeof(ops));
    Optors->data = '(';
    Optors->ant = NULL;
    top_ops = Optors;
    central_operations();
    return 0;
}
void central_operations(){
    int i, longitud;
    char pop_element;
    char cadena[25];
    printf("Examen Estructura de datos");
    printf("\nIngresa una cadena en infijo: ");
    gets(cadena);
    longitud = strlen(cadena);
    printf("\n\nCadena en Infijo: %s",cadena);
    for(i = 0; i < longitud; i++){
        Data_controler(cadena[i]);
    }
    while(top_ops != NULL){
        pop_element = pop_ops();
        //Here put the instruction to move to the other element of the Stack
        push_post(pop_element);
    }
    pop_post();//Here the value of top_ops is NULL
    change_post();
    cad_reverse(longitud,&cadena[0]);
    while(top_change_post != NULL){
        //printf("\ntop_change_post: %c", top_change_post->data);
        evaluate();
        top_change_post = top_change_post->ant;
    }
    printf("\nResultado de la operacion: %d",top_digits_eval->data);
}
void cad_reverse(int longitud,char *pointer_cad){
    char pop_element;
    ops *Opt_rev;
    Opt_rev = (ops*)malloc(sizeof(ops));
    Opt_rev->data = '(';
    Opt_rev->ant = NULL;
    top_ops = Opt_rev;
    int i;
    char cad_rev[25];
    for(i = (longitud-1); i >= 0; i--){
        if(*pointer_cad == ')')
            cad_rev[i] = '(';
        else if(*pointer_cad == '(')
            cad_rev[i] = ')';
        else
            cad_rev[i] = *pointer_cad;
        pointer_cad++;
    }
    for(i = 0; i < longitud; i++){
        Data_controler(cad_rev[i]);
        //printf("\nCad_rev: %c",cad_rev[i]);
    }
    while(top_ops != NULL){//Con esto volteo los operadores restantes de la pila de operadores a la cadena de posfijo
        pop_element = pop_ops();
        //Here put the instruction to move to the other element of the Stack
        push_post(pop_element);
    }
    pop_post();
    display_post(0);
}
void Data_controler(char data){
    char pop_element;
    int isop = isoperator(data);
    if(isop == 1){//if isoperator return 1(data is an operator)
        if(top_ops == NULL){
            push_ops(data);
        }
        else if(hierarchy(data) < hierarchy(top_ops->data) || hierarchy(data) == hierarchy(top_ops->data)){
            //printf("\nMenor o igual");
            pop_element = pop_ops();
            push_ops(data);
            push_post(pop_element);
        }
        else{
            push_ops(data);
        }
    }
    else{//data is a number o letter
        if(data == '('){
            push_ops(data);
        }
        else if(data == ')'){
            while(top_ops->data != '('){
                pop_element = pop_ops();
                push_post(pop_element);
            }
            pop_ops();
            //Here We need a while to pop the elements from operand_stack and push in postfix_stack
        }
        else{//data is a number or a leter
            push_post(data);
        }
    }
}
int isoperator(char data){
    if(data == '^' || data == '*' || data == '/' || data == '+' || data == '-'){//Si el dato
        return(1);
    }
    else{
        return(0);
    }
}
int hierarchy(char data){
    if(data == '^'){
        return(4);
    }
    else if(data == '*' || data == '/'){
        return(3);
    }
    else if(data == '+' || data == '-'){
        return(2);
    }
    else if(data == '('){
        return(1);
    }
}
void push_ops(char data){
    ops *new_data;
    new_data = (ops*)malloc(sizeof(ops));//Each time that we call the function a new struct is created and added to the stack;
    new_data->data = data;
    //printf("\nElemento agregado a pila de operandos\nDato: %c",new_data->data);
    //printf("\nDireccion del nuevo elemento: %p",new_element);
    new_data->ant = top_ops;
    top_ops = new_data;
    //printf("\nTop: %p",top_ops);
}
char pop_ops(){
    ops *top_aux;
    top_aux = top_ops;
    top_ops = top_ops->ant;
    //printf("\nDato eliminado, Puedes disponer de ese espacio de memoria\nTop: %p",top1);
    return top_aux->data;
    free(top_aux);
}
void push_post(char data){
    post *new_data;
    new_data = (post*)malloc(sizeof(post));//Each time that we call the function a new struct is created and added to the stack;
    new_data->data = data;
    //printf("\nElemento agregado a la cadena en posfijo\n Data: %c", new_data->data);
    //printf("\nDireccion del nuevo elemento: %p",new_element);
    new_data->ant = top_post;
    top_post = new_data;
    //printf("\nTop: %p",top_ops);
}
void pop_post(){
    post *top_aux;
    top_aux = top_post;
    top_post = top_post->ant;
    //printf("\nTop: %p",top_post);
    free(top_aux);
}
void change_post(){
    //printf("\nTop: %p",top_post);
    while(top_post != NULL){//while pointer point to an element
        //printf("\nTop: %p",iterator);
        push_new_post(top_post->data);
        top_post = top_post->ant;
    }
    display_post(1);
}
void push_new_post(char data){
    post *new_data;
    new_data = (post*)malloc(sizeof(post));//Each time that we call the function a new struct is created and added to the stack;
    new_data->data = data;
    //printf("\nDireccion del nuevo elemento: %p",new_element);
    new_data->ant = top_change_post;
    top_change_post = new_data;
}
void display_post(int option){
    post *iterator;
    if(option){
         iterator = top_change_post;
         printf("\n\nCadena en Postfijo: ");
    }
    else{
        iterator = top_post;
        printf("\nCadena en Prefijo: ");
    }
    while(iterator != NULL){//while pointer point to an element
        //printf("\nTop: %p",iterator);
        printf("%c",iterator->data);
        iterator = iterator->ant;
    }
    printf("\n\n");
}
void evaluate(){
    //Here top_post has a different value of NULL
    int oprnd1, oprnd2, resultado, numero;
    numero = (top_change_post->data) - '0';
    if(isoperator(top_change_post->data) != 1){//If is a digit
        push_digits_eval(numero);
    }
    else{//If is an operator
        oprnd1 = pop_digits_eval();
        oprnd2 = pop_digits_eval();
        resultado = operation(oprnd1,oprnd2,top_change_post->data);
        //printf("\nResultado: %d",resultado);
        push_digits_eval(resultado);
    }
}
int operation(int num1, int num2, char operador){
    switch(operador){
        case '+':
            return(num2+num1);
        break;
        case '-':
            return(num2-num1);
        break;
        case '*':
            return(num2*num1);
        break;
        case '/':
            return(num2/num1);
        break;
        case '^':
            return (pow(num2,num1));
        break;
    }
}
void push_digits_eval(int data){
    //int idata = data - '0';
    res *new_data;
    new_data = (res*)malloc(sizeof(res));//Each time that we call the function a new struct is created and added to the stack;
    new_data->data = data;
    //printf("\nElemento agregado a pila de digitos\nDato: %d",new_data->data);
    //printf("\nDireccion del nuevo elemento: %p",new_element);
    new_data->ant = top_digits_eval;
    top_digits_eval = new_data;
}
int pop_digits_eval(){
    res *top_aux;
    top_aux = top_digits_eval;
    top_digits_eval = top_digits_eval->ant;
    //printf("\nDato eliminado: %d",top_aux->data);
    return top_aux->data;
    free(top_aux);
}


