//Bibliotecas Comunes
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

//Bibliotecas Graficas
#include <graphics.h>
#include <winbgim.h>

//Biblioteca de archivos
#include <fstream>
#include <string.h>

//Biblioteca de hilos
//#include <pthread.h>

//Estadisticos
float Varianza(int tp);
float Media();
float Mediana();
int Sumatoria();

//Calculos Necesarios
float suamtoriaCSX(int ppow);
float suamtoriaRSY(int pws);
//Funciones necesarias (sin retorno)
void ModelosMAth();
void lineal();
void cuadratico();
void ErrCuad();
void ErrLin();
void Menu();
void Moda();
void Ordenar();
void SetArr();
void ContadorELMS();
void GraphicPuntos();
void GraphicHistograma();
void GraphTalloYHoja();
void CreateArch();
void NewEntryArch();

//Informacion Global
int tm=0,*t_lls;
int SetCnt=1,*arrSets[2],cnt=0,FrMAX=-999999;
int *A_xy[2];
int operaciones=0;
float a[3][3];
float b[3];
float media,percErr,Sxy;
float cRRLin,E_mL,E_bL; //crr coeficiente de corelacion
float x[3]={0,0,0},mL,bL;

FILE *Arch, *ArchLog;

int main(int argc, char const *argv[]){
    int rang;

    //Entrada de datos
    NewEntryArch();
    //crear un archivo para guardar los datos o continuar escribiendo en un archivo existente
    CreateArch();
  
    //Codigo de proceso

    Ordenar(); // ordena la matriz de datos
    ContadorELMS(); 
    for (int i = 0; i < 2; i++){ 
        arrSets[i]=new int [SetCnt];
    }
    SetArr();
    Menu();
    return 0;
}
void Menu(){
    int opc,comnd=0;
    float aux;
    system("cls");
    do{
        printf("\n\tQue desea hacer?");
        printf("\n\t[1] Obtener varianza y desviacion Muestral.");
        printf("\n\t[2] Obtener varianza y desviacion Poblacional.");
        printf("\n\t[3] Obtener la media.");
        printf("\n\t[4] Obtener la mediana.");
        printf("\n\t[5] Obtener la moda.");
        printf("\n\t[6] Hacer un modelo matematico de los datos.");
        printf("\n\t[7] Imprimir todas las anteriores (varianza poblacional no disponible).");
        printf("\n\t[8] Mostrar Grafico de Puntos.");
        printf("\n\t[9] Mostrar Grafico de Barras.");
        printf("\n\t[10] Mostrar Grafico de Tallos y hojas.");
        printf("\n\n\t[11] Eliminar archivo de registro.");
        printf("\n\t[12] Cerrar el programa.\n\t");
        scanf("%d",&opc);
        system("cls");
        switch (opc){
            case 1:
                aux=Varianza(1);
                printf("\n\tLa varianza es %.2f.", aux);  
                printf("\n\tLa Desviacion es %.2f.", sqrt(aux));
                fprintf(ArchLog,"\nDatos Muestrales"); 
                fprintf(ArchLog,"\nLa varianza es %.2f.", aux); 
                fprintf(ArchLog,"\nLa Desviacion es %.2f.", sqrt(aux)); 
                break;
            case 2:
                aux=Varianza(2);
                fprintf(ArchLog,"\nDatos Poblacionales");
                printf("\n\tLa varianza es %.2f.", aux); 
                printf("\n\tLa Desviacion es %.2f.", sqrt(aux));
                fprintf(ArchLog,"\n\nLa varianza es %.2f.", aux); 
                fprintf(ArchLog,"\nLa Desviacion es %.2f.", sqrt(aux));  
                break;
            case 3:
                printf("\n\tLa media (el promedio) es %.2f.",Media());
                fprintf(ArchLog,"\n\nLa media (el promedio) es %.2f.",Media()); 
                break;
            case 4:
                printf("\n\tLa mediana (el valor central) es %.2f.", Mediana());
                fprintf(ArchLog,"\n\nLa mediana (el valor central) es %.2f.", Mediana()); 
                break;
            case 5:
                fprintf(ArchLog,"\n\n");
                Moda();
                break;
            case 6:
                ModelosMAth();
                break;
            case 7:
                aux=Varianza(1);
                printf("\n\tLa varianza es %.2f.", aux);  
                printf("\n\tLa Desviacion es %.2f.", sqrt(aux)); 
                printf("\n\tLa media (el promedio) es %.2f.",Media());
                printf("\n\tLa mediana (el valor central) es %.2f.", Mediana());
                ModelosMAth();
                fprintf(ArchLog,"\nLa varianza es %.2f.", aux); 
                fprintf(ArchLog,"\nLa Desviacion es %.2f.", sqrt(aux));
                fprintf(ArchLog,"\nLa media (el promedio) es %.2f.",Media());
                fprintf(ArchLog,"\nLa mediana (el valor central) es %.2f.", Mediana()); 
                fprintf(ArchLog,"\n\n");
                Moda();
                break;
            case 8:
                GraphicPuntos();
                break;
            case 9:
                GraphicHistograma();
                break;
            case 10:
                GraphTalloYHoja();
                break;
            case 11:
                fclose(ArchLog);
                remove("LogsCalulosEstadisticos.doc");
                CreateArch();
                printf("\n\tRegistros borrados con exito.\n");
                break;
            case 12:
                printf("\n\tConfirma comando [1::yes/0::no]\n\t");
                scanf("%d",&comnd);
                break;
            default:
                printf("\n\t Opcion no valida.");
                break;
        }
        printf("\n");
        system("pause");
        system("cls");
    }while(comnd==0);
    
    fprintf(ArchLog,"\n\n\tCantidad de datos:%d.",tm);
    fprintf(ArchLog,"\nDatos\n");
    for (int i = 1; i < tm+1; i++){
        fprintf(ArchLog,"\t[%d,%d]",A_xy[0][i-1],A_xy[1][i-1]);
        if (i%int(sqrt(tm)/2)==0){
            fprintf(ArchLog,"\n");
        } 
    }
    fprintf(ArchLog,"\n\n");
    fprintf(ArchLog,"\nSe ejecutaron un total de %d operaciones matematicas para reslover los problemas solicitados.",operaciones);
    fclose(ArchLog);
}

float Varianza(int tp){
    int n,media,VAR=0,tpM_P;
    float r,med_sqrt;

    media=Media();

    printf("\n\tQue tipo de varianza?.");
    printf("\n\t[1] Metodo 1 (Menos operaciones).");
    printf("\n\t[2] Metodo 2 (Mas operaciones).\n\t");
    scanf("%d",&tpM_P);
    system("cls");
    
    switch (tpM_P){
    case 1: //Varianza tipo 1
        fprintf(ArchLog,"\n\n  --metodo con menos operaciones--");
        for (int i = 0; i < tm; i++){
            VAR+=pow((A_xy[1][i]-media),2);
            operaciones+=2;
        }
        break;
    case 2: //Varianza tipo 2
        fprintf(ArchLog,"\n\n  --metodo con mas operaciones--");
        med_sqrt=pow(media,2);
        for (int i = 0; i < tm; i++){
            VAR+=pow(A_xy[1][i],2)-med_sqrt;
            operaciones+=3;
        }
        break;
    default:
        printf("\nError con la varianza, 1\n");
        break;
    }

    switch (tp){
    case 1: //Varianza mustral
        r=(float) VAR/(tm-1);
        operaciones+=1;
        break;
    case 2: //Varianza Poblacional
        r=(float) VAR/tm;
        break;
    default:
        printf("\nError con la varianza 2\n");
        break;
    }
    operaciones+=1;
    return r;
}
float Media(){
    int sum=Sumatoria();
    float r=(float) sum/tm;
    operaciones+=1;
    return r;
}
float Mediana(){
    float r;
    int nx;
    if (tm%2==0){
        nx=(tm/2)-1;
        r=(float) (A_xy[1][nx]+A_xy[1][nx+1])/2;
        operaciones+=4;
    }else{
        nx=((tm+1)/2);
        r=A_xy[1][nx];
        operaciones+=2;
    }
    return r;
}
void Moda(){
    for (int i = 0; i < SetCnt; i++){
        if (arrSets[1][i]==FrMAX){
            printf("\n\tLa moda es: %d", arrSets[0][i]);
            fprintf(ArchLog,"\nLa moda es: %d", arrSets[0][i]); 
        }
    }
}
void ContadorELMS(){
    int NumPosAux=0;

    for (int i = 0; i < tm; i++){
        if (A_xy[1][i]!=A_xy[1][NumPosAux]){
            NumPosAux=i;
            SetCnt+=1; //Contador de elemntos distintos
            operaciones+=1;
        }
    }
}
int Sumatoria(){
    int sum=0;
    for (int i = 0; i < tm; i++){
        sum+=A_xy[1][i];
        operaciones+=1;
    }
    return sum;
}

void Ordenar(){
    //ordenador de valores acendente
    int menor,pos,aux;
    int menor0,aux0;
    for (int i = 0; i < tm; i++){
        menor=190000;
        aux=A_xy[1][i];
        aux0=A_xy[0][i];
        for (int i1 = i; i1 < tm; i1++){
            if (A_xy[1][i1]<menor){
                menor=A_xy[1][i1];
                menor0=A_xy[0][i1];
                pos=i1;
            }   
        }
        A_xy[1][i]= menor;
        A_xy[1][pos]= aux;
        A_xy[0][i]= menor0;
        A_xy[0][pos]= aux0;
    }
}
void SetArr(){
    int cntAux=0, NumPosAux=0,i2=0;
    for (int i = 0; i < tm; i++){
        if (A_xy[1][i]!=A_xy[1][NumPosAux]){
            NumPosAux=i;
            arrSets[0][i2]=A_xy[1][i-1];
            arrSets[1][i2]=cntAux;
            cntAux=1;
            i2+=1;
        }else{
            cntAux+=1;
        }
        if (i == tm-1){
            arrSets[0][i2]=A_xy[1][i]; //Guarda el numero
            arrSets[1][i2]=cntAux; //Guarda la frecuencia del numero
        }
        if (cntAux>FrMAX){
            FrMAX=cntAux;
        }
          
    }
}
void ModelosMAth(){
    a[0][0]= tm;
    a[0][1]= suamtoriaCSX(1);
    a[0][2]= suamtoriaCSX(2);
    b[0]= suamtoriaRSY(1);

    a[1][0]= suamtoriaCSX(1);
    a[1][1]= suamtoriaCSX(2);
    a[1][2]= suamtoriaCSX(3);
    b[1]= suamtoriaRSY(2);

    a[2][0]= suamtoriaCSX(2);
    a[2][1]= suamtoriaCSX(3);
    a[2][2]= suamtoriaCSX(4);
    b[2]= suamtoriaRSY(3);

    fprintf(ArchLog,"\n");
    for (int i = 0; i < 3; i++){
        for (int i2 = 0; i2 < 3; i2++){
            fprintf(ArchLog,"\t%8.0f",a[i][i2]); 
        }
        fprintf(ArchLog,"\t%8.0f",b[i]); 
        fprintf(ArchLog,"\n"); 
    }

    media= b[1]/tm;

    printf("\n");

    lineal();
    printf("\n\t\t --Ajuste lineal--");
    printf("\n\t y = (%4.3f%c%4.3f)x + (%4.3f%c%4.3f)",mL,241,E_mL,bL,241,E_bL);
    printf("\n\t Modelo matematico con un coeficiente de Correlacion lineal de %4.3f.\n",cRRLin);
    fprintf(ArchLog,"\n\n --Ajuste lineal--"); 
    fprintf(ArchLog,"\n\n y = (%4.3f%c%4.3f)x + (%4.3f%c%4.3f)",mL,241,E_mL,bL,241,E_bL); 
    fprintf(ArchLog,"\n Modelo matematico con un coeficiente de Correlacion lineal de %4.3f.\n",cRRLin); 
    
    cuadratico();
    printf("\n\t\t--Ajuste Cuadratico--");
    printf("\n\t y = (%4.3f)x2 + (%4.3f)x +  %4.3f",x[2],x[1],x[0]);
    printf("\n\t Modelo matematico con una confiaza del %5.3f%% y una desviacion de %5.3f.\n",percErr,Sxy);
    fprintf(ArchLog,"\n\n --Ajuste Cuadratico--"); 
    fprintf(ArchLog,"\n y = (%4.3f)x2 + (%4.3f)x +  %4.3f",x[2],x[1],x[0]); 
    fprintf(ArchLog,"\n Modelo matematico con una confiaza del %5.3f%% y una desviacion de %5.3f.\n",percErr,Sxy); 
}
void GraphicPuntos(){
    int vx,vy;
	char textostg[20];
	int texto=0;
	int textoy=1,fr=0;
    int oriy=650,orix=50;
    vx=(SetCnt*30)+orix;
    vy=oriy-(cnt*20);

    initwindow(orix+vx+30, 700);
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
    fprintf(ArchLog,"\n\n");
    for (int i = 0; i < SetCnt; i++){
        fprintf(ArchLog,"\n\tValor: %d  ||  Frecuencia %d",arrSets[0][i],arrSets[1][i]);
    }
    
	getch();
	closegraph();
}
void GraphicHistograma(){
    float max,min,rango,k,am;
	int inter[2][30];
	float mc[30];
	int frec[30];
	int freca[30];
	
	max=A_xy[1][tm-1];
	min=A_xy[1][0];
	rango=max-min;
	k=round(1+(3.322*log10(tm)));
	am=round(rango/k);
	inter[0][0]=min;
	inter[1][0]=min+am;
	int maxint=-2000; //intervalo con mayor frecuencia 
	for(int x=1;x<=k;x++){
		inter[0][x]=inter[1][x-1];
		inter[1][x]=inter[0][x]+am;
        operaciones+=1;
	}
	for(int x=0;x<=k;x++){
		mc[x]=(inter[0][x]+inter[1][x])/2;
        operaciones+=2;
	}
	for(int x=0;x<=k;x++){	
		frec[x]=0;
		for(int y=0;y<SetCnt;y++){
			if(arrSets[0][y]>=inter[0][x] && arrSets[0][y]<inter[1][x]){
				frec[x]+=arrSets[1][y];
                operaciones+=1;
			}	
		}
		if(maxint<frec[x]){
		    maxint=frec[x];
		}	
	}
	freca[0]=frec[0];
	for(int x=1;x<=k;x++){
		freca[x]=freca[x-1]+frec[x];
        operaciones+=1;
	}

    printf("\n\tIntervalo: %.1f",k);
    printf("\n\tRango: %.1f",rango);
    printf("\n\tAmplitud: %.1f",am);

	int vx,vy;
    int orix=50,oriy=650;
	char textostg[20];
	int texto=0;
	int textoy=1,fr=0;
	int an=5; //ancho de la barra
	
	vx=((k+1)*30)+orix;
    vy=oriy-(maxint*20);
    initwindow(orix+vx+30,700);
    line(orix,oriy,vx+30,oriy);
    line(orix,oriy,50,vy-20);
	for(int y=oriy-20;y>=vy;y-=20){
		if(textoy%2==0){
			line(orix,y,vx+30,y);
		}
		line(orix-3,y,orix+3,y);
		itoa(textoy,textostg,10);	
		settextstyle(8,HORIZ_DIR,1);
		outtextxy(orix-28,y-9,textostg);
		textoy+=1;
	}
    for (int x=80;x<=vx;x+=30){
		int y=(oriy-(frec[fr]*20));
        setfillstyle(SOLID_FILL,RED);	
		bar(x-an,y,x+an,oriy);		
		line(x,oriy+5,x,oriy-5);
		itoa(mc[fr],textostg,10);
		settextstyle(8,HORIZ_DIR,1);
		outtextxy(x-11,oriy+8,textostg);
		fr+=1;
	}
    printf("\n");
    system("pause");
    closegraph();
}
void GraphTalloYHoja(){
    int aux = 0,jax,i,j;
    
    for(i=0; i<tm;i++){
    if(i>=1){
        if(t_lls[aux-1]!=(A_xy[1][i]/10)){
            t_lls[aux] = A_xy[1][i]/10;
            aux++;
            operaciones+=2;
        }
    }else if(i==0){
        t_lls[aux]=A_xy[1][i]/10;
        aux++;
        operaciones+=2;
    }
    }
    fprintf(ArchLog,"\n\n");
    for(i=0;i<aux;i++){
        printf("%4d ->|", t_lls[i]);
        fprintf(Arch,"%4d ->|", t_lls[i]);
        jax=0;
        for(j=0;j<tm;j++){
            if(t_lls[i]==(A_xy[1][j]/10)){
				if (jax==28){
					printf("\n%4d ->|", t_lls[i]);
                    fprintf(Arch,"\n%4d ->|", t_lls[i]);
					jax=0;
				}
                operaciones+=1;
				jax+=1;
                printf(" %i ",(int(A_xy[1][j])%10));
            }      
        }
		printf("\n\n");
    }
}
void lineal(){
    mL=(tm*b[1]-a[0][1]*b[0])/(tm*a[0][2]-pow(a[0][1],2));
    bL=(b[0]*a[0][2]-a[0][1]*b[1])/(tm*a[0][2]-pow(a[0][1],2));
    ErrLin();
    operaciones+=16;
}
void cuadratico(){
    float x_1[3];
    float er[3]={0,0,0};
    float errpc=0.000001;
    int i;
    do{
        x_1[0]=x[0];
        x_1[1]=x[1];
        x_1[2]=x[2];
        x[0]=(b[0]-a[0][1]*x[1]-a[0][2]*x[2])/a[0][0];
        x[1]=(b[1]-a[1][0]*x[0]-a[1][2]*x[2])/a[1][1];
        x[2]=(b[2]-a[2][0]*x[0]-a[2][1]*x[1])/a[2][2];
        er[0]=abs((x[0]-x_1[0])/x[0])*100;
        er[1]=abs((x[1]-x_1[1])/x[1])*100;
        er[2]=abs((x[2]-x_1[2])/x[2])*100;
        operaciones+24;
    }while((er[0]>errpc)&&(er[1]>errpc)&&(er[2]>errpc));
    ErrCuad();
}
float suamtoriaCSX(int ppow){
    float s=0;

    switch (ppow){
    case 1:
        for (int i = 0; i < tm; i++){
            s+=A_xy[0][i];
            operaciones+=1;
        }
        break;
    case 2:
        for (int i = 0; i < tm; i++){
            s+=pow(A_xy[0][i],2);
            operaciones+=3;
        }
        break;
    case 3:
        for (int i = 0; i < tm; i++){
            s+=pow(A_xy[0][i],3);
            operaciones+=4;
        }
        break;
    case 4:
        for (int i = 0; i < tm; i++){
            s+=pow(A_xy[0][i],4);
            operaciones+=5;
        }
        break;
    default:
        printf("\n\tError en Sumatoias::POWX");
        break;
    }
    return s;   

}
float suamtoriaRSY(int pws){
    float s=0;
    switch (pws){
    case 1:
        for (int i = 0; i < tm; i++){
            s+=A_xy[1][i];
            operaciones+=1;
        }
        break;
    case 2:
        for (int i = 0; i < tm; i++){
            s+=A_xy[1][i]*A_xy[0][i];
            operaciones+=2;
        }
        break;
    case 3:
        for (int i = 0; i < tm; i++){
            s+=A_xy[1][i]*pow(A_xy[0][i],2);
            operaciones+=4;
        }
        break;
    case 4:
        for (int i = 0; i < tm; i++){
            s+=pow(A_xy[1][i],2);
            operaciones+=3;
        }
        break;
    default:
        printf("\n\tError en Sumatoias::POWsY");
        break;
    }
    return s;   
}
void ErrCuad(){
    float evalModel[tm];
    float St=0,Sr=0,Sy;
    for (int i = 0; i < tm; i++){
        evalModel[i]=x[0]+x[1]*A_xy[0][i]+x[2]*pow(A_xy[0][i],2);
        St+=pow((A_xy[1][i]-media),2);
        Sr+=pow((A_xy[1][i]-evalModel[i]),2);
        operaciones+=9;
    }
    Sy=sqrt(St/(tm-1));
    Sxy=sqrt(Sr/(tm-3));
    percErr=((St-Sr)/St)*100;
    operaciones+=9;
}
void ErrLin(){
    float Bta_2=0;
    cRRLin=(tm*b[1]-a[0][1]*b[0])/(sqrt(tm*a[0][2]-pow(a[0][1],2))*sqrt(tm*suamtoriaRSY(4)-pow(b[0],2)));
    operaciones+=11;
    for (int i = 0; i < tm; i++){
        Bta_2+=pow((bL+mL*A_xy[0][i]-A_xy[1][i]),2);
        operaciones+=4;
    }
    E_mL=sqrt((tm/(tm*a[0][2]-pow(a[0][1],2)))*(Bta_2/(tm-2)));
    E_bL=sqrt((a[0][2]/(tm*a[0][2]-pow(a[0][1],2)))*(Bta_2/(tm-2)));
    operaciones+=14;
}
void CreateArch(){
    do{
        ArchLog = fopen("LogsCalulosEstadisticos.doc","ab");
        if (ArchLog == NULL){
            ArchLog=fopen("LogsCalulosEstadisticos.doc","wb");
        }
        if (ArchLog == NULL){
            printf("\n\tOcurrio un error al crear o abrir el archivo LOGs. %s \n");
            printf("\n\tIntente cerrar el archivo si esta en uso. %s \n");
            system("pause");
        }
    }while (ArchLog==NULL);
}
void NewEntryArch(){
    char Archname[100],c;
    do{
        printf("\n\t Ingresa la direccion del archivo que contiene los datos con el fotmato X y Y:");
        scanf("%s",Archname);
        Arch=fopen(Archname,"r");
        if (Arch == NULL){ //comprobar si el archivo se abrio o existe
            printf("\n\tNo fue posible abrir el archivo %s \n"),Arch;
            system("pause");
            system("cls");
        }
    }while (Arch==NULL);
    //contador de datos
    c = fgetc(Arch);
    while (c != EOF){
        if (c=='\n') ++tm;
        c = fgetc(Arch);
    }
    //Asignar espacio para acceder a los datos de forma imediata en funcion de la cantidad de datos
    t_lls = new int [tm];
    for (int i = 0; i < 2; i++){
        A_xy[i]= new int [tm];
    }
    //Guarda los datos del archivo en los espacios correspondientes
    rewind(Arch);
    for (int i = 0; i < tm; i++){
        fscanf(Arch,"%d,%d",&A_xy[0][i],&A_xy[1][i]);
    }
}