/*
 * Handles calculations, all interactions with computational machinery (calculator, and thus indirectly, parser)
 * Ensures that calculation is only done once for a set of graphs
 * Handles all signals with instructions for graphs
 */

#ifndef GRAPHCONTROL_H
#define GRAPHCONTROL_H

#include <QHBoxLayout>

#include "graph.h"
#include "calculator.h"

class GraphController : public QWidget {
	Q_OBJECT

private:
	struct graphprops {
		QPointF mtopleft; //Location in computation units of the lower left corner
		double xr;	// X range: total number of units of x range displayed
		double xsc;	// X coordinate mark scale
		double yr;	// Y range: total number of units of y range displayed
		double ysc;	// Y coordinate mark scale
	} mgraphprops;

	struct pixprops {
		int width;
		int height;
	} mpixprops;

	Calculator *mcalc;
	string mfct;
	int mmode;		// 0 => point, 1 => iterate, 2 => iterate and currently drawing iterations
	Graph **mgraphs;
	int msize;

	QPointF calcToGraph(QPointF p);
	QPointF graphToCalc(QPointF p);
public:
	GraphController(int numGraphs, Calculator *c = new Calculator(), int width=400, int height=400, QWidget *parent=0);
	~GraphController();
public slots:
	 void s_updateCursor(QPointF p, Graph *g);
	 void s_updateDot(QPointF p);
};
#endif
