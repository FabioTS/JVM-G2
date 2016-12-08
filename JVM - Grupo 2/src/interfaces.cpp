#include "interfaces.h"

unsigned short *readInterfaces (FILE* fp, int length) {
	unsigned short *ret = (unsigned short *) malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++) {
		ret[i] = readU2(fp);
	}

	return ret;
}

void showInterfaces (unsigned short *interfaces, cp_info *cp, int length) {
	for (int i = 0; i < length; i++) {
		showInterface(interfaces[i], cp, i);		
	}
}

/*void showInterface (unsigned short interface, cp_info *cp) {
	cout << "\tInterface: " << dereferenceIndex(cp, interface) << endl;
}*/

void showInterface (unsigned short interface, cp_info *cp, int index) {
	cout << "\tInterface " << index << ": " << dereferenceIndex(cp, interface) << endl;
}