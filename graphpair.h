#ifndef GRAPHPAIR_H
#define GRAPHPAIR_H

#include <QWidget>
#include <QHBoxLayout>
#include "graph.h"
//#include "parser.h"

class GraphPair : public QWidget {
	Q_OBJECT

	QHBoxLayout *layout;
	Graph *left;
	Graph *right;
	Calculator *transform;

public:
	GraphPair(int graphWidth, int graphHeight, Calculator * c = new Calculator(), QWidget *parent=0);
	~GraphPair();
	
};
#endif
