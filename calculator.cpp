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

void Calculator::setFct(string f) {
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

int Calculator::iterate(QPointF seed, std::vector<QPointF> *output) {
	if(output->size() != 0) {
		output->clear();
	}

	cx result;
	double xdifference;
	double ydifference;
	t->setVar(ITR_VAR, qpfToCx(seed));
    for(int i = 0; i < 10000; ++i) {
		try {
			result = t->eval();
			output->push_back(cxToQpf(result));
			if(i >= 1) {
				xdifference = (*output)[i].x() - (*output)[i-1].x();
				ydifference = (*output)[i].y() - (*output)[i-1].y();
				if( (xdifference > 0 ? xdifference : -xdifference) < ITERATION_THRESHHOLD &&
					(ydifference > 0 ? ydifference : -ydifference) < ITERATION_THRESHHOLD) {
					return i;
				}
			}
			t->setVar(ITR_VAR , result);
		} catch(const std::invalid_argument& e) {
			return i;
		}
	}
    return 10000;
}
