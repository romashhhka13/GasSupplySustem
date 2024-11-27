#include "Addition.h"
#include <format>

using namespace std;

bool ObjectsExist(const unordered_set<int>& id_set)
{
	if (id_set.size() == 0) {
		cout << "Not objects!\n";
		return false;
	}
	return true;
}

string EnterLine()
{
	string line;
	cin >> ws;
	getline(cin, line);
	cerr << line << '\n';
	return line;
}

int ChooseActionMenu(vector<string>& menu, bool with_exit = false)
{
	if (menu.size() < 1)
		return -1;
	int i = 1;
	for (auto& s : menu)
		cout << std::format("{}. {}", i++, s) << "\n";
	if (with_exit)
		cout << "0. Exit\n";

	cout << "Choose action: ";
	return GetCorrectNumber<int>(0, menu.size());
}

