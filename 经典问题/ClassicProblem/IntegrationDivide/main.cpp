#include "IntegrateDivde.h"

int main()
{
	IntegrateDivde *d = new IntegrateDivde(11,5, IntegrateDivde::FixedCountResult);
	std::cout << d->results() << std::endl;
	std::cout << d->result() << std::endl;
	while (1);
	delete d;
}