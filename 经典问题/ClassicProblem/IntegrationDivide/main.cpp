#include "IntegrateDivde.h"

int main()
{
	IntegrateDivde *d = new IntegrateDivde(11, IntegrateDivde::CompleteResult);
	std::cout << d->results() << std::endl;
	std::cout << d->result() << std::endl;
	while (1);
	delete d;
}