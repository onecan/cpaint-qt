#include <QApplication>
#include "uibuilders.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	QVBoxLayout *layout = new QVBoxLayout();
	QWidget *mainWidget = new QWidget();

	GraphController* g = new GraphController(2, new Calculator("0.9*Z"), 400, 400);

	QTabWidget *t = new QTabWidget();	
	QPushButton *apply = new QPushButton();
	QPushButton *cancel = new QPushButton();
	QComboBox *mode = new QComboBox();;
	ui_functionControls(t, apply, cancel, mode, g);	
	
	layout->addWidget(t);
	layout->addWidget(g);
	mainWidget->setLayout(layout);
	mainWidget->show();
	
	
	return app.exec();
}

