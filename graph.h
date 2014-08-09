#ifndef GRAPH_H
#define GRAPH_H

#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QColor>
#include <iostream>

#include "calculator.h"
#include "diff.h"

#define drawpt(P) \
	mpainter->drawPoints( ((QPointF *) (P)), 1);
#define drawMousept(P) \
	mpainter->drawEllipse( ((QPointF) (P)), CURSOR_POINT_RADIUS, CURSOR_POINT_RADIUS);
#define applyDiff(D) \
	mpainter->drawPixmap( ((diff) (D)).pos, ((diff) (D)).buffer );
#define applyCursorDiff(D) \
	mpainter->drawPixmap( ((cursordiff) (D)).pos, ((cursordiff) (D)).buffer );

class Graph : public  QLabel {
	Q_OBJECT

private:
	QPainter *mpainter;
	QPixmap *mout; 			// Displayed buffer

	cursordiff mcursorcache;	//stores what was under the cursor dot

	struct graphprops {
		QPointF mtopleft; //Location in computation units of the lower left corner
		double xr;	// X range: total number of units of x range displayed
		double xsc;	// X coordinate mark scale
		double yr;	// Y range: total number of units of y range displayed
		double ysc;	// Y coordinate mark scale
	} mgraphprops;
	int mode;		// 0 => point, 1 => iterate, 2 => iterate and currently drawing iterations
	bool currentlyIterating;

	Calculator *calc;

	QPointF graphToCalc(QPointF p);
	QPointF calcToGraph(QPointF p);
	void cacheCursorDiff(QPointF p);

public:
	Graph(int width, int height, Calculator *c = new Calculator,  QWidget * parent=0, Qt::WindowFlags f=0);
	~Graph();
	//void drawCoordinates();		// draw on coordinate axes
	void drawCursor(QPointF p);
	void drawDot(QPointF p, bool withCursor = true);
	void drawIterations(int numPerCycle, std::vector<QPointF> *points);


protected:
	void mouseMoveEvent(QMouseEvent *ev);
	void mousePressEvent(QMouseEvent *ev);


public slots:
	 //void s_applyGraphChanges(QPointF center, double newxr, double newyr, double newxsc, double newysc);
	 void s_updateCursor(QMouseEvent *ev);
	 void s_updateDot(QMouseEvent *ev);
	 
signals:
	void s_updatePartnerDot(QMouseEvent *ev);	//For when click
	void s_updatePartnerCursor(QMouseEvent *ev);	//For cursor move
};


#endif
