#include "graphcontroller.h"
#include <iostream>

inline QPointF GraphController::calcToGraph(QPointF p) {
	double xfac = mpixprops.width / mgraphprops.xr;
	double yfac = mpixprops.height / mgraphprops.yr;
	double x = xfac * (p.x() - mgraphprops.mtopleft.x());
	double y = yfac * (-p.y() + mgraphprops.mtopleft.y());
	return QPointF(x, y);
}

inline QPointF GraphController::graphToCalc(QPointF p) {
	double xfac = mgraphprops.xr / mpixprops.width;
	double yfac = mgraphprops.yr / mpixprops.height;
	double x = xfac * p.x() + mgraphprops.mtopleft.x();
	double y = yfac * p.y() - mgraphprops.mtopleft.y();
	return QPointF(x, -y);
}

GraphController::GraphController(int numGraphs, Calculator *c, int width, int height, QWidget *parent) :
	QWidget(parent) {
		mgraphprops = { 
			QPointF(-2, 2),
				4, 1,
				4, 1
		};
		mpixprops = {
			width,
			height
		};

		mcalc = c;

		mmode = 1;
		mfct = mcalc->getFct();
		mgraphs = new Graph* [numGraphs];
		msize = numGraphs;

		QHBoxLayout *layout = new QHBoxLayout();
		for(int i = msize - 1; i >= 0; --i) {
			mgraphs[i] = new Graph(width, height, this);
			Graph *g = mgraphs[i];
			layout->addWidget(g);
			QObject::connect(g, SIGNAL(s_updatePartnerDot(QPointF)), this, SLOT(s_updateDot(QPointF)));
			QObject::connect(g, SIGNAL(s_updatePartnerCursor(QPointF, Graph *)), this, SLOT(s_updateCursor(QPointF, Graph *)));
		}

		this->setLayout(layout);

}

GraphController::~GraphController() {
		for(int i = msize - 1; i >= 0; --i) {
			delete (mgraphs + i);
		}
		delete [] mgraphs;
		delete mcalc;
}

void GraphController::s_updateCursor(QPointF p, Graph *g) {
	QPointF transformed = calcToGraph( mcalc->eval( graphToCalc(p) ));
	for(int i = msize - 1; i >= 0; --i) {
		if(g != mgraphs[i]) {
			mgraphs[i]->drawCursor(transformed);
		}
	}
}

// As is stands, this implementation causes the green sursor on the input graph to jump to the dot drawn.
// I am calling it a feature for now (it directs attention to the drawn dot, making it easy to find) pending feedback
void GraphController::s_updateDot(QPointF p) {
	// DEBUG
	QPointF temp0 = p;
	QPointF temp1 = graphToCalc(temp0);
	QPointF temp2 = mcalc->eval(temp1);
	QPointF temp3 = calcToGraph(temp2);
	printf("(%f, %f) -> (%f, %f) -> (%f, %f) -> (%f, %f)\n",
			temp0.x(), temp0.y(),
			temp1.x(), temp1.y(),
			temp2.x(), temp2.y(),
			temp3.x(), temp3.y());
	// END_DEBUG
	if(mmode == 0) {
		QPointF transformed = calcToGraph( mcalc->eval( graphToCalc(p) ));
		for(int i = msize - 1; i >= 0; --i) {
			mgraphs[i]->drawDot(transformed);
		}
	} else if(mmode == 1) {
		mmode = 2;

		std::vector<QPointF> *points = new std::vector<QPointF>();
		int numPoints = mcalc->iterate(graphToCalc(p), points);
		// DEBUG
		printf("%d\n", numPoints);
		for(int i = numPoints - 1; i >= 0; --i) {
			(*points)[i] = calcToGraph( (*points)[i] );
		}
		for(int i = msize - 1; i >= 0 && mmode == 2; --i) {
			mgraphs[i]->drawIterations(points, numPoints);
		}
		mmode = 1;
	} else if(mmode == 2) {
		mmode = 1;
	}
}

