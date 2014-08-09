#include "inputedit.h"

InputEdit::InputEdit(QWidget * parent) :
	QLineEdit(parent) {
	this->setModified(false);
	buffer = "";
};

InputEdit::~InputEdit() {};

void InputEdit::changeEvent(QEvent *ev) {
	this->setModified(true);
}

void InputEdit::s_cancel() {
	this->clear();
	this->setText(buffer);
	this->setModified(false);
}

void InputEdit::s_apply() {
	buffer = this->text();
	this->setModified(false);
};
