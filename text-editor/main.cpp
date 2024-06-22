#include "text_editor.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	TextEditor editor;
	do {
		cout << "> ";
		string cmd;
		cin >> cmd;
		if (cmd == "q") {
			break;
		} else if (cmd == "u") {
			editor.undo();
			cout << editor.getText() << endl;
		} else if (cmd == "r") {
			editor.redo();
			cout << editor.getText() << endl;
		} else if (cmd == "c") {
			editor.commit();
			cout << editor.getText() << endl;
		} else if (cmd == "i") {
			int position;
			string text;
			cin >> position;
			cin >> text;
			editor.prepare(make_shared<InsertCommand>(position, text));
		} else if (cmd == "d") {
			int position;
			int length;
			cin >> position;
			cin >> length;
			editor.prepare(make_shared<DeleteCommand>(position, length));
		} else if (cmd == "v") {
			int position;
			int length;
			cin >> position;
			cin >> length;
			editor.prepare(make_shared<ReverseCommand>(position, length));
		}
	} while (true);

	return EXIT_SUCCESS;
}
