#ifndef RULELAYOUT_H
#define RULELAYOUT_H

#include <QHBoxLayout>

#include "rule.h"

// TODO consider getting rid of this class (unneccesary)
class RuleLayout : QHBoxLayout {
	public:
		Rule rule;

		RuleLayout(const Rule &r);
};

#endif
