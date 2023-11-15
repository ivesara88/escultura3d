#include "sculptor.hpp" //inclus�o de declara��o da classe
#include <iostream> //inclus�o das fun��es de entrada e sa�da
#include <cmath> //inclus�o de fun��es matem�ticas
#include <fstream> //inclus�o de fluxo para arquivos
#include <cstdlib> //inclus�o de fun��o exit

using namespace std; 

//implementa��o do construtor de classe
Sculptor::Sculptor(int _nx, int _ny, int _nz) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	nx = _nx;
	ny = _ny;
	nz = _nz;
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	//atribui os valores aos m�todos protect
	
	v = new Voxel ** [nx]; //1� dimens�o da matriz: aloca nx blocos do tipo Voxel a partir de v
	
	for (i = 0; i < nx; i++) {
		
		v[i] = new Voxel * [ny]; //2� dimens�o da matriz: aloca ny blocos do tipo Voxel a partir de v[i]
	}
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			v[i][j] = new Voxel [nz]; //3� dimens�o da matriz: aloca nz blocos do tipo Voxel a partr de v[i][j]
		}
	}
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				this -> v[i][j][k].r = this -> r;
				this -> v[i][j][k].g = this -> g;
				this -> v[i][j][k].b = this -> b;
				this -> v[i][j][k].a = this -> a;
				this -> v[i][j][k].isOn = false;
				//inicializa��o de cada voxel para cada membro da struct
			}
		}
	}
}

//implementa��o do destrutor de classe 
Sculptor::~Sculptor() {
	
	int i;
	int j;
	//contadores de itera��o
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			delete [] v[i][j]; //libera o �ltima sequ�ncia alocada
		}
	}
	
	for (i = 0; i < nx; i++) {
		
		delete [] v[i]; //libera a pen�ltima sequ�ncia alocada
	}
	
	delete [] v; //libera a primeira sequ�ncia alocada
}

//implementa��o do membro de sele��o de cor de voxel
void Sculptor::setColor(float r, float g, float b, float alpha) {
	
	this -> r = r;
	this -> g = g;
	this -> b = b;
	this -> a = alpha;
	//atribui cores e transpar�ncia de acordo com os par�metros
}

//implementa��o do membro de ativa��o de voxel
void Sculptor::putVoxel(int x, int y, int z) {
	
	if ((this -> nx > x) && (this -> ny > y) && (this -> nz > z)) {
		
		this -> v[x][y][z].isOn = true;
	
		this -> v[x][y][z].r = this -> r;
		this -> v[x][y][z].g = this -> g;
		this -> v[x][y][z].b = this -> b;
		this -> v[x][y][z].a = this -> a;
		//ativa o voxel e atribui a ele a cor atual se a posi��o for v�lida
	}
}

//implementa��o do membro de desativa��o de voxel
void Sculptor::cutVoxel(int x, int y, int z) {
	
	if ((this -> nx > x) && (this -> ny > y) && (this -> nz > z)) {
		
		this -> v[x][y][z].isOn = false;
		//desativa o voxel se a posi��o for v�lida
	}
}

//implementa��o do membro de ativa��o de bloxo de voxels
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	if ((this -> nx >= x0 && this -> nx >= x1) && (this -> ny >= y0 && this -> ny >= y1) && (this -> nz >= z0 && this -> nz >= z1)) {
		
		for (i = x0; i < x1; i++) {
		
			for (j = y0; j < y1; j++) {
			
				for (k = z0; k < z1; k++) {
				
					this -> v[i][j][k].isOn = true;
	
					this -> v[i][j][k].r = this -> r;
					this -> v[i][j][k].g = this -> g;
					this -> v[i][j][k].b = this -> b;
					this -> v[i][j][k].a = this -> a;
					//ativa um bloco de voxels e atribui a eles a cor atual se as posi��es forem v�lidas
				}
			}
		}	
	}
}

//implementa��o do membro de desativa��o de bloxo de voxels
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	if ((this -> nx >= x0 && this -> nx >= x1) && (this -> ny >= y0 && this -> ny >= y1) && (this -> nz >= z0 && this -> nz >= z1)) {
		
		for (i = x0; i < x1; i++) {
		
			for (j = y0; j < y1; j++) {
			
				for (k = z0; k < z1; k++) {
				
					this -> v[i][j][k].isOn = false;
					//desativa um bloco de voxels se as posi��es forem v�lidas
				}
			}
		}	
	}		
}

//implementa��o do membro de ativa��o de esfera
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int r) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if ((pow(i - xcenter, 2)) + (pow(j - ycenter, 2)) + (pow(k - zcenter, 2)) <= (pow(r, 2))) {
					
					this -> v[i][j][k].isOn = true;
	
					this -> v[i][j][k].r = this -> r;
					this -> v[i][j][k].g = this -> g;
					this -> v[i][j][k].b = this -> b;
					this -> v[i][j][k].a = this -> a;
					//ativa um bloco de voxels e atribui a eles a cor atual se a condi��o for satisfeita					
				}
			}
		}
	}	
}

//implementa��o do membro de desativa��o de esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int r) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if ((pow(i - xcenter, 2)) + (pow(j - ycenter, 2)) + (pow(k - zcenter, 2)) <= (pow(r, 2))) {
					
					this -> v[i][j][k].isOn = false;
					//desativa um bloco de voxels e atribui a eles a cor atual se a condi��o for satisfeita	
				}
			}
		}
	}
}

//implementa��o do membro de ativa��o de elipsoide
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if ((pow(i - xcenter, 2) / pow(rx, 2)) + (pow(j - ycenter, 2) / pow(ry, 2)) + (pow(k - zcenter, 2) / pow(rz, 2)) <= 1) {
					
					this -> v[i][j][k].isOn = true;
	
					this -> v[i][j][k].r = this -> r;
					this -> v[i][j][k].g = this -> g;
					this -> v[i][j][k].b = this -> b;
					this -> v[i][j][k].a = this -> a;
					//ativa um bloco de voxels e atribui a eles a cor atual se a condi��o for satisfeita					
				}
			}
		}
	}
}

//implementa��o do membro de desativa��o de elipsoide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	
	int i;
	int j;
	int k;
	//contadores de itera��o
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if ((pow(i - xcenter, 2) / pow(rx, 2)) + (pow(j - ycenter, 2) / pow(ry, 2)) + (pow(k - zcenter, 2) / pow(rz, 2)) <= 1) {
					
					this -> v[i][j][k].isOn = false;
					//desativa um bloco de voxels e atribui a eles a cor atual se a condi��o for satisfeita	
				}
			}
		}
	}
}

//implementa��o do membro de grava��o de arquivo
void Sculptor::writeOFF(char *filename) {
	
	int i;
	int j;
	int k;
	int n_voxels;
	//contadores de itera��o
	
	int n_vertices; //contador de vertices
	
	n_voxels = 0;
	
	ofstream fout; //objeto para fluxo de sa�da
	
	fout.open (filename); //abertura de fluxo para arquivo
	
	if(!fout.is_open()) {
		
		cout << "O arquivo n�o p�de ser aberto" << endl;
		
		exit (1);
	} //verifica abertura do fluxo
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if (v[i][j][k].isOn == true) {
					
					n_voxels = n_voxels + 1; //guarda o n�mero de voxels ativados atualmente
				}
			}
		}
	}
	
	fout << "OFF" << endl; //escreve no arquivo o tipo de arquivo
	fout << n_voxels*8 << " " << n_voxels*6 << " " << n_voxels*0 << endl; //escreve no arquivo o n�mero de v�rtices, faces e arestas
	
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if (v[i][j][k].isOn == true) {
					
					fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl; //PO
					fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl; //P1
					fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl; //P2
					fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl; //P3
					fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl; //P4
					fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl; //P5
					fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl; //P6
					fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl; //P7
				}
			}
		}
	} //define as coordenadas dos v�rtices do cubo
	
	n_voxels = 0; //torna a vari�vel para o valor nulo
	
	for (i = 0; i < nx; i++) {
		
		for (j = 0; j < ny; j++) {
			
			for (k = 0; k < nz; k++) {
				
				if (v[i][j][k].isOn == true) {
					
					n_vertices = n_voxels * 8;
					
					fout << "4" << " " << n_vertices + 0 << " " << n_vertices + 1 << " " << n_vertices + 2 << " " << n_vertices + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					fout << "4" << " " << n_vertices + 0 << " " << n_vertices + 3 << " " << n_vertices + 5 << " " << n_vertices + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;					 
					fout << "4" << " " << n_vertices + 4 << " " << n_vertices + 5 << " " << n_vertices + 7 << " " << n_vertices + 6 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					fout << "4" << " " << n_vertices + 1 << " " << n_vertices + 6 << " " << n_vertices + 7 << " " << n_vertices + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					fout << "4" << " " << n_vertices + 0 << " " << n_vertices + 4 << " " << n_vertices + 6 << " " << n_vertices + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					fout << "4" << " " << n_vertices + 2 << " " << n_vertices + 7 << " " << n_vertices + 5 << " " << n_vertices + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					
					n_voxels = n_voxels + 1;
				}
			}
		}
	} //define n�mero de v�rtices, refer�ncia dos v�rtices, cor e transpar�ncia de cada face do voxel
	
	fout.close(); //fecha o fluxo
}
