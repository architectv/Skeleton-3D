#ifndef ALIASINGER_H
#define ALIASINGER_H

#include "./entity/model.h"
#include "./display/view.h"

class Aliasinger
{
public:
	Aliasinger() = delete;
	Model ModelAlias(View&, Model);
};

#endif // ALIASINGER_H