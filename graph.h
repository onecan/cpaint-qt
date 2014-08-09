/* * Graph is a QLabel solely to allow convenient display of its internal QPixmap
 * Graph handles DRAWING ONLY. There is no computation done here, QPointFs go in, QPointFs come out, nothing else.
 * Graph catches events and emits signals which the GraphController catches and processes
 * Graph should never have slots, that should be handled by GraphController
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QColor>
#include <iostream>

#include "diff.h"

class Graph : public QLabel {
	Q_OBJECT

private:
	QPainter *mpainter;
	QPixmap *mout;

	cursordiff mcursorcache;

	void applyCursorDiff();
	void cacheCursorDiff(QPointF p);

public:
	void clear();
	Graph(int width=400, int height=400, QWidget * parent=0, Qt::WindowFlags f=0);
	~Graph();
	void drawCursor(QPointF p);
	void drawDot(QPointF p, bool withCursor = true);
	void drawIterations(std::vector<QPointF> *points, int numPoints);

protected:
	void mouseMoveEvent(QMouseEvent *ev);
	void mousePressEvent(QMouseEvent *ev);

signals:
	void s_updatePartnerCursor(QPointF p, Graph *g);
	void s_updatePartnerDot(QPointF p);
};

#endif
