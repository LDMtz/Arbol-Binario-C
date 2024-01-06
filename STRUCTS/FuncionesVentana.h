#ifndef FUNCIONESVENTANA_H
#define FUNCIONESVENTANA_H

extern const int SeparationX;
extern const int SeparationY;

void CalculatePositionLabelNode(struct AlumnTreeNode *Node, HWND hwnd, const char *name, int numberNode,int x, int y);
void PrintLabelNode(HWND hwnd, const char *name, int numberNode,int x, int y);

#endif
