#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define M 7
#define N 7
int visitado[M][N];
int camino[M][N];
int filainicial;
int columnainicial;
bool dentroDeMatriz(int x, int y){    
	if (x >= 0 and y >= 0 and x < M and y < N) 
		return true; 
	return false;
}

bool viable(int matriz[M][N], int x, int y){
	if (matriz[x][y] == 1 and !visitado[x][y]) 
		return true; 
	return false; 
}

void maximaCovertura(int matriz[M][N], int i, int j, int x, int y, int &distanciaMaxima, 
                     int distanciaActual, int posicionAnterior){
	if (i == x and j == y){
		if (distanciaActual > distanciaMaxima){
			
			for (int k = 0; k < N; k++){ 
				for (int w = 0; w < M; w++){ 
					camino[k][w] = visitado[k][w]; 
				}
			}
			camino[x][y] = distanciaActual; 
			camino[filainicial][columnainicial] = distanciaActual+1; 
		}
		distanciaMaxima = max(distanciaMaxima, distanciaActual);
		return;
	}
	if (posicionAnterior == 1){
		visitado[i][j] = visitado[i - 1][j] + 1;
	}
	if (posicionAnterior == 2){
		visitado[i][j] = visitado[i + 1][j] + 1;
	}
	if (posicionAnterior == 3){
		visitado[i][j] = visitado[i][j - 1] + 1;
	}
	if (posicionAnterior == 4){
		visitado[i][j] = visitado[i][j + 1] + 1;
	}
	if (posicionAnterior == 0){
		visitado[i][j] = 0;
	}
	if (dentroDeMatriz(i + 1, j) and viable(matriz, i + 1, j))
		maximaCovertura(matriz, i + 1, j, x, y, distanciaMaxima, distanciaActual + 1, 1);
	if (dentroDeMatriz(i - 1, j) and viable(matriz, i - 1, j))
		maximaCovertura(matriz, i - 1, j, x, y, distanciaMaxima, distanciaActual + 1, 2);
	if (dentroDeMatriz(i, j + 1) and viable(matriz, i, j + 1))
		maximaCovertura(matriz, i, j + 1, x, y, distanciaMaxima, distanciaActual + 1, 3);
	if (dentroDeMatriz(i, j - 1) and viable(matriz, i, j - 1))
		maximaCovertura(matriz, i, j - 1, x, y, distanciaMaxima, distanciaActual + 1, 4);
	visitado[i][j] = 0; 
}

int main()
{

	int matriz[M][N] = {
		{1, 1, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1}};
	int distanciaMaxima = 0;
	filainicial=0;
	columnainicial=0;
	auto start = high_resolution_clock::now();
	maximaCovertura(matriz, filainicial, columnainicial, 0, 1, distanciaMaxima, 0, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	
	cout << "Longitud de la ruta mas larga: " << distanciaMaxima + 1 << endl;
	for (int x = 0; x < M; x++) 
	{
		for (int y = 0; y < N; y++) 
		{
			cout << camino[x][y]; 	
			if( camino[x][y]<10){		
				cout << ' ';		  
				cout << ' ';		 
			}
			else{
				cout << ' ';	
			}
		}
		cout << endl; 
	}
	cout << "Tiempo de ejecucion: "<< duration.count() << " microsegundos" << endl;
	return 0;
}