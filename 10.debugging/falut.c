
int devideByValue(int _a)
{
	return _a / 0;
}

void DoSomething(int _a)
{
	devideByValue(_a);
}

int main()
{
	DoSomething(5);
	return 1;
}
