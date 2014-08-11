#include "apply.h"
const QString ApplyFunctionSettings::alteredStyle = "background-color:red";
const QString ApplyFunctionSettings::defaultStyle = "background-color:white";

ApplyFunctionSettings::ApplyFunctionSettings(QWidget *parent):
	QPushButton(parent) {
	somethingChanged = false;
	this->setStyleSheet(defaultStyle);
}

ApplyFunctionSettings::~ApplyFunctionSettings() {}

void ApplyFunctionSettings::s_functionAltered(QString &test) {
	if(somethingChanged == false) {
		somethingChanged = true;
		this->setStyleSheet(alteredStyle);
	}
}

void ApplyFunctionSettings::mousePressEvent(QMouseEvent *ev) {
	somethingChanged = false;
	this->setStyleSheet(defaultStyle);
	QPushButton::mousePressEvent(ev);
}
