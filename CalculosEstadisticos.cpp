#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Bibliotecas Graficas
#include <graphics.h>
#include <winbgim.h>

/* //bibliotecas para conjuntos
#include <iostream>
#include <set>
using namespace std; */


//Estadisticos
float Varianza(int tp);
float Media();
float Mediana();
int Moda();
int Sumatoria();

//Funciones necesarias (sin retorno)
void Ordenar();
void SetArr();
void GraphicPuntos();

//Informacion Global
int *arr,tm;
int SetCnt=1,*arrSets[2],cnt=0; 

int main(int argc, char const *argv[]){
    int rang;

    // Genearador de datos (Temporal para las pruebas de funciones)
    printf("\n\tIngresa la cantidad de datos: ");
    scanf("%d",&tm);
    arr = new int [tm];

    printf("\n\tIngresa el rango (0 to n): ");
    scanf("%d",&rang);


    srand(time(NULL));
    for (int i = 0; i < tm; i++){
        arr[i]=rand()%(rang+1);
        //scanf("%d",&arr[i]);
    }

    Ordenar();

    for (int i = 0; i < tm; i++){
        printf(" %d, ",arr[i]);
    }

    printf("\n\tLa moda es: %d \n",Moda());
    for (int i = 0; i < 2; i++){
        arrSets[i]=new int [SetCnt];
    }
    
    SetArr();
    printf("\n\tHay %d valores diferentes. \n",SetCnt);
    for (int i = 0; i < SetCnt; i++){
        printf("\n\tValor: %d | Frecuency: %d\n",arrSets[0][i],arrSets[1][i]);
    }
    
    printf("\n\tLa Media es: %.2f \n",Media());
    printf("\n\tLa Mediana es: %.2f \n",Mediana());
    float varia= (float) Varianza(1);
    printf("\n\tLa Varianza es: %.2f \n",varia);
    printf("\n\tLa Desviacion es: %.2f \n",sqrt(varia));
    //Fin de generador
    
    //Codigo de procesos
    GraphicPuntos();

    return 0;
}

void Ordenar(){
    //ordenador de valores acendente
    int menor,pos,aux;
    for (int i = 0; i < tm; i++){
        menor=190000;
        aux=arr[i];
        for (int i1 = i; i1 < tm; i1++){
            if (arr[i1]<menor){
                menor=arr[i1];
                pos=i1;
            }   
        }
        arr[i]= menor;
        arr[pos]= aux;
    }
}

float Media(){
    int sum=Sumatoria();
    return (float)(sum/tm);
}

int Sumatoria(){
    int sum=0;
    for (int i = 0; i < tm; i++){
        sum+=arr[i];
    }
    return sum;
}

float Mediana(){
    float r;

    if (tm%2==0){
        r=(float) (arr[tm/2]+arr[(tm/2)+1])/2;
    }else{
        r=arr[(tm+1)/2];
    }
    return r;
}

int Moda(){

    int cntAux=0, NumPos=0, NumPosAux=0;
    for (int i = 0; i < tm; i++){
        if (arr[i]!=arr[NumPosAux]){
            NumPosAux=i;
            cntAux=1;
            SetCnt+=1;
        }else{
            cntAux+=1;
        }
        if (cntAux>cnt){
            cnt=cntAux;
            NumPos=i-1;
        }        
    }
    
    return arr[NumPos];
}

void SetArr(){

    int cntAux=0, NumPosAux=0,i2=0;
    for (int i = 0; i < tm; i++){
        if (arr[i]!=arr[NumPosAux]){
            NumPosAux=i;
            arrSets[0][i2]=arr[i-1];
            arrSets[1][i2]=cntAux;
            cntAux=1;
            i2+=1;
        }else{
            cntAux+=1;
        }
        if (i == tm-1){
            arrSets[0][i2]=arr[i];
            arrSets[1][i2]=cntAux;
        }
            
    }
}

float Varianza(int tp){
    int n,media,VAR=0;
    float r;

    media=Media();
    for (int i = 0; i < tm; i++){
        VAR+=pow((arr[i]-media),2);
    }

    switch (tp){
    case 1: //Varianza mustral
        r=(float) VAR/(tm-1);
        break;
    case 2: //Varianza Poblacional
        r=(float) VAR/tm;
        break;
    default:
        printf("\nOpcion no valida\n");
        break;
    }

    return r;
}

void GraphicPuntos(){
    int vx,vy;
	char textostg[20];
	int texto=0;
	int textoy=1,fr=0;
    int ori=450;

    initwindow(1200, 700);
	vx=(SetCnt*30)+50;
    vy=ori-(cnt*20);
    line(50,ori,vx+30,ori);
    line(50,ori,50,vy-20);
    for (int x=80;x<=vx;x+=30)
	{
		for(int y=430;y>=(ori-(arrSets[1][fr]*20));y-=20)
	{
        setfillstyle(SOLID_FILL, RED);
		circle(x,y,5);
        floodfill(x, y, WHITE);
		
	}
	fr+=1;
		line(x,455,x,445);
		itoa(arrSets[0][texto],textostg,10);
		settextstyle(2,HORIZ_DIR,0);
		outtextxy(x,456,textostg);
		texto+=1;
	}
	for(int y=430;y>=vy;y-=20)
	{
		if(textoy%2==0)
		{
			line(50,y,vx+30,y);
		}
		line(47,y,53,y);
		itoa(textoy,textostg,10);	
		settextstyle(2,HORIZ_DIR,0);
		outtextxy(20,y,textostg);
		textoy+=1;
		
	}
	getch();
	closegraph();
}