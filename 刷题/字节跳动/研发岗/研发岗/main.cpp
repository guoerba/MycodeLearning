 

struct time;
struct time {
	int H;
	int M;
	time() :H(0), M(0) {};
	time(int h, int m) :H(h), M(m) {};
};

struct time mintotime(int min)
{
	struct time t;
	if (min >= 60)
	{
		int h = min - 60;
		t.H = h;
		t.M = min - h;
	}
	else
	{
		t.H = 0;
		t.M = min;
	}
	return t;
}

int timesub(struct time a, struct time b)
{
	int at = a.H * 60 + a.M;
	int bt = b.H * 60 + b.M;
	return at - bt;
}

int timesub(struct time a, int min)
{
	int at = a.H * 60 + a.M;
	return at - min;
}

bool timemax(struct time a, struct time b)
{
	if (b.H < a.H)
		return true;
	else if (b.H == a.H)
	{
		if (b.M < a.M)
			return true;
		else
			return false;
	}
	else
		return false;
}

int main()
{
	int N, H, M;
	std::cin >> N;
	std::vector<struct time>clocks(N);
	for (int i = 0; i < N; i++)
	{
		std::cin >> H >> M;
		clocks[i].H = H;
		clocks[i].M = M;
	}
	int X, A, B;
	std::cin >> X;
	std::cin >> A >> B;
	struct time classtime(A, B);

	std::sort(clocks.begin(), clocks.end(), timemax);

	/*for (auto i : clocks)
		std::cout << i.H << ":" << i.M << " ";
	std::cout << std::endl;*/
	for (auto it = clocks.begin(); it != clocks.end(); ++it)
	{
		if (timemax(*it, classtime))
			continue;
		int tmp = timesub(classtime, *it);
		if (tmp < X)
			continue;
		std::cout << (*it).H << " " << (*it).M << std::endl;
		break;
	}
	while (1);

}