#include <cassert>
#include <iostream>
#include "Prototypes.h"

int main()
{
	auto i = Corrosion::make_identity();
	std::cout << i(12);
}
