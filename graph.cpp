#include "graph.h"

inline void Graph::applyCursorDiff() {
	mpainter->drawPixmap( mcursorcache.pos, mcursorcache.buffer );
}

inline void Graph::cacheCursorDiff(QPointF p) {
	QRect rectToCopy( QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH + 1, CURSOR_HEIGHT + 1) );
	mcursorcache.pos = rectToCopy;
	mcursorcache.buffer = mout->copy(rectToCopy);
}

Graph::Graph(int width, int height, QWidget *parent, Qt::WindowFlags f) :
	QLabel(parent, f) {

	mout = new QPixmap(width, height);
	mout->fill(QColor(255, 255, 255, 255));
	this->setPixmap(*mout);

	mpainter = new QPainter();

	this->setMouseTracking(true);
}

Graph::~Graph() {
	delete mout;
	mout = NULL;
	delete mpainter;
	mpainter = NULL;
}


void Graph::drawCursor(QPointF p) {
	mpainter->begin(mout);
	applyCursorDiff();
	mpainter->setPen(QColor(0,255, 0, 255));

	QRect drawrect( QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH, CURSOR_HEIGHT) );
	cacheCursorDiff(p);
	mpainter->drawEllipse(drawrect);
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::drawDot(QPointF p, bool withCursor) {
	mpainter->begin(mout);
	mpainter->setPen(QColor(255, 0, 0, 255));
	applyCursorDiff();
	mpainter->drawEllipse( p + QPointF(1, 1), CURSOR_POINT_RADIUS, CURSOR_POINT_RADIUS);

	QRect drawrect(QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH, CURSOR_HEIGHT));
	cacheCursorDiff(p);
	if(withCursor) {
		mpainter->setPen(QColor(0,255, 0, 255));
		mpainter->drawEllipse(drawrect);
	}
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::drawIterations(std::vector<QPointF> *points, int numPoints) {
	mpainter->begin(mout);
	mpainter->setPen(QColor(255, 0, 0, 255));
	QPointF p;
	for(int i = numPoints - 1; i >= 0; --i) {
		p = (*points)[i];
		applyCursorDiff();
		mpainter->drawEllipse( p + QPointF(1, 1), CURSOR_POINT_RADIUS, CURSOR_POINT_RADIUS);
		cacheCursorDiff(p);
	}
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::mouseMoveEvent(QMouseEvent *ev) {
	drawCursor(ev->pos());
	emit s_updatePartnerCursor(ev->posF(), this);
}

void Graph::mousePressEvent(QMouseEvent *ev) {
	emit s_updatePartnerDot(ev->posF());
}
