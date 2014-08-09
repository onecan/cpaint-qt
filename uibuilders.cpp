#include "uibuilders.h"

void ui_functionControls_presets(QComboBox *presets) {
	presets->setDuplicatesEnabled(false);
	presets->addItem("Linear");
	presets->addItem("Polar Linear");
	presets->addItem("Quadratic");
	presets->addItem("Inverse Quadratic");
}

void ui_functionControls_mode(QComboBox *mode) {
	mode->addItem("Point");
	mode->addItem("Iterate");
}

void ui_functionControls_subfuncs(QListWidget *l) {
}

void ui_functionControls(QTabWidget *t, QPushButton *apply, QPushButton *cancel, QComboBox *mode) {
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
	apply->setText("Apply");
	bottomBox->addWidget(apply);
	cancel->setText("Cancel");
	bottomBox->addWidget(cancel);


	QVBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(topBox);
	layout->addLayout(middleBox);
	layout->addLayout(bottomBox);

	container->setLayout(layout);
	t->addTab(container, "Function");
}
