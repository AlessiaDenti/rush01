/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   riempitabella.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:27:50 by adenti            #+#    #+#             */
/*   Updated: 2025/10/25 15:27:53 by adenti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int trovan(int n, int *nu) // ritorna posizione di n, se non lo trova -1 
{
	int i = 0;
	while (nu[i] != '\0')
	{	
		if (nu[i] == n)
			return (i);
		i++;
	}
	return (-1);
}

void g(int ncerca, int nmette, int *cerca, int **carota) // funziona solo per 4 e 1 nelle celle esterne 
{
 	int posizione = trovan(ncerca, cerca);   //ncerca=4, num=cerca
	if (posizione != -1)
	{
		if(posizione / 4 == 0)
			carota[0][posizione] == nmette;	//nmette =1
		else if (posizione / 4 == 1)
			carota[3][posizione - 4] == nmette;
		else if (posizione / 4 == 2)
			carota[posizione - 8][0] == nmette;
		else 
			carota[3][posizione - 12] == nmette;
	}
}

g(4,1,num)
g(1, 4, num)

int **riempi(int *num)
{
	int **carota[4][4];
	int i = 0;
	int j;
	
	// in num se ho 4 o 1 allora riempio la cella 
	int posizione = trovan(4, num);
	if (posizione != -1)
	{
		if(posizione / 4 == 0)
			carota[0][posizione] == 1
		else if (posizione / 4 == 1)
			carota[3][posizione - 4] == 1
		else if (posizione / 4 == 2)
			carota[posizione - 8][0] == 1
		else 
			carota[3][posizione - 12] == 1
	}
		// coltop ho 0, colbot ho 1, rigasx ho 2, rigade=x ho 3
	carota[i][j]
	
	
	
	
	while(i < 4)
	{
		j = 0;
		while (j < 4)
		{
			carota[i][j]
			j++;
		}
		i++;
	}
}
