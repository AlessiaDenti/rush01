/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:57:14 by adenti            #+#    #+#             */
/*   Updated: 2025/10/25 19:57:16 by adenti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	int i =0;
	int k = 1;
	int max = matrice[0][col];
	while (i < 4 || max == 4)
	{
		if(matrice[i+1][j] > max)
		{
			k++;
			max = matrice[i+1][j];
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
	while (i > 0 || max == 4)
	{
		if(matrice[i-1][j] > max)
		{
			k++;
			max = matrice[i-1][j];
		}
		i--;
	}
	return (k); // numero di scatole vedo contandole 
}


// if cell ==4 SKIP IT and if cell ful skip it
// count the number of 4 in all matrice 

/*void put4_4(int carota[4][4])
{
	int i=0;
	int j=0;
	while (i < 4)
	{
		if (checkrighe(4, matrice[i]) == 0)
		{
			while(j < 4)
			{
				if (checkcol(4, j, matrice) == 0)
				{
					matrice[i][j] = 4;
					break;// find in wich colum to put it
				}
				j++;
			}
		}
		i++;
	}
}*/

void riempicolonna(int p; int col, int matrice[4][4]) // riempe la colonna
{
	int i = 0;
	int n = 1+p;
	while (i < 4)				//colonne
		{
			if (matrice[i][j] == 0)		//cella vuota
			{	
				while (n <= 4)
				{
					if(checkcol(n,j,matrice) == 0 && checkrighe(n, matrice[i]) == 0)
					{
						matrice[i][j] == n;
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
	//int p = 1;
	int copia[4][4] = matrice;
	while(j < 4)						//righe 
	{	
		//copia = matrice;
		riempicolonna(p, j, copia);
		ktop = checkalt(j, copia);
		kbot = checkaltrev(j, copia);
		if (ktop == cerca[j] && kbot == cerca[j+4])
			j++;
		else
		{
			back(cerca, matrice, p++);
		}
	}
}

back(cerca, carota, 0)







