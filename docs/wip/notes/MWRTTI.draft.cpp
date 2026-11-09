#include "PowerPC_EABI_Support/Runtime/exception.h"

namespace std {
class bad_cast : public exception {
public:
	bad_cast() { }
	virtual ~bad_cast() { }
	virtual const char* what() const { return "bad_cast"; }
};
} // namespace std

typedef struct TypeId TypeId;

typedef struct RTTIBaseDesc {
	TypeId* type;
	long offset;
} RTTIBaseDesc;

struct TypeId {
	char* tname;
	RTTIBaseDesc* bases;
};

typedef struct RTTIVTableHeader {
	TypeId* rtti;
	long d_offset;
} RTTIVTableHeader;

#define RTTI_MULTIBASE 0x80000000

static inline int rtti_strcmp(const char* a, const char* b)
{
	while (*a == *b) {
		if (*a == 0) {
			return 0;
		}
		a++;
		b++;
	}
	return *(unsigned char*)a - *(unsigned char*)b;
}

extern "C" void* __dynamic_cast(void* ptr, long vtoffset, TypeId* totype, TypeId* fromtype, short isref)
{
	RTTIVTableHeader* vtab;
	TypeId* rtti;
	long d_offset;
	const char* name;
	RTTIBaseDesc* bases;

	if (ptr == 0) {
		return 0;
	}

	vtab = *(RTTIVTableHeader**)((char*)ptr + vtoffset);
	if ((rtti = vtab->rtti) == 0) {
		goto bad;
	}
	d_offset = vtab->d_offset;
	ptr = (char*)ptr + d_offset;
	if (totype == 0 || rtti_strcmp(rtti->tname, name = totype->tname) == 0) {
		return ptr;
	}
	if ((bases = rtti->bases) == 0) {
		goto bad;
	}
	for (; bases->type != 0; bases++) {
		long offset = bases->offset;
		if (offset & RTTI_MULTIBASE) {
			long count = ((long*)bases)[2];
			if (d_offset + (offset & ~RTTI_MULTIBASE) == 0 && rtti_strcmp(bases->type->tname, name) == 0) {
				RTTIBaseDesc* sub = (RTTIBaseDesc*)((char*)bases + 0xC);
				long i;
				for (i = 0; i < count; i++, sub++) {
					if (d_offset + sub->offset == 0 && rtti_strcmp(sub->type->tname, fromtype->tname) == 0) {
						return (char*)ptr + sub->offset;
					}
				}
				goto bad;
			}
			bases = (RTTIBaseDesc*)((char*)bases + 0xC) + (count - 1);
		} else if (rtti_strcmp(bases->type->tname, name) == 0) {
			return (char*)ptr + offset;
		}
	}

bad:
	if (isref) {
		throw std::bad_cast();
	}
	return 0;
}
