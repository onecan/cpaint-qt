#include "uibuilders.h"

void ui_functionControls(QTabWidget *t, QPushButton *clear, QPushButton *cancel, QPushButton *apply, QComboBox *mode, GraphController *g) {
	QWidget *container = new QWidget();

	QHBoxLayout *topBox = new QHBoxLayout();
	topBox->addWidget(new QLabel("Function"));
	topBox->addWidget(new InputEdit());


	QHBoxLayout *middleBox = new QHBoxLayout();
	QListWidget *subfunc = new QListWidget();
	ui_functionControls_subfuncs(subfunc);
	middleBox->addWidget(subfunc);


	QHBoxLayout *bottomBox = new QHBoxLayout();
	QComboBox *presets = new QComboBox();
	ui_functionControls_presets(presets);
	bottomBox->addWidget(new QLabel("Load Preset"));
	bottomBox->addWidget(presets);

	bottomBox->addSpacerItem(new QSpacerItem(40, 20));
	bottomBox->addWidget(new QLabel("Mode"));

	ui_functionControls_mode(mode);
	bottomBox->addWidget(mode);

	bottomBox->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding));
	ui_functionControls_clear(clear, g);
	ui_functionControls_cancel(cancel);
	ui_functionControls_apply(apply, g);
	bottomBox->addWidget(clear);
	bottomBox->addWidget(cancel);
	bottomBox->addWidget(apply);


	QVBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(topBox);
	layout->addLayout(middleBox);
	layout->addLayout(bottomBox);

	container->setLayout(layout);
	t->addTab(container, "Function");
}

void ui_functionControls_apply(QPushButton *apply, GraphController *g) {
	apply->setText("Apply Changes");
}

void ui_functionControls_cancel(QPushButton *cancel) {
	cancel->setText("Cancel");
}

void ui_functionControls_clear(QPushButton *clear, GraphController *g) {
	clear->setText("Clear Graphs");
	QObject::connect(clear, SIGNAL(pressed()), g, SLOT(s_clear()) );
}

void ui_functionControls_mode(QComboBox *mode) {
	mode->addItem("Point");
	mode->addItem("Iterate");
}

void ui_functionControls_presets(QComboBox *presets) {
	presets->setDuplicatesEnabled(false);
	presets->addItem("Linear");
	presets->addItem("Polar Linear");
	presets->addItem("Quadratic");
	presets->addItem("Inverse Quadratic");
}

void ui_functionControls_subfuncs(QListWidget *l) {
}
