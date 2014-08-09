#include "calculator.h"
Calculator::Calculator() {
	t = new parser::Tree(ITR_VAR);
}

Calculator::Calculator(string f) {
	t = new parser::Tree(f);
}

Calculator::~Calculator() {
	delete t;
}

void Calculator::setFunc(string f) {
	delete t;
	t = new parser::Tree(f);
}	

void Calculator::setVar(string var, string a) {
	t->setVar(var, a);
}

void Calculator::setVar(string var, QPointF p) {
	t->setVar(var, qpfToCx(p));
}

QPointF Calculator::evalVar(string var) {
	return cxToQpf( t->evalVar(var) );
}

QPointF Calculator::eval(QPointF seed) {
	t->setVar(ITR_VAR, qpfToCx(seed));
	return cxToQpf( t->eval() );
}

string Calculator::toString() {
	return t->toString();
}

void Calculator::applyPreset(int preset) {
//	delete t;
//	IMPLEMENTATION NEEDED
	switch(preset) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

string Calculator::getFct() {
	return t->getFct();
}

string Calculator::getVarFct(string var) {
	return t->getVarFct(var);
}
	

//Utils
QPointF Calculator::cxToQpf(cx a) {
	return QPointF(a.real(), a.imag());
}

QPointF Calculator::cxToQpf(cx *a) {
	return QPointF(a->real(), a->imag());
}

cx Calculator::qpfToCx(QPointF p) {
	return cx(p.x(), p.y());
}

cx Calculator::qpfToCx(QPointF *p) {
	return cx(p->x(), p->y());
}

void Calculator::iterate(QPointF seed, int numTimes, std::vector<QPointF> *output) {
	t->setVar(ITR_VAR, qpfToCx(seed));
	if(output->size() != 0) {
		output->clear();
	}
	for(int i = numTimes; i >= 0; --i) {
		try {
			cx result = t->eval();
			output->push_back(cxToQpf(result));
			t->setVar(ITR_VAR , result);
		} catch(const std::invalid_argument& e) {
			break;
		}
	}
}
