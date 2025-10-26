#include <stdio.h>

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

int checkalt(int col, int matrice[4][4])		//controlla altezza delle colonne
{
	int i = 0;
	int k = 1;
	int max = matrice[0][col];
	while (i < 3 && max != 4)		//i < 3
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
	while (i > 0 && max != 4)		//i < 3
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

int checkrigasx(int row, int matrice[4][4])
{
	int j = 0;
	int k = 1;
	int max = matrice[row][0];
	while (j < 3 && max != 4)		//i < 3
	{
		if(matrice[row][j+1] > max)
		{
			k++;
			max = matrice[row][j + 1];
		}
		j++;
	}
	return (k); // numero di scatole vedo contandole 
}

int checkrigadx(int row, int matrice[4][4])
{
	int j = 3;
	int k = 1;
	int max = matrice[row][3];
	while (j > 0 && max != 4)		//i < 3
	{
		if(matrice[row][j-1] > max)
		{
			k++;
			max = matrice[row][j - 1];
		}
		j--;
	}
	return (k); // numero di scatole vedo contandole 
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
	
	i = 0;
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
	}
	
	return 1;		//tutto a posto
}

int solve(int *cerca, int matrice[4][4], int i, int j)	// riempi celle backtracking
{
	if (i == 4) 
		return controllocerca(matrice, cerca);  // fine: tutti i valori sono stati provati
    if (j == 4) 
    	return solve(cerca, matrice, i+1, 0);		//riga successiva
	if (matrice[i][j] != 0) 
		return solve(cerca, matrice, i, j+1);		//colonna successiva

	int n = 1;
	while (n <= 4)
	{
		if (checkrighe(n, matrice[i]) == 0 && checkcol(n, j, matrice) == 0)
		{
			matrice[i][j] = n;
			
			if (solve(cerca, matrice, i, j+1))
				return 1;
				
			matrice[i][j] = 0;
		}
		n++;
	}
	return 0;
}

int main(void)
{
	int i = -1;
	int j;
	int matricey[4][4] = {{0,0,0,0} ,{0,0,0,0}, {0,0,0,0},{0,0,0,0}};
	//int cerca[16] = {4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2}; 
	//int cerca[16] = {2,2,1,4,2,2,4,1,2,1,2,3,2,3,2,1}; 
	int cerca[16] = {2,1,2,4,2,4,2,1,2,3,1,2,3,2,2,1};
	//int cerca[16] = {2,1,2,4,2,4,2,1,2,3,1,2,3,2,2,1}; 
	//int cerca[16] = {2,1,3,3,3,3,2,1,2,1,2,4,2,4,2,1}; 
	//int cerca[16] = {1,2,3,2,3,2,1,2,1,2,2,3,3,3,1,2}; 

	//printf("\n"); 
	 if(solve(cerca, matricey, 0, 0))
    {
        printf("Soluzione trovata:\n");
        while (++i < 4)
        {
            j = -1;
            while(++j < 4)
                printf("%d ", matricey[i][j]);
            printf("\n");
        }
    }
    else
    {
        printf("Nessuna soluzione trovata!\n");
    }
    
    return 0;
}


