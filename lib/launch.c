#include "framework.c"

void ui() {
	TitleBar("Test", 0x000000ff, 0xffffffff);
	Text("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	Text("abcdefghijklmnopqrstuvwxyz\n0123456789");
}

int main()
{
	run(ui);
	return 0;
}