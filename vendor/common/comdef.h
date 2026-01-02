#ifndef _H_COMDEF_H__
#define _H_COMDEF_H__

#include <stdint.h>
#include <stddef.h>

#define container_of(ptr, type, member) ( \
	(type *)( (char *)(ptr) - offsetof(type,member) ))


#endif // !_H_COMDEF_H__

