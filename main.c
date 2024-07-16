/*GHASSAN QANDEEL
1212397
SECTION 3*/
#include <stdio.h>
#include <stdlib.h>
typedef struct CharStack
{
    char characters;
    struct CharStack* next;
} CharStack;

void PrintStack(CharStack*cs);
CharStack *Make_Stack();
int getNumberOfEquationsInFile();
void ReadFromFile(CharStack*cs[]);
CharStack*ReverseStack(CharStack*cs);
CharStack*ReverseStackForprefix(CharStack*cs);
int ValidityOfEquations(CharStack*cs);
int ValidityOfEquations1(CharStack*cs);
int Validity(CharStack*cs);
int ConvertToInt(char c);
char Top( CharStack* cs );
void Pop ( CharStack * cs);
int Find (CharStack * cs,char c);
CharStack*Clone(CharStack*cs);
CharStack*ForNumberMoreThanDigit(CharStack*cs);
int BelongTo0_9(char c);
int BelongToOperation(char c);
int BelongToOpenBrackets(char c);
int BelongToCloseBrackets(char c);
int DisplayMenu();
int SizeOfEquation(CharStack*cs);
CharStack * InfixToPrefix (CharStack * cs);
CharStack * PostfixToPrefix (CharStack * cs);
int Priority (char c);
void WriteOnFile(FILE*ofile,CharStack* cs[]);
int EvaluteValidEqu(CharStack * cs);
int MathOP(int x,int y,char c);



int main()
{
    CharStack *arrayofstack[getNumberOfEquationsInFile()];
    FILE*ofile;
    for (int i=0; i<getNumberOfEquationsInFile(); i++)
        arrayofstack[i]=Make_Stack();
ReadFromFile(arrayofstack);

        int sw;
        printf("welcome,please choose what you want to do\n\n");
        sw=DisplayMenu();

        while(sw!=0)
        {
            if(sw==1)
            {
                ReadFromFile(arrayofstack);
                sw=DisplayMenu();
            }
            else if(sw==2)
            {
            for(int i=0; i<getNumberOfEquationsInFile(); i++)
                {
                    if (Validity(arrayofstack[i])== 1)
                    {
                        printf("Equation No %d -> Valid ",(i+1));
                    }
                    else if (Validity(arrayofstack[i])== 0)
                    {
                        printf("Equation No %d -> Invalid :",(i+1));
                    }
                    else if (Validity(arrayofstack[i])== -1)
                    {
                        printf("Equation No %d -> Invalid :",(i+1));
                    }
                    printf("\n");
                }
                sw=DisplayMenu();
            }
            else if(sw==3)
            {
                for(int i=0; i<getNumberOfEquationsInFile(); i++)
                    {if (Validity(arrayofstack[i])==1)
                    PrintStack(InfixToPrefix(arrayofstack[i]));
                    printf("\n");}
                    sw=DisplayMenu();
            }
            else if(sw==4)
            {
                for(int i=0; i<getNumberOfEquationsInFile(); i++)
                    {if (Validity(arrayofstack[i])==1)
                    printf("Equation No -> %d %d",(i+1),EvaluteValidEqu(InfixToPrefix(arrayofstack[i])));
                    printf("\n");}
                    sw=DisplayMenu();

            }
            else if(sw==5)
            {
                for(int i=0; i<getNumberOfEquationsInFile(); i++)
                    {if (Validity(arrayofstack[i])==0)
                    PrintStack((arrayofstack[i]));
                    printf("\n");}
                    sw=DisplayMenu();

            }
            else if (sw==6)
            {
                WriteOnFile(ofile,arrayofstack);
                break;
            }
        }

}

CharStack*Make_Stack()
{

    CharStack* cs;

    cs=(CharStack*)malloc(sizeof(CharStack));

    if (cs==NULL)
        printf("ERROR CHAR STACK OPEN");

    cs->next = NULL;

    return cs;
}
int getNumberOfEquationsInFile()
{
    FILE *fptr;
    int x = 0;
// Open a file in read mode
    fptr = fopen("Input_file.txt", "r");

    char myString[1000];

// check how many number in file
    while(fgets(myString, 1000, fptr))
        x++;

// Close the file
    fclose(fptr);
    return x;
}

void ReadFromFile(CharStack* cs[])
{
    FILE*fptr;
char name [20];
    int i = 0;
    printf("Enter name of the file\n");
    scanf("%s",name);

// Open a file in read mode
    fptr = fopen(name, "r");
if(fptr==NULL)
{
    printf("not exist");
    exit(-1);
}
// Store the content of the file
    char myString[1000];

// Read the content and print it
    while(fgets(myString, 1000, fptr))
    {
        for(int j=0 ; j<(strlen(myString)); j++)
            if (myString[j]!=(char)10)
                push(cs[i], myString[j]);
        i++;
    }
// Close the file
    fclose(fptr);
    for(int i = 0; i<getNumberOfEquationsInFile(); i++)
        cs[i]=ReverseStack(cs[i]);
}


void push (CharStack* cs,char c)
{

    CharStack* tempstack;
    tempstack = (CharStack*)malloc(sizeof(CharStack));
    if (tempstack==NULL)
        printf("ERROR!!!!!");

    tempstack->characters=c;
    tempstack->next=cs->next;
    cs->next=tempstack;
}
CharStack*ReverseStack(CharStack*cs)
{
    CharStack*temp ;
    temp=Make_Stack();
    while(cs->next!=NULL)
    {
        push(temp,cs->next->characters);
        cs=cs->next;
    }
    return temp;
}

int ValidityOfEquations(CharStack*Cs)
{

    CharStack *temp,*temp1,*cs;
    temp=Make_Stack();
    temp1=Make_Stack();
    cs=Clone(Cs);
    int x=0,y=0;
    while(cs->next!=NULL)
    {
        if(Top(cs)=='[' || Top(cs)=='(')
        {
            push(temp,Top(cs));
            x++;
        }
        else if(Top(cs)==']' ||Top(cs)==')')
        {
            push(temp1,Top(cs));
            y++;
        }

        Pop(cs);
    }

    temp1=ReverseStack(temp1);
    temp=ReverseStack(temp);





    int index=0;
    if (x==y)
        while(temp->next!=NULL||temp1->next!=NULL)
        {
            if(temp1->next==NULL)
                printf("%c No closing exist",Top(temp1));
            if(temp->next==NULL)
                printf("%c No opening exist",Top(temp));

            if(((Top(temp)=='(')&&(Find(temp1,')')))||((Top(temp)=='[')&&(Find(temp1,']'))))
                index++;

            else
            {
                printf("%c Not closing",Top(temp));
                break ;
            }
            Pop(temp);
        }
    else if (x!=y)
        index-1;


    if ((index==x)&&(index==y))
        return 1;
    else
        return 0;

}

int ConvertToInt(char c)
{
    for (int i=0; i<10; i++)
        if ((int)c==(48+i))
            return i ;

}

char Top( CharStack* cs )
{
    if(cs!=NULL )
        return cs->next->characters;
    else
    {
        printf( "Empty stack" );
        return 0;
    }
}
void Pop ( CharStack * cs)
{
    CharStack* firstcell;
    firstcell=Make_Stack();

    if (cs==NULL)
        printf("is empty ");
    else
    {

        firstcell=cs->next;
        cs->next=cs->next->next;
        free (firstcell);


    }
}


int Find (CharStack * cs,char c)
{
    CharStack * copy = Make_Stack();
    CharStack * copy1 = Make_Stack();
    copy=Clone(cs);
    copy1=Clone(cs);
    int i=0,flag=0;

    while(copy->next!=NULL)
    {
        if(copy->next->characters==c)
        {
            flag = 1;
            break;
        }
        i++;
        Pop(copy);
    }

    while (cs->next!=NULL)
        Pop(cs);

    int j=0;
    while(copy1->next!=NULL)
    {
        if(j!=i)
            push(cs,copy1->next->characters);

        else if (j==i)
        {
            Pop(copy1);
            j++;
            continue;
        }

        Pop(copy1);
        j++;
    }
    return flag ;
}
CharStack*Clone(CharStack*cs)
{
    CharStack* b;
    CharStack* c;
    b=Make_Stack();
    c=Make_Stack();

    while(cs->next!=NULL)
    {
        push(b,Top(cs));
        push(c,Top(cs));
        Pop(cs);
    }

    while(b->next!=NULL)
    {
        push(cs,Top(b));
        Pop(b);
    }

    c=ReverseStack(c);
    return c;
}
void PrintStack(CharStack*cs)
{
    CharStack*temp=Make_Stack();
    temp=Clone(cs);
    while(temp->next!=NULL)
    {
        printf("%c",Top(temp));
        Pop(temp);
    }
}

/*CharStack*ForNumberMoreThanDigit(CharStack*cs)
{
    CharStack*copy=Make_Stack();
    CharStack*copy1=Make_Stack();
    CharStack*temp =Make_Stack();
    copy=Clone(cs);
    copy1=Clone(cs);
    Pop(copy1);

    int first=0,end=0;
    int size=SizeOfEquation(cs);
    while(copy1->next!=NULL)
    {

    }
}*/

int BelongTo0_9(char c)
{
    return(((int)c>=48)&&(((int)c<=57)));
}
int BelongToOperation(char c)
{
    return(c=='+'||c=='-'||c=='/'||c=='*'||c=='%');
}
int BelongToOpenBrackets(char c)
{
    return (c=='['||c=='(');
}
int BelongToCloseBrackets(char c)
{
    return (c==']'||c==')');
}

int ValidityOfEquations1(CharStack*cs)
{
    CharStack*copy=Make_Stack();
    CharStack*copy1=Make_Stack();
    copy=Clone(cs);
    copy1=Clone(cs);
    Pop(copy1);
    while(copy1->next!=NULL)
    {
        if((BelongTo0_9(Top(copy))&&BelongToOpenBrackets(Top(copy1)))||(BelongToCloseBrackets(Top(copy))&&BelongTo0_9(Top(copy1))))
        {
            printf("No operation between %c%c ",Top(copy),Top(copy1));
            return 0;
        }
        Pop(copy1);
        Pop(copy);

    }
    return 1;
}
int Validity(CharStack*cs)
{
    if (ValidityOfEquations(cs)&&ValidityOfEquations1(cs))
        return 1 ;
    else if (ValidityOfEquations(cs)||ValidityOfEquations1(cs))
        return 0;
    else if ((ValidityOfEquations(cs)==0)&&(ValidityOfEquations1(cs)==0))
        return -1;

}
int DisplayMenu()
{
    int sw;

    printf("1-Read from input file\n");
    printf("2-Check	the validity of equations \n");
    printf("3-Convert equations from infix to prefix \n");
    printf("4-Evaluate the	prefix expressions \n");
    printf("5-Print	invalid equations\n");
    printf("6-Print	on file \n");
    printf("0-Exit\n");
    scanf("%d",&sw);

    return sw;
}
int SizeOfEquation(CharStack*cs)
{
    CharStack* copy=Make_Stack();
    copy=Clone(cs);
    int i=0;
    while(copy->next!=NULL)
    {
        i++;
        Pop(copy);
    }
    return i ;

}

CharStack * InfixToPrefix (CharStack * cs)
{
    CharStack * copy = Make_Stack();
    CharStack * temp = Make_Stack();
    CharStack * finalstack = Make_Stack();
    copy = Clone(cs);
    copy=ReverseStackForprefix(copy);
    int flagopenbrackets=0;

    while(copy->next!=NULL)
    {
        if (BelongTo0_9(Top(copy)))
            push(finalstack,Top(copy));

        else if (BelongToOpenBrackets(Top(copy)))
        {
            push(temp,Top(copy));
            flagopenbrackets=1;
        }

        else if (Top(copy)==')')
        {
            flagopenbrackets=0;
            while(Top(temp)!='(')
            {
                push(finalstack,Top(temp));
                Pop(temp);
            }
            Pop(temp);
        }

        else if (Top(copy)==']')
        {
            flagopenbrackets=0;
            while(Top(temp)!='[')
            {
                push(finalstack,Top(temp));
                Pop(temp);
            }
            Pop(temp);
        }
        else if (BelongToOperation(Top(copy))&&(flagopenbrackets==0))
        {
            while((temp->next!=NULL)&&(Priority(Top(copy))<=Priority(Top(temp))))
            {
                push(finalstack,Top(temp));
                Pop(temp);
            }
            push(temp,Top(copy));
        }
        else if (BelongToOperation(Top(copy))&&(flagopenbrackets==1))
            push(temp,Top(copy));



        Pop(copy);


    }
    while(temp->next!=NULL)
    {
        push(finalstack,Top(temp));
        Pop(temp);

    }
    return finalstack;
}
int Priority (char c)
{
    if (c=='+'||c=='-')
        return 1;
    else if (c=='*'||c=='/')
        return 2;
    else
        return 0;



}
/*CharStack * PostfixToPrefix (CharStack * cs)
{
    int size =SizeOfEquation(cs);

    CharStack*finalstack=Make_Stack();
    finalstack=Clone(cs);
    CharStack*tempprefix=Make_Stack();
    CharStack*finalprefix=Make_Stack();

    while(finalstack->next!=NULL)
    {
        if (BelongTo0_9(Top(finalstack)))
            push (tempprefix,Top(finalstack));


        CharStack*temp=Clone(tempprefix);
        if (temp->next!=NULL)
            Pop(temp);

        else if (BelongToOperation(Top(finalstack)))
        {
            if(BelongTo0_9(Top(tempprefix))&&BelongTo0_9(Top(temp)))
            {
                char t,t1;
                t=Top(tempprefix);
                Pop(tempprefix);

                t1=Top(tempprefix);
                Pop(tempprefix);

                push(tempprefix,Top(finalstack));
                push(tempprefix,t1);
                push(tempprefix,t);
            }
            else if (BelongTo0_9(Top(tempprefix))&&BelongToOperation(Top(temp)))
            {
                char t2;
                t2=Top(tempprefix);
                Pop(tempprefix);

                push(tempprefix,Top(finalstack));
                while(tempprefix->next!=NULL)
                {
                    push(tempprefix,Top(tempprefix));
                    Pop(tempprefix);
                }
                push(tempprefix,t2);
            }
            //tempprefix=ReverseStack(tempprefix);

        }

        printf("\n<<<<<<<<<<<<");
        PrintStack(finalstack);
        printf("<<<<<<<<<<<<\n");
        PrintStack(tempprefix);
        Pop(finalstack);

    }

    while(tempprefix->next!=NULL)
    {
        push(finalprefix,Top(tempprefix));
        Pop(tempprefix);
    }



    return finalprefix;

}*/
CharStack*ReverseStackForprefix(CharStack*cs)
{
    CharStack*temp =Make_Stack();
    CharStack*clo =Make_Stack();
    clo=Clone(cs);
    while(clo->next!=NULL)
    {
        if (Top(clo)=='(')
            push(temp,')');
        else if (Top(clo)==')')
            push(temp,'(');
        else if (Top(clo)=='[')
            push(temp,']');
        else if (Top(clo)==']')
            push(temp,'[');

        else
            push(temp,Top(clo));
        Pop(clo);
    }
    return temp ;
}
void WriteOnFile(FILE*ofile,CharStack*cs[])
{

    ofile=fopen("Output_file.txt","w");
    for(int i=0; i<(getNumberOfEquationsInFile()); i++)
    {
        if (Validity(cs[i])==0)
            while(cs[i]->next!=NULL)
            {
                fprintf(ofile,"%c",Top(cs[i]));
                Pop(cs[i]);
            }

        fprintf(ofile,"\n","\n");
    }
    fclose(ofile);


}
int EvaluteValidEqu(CharStack * cs)
{

    CharStack * copy =Make_Stack();
    CharStack * temp =Make_Stack();
    copy=Clone(cs);
    copy=ReverseStack(copy);

    int result=0;
    while(copy->next!=NULL)
    {
        if(BelongTo0_9(Top(copy)))
            push(temp,Top(copy));

        else
        {
            int x,y ;
            x=ConvertToInt(Top(temp));
            Pop(temp);
            y=ConvertToInt(Top(temp));
            Pop(temp);
            result=MathOP(x,y,Top(copy));
            push(temp,(char)result);
        }

        Pop(copy);
    }



    return result;

}
int MathOP(int x,int y,char c)
{
    int z;
    if(c=='+')
        z=x+y;
    else if(c=='-')
        z=x-y;
    else if(c=='*')
        z=x*y;
    else if(c=='/')
        z=x/y;

    return z;



}
