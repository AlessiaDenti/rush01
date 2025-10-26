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


int controllocerca(int matrice[4][4], int cerca[16])		// separa controllo righe e colonne
{
	int i = 0;
	
	while (i < 4)
	{
		if (checkalt(i, matrice) != cerca[i])		//controlla alt da alto 
			return 0;
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (checkaltrev(i, matrice) != cerca[i + 4])		//controlla basso a alto 
			return 0;
		i++;
	}
	
	/*i = 0;
	while (i < 4)
	{
		if (checkrigasx(i, matrice) != cerca[i + 8])		//controlla sx a dx 
			return 0;
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (checkrigadx(i, matrice) != cerca[i + 12])		//controlla dx a sx 
			return 0;
		i++;
	}*/
	
	return 1;		//tutto a posto
}

int solve(int *cerca, int matrice[4][4], int i, int j)	// riempi celle backtracking
{
	if (i == 4) 
		return 1;  // fine: tutti i valori sono stati provati
    if (j == 4) 
    	return solve(cerca, matrice, i+1, 0);
	if (matrice[i][j] != 0) 
		return solve(cerca, matrice, i, j+1);
	
	int copia[4][4];
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
	
	int n=0;
	int ri;
	while (++n <= 4)
	{
		if (checkrighe(n, matrice[i]) == 0 && checkcol(n, j, matrice) == 0)
		{
			matrice[i][j] = n;
			//riempe colonne e erifica vincoli
			int col = -1;
			while (++col < 4)
			{
				riempicolonna(0, col, matrice);
			}
			
			if (controllocerca(matrice, cerca) && solve(cerca, matrice, i, j+1))
                return 1;
            
            ri = -1;
            while (++ri < 4)
            {
            	int col = -1;
            	while (++col < 4)
            		 matrice[ri][col] = copia[ri][col];
            }
		}
	}
	return 0;
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
	//caso4(4, 1, cerca, matricey);
	//g(1, 4, cerca, matricey);
	//put4_4(matricey);
	//back(cerca, matricey, 0);
	//printf("%d \n", trovan(2,cerca));
	solve(cerca, matricey, 0, 0);
	while (++i <4){
		j=-1;
		while(++j <4)
			printf("%d", matricey[i][j]);
		printf("\n");  
	}
}


