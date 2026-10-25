#include "PowerPC_EABI_Support/Runtime/MWCPlusLib.h"

#define AMBIGUOUS_BASE 0x80000000

namespace std {
class exception {
public:
	exception() { }
	virtual ~exception() { }
	virtual const char* what() const;
};

class type_info {
public:
	const char* tname;
	const void* tbase;
};

class bad_cast : public exception {
public:
	bad_cast() { }
	virtual ~bad_cast() { }
	virtual const char* what() const { return "bad_cast"; }
};
} // namespace std

typedef struct RTTIBaseDesc {
	const std::type_info* type;
	long offset;
} RTTIBaseDesc;

typedef struct RTTIVTableHeader {
	const std::type_info* type;
	long offset;
} RTTIVTableHeader;

static inline int __rtti_strcmp(const char* s1, const char* s2)
{
	for (; *s1 == *s2; s1++, s2++) {
		if (*s1 == 0) {
			return 0;
		}
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

extern "C" void* __dynamic_cast(void* ptr, long vtoffset, const std::type_info* totype, const std::type_info* srctype, short isref)
{
	RTTIVTableHeader* vtab;
	const RTTIBaseDesc* bases;
	long count;

	if (ptr == NULL) {
		return NULL;
	}

	vtab = *(RTTIVTableHeader**)((char*)ptr + vtoffset);
	if (vtab->type != NULL) {
		ptr = (char*)ptr + vtab->offset;
		if (!totype) {
			return ptr;
		}
		if (__rtti_strcmp(vtab->type->tname, totype->tname) == 0) {
			return ptr;
		}
		if ((bases = (const RTTIBaseDesc*)vtab->type->tbase) != NULL) {
			for (; bases->type != NULL; bases++) {
				long offset = bases->offset;
				if (offset & AMBIGUOUS_BASE) {
					count = *(long*)(bases + 1);
					if (vtab->offset + (offset & ~AMBIGUOUS_BASE) == 0 && __rtti_strcmp(bases->type->tname, totype->tname) == 0) {
						const RTTIBaseDesc* sub = (const RTTIBaseDesc*)((char*)bases + 0xC);
						for (; count > 0; count--, sub++) {
							if (vtab->offset + sub->offset == 0 && __rtti_strcmp(sub->type->tname, srctype->tname) == 0) {
								return (char*)ptr + sub->offset;
							}
						}
						break;
					}
					bases = (const RTTIBaseDesc*)((char*)bases + 0xC);
					bases += count - 1;
				} else if (__rtti_strcmp(bases->type->tname, totype->tname) == 0) {
					return (char*)ptr + offset;
				}
			}
		}
	}

	if (isref) {
		throw std::bad_cast();
	}
	return NULL;
}
