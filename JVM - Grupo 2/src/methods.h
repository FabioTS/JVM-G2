#ifndef METHOD
#define METHOD

#include "baseTypes.h"
#include "constantPool.h"
#include "attributes.h"

using namespace std;

//struct para armazenar os metodos
typedef struct {
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	attribute_info *attributes;
} method_info;

string getMethodFlags (uint16_t flags);
method_info readMethod (FILE* fp,cp_info *cp);
method_info *readMethods (FILE* fp, int length,cp_info *cp);
void showMethod (method_info f, cp_info *cp);
void showMethods (method_info *f, cp_info *cp, int length);

#endif 