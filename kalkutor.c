#include <stdio.h>
#include <math.h>
#define MATRICA 1
#define VEKTOR 2

typedef int Math_Entity;

char odabirOperacija(Math_Entity entity, int dimenzija){
    char operacija;
    do{
        if(entity == VEKTOR){
            printf("Unesite + za zbrajanje, - za oduzimanje, * za mnozenje skalarom, . za skalarni umnozak, X za vektorski umnozak i d za duljinu vektora.\nUnesite 0 za izlazak.\nOperacija > ");
        }
        else if (entity == MATRICA){
            printf("Unesite + za zbrajanje, - za oduzimanje, * za mnozenje skalarom, . umnozak matrica, T za transponiranje matrice, D za racunanje determinante i r za racunanje ranga.\nUnesite 0 za izlazak.\nOperacija > ");
        }
        scanf(" %c", &operacija);
        if(operacija == 'X' && dimenzija != 3){
            printf("Vektorski umnozak je moguc samo u 3 i 7 dimenzija!\n");
        }
    } while(!((operacija == 'X' && dimenzija == 3 && entity == VEKTOR) || operacija == '+' || operacija == '-' || operacija == '*' || operacija == '.' || (operacija == 'd' && entity == VEKTOR) || (operacija == 'T' && entity == MATRICA) || operacija == '0' ||
           (operacija == 'D' && entity == MATRICA) || (operacija == 'r' && entity == MATRICA)));
    
    return operacija;
}

void popuniPolje(double polje[], int m, int n, int veci){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(n > 1){
                printf("Unesite [%d][%d] clan > ", i+1, j+1);
            }
            else{
                printf("Unesite [%d] clan > ", i+1);
            }
            scanf("%lf", &polje[i*veci + j]); 
        }
    }
}

int max(int m, int n){
    return (m > n) ?  m : n;
}

void zamijeni_dimenzije(int *m, int*n){
    int temp = *m;
    *m = *n;
    *n = temp;
}

void zbrajanje_oduzimanje(double polje[], int m, int n, char operator, Math_Entity entity, int veci){
    double polje2[veci][veci];
    printf("Unesite drugi clan operacije >\n");
    popuniPolje(&polje2[0][0], m, n, veci);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(operator == '+'){
                polje[i*veci + j] += polje2[i][j]; 
            }
            else if(operator == '-'){
                polje[i*veci + j] -= polje2[i][j];
            }
        }
    }
}

void mnozenje_skalarom(double polje[], int m, int n, int veci, double skalar){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            polje[i*veci + j] *= skalar; 
        }
    }
}

double skalarni_umnozak(double polje[], int m, int n){
    double polje2[m][m], skalarni = 0;
    printf("Unesite drugi clan operacije >\n");
    popuniPolje(&polje2[0][0], m, 1, m);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            skalarni += polje[i*m + j] * polje2[i][j]; 
        }
    }
    return skalarni;
}

double duljina_vektora(double polje[], int m, int n){
    double duljina = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            duljina += pow(polje[i*m + j], 2);
        }
    }
    return sqrt(duljina);
}

void vektorski_umnozak(double polje[], int m){
    double polje2[m][m], i, j, k;
    printf("Unesite drugi clan operacije >\n");
    popuniPolje(&polje2[0][0], m, 1, m);
    i = polje[1*m]*polje2[2][0] - polje[2*m]*polje2[1][0];
    j = polje[2*m]*polje2[0][0] - polje[0*m]*polje2[2][0];
    k = polje[0*m]*polje2[1][0] - polje[1*m]*polje2[0][0];
    polje[0*m] = i;
    polje[1*m] = j;
    polje[2*m] = k;
}

void transponirana_matrica(double polje[], int m, int n, int veci){
    double temp;
    for(int i = 0; i < veci; i++){
        for(int j = i; j < veci; j++){
            temp = polje[i*veci + j];
            polje[i*veci + j] = polje[j*veci + i];
            polje[j*veci + i] = temp;
        }
    }
}

void umnozak_matrica(double polje[], int *m, int *n, int veci){
    int p, brojac = 0;
    printf("Unesite drugu dimenziju matrice (oblik matrice je %d x p) > ", *n);
    scanf("%d", &p);
    double rezultat[*m * p], polje2[*n][p], uk;
    printf("Unesite elemente druge matrice >\n");
    popuniPolje(&polje2[0][0], *n, p, p);
    for(int i = 0; i < *m; i++){
        for(int k = 0; k < p; k++){
            uk = 0;
            for(int j = 0; j < *n; j++){
                uk += polje[i*veci + j] * polje2[j][k];
            }
            rezultat[brojac++] = uk;
        }
    }
    *n = p;
    for(int i = 0; i < *m; i++){
        for(int j = 0; j < *n; j++){
            polje[i*veci + j] = rezultat[i*p + j];
        }
    }
}

_Bool jeStozer(double polje[], int m, int n, int redak, int stupac){
    for(int i = redak; i < redak+1; i++){
        for(int j = 0; j < stupac; j++){
            if(polje[i*n + j] == 1){
                return 0;
            }
        }
    }
    return 1;
}

void ponistavanjeStupca(double polje[], int m, int n, int redak, int stupac){
    double mnozitelj;
    for(int i = redak+1; i < m; i++){
        mnozitelj = polje[i*n + stupac];
        for(int j = stupac; j < n; j++){
            polje[i*n + j] -= mnozitelj*polje[redak*n + j];
        }
    }

}

int rang_matrice(double polje[], int m, int n, int veci){
    int rang = 0;
    if(m == 1){
        transponirana_matrica(polje, m, n, veci);
        if(duljina_vektora(polje, n, m) == 0){
            transponirana_matrica(polje, m, n, veci);
            return 0;
        }
        else{
            transponirana_matrica(polje, m, n, veci);
            return 1;
        }
    }
    double pompolje[m][n], djelitelj;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            pompolje[i][j] = polje[i*veci + j];
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if((jeStozer(&pompolje[0][0], m, n, i, j)) == 1 && pompolje[i][j] != 0){
                djelitelj = pompolje[i][j];
                //postavljanje i-tog retka na stožerni oblik
                for(int d = 0; d < n; d++){
                    pompolje[i][d] /= djelitelj;
                } 
            ponistavanjeStupca(&pompolje[0][0], m, n, i, j);
            rang++;
            break;
            }  
        }
    }
    return rang;
}

int main(){
    Math_Entity entity;
    char operacija;
    //biranje entiteta
    do{
    printf("Unesi 1 za matrice, 2 za vektore, 0 za kraj > ");
    scanf("%d", &entity);
    } while(entity != 1 && entity !=2 && entity != 0);
    
    if(entity == 0){
        printf("KRAJ");
        return 0;
    }

    int m, n, veci;
    //biranje dimenzija vektora/matrice
    if(entity == VEKTOR){
        printf("Unesite dimenziju vektora > ");
        scanf("%d", &m);
        n = 1;
        } 
    else if(entity == MATRICA){
        printf("Unesite dimenzije matrice > ");
        scanf("%d %d", &m, &n);
    }

    veci = max(m, n); //uzimanje veće dimenzije za stvaranje kvadratne matrice radi lakšeg transponiranja
    double polje[veci][veci], rjesenje;
    int rang;
    popuniPolje(&polje[0][0], m, n, veci);
    
    while(1){
        //biranje operacije
        operacija = odabirOperacija(entity, m);
        if(operacija == '0'){
            break;
        }
        //izvršavanje operacija 
        switch(operacija){
            case '+':
            case '-':
                zbrajanje_oduzimanje(&polje[0][0], m, n, operacija, entity, veci);
                break;
            case '*':
                {
                double skalar;
                printf("Unesite skalar > ");
                scanf("%lf", &skalar);
                mnozenje_skalarom(&polje[0][0], m, n, veci, skalar);
                break;
                }
            case '.':
                if(entity == VEKTOR){
                    rjesenje = skalarni_umnozak(&polje[0][0], m, n);
                }
                else if(entity == MATRICA){
                    umnozak_matrica(&polje[0][0], &m, &n, veci);
                }
                break;
            case 'd':
                rjesenje = duljina_vektora(&polje[0][0], m, n);
                break;
            case 'T':
                transponirana_matrica(&polje[0][0], m, n, veci);
                zamijeni_dimenzije(&m, &n);
                break;
            case 'X':
                vektorski_umnozak(&polje[0][0], m);
                break;
            case 'D':
                break;
            case 'r':
                rang = rang_matrice(&polje[0][0], m, n, veci);
                break;
        }
        if(operacija == 'd' || (operacija == '.' && entity == VEKTOR) || operacija == 'r'){
            if(operacija == 'r'){
                printf("Rang: %d\n", rang);    
            }
            else{
                printf("Rezultat: %lf\n", rjesenje);
            }
        }
        else{
            printf("Rezultat:\n");
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    printf("%8.4lf ", polje[i][j]);
                }
                printf("\n");
            }
            printf("%d %d\n", m, n);
        }
    }
    printf("KRAJ");
    return 0;
}