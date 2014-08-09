#include "graphpair.h"

GraphPair::GraphPair(int graphWidth, int graphHeight, Calculator *c, QWidget *parent) :
	QWidget(parent) {
		transform = c;

		layout = new QHBoxLayout();
		left = new Graph(graphWidth, graphHeight, transform);
		right = new Graph(graphWidth, graphHeight, transform);
		layout->addWidget(left);
		layout->addWidget(right);

		this->setLayout(layout);

		QObject::connect(left, SIGNAL(s_updatePartnerDot(QMouseEvent *)), right, SLOT(s_updateDot(QMouseEvent*)));
		QObject::connect(right, SIGNAL(s_updatePartnerDot(QMouseEvent *)), left, SLOT(s_updateDot(QMouseEvent*)));
		QObject::connect(left, SIGNAL(s_updatePartnerCursor(QMouseEvent *)), right, SLOT(s_updateCursor(QMouseEvent *)));
		QObject::connect(right, SIGNAL(s_updatePartnerCursor(QMouseEvent *)), left, SLOT(s_updateCursor(QMouseEvent *)));
}

GraphPair::~GraphPair() {
	delete left;
	delete right;
	delete layout;
	//delete transform;
}
