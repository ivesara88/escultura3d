//Arquivo para implementação da struct voxel
#ifndef VOXEL_HPP //diretiva de compilação condicional
#define VOXEL_HPP //se não estiver definido o símbolo, define-o

struct Voxel {
	
	float r; //cor red
	float g; //cor green
	float b; //cor blue
	float a; //transparência
	bool isOn; //ativação do voxel
};

#endif
