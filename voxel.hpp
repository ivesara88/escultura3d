//Arquivo para implementa��o da struct voxel
#ifndef VOXEL_HPP //diretiva de compila��o condicional
#define VOXEL_HPP //se n�o estiver definido o s�mbolo, define-o

struct Voxel {
	
	float r; //cor red
	float g; //cor green
	float b; //cor blue
	float a; //transpar�ncia
	bool isOn; //ativa��o do voxel
};

#endif
