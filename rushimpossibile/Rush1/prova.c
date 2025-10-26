#include <stdio.h>

/*int trovan(int n, int *nu) // ritorna posizione di n, se non lo trova -1 
{
	int i = 0;
	while (nu[i] != '\0')
	{	
		if (nu[i] == n)
			return (i);
		i++;
	}
	return (-1);
}*/

void g(int ncerca, int nmette, int *cerca, int carota[4][4]) // funziona solo per 4 e 1 nelle celle esterne 
{
	int j=0;
	
	while (cerca[j] != '\0'){
		if (cerca[j] == ncerca)
		{
			if(j / 4 == 0)
				carota[0][j] = nmette;	//nmette =1
			else if (j / 4 == 1)
				carota[3][j - 4] = nmette;
			else if (j / 4 == 2)
				carota[j - 8][0] = nmette;
			else 
				carota[j - 12][3] = nmette;
		}
		j++;
	}
}

void caso4( int ncerca, int nmette, int *cerca, int carota[4][4])
{
	int j=0;
	int i;
	while (cerca[j] != '\0'){
		if (cerca[j] == 4)
		{
			if(j / 4 == 0){
			i = 0;
			while(i<4){
				carota[i][j] = i + 1;
				i++;}	//nmette =1
			}
			else if (j / 4 == 1){
			i = 3;
			while(i>=0){
				carota[i][j - 4] = 4-i;
				i--;}
			}
			else if (j / 4 == 2){
			i = 0;
			while(i<4){
				carota[j - 8][i] = i + 1;
				i++;}
			}
			else {i = 3;
			while(i>=0){
				carota[j - 12][i] = 4 - i;
				i--;}
			}
		}
		j++;
	}
} //una funzione per le righe e una per le colonne 

int checkrighe(int nume, int riga[4])	//cerca numero in righe
{
	int j =0;
	while(j<4)
	{
		if(riga[j] == nume)
			return 1;
		j++;
	}
	return 0;
}

int checkcol(int nume,int col, int matrice[4][4])	//cerca numero in colonne
{
	int i = 0;
	while(i<4)
	{
		if(matrice[i][col] == nume)
			return 1;
		i++;
	}
	return 0;
}


void put4_4(int carota[4][4])
{
	int i=0;
	int j=0;
	while (i < 4)
	{
		if (checkrighe(4, carota[i]) == 0)
		{
			while(j < 4)
			{
				if (checkcol(4, j, carota) == 0)
				{
					carota[i][j] = 4;
					break;// find in wich colum to put it
				}
				j++;
			}
		}
		i++;
	}
}


int checkalt(int col, int matrice[4][4])		//controlla altezza delle colonne
{
	int i = 0;
	int k = 1;
	int max = matrice[0][col];
	while (i < 4 && max != 4)
	{
		if(matrice[i+1][col] > max)
		{
			k++;
			max = matrice[i+1][col];
		}
		i++;
	}
	return (k); // numero di scatole vedo contandole 
}

int checkaltrev(int col, int matrice[4][4])		//controlla altezza delle colonne
{
	int i = 3;
	int k = 1;
	int max = matrice[3][col];
	while (i > 0 && max != 4)
	{
		if(matrice[i-1][col] > max)
		{
			k++;
			max = matrice[i-1][col];
		}
		i--;
	}
	return (k); // numero di scatole vedo contandole 
}


void riempicolonna(int p, int col, int matrice[4][4]) // riempe la colonna
{
	int i = 0;
	int n = 1+p;
	while (i < 4)				
		{
			if (matrice[i][col] == 0)		//cella vuota
			{	
				while (n <= 4)
				{
					if(checkcol(n,col,matrice) == 0 && checkrighe(n, matrice[i]) == 0)
					{
						matrice[i][col] = n;
						break;
					}
					n++;
				}
			}
			n = 1;
			i++;
		}	// riempito colonna
}



void back(int *cerca, int matrice[4][4], int p)	// riempi celle backtracking
{
	int j=0;
	int ktop;
	int kbot;
	int o;
	//int p = 1;
	int copia[4][4]={{0,0,0,0} ,{0,0,0,0}, {0,0,0,0},{0,0,0,0}};
	int v=0;
	int z;
	while(v < 4)
	{
		z=0;
		while(z < 4){
			copia[v][z] = matrice[v][z];
			z++;
			}
			v++;
	}
	
	while(j < 4)						
	{	
		//copia = matrice;
		riempicolonna(p, j, copia);
		ktop = checkalt(j, copia);
		kbot = checkaltrev(j, copia);
		if (ktop == cerca[j] && kbot == cerca[j+4]) //manca check sulle righe
		{
			o = -1;
			while(++o < 4)
				matrice[o][j] = copia[o][j];
			j++;
			p = 0;
		}
		else
		{
			back(cerca, matrice, p+1);
		}
	}
}



int main(void)
{
	int i = -1;
	int j;
	int matricey[4][4] = {{0,0,0,0} ,{0,0,0,0}, {0,0,0,0},{0,0,0,0}};
	int cerca[16] = {4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2}; 
	//int cerca[16] = {2,2,1,4,2,2,4,1,2,1,2,3,2,3,2,1}; 
	//int cerca[16] = {2,1,2,4,2,4,2,1,2,3,1,2,3,2,2,1}; 
	//int cerca[16] = {2,1,3,3,3,3,2,1,2,1,2,4,2,4,2,1}; 
	//int cerca[16] = {1,2,3,2,3,2,1,2,1,2,2,3,3,3,1,2}; 

	//printf("\n"); 
	caso4(4, 1, cerca, matricey);
	g(1, 4, cerca, matricey);
	put4_4(matricey);
	back(cerca, matricey, 0);
	//printf("%d \n", trovan(2,cerca));
	while (++i <4){
		j=-1;
		while(++j <4)
			printf("%d", matricey[i][j]);
		printf("\n");  
	}
}


