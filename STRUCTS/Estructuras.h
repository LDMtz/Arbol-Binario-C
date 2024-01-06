#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct AlumnTreeNode{
	int NumberTreeNode;
	char Name[31];
	
	struct AlumnTreeNode *nRight;
	struct AlumnTreeNode *nLeft;
	struct TaskList *RootTaskNode;
};

//TODO: IMPLEMENTAR TAREAS A LOS ALUMNOS
/*
struct TaskList{
	int NumberTask;
	char Description[31];
	int State; //<-- 0 (pendiente) y 1(completada)
	
	struct TaskList *Sig;
};*/

extern int CurrentAlumns;
extern struct AlumnTreeNode *AlumnRoot;

#endif
