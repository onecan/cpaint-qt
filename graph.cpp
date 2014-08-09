#include "graph.h"


Graph::Graph(int width, int height, Calculator *c, QWidget *parent, Qt::WindowFlags f) :
	QLabel(parent, f) {
	mode = 1;

	mout = new QPixmap(width, height);
	mout->fill(QColor(255, 255, 255, 255));
	this->setPixmap(*mout);
	mpainter = new QPainter();
	calc = c;
	currentlyIterating = false;

	mgraphprops = { 
		QPointF(-2, 2),
		4, 1,
		4, 1
	};
	this->setMouseTracking(true);
}


Graph::~Graph() {
	delete mout;
	delete mpainter;
}

void Graph::drawCursor(QPointF p) {
	mpainter->begin(mout);
	applyCursorDiff(mcursorcache);
	mpainter->setPen(QColor(0,255, 0, 255));

	QRect drawrect(QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH, CURSOR_HEIGHT));
	cacheCursorDiff(p);
	mpainter->drawEllipse(drawrect);
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::drawDot(QPointF p, bool withCursor) {
	mpainter->begin(mout);
	mpainter->setPen(QColor(255, 0, 0, 255));
	applyCursorDiff(mcursorcache);
	drawMousept(p + QPoint(1, 1));

	QRect drawrect(QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH, CURSOR_HEIGHT));
	cacheCursorDiff(p);
	if(withCursor) {
		mpainter->setPen(QColor(0,255, 0, 255));
		mpainter->drawEllipse(drawrect);
	}
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::cacheCursorDiff(QPointF p) {
	QRect cprect(QPoint(p.x()-1, p.y()-1), QSize(CURSOR_WIDTH + 2, CURSOR_HEIGHT + 2));
	mcursorcache.pos = cprect;
	mcursorcache.buffer = mout->copy(cprect);
}

void Graph::mouseMoveEvent(QMouseEvent *ev) {
	drawCursor(ev->pos());
	emit s_updatePartnerCursor(ev);
}


void Graph::mousePressEvent(QMouseEvent *ev) {
	QPointF seed = graphToCalc(ev->posF());

	// _DEBUG_
	QPointF temp = ev->posF();
	QPointF temp0 = graphToCalc(temp);
	QPointF temp1 = calc->eval(seed);
	QPointF temp2 = calcToGraph(temp1);
	printf("(%f, %f) -> (%f, %f) -> (%f, %f) -> (%f, %f)\n", 
			temp.x(), temp.y(), 	//original pixel coordinate
			temp0.x(), temp0.y(), 	//calculator space cordinate
			temp1.x(), temp1.y(),	//calc space result
			temp2.x(), temp2.y() ); //reconverted graph space result
	// _GUBED_

	switch(mode) {
		case 0:
			{
				drawDot(calcToGraph(calc->eval(seed)), false );
				emit s_updatePartnerDot(ev);
				break;
			}
		case 1:
			{
				mode = 2;
			
				std::vector<QPointF> *points = new std::vector<QPointF>();
				int numPerCycle = 30;
				calc->iterate(seed, numPerCycle, points);
				drawIterations(numPerCycle, points);
				// emit some kind of update signal for partner
				
				break;
			}
			
		case 2:
			{
				mode = 1;
				break;
			}
	}
}

void Graph::drawIterations(int numPerCycle, std::vector<QPointF> *points) {
	mpainter->begin(mout);
	for(int i = numPerCycle - 1; i >= 0; --i) {
		mpainter->setPen(QColor(255, 0, 0, 255));
		applyCursorDiff(mcursorcache);
		QPointF p = (*points)[i];
		p = calcToGraph((*points)[i]);
		drawMousept(p + QPoint(1, 1));

		QRect drawrect(QPoint(p.x(), p.y()), QSize(CURSOR_WIDTH, CURSOR_HEIGHT));
		cacheCursorDiff(p);
	//	mpainter->setPen(QColor(0,255, 0, 255));
	//	mpainter->drawEllipse(drawrect);
	}
	mpainter->end();
	this->setPixmap(*mout);
}

void Graph::s_updateDot(QMouseEvent *ev) {
	QPointF seed = graphToCalc(ev->posF());
	drawDot( calcToGraph(calc->eval(seed)) );
}


void Graph::s_updateCursor(QMouseEvent *ev) {
	QPointF seed =  graphToCalc(ev->posF());
	drawCursor(calcToGraph(calc->eval(seed)) );
}

QPointF Graph::graphToCalc(QPointF p) {
	double xfac = mgraphprops.xr / mout->width();
	double yfac = mgraphprops.yr / mout->height();
	double x = xfac * p.x() + mgraphprops.mtopleft.x();
	double y = yfac * p.y() - mgraphprops.mtopleft.y();
	return QPointF(x, -y);
}

QPointF Graph::calcToGraph(QPointF p) {
	double xfac = mout->width() / mgraphprops.xr;
	double yfac = mout->height() / mgraphprops.yr;
	double x = xfac * (p.x() - mgraphprops.mtopleft.x());
	double y = yfac * (-p.y() + mgraphprops.mtopleft.y());
	return QPointF(x, y);
}

/*
//temporary to get debug output
void Graph::mousePressEvent(QMouseEvent *event)
{
	if((event->button() & Qt::LeftButton)  == Qt::LeftButton) {
		std::cout << "left mouse click " << std::endl;
	}
	else if ((event->button() & Qt::RightButton) == Qt::RightButton)
		std::cout << "right mouse click " << std::endl;
	else if ((event->button() & Qt::MidButton)  == Qt::MidButton)
		std::cout << "middle mouse click " << std::endl;

}
*/

