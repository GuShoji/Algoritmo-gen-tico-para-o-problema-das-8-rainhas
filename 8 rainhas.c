#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<time.h>

#define MAX_IND 1000

float alg(char x);
float sinal(char x, float a);
float func(float L1, float L2, float C1, float C2, float w);
float converter(int matriz[], int inicio, int fim);

typedef struct geracao{
    int matriz[24];
    int erro;
}geracao;


int main()
{
    FILE *file, *resul;
    clock_t t;
    char x[100], num[19], nume[4], pot[17], pote[4], c;
    int i, a, j=0,k=0, try=0, trytry=0, check=0, teste[52]={1,0,1,0,1,1,0,1,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0};

    
    j=0;

   /*for(i=0;i<121;i++)
  {
      printf("%.14lf --- %.14lf\n", tab[i].freq, tab[i].ganho);
  }*/
   t = clock();
    srand(time(NULL));
    geracao g[MAX_IND];
    geracao reserva;
    gerar_geracao(g);
    erro(g);
    for(i=0;i<100;i++)
    {
    merge_sort(g, 0, MAX_IND-1);
    //imprimir(g);
    imprimir_solo(g);
    selecao(g);
    mutacao(g);
    erro(g);
    scanf("%d", &try);
    }
    //printf("--------------------\n");
    
    
   //printf("%.14lf\n", func(converter(teste,0,12),converter(teste,13,25),converter(teste,26,38),converter(teste,39,51), (2*pi*100000)));

    //erro(g, tab);

   
   return 0;
}


erro(geracao ger[])
{
    int i, j, k, l, ini, fim, erro;
    int peso[8] = {7, 5, 3, 1, -1, -3, -5, -7};
    int vetor[8];
    int ataques;
    for(i=0;i<MAX_IND;i++)
    {
        ini=0;
        fim=2;
        
        for(j=0;j<8;j++)
        {
            vetor[j]=converter(ger[i].matriz, ini, fim);
            ini+=3;
            fim+=3;
        }
        erro=0;
        
        for(j=0;j<8;j++)   
        {
            for(k=j+1, l=1;k<8;k++,l++)
            {
                
                if(vetor[j]==vetor[k])
                {
                    erro++;
                   
                }
                if(vetor[j]==vetor[k]+l)
                    {
                        erro++;
                       
                    }
                    if(vetor[j]==vetor[k]-l)
                    {
                        erro++;
                        
                    }
                
            }
            for(l=j-1,k=1;l>-1;l--,k++)
            {
                
                if(vetor[j]==vetor[l])
                    {
                        erro++;
                      
                    }
                    if(vetor[j]==vetor[l]+k)
                    {
                        erro++;
                        
                    }
                     if(vetor[j]==vetor[l]-k)
                    {
                        erro++;               
                    }
                
            }
        }     
         ger[i].erro = erro/2;
        
    }

}


int imprimir_solo(geracao ger[])
{
    int i, j, ini, fim, output=0;
    int vetor[8];
    ini=0;
    fim=2;
    
    for(j=0;j<24;j++)
    {
            printf("%d", ger[0].matriz[j]);
    }
    printf("--------- %d", ger[0].erro);
    printf("\n");
    
    for(j=0;j<8;j++)
        {
            vetor[j]=converter(ger[0].matriz, ini, fim);
            ini+=3;
            fim+=3;
        }
       for(j=0;j<8;j++)
        {
        printf("%d-", vetor[j]);
        }
        printf("\n");
        printf("%d\n", ger[0].erro);
   
}

float converter(int matriz[], int inicio, int fim)
{
    int i, j, x=0, exp=0;
    float out;
    for(i=fim, j=1;i>inicio-1;i--)
    {
        x+=matriz[i]*j;
        j=j*2;
    }

    //printf("%.14lf\n", out);
    return x;
}

copiar(geracao a[], geracao *b)
{
    int i;
    if(a[0].erro < b->erro)
    {
    for(i=0;i<52;i++)
    {
        b->matriz[i] = a[0].matriz[i];
    }
    b->erro = a[0].erro;
    }
}

elitismo(geracao a[], geracao *b)
{
   
    int i, j;
    if(a[0].erro > b->erro)
    {
    for(j=0;j<52;j++)
    {
        a[0].matriz[j] = b->matriz[j];
    }
    a[0].erro = b->erro;
    
    }
}


gerar_geracao(geracao g[])
{
    int i, j;
    srand(time(NULL));
    for(i=0;i<MAX_IND;i++)
    {
        for(j=0;j<32;j++)
        {
            g[i].matriz[j]=rand()%2;
            //printf("%d", g[i].matriz[j]);
        }
        g[i].erro=0;
        
        //printf("\n");
    }
}





mutacao(geracao ger[])
{
    int i,mutx=0, muty=0, x=0;
    x=MAX_IND*24*0.25;
    for(i=0;i<x;i++)
    {
    mutx = (rand()%1000);
    muty = (rand()%24);
    if(ger[mutx].matriz[muty]==1)
    {
        ger[mutx].matriz[muty]=0;
    }
    else
    {
        ger[mutx].matriz[muty]=1;
    }
    }  
}

void merge(geracao ger[], int inicio, int meio, int fim)
{
    int tamanho = fim - inicio + 1;
    geracao *temp = (geracao *)malloc(tamanho * sizeof(geracao));
    int aux = 0;
    int p1 = inicio;
    int p2 = meio + 1;

    while (p1 <= meio && p2 <= fim)      
    {
       
        if (ger[p1].erro < ger[p2].erro)
        {
            temp[aux++] = ger[p1++];
        }
        else
        {
            temp[aux++] = ger[p2++];
        }
    }

    while (p1 <= meio)
    {
        temp[aux++] = ger[p1++];
    }

    while (p2 <= fim)
    {
        temp[aux++] = ger[p2++];
    }

    for (aux = 0; aux < tamanho; ++aux)
        ger[inicio + aux] = temp[aux];

    free(temp);        
   
}

merge_sort(geracao ger[], int inicio, int fim)
{
    int meio;
    if(inicio<fim)
    {
        meio = floor((inicio+fim)/2);
        merge_sort(ger, inicio, meio);
        merge_sort(ger, meio+1, fim);
        merge(ger, inicio, meio ,fim);
    }

}



int sorteio4(int inicio, int fim)
{
    int result4=0, output=0;
    result4 = (rand()%100)+1;
    if(result4<=50)
    {
        output=inicio;
    }
    else
    {
        if(result4<=75)
        {
            output=inicio+1;
        }
        else
        {
            if(result4<=80)
            {
                output=inicio+2;
            }
            else
            {
                if(result4<=85)
                {
                    output=inicio+3;
                }
                else
                {
                    if(result4<=90)
                    {
                    output=inicio+4;
                    }
                    else
                    {
                         if(result4<=92)
                        {
                        output=inicio+5;
                        }
                        else
                        {
                            if(result4<=94)
                            {
                            output=inicio+6;
                            }
                            else
                            {
                                if(result4<=96)
                                {
                                output=inicio+7;
                                }
                                else
                                {
                                    if(result4<=98)
                                    {
                                    output=inicio+8;
                                    }
                                    else
                                    {
                                        output=inicio+9;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("------%d-----\n", output);
    return output;
}

sorteio3(int inicio, int fim)
{

    int result3=0;
    
    result3 = (rand()%10000)+1;
    //printf("----sort3----- %d\n", result3);
    if(result3<=5000)
    {
        //printf("----QQ1-----\n");
        sorteio4(inicio, ((((fim+1-inicio)/5)-1)+inicio));
    }
    else
    {
        if(result3<=7500)
        {
            //printf("----QQ2-----\n");
            sorteio4(((((fim+1-inicio)/5))+inicio), (((((fim+1-inicio)*2)/5)-1)+inicio));
        }
        else
        {
            if(result3<=8750)
            {
                //printf("----QQ3-----\n");
                sorteio4((((((fim+1-inicio)*2)/5))+inicio), (((((fim+1-inicio)*3)/5)-1)+inicio));
            }
            else
            {
                if(result3<=9375)
                {
                    //printf("----QQ4-----\n");
                    sorteio4((((((fim+1-inicio)*3)/5))+inicio), (((((fim+1-inicio)*4)/5)-1)+inicio));
                }
                else
                {
                   //printf("----QQ5-----\n");
                    sorteio4((((((fim+1-inicio)*4)/5))+inicio), (((((fim+1-inicio)*5)/5)-1)+inicio));
                }
            }
        }
    }
   
}


sorteio2(int inicio, int fim)
{
    
    int result1=0;
    result1 = (rand()%10000)+1;
    //printf("----sort2----- %d\n", result1);
    if(result1<=5000)
    {
        //printf("----QQ1-----\n");
        sorteio3(inicio, ((((fim+1-inicio)/5)-1)+inicio));
    }
    else
    {
        if(result1<=7500)
        {
            //printf("----QQ2-----\n");
            sorteio3(((((fim+1-inicio)/5))+inicio), (((((fim+1-inicio)*2)/5)-1)+inicio));
        }
        else
        {
            if(result1<=8750)
            {
                //printf("----QQ3-----\n");
                sorteio3((((((fim+1-inicio)*2)/5))+inicio), (((((fim+1-inicio)*3)/5)-1)+inicio));
            }
            else
            {
                if(result1<=9375)
                {
                    //printf("----QQ4-----\n");
                    sorteio3((((((fim+1-inicio)*3)/5))+inicio), (((((fim+1-inicio)*4)/5)-1)+inicio));
                }
                else
                {
                    //printf("----QQ5-----\n");
                    sorteio3((((((fim+1-inicio)*4)/5))+inicio), (((((fim+1-inicio)*5)/5)-1)+inicio));
                }
            }
        }
    }
    
}


sorteio1(int inicio, int fim)
{
    
    int result1=0;
    result1 = (rand()%400)+1;
     //printf("----sort1----- %d\n", result1);
    if(result1<=300)
    {
        //printf("----Q1-----\n");
        sorteio2(inicio,(((fim/4)-1)));
    }
    else
    {
        if(result1<=350)
        {
            //printf("----Q2-----\n");
            sorteio2((fim/4),((fim/2)-1));
        }
        else
        {
            if(result1<=400)
            {
                //printf("----Q3-----\n");
                sorteio2((fim/2),(((fim*3)/4)-1));
            }
            else
            {
                //printf("----Q4-----\n");
                sorteio2(((fim*3)/4),fim);
            }
        }
    }
}




int imprimir_solos(geracao g)
{
    int j, output=0;
        for(j=0;j<52;j++)
        {
            printf("%d", g.matriz[j]);
        }
        printf("--------- %lf", g.erro);
        printf(":::\n");
        
        if(g.erro==0.001521)
        {
        output=1;
        }
    return output;
}


crossover(geracao ger[], geracao temp[], int posicao, int p1, int p2)
{
    int i, c1, c2, c3, c4, c5, c6, c7, c8;
    c1= rand()%3;
    c2= (rand()%3)+3;
    c3= (rand()%3)+6;
    c4= (rand()%3)+9;
    c5= (rand()%3)+12;
    c6= (rand()%3)+15;
    c7= (rand()%3)+18;
    c8= (rand()%3)+21;
    //printf("%d-%d-%d-%d-%d-%d-%d-%d\n", c1,c2,c3,c4,c5,c6,c7,c8);
    for(i=0;i<c1;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c2;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c3;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c4;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c5;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c6;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c7;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    for(;i<c8;i++)
    {
        temp[posicao].matriz[i]=ger[p1].matriz[i];
    }
    //imprimir_solo(temp, posicao);
    //printf("-----------filho---------\n");
}




selecao(geracao ger[])
{
    int i, result1, result2, p1=0, p2=0;
    geracao *temp = (geracao *)malloc(1000 * sizeof(geracao));
    //printf("------inicio seleção-----\n");
    for(i=0;i<MAX_IND;i++)
    {
    p1=sorteio1(0,MAX_IND);
    //printf("------%d-----\n", p1);
    //imprimir_solo(ger, p1);
    p2=sorteio1(0,MAX_IND);
    //printf("------%d-----\n", p2);
    //imprimir_solo(ger, p2);
    crossover(ger, temp, i, p1, p2);
    }
    for(i=0;i<MAX_IND;i++)
    {
    ger[i]=temp[i];
    }
    
    //printf("------fim seleção-----\n");
}

imprimir(geracao g[])
{
    int i, j;
    for(i=0;i<MAX_IND;i++)
    {
        for(j=0;j<24;j++)
        {
            printf("%d", g[i].matriz[j]);
        }
        printf("--------- %d", g[i].erro);
        printf("\n");
    }
}

float sinal(char x, float a)
{
    if(x=='-')
    {
        return -a;
    }
return a;
}

float func(float L1, float L2, float C1, float C2, float w)
{
    float a, b;
    a=(C1*C2*L1*L2*100*pow(w,4))-((C2*L2+(C2+C1)*L1)*100+C1*L2*50)*pow(w,2)+(100+50);
    b=(-(C1*C2*L2*50*100+C1*L1*L2)*pow(w,3))+(((C2+C1)*50*100+L2+L1)*w);
    //printf("%.14lf\n %.14lf\n", a, b);
    float complexo = sqrt(pow(b,2)+pow(a,2));
  
    float fun = fabs(150/complexo);
    return fun;
}

float alg(char x)
{
    float a;
    if(x=='0')
      {
          a=0;
      }
      else
      {
          if(x=='1')
          {
          a=1;
          }
          else
          {
            if(x=='2')
            {
            a=2;
            }
            else
            {
                if(x=='3')
                {
                a=3;
                }
                else
                {
                    if(x=='4')
                    {
                    a=4;
                    }
                    else
                    {
                        if(x=='5')
                        {
                        a=5;
                        }
                        else
                        {
                            if(x=='6')
                            {
                            a=6;
                            }
                            else
                            {
                                if(x=='7')
                                {
                                a=7;
                                }
                                else
                                {
                                    if(x=='8')
                                    {
                                    a=8;
                                    }
                                    else
                                    {
                                    a=9;
                                    }
                                }
                            }
                        }
                    }
                }
            }
          }
      }
      
      return a;
}

