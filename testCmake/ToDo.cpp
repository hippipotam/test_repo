#include "ToDo.h"

#include <cstdio>

using namespace std;

ToDo::ToDo()
{
	printf("ToDo constructor\n");
}

ToDo::~ToDo()
{
	printf("ToDo destructor\n");
}

size_t ToDo::size() const
{
	return this_tasks.size();
}

void ToDo::addTask(const string &task)
{
	this_tasks.push_back(task);
}

string ToDo::getTask(size_t index) const
{
	if (index < this_tasks.size()) {
		return this_tasks[index];
	}
	return "";
}
