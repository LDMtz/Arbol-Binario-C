#ifndef ARBOLES_H
#define ARBOLES_H

struct AlumnTreeNode *NewAlumnTreeNode(int number, const char *name);
struct AlumnTreeNode *AddAlumn(struct AlumnTreeNode *Node,int number, const char *name);
void Preorden(struct AlumnTreeNode *Node);
void Postorden(struct AlumnTreeNode *Node);
void Inorden(struct AlumnTreeNode *Node);
struct AlumnTreeNode *DeleteNode(struct AlumnTreeNode *Node, int number);
struct AlumnTreeNode *PrintAlumns(struct AlumnTreeNode *Root);

#endif // ARBOLES_H
