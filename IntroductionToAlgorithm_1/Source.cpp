#include <string.h>
#include <iostream>
using namespace std;
char *daonguoctu(char *s) {
	static char c[100];
	int i, n = strlen(s);
	int tam = n - 1;
	for (i = n - 1; i >= 0; i--) {
		if (s[i] == ' ' || i == 0) {
			int cursor = (i == 0 ? i : i + 1);
			while (cursor <= tam)
				printf("%c", s[cursor++]);
			printf(" ");
			tam = i - 1;
		}
	}
	return 0;
}
int main() {
	char *s;
	s = new char[100];
	cin >> s;
	cout << endl << daonguoctu(s);
	return 0;
}