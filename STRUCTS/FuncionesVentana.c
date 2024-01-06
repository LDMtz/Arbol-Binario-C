#include <windows.h>
#include <stdio.h>

#include "Estructuras.h"
#include "FuncionesVentana.h"

const int SeparationX = 60;
const int SeparationY = 40;

void CalculatePositionLabelNode(struct AlumnTreeNode *Node, HWND hwnd, const char *name, int numberNode, int x, int y){
	if(!AlumnRoot) //Si es el primer nodo
	    PrintLabelNode(hwnd,name,numberNode,x,y);
	else
		if (numberNode > Node->NumberTreeNode ) // Si es mayor va a la derecha
	 		if (Node->nRight == NULL) //Si tiene espacio a la derecha
	    		PrintLabelNode(hwnd,name,numberNode,x+SeparationX, y+SeparationY);
	 		else // Si la derecha ya está ocupada, recursividad
	 			CalculatePositionLabelNode(Node->nRight,hwnd, name, numberNode, x+SeparationX, y+SeparationY);
	 	else // Si es menor va a la izquierda
	 		if (Node->nLeft == NULL) //Si tiene espacio a la izquierda
	    		PrintLabelNode(hwnd,name,numberNode,x-SeparationX, y+SeparationY);
	 		else // Si la izquierda ya está ocupada, recursividad
	 			CalculatePositionLabelNode(Node->nLeft,hwnd, name, numberNode,x-SeparationX, y+SeparationY);	
	
}

void PrintLabelNode(HWND hwnd, const char *name, int numberNode, int x, int y){
  	char NumberAndName[30];
	sprintf(NumberAndName, "%d. %s", numberNode, name);
	
	HWND Lbl = CreateWindow("STATIC", NumberAndName ,WS_VISIBLE | WS_CHILD,x, y, 200, 30,hwnd, NULL, NULL, NULL);
	HDC hdc = GetDC(Lbl);
    // Medir el tamaño del texto
    SIZE textSize;
    GetTextExtentPoint32(hdc, NumberAndName, strlen(NumberAndName), &textSize);
    // Liberar el contexto de dispositivo (DC)
    ReleaseDC(Lbl, hdc);
    // Ajustar el tamaño del control al tamaño del texto
    SetWindowPos(Lbl, NULL, 0, 0, textSize.cx, textSize.cy, SWP_NOMOVE | SWP_NOZORDER);
}
