#include <QApplication>
#include "graph.h"
#include "graphpair.h"
#include "uibuilders.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	QVBoxLayout *layout = new QVBoxLayout();
	QWidget *mainWidget = new QWidget();

	GraphPair * g = new GraphPair(400, 400, new Calculator("Z^2"));
	
	QTabWidget *t = new QTabWidget();	
	QPushButton *apply = new QPushButton();
	QPushButton *cancel = new QPushButton();
	QComboBox *mode = new QComboBox();;
	ui_functionControls(t, apply, cancel, mode);	
	
	layout->addWidget(t);
	layout->addWidget(g);
	mainWidget->setLayout(layout);
	mainWidget->show();
	
	
	return app.exec();
}

