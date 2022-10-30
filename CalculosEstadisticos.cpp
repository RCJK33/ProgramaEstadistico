//Bibliotecas Comunes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Bibliotecas Graficas
#include <graphics.h>
#include <winbgim.h>

//Estadisticos
float Varianza(int tp,int tpFr);
float Media();
float Mediana();
int Moda();
int Sumatoria();

//Funciones necesarias (sin retorno)
void Ordenar();
void SetArr();
void GraphicPuntos();
void GraphicHistograma();
void TallosYHojas();

//Informacion Global
int *arr,tm,*tallos;
int SetCnt=1,*arrSets[2],cnt=0; 

int main(int argc, char const *argv[]){
    int rang;
    // Genearador de datos (Temporal para las pruebas de funciones)
    printf("\n\tIngresa la cantidad de datos: ");
    scanf("%d",&tm);
    arr = new int [tm];
    tallos = new int [tm];

    printf("\n\tIngresa el rango (0 to n): ");
    scanf("%d",&rang);

    srand(time(NULL));
    for (int i = 0; i < tm; i++){
        //arr[i]=rand()%(rang+1);
        scanf("%d",&arr[i]);
    }
    //Codigo de procesos
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

    float varia= (float) Varianza(1,1);
    printf("\n\tLa Varianza es: %.2f \n",varia);
    printf("\n\tLa Desviacion es: %.2f \n",sqrt(varia));
    
    //TallosYHojas();
    //GraphicPuntos();
    GraphicHistograma();

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
            cntAux=1; //reinicio de contador de frecuencia
            SetCnt+=1; //Contador de elemntos distintos
        }else{
            cntAux+=1;
        }
        if (cntAux>cnt){
            cnt=cntAux; //Guarda el valor de frecuencia mas alta
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

float Varianza(int tp,int tpFr){
    int n,media,VAR=0;
    float r,med_sqrt;

    media=Media();
    
    switch (tpFr){
    case 1:
        for (int i = 0; i < tm; i++){
        VAR+=pow((arr[i]-media),2);
        }
        break;
    case 2:
        med_sqrt=pow(media,2);
        for (int i = 0; i < tm; i++){
        VAR+=pow(arr[i],2)-med_sqrt;
        }
        break;
    default:
        printf("\nOpcion no valida\n");
        break;
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
    int oriy=650,orix=50;
    vx=(SetCnt*30)+orix;
    vy=oriy-(cnt*20);

    initwindow(orix+vx+orix, 700);
    line(orix,oriy,vx+30,oriy);
    line(orix,oriy,orix,vy-20);
    for (int x=orix+30;x<=vx;x+=30){
		for(int y=oriy-20;y>=(oriy-(arrSets[1][fr]*20));y-=20){
            setfillstyle(SOLID_FILL, RED);
		    circle(x,y,5);
            floodfill(x, y, WHITE);
	    }
	    fr+=1;
		line(x,oriy+5,x,oriy-5);
		itoa(arrSets[0][texto],textostg,10);
		settextstyle(8,HORIZ_DIR,1);
		outtextxy(x-11,oriy+8,textostg);
		texto+=1;
	}
    for(int y=oriy-20;y>=vy;y-=20){
		if(textoy%3==0){
			line(orix,y,vx+30,y);
		}
		line(orix-3,y,orix+3,y);
		itoa(textoy,textostg,10);	
		settextstyle(8,HORIZ_DIR,1);
		outtextxy(orix-28,y-9,textostg);
		textoy+=1;
	}
	getch();
	closegraph();
}

void TallosYHojas(){
    int aux = 0,jax,i,j;
    
    for(i=0; i<tm;i++){
    if(i>=1){
        if(tallos[aux-1]!=(arr[i]/10)){
            tallos[aux] = arr[i]/10;
            aux++;
        }
    }else if(i==0){
        tallos[aux]=arr[i]/10;
        aux++;
    }
    }
    
    for(i=0;i<aux;i++){
        printf("%4d ||", tallos[i]);
        jax=0;
        for(j=0;j<tm;j++){
            if(tallos[i]==(arr[j]/10)){
				if (jax==28){
					printf("\n%4d ||", tallos[i]);
					jax=0;
				}
				jax+=1;
                printf(" %i ",(arr[j]%10));
            }      
        }
		printf("\n\n");
    }
}
void GraphicHistograma(){
    float max,min,rango,k,am;
	int inter[2][30];
	float mc[30];
	int frec[30];
	int freca[30];
	
	max=arr[tm-1];
	min=arr[0];
	rango=max-min;
	k=round(1+(3.322*log10(tm)));
	am=round(rango/k);
	//printf("%f---%f---%f---%f---%f",max,min,rango,k,am);
	inter[0][0]=min;
	inter[1][0]=min+am;
	int maxint=-2000; //intervalo con mayor frecuencia 
	for(int x=1;x<=k;x++){
		inter[0][x]=inter[1][x-1];
		inter[1][x]=inter[0][x]+am;
		
	}

	for(int x=0;x<=k;x++){
		mc[x]=(inter[0][x]+inter[1][x])/2;

	}
	for(int x=0;x<=k;x++){	
		frec[x]=0;
		for(int y=0;y<SetCnt;y++)
		{
			if(arrSets[0][y]>=inter[0][x] && arrSets[0][y]<inter[1][x]){
				frec[x]+=arrSets[1][y];
			}	
		}
		if(maxint<frec[x])
		{
		maxint=frec[x];
		}	
	}
	freca[0]=frec[0];
	for(int x=1;x<=k;x++)
	{
		freca[x]=freca[x-1]+frec[x];
	}
	/*for(x=0;x<=k;x++)
	{
		printf("%d\n",frec[x]);
	}*/
	int vx,vy;
    int orix=50,oriy=650;
	char textostg[20];
	int texto=0;
	int textoy=1,fr=0;
	int an=5; //ancho de la barra
	
	vx=((k+1)*30)+orix;
    vy=oriy-(maxint*20);
    initwindow(orix+vx+orix,700);
    
    line(orix,oriy,vx+30,oriy);
    line(orix,oriy,50,vy-20);
    for (int x=80;x<=vx;x+=30)
	{
		int y=(oriy-(frec[fr]*20));
		//setfillstyle(SOLID_FILL, RED);
		bar(x-an,y,x+an,oriy);
		//floodfill(x,y,WHITE);
		
		line(x,oriy+5,x,oriy-5);
		itoa(mc[fr],textostg,10);
		settextstyle(2,HORIZ_DIR,0);
		outtextxy(x,oriy+6,textostg);
		texto+=1;
		fr+=1;
	}
	for(int y=oriy-20;y>=vy;y-=20)
	{
		if(textoy%2==0)
		{
			line(orix,y,vx+30,y);
		}
		line(orix-3,y,orix+3,y);
		itoa(textoy,textostg,10);	
		settextstyle(2,HORIZ_DIR,0);
		outtextxy(orix-30,y,textostg);
		textoy+=1;
		
	}	
	getch();
	closegraph();
}