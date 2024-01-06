#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Estructuras.h"
#include "FuncionesArbol.h"

int CurrentAlumns = 0;
struct AlumnTreeNode *AlumnRoot =NULL;

struct AlumnTreeNode *NewAlumnTreeNode(int number, const char *name) {
	struct AlumnTreeNode *Node = (struct AlumnTreeNode*)malloc(sizeof(struct AlumnTreeNode));
	Node->nLeft = Node->nRight = NULL;
    Node->NumberTreeNode = number;
    strncpy(Node->Name, name, sizeof(Node->Name) - 1);
    Node->Name[sizeof(Node->Name) - 1] = '\0';
	CurrentAlumns++; //Solo para llevar el conteo de alumnos
	return Node;
}

struct AlumnTreeNode *AddAlumn(struct AlumnTreeNode *Node, int number, const char *name){
	
	if(!Node){
		AlumnRoot=NewAlumnTreeNode(number,name);
		return 0;
	}
	
	if (number > Node->NumberTreeNode) // Si es mayor va a la derecha
 		if (Node->nRight == NULL)// Tienes espacio a la derecha?
 			Node->nRight = NewAlumnTreeNode(number,name);
 		else// Si la derecha ya está ocupada, recursividad 
 			AddAlumn(Node->nRight,number,name);
 	else // Si es menor va a la izquierda
 		if(Node->nLeft == NULL)// Si no, a la izquierda
 			Node->nLeft = NewAlumnTreeNode(number,name);
 		else// Si la izquierda ya está ocupada, recursividad
 			AddAlumn(Node->nLeft,number,name);
 			
};

void Preorden(struct AlumnTreeNode *Node){
	if(Node != NULL){
		printf("%d,", Node->NumberTreeNode);
	 	Preorden(Node->nLeft);
	 	Preorden(Node->nRight);		
	}
}

void Postorden(struct AlumnTreeNode *Node) {
 	if(Node != NULL){
 		Postorden(Node->nLeft);
 		Postorden(Node->nRight);
 		printf("\nNumero de Alumno: %d\nNombre: %s\n", Node->NumberTreeNode,Node->Name);
 	}
}

void Inorden(struct AlumnTreeNode *Node) {
 	if (Node != NULL){
 	Inorden(Node->nLeft);
 	printf("\nNumero de Alumno: %d\nNombre: %s\n", Node->NumberTreeNode,Node->Name);
 	Inorden(Node->nRight);
 	}
}

struct AlumnTreeNode *DeleteNode(struct AlumnTreeNode *Node, int number) {
	//TODO: CORREGIR ESTA FUNCION
 	//Se encontro el nodo
	if(Node->NumberTreeNode == number){
		// Caso de que no tenga hijos
		if(Node->nLeft == NULL && Node->nRight == NULL){
			free(Node);
			Node = NULL;
	 	}
	 	// Caso de que tenga un hijo.
		if(Node->nLeft != NULL || Node->nRight != NULL){
			if (Node->nLeft != NULL) {
				struct AlumnTreeNode *Aux = Node;
				Node = Node->nLeft;
				free(Aux);
		 	}else{
				struct AlumnTreeNode *Aux = Node;
				Node = Node->nRight;
				free(Aux);
			}
		}
	 	// Caso de que tenga dos hijos.
		if(Node->nLeft != NULL && Node->nRight != NULL){
		 	struct AlumnTreeNode *Aux = Node->nRight;
			struct AlumnTreeNode *SuccessorFather = Node;
			 
			while (Aux->nLeft != NULL) {
				SuccessorFather = Aux;
				Aux = Aux->nLeft;
		 	}
		 
		 	//(*Node)->NumberTreeNode = Aux->NumberTreeNode;
		 	Node= Aux;
	 	
		 	if (SuccessorFather == Node)
		 		Node->nRight = Aux->nRight;
		 	else
		 		SuccessorFather->nLeft = Aux->nRight;
		 
		 	free(Aux);
		}
 	}
 	else if (number < Node->NumberTreeNode){ // El dato es menor, continuar buscando en el subárbol izquierdo
 		DeleteNode(Node->nLeft, number);
 	}
 	else{ // El dato es mayor, continuar buscando en el subárbol derecho
 		DeleteNode(Node->nRight, number);
 	}
}

struct AlumnTreeNode *PrintAlumns(struct AlumnTreeNode *Root){
	//TODO: ACTUALIZAR ESTA FUNCION
	int Option;
	printf("\nDe que forma quiere recorrer el arbol: ");
	printf("\n1.Preorden | 2.Postorden | 3.Inorden ");
	do{
		printf("\n---> Opcion: ");
		scanf("%d",&Option);
		switch(Option){
			case 1:
				if(Root){
					printf("\nImprimiendo Preorden:");
					Preorden(Root);
				}	
				else
					printf("\nNo hay nodos en el arbol\n");

				break;
			case 2:
				if(Root){
					printf("\nImprimiendo Postorden:");
					Postorden(Root);
				}	
				else
					printf("\nNo hay nodos en el arbol\n");
				break;
			case 3:
				if(Root){
					printf("\nImprimiendo Inorden:");
					Inorden(Root);
				}	
				else
					printf("\nNo hay nodos en el arbol\n");
				break;
			default:
				printf("\nError: Ingrese una opcion valida");
				break;
		}
	}while(Option>3||Option<=0);
	
};

