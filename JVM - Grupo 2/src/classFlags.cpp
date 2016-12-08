#include "classFlags.h"

void showFlags (U2 accessFlags) {
	bool first = true;

	cout << "flags: ";

	if (accessFlags & 0x01) {
		first = false;
		cout << flagNames[0];
	}
	if (accessFlags & 0x010) {
		if (first) {
			first = false;
			cout << ", ";
		}
		cout << flagNames[1];
	}
	if (accessFlags & 0x020) {
		if (first) {
			first = false;
			cout << ", ";
		}
		cout << flagNames[2];
	}
	if (accessFlags & 0x0200) {
		if (first) {
			first = false;
			cout << ", ";
		}
		cout << flagNames[3];
	}
	if (accessFlags & 0x0400) {
		if (first) {
			first = false;
			cout << ", ";
		}
		cout << flagNames[4];
	}
	
	cout << " (0x" << hex << accessFlags << dec << ")" << endl;
}
