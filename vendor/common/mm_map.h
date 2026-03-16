#ifndef __H_MM_MAP_H_
#define __H_MM_MAP_H_

extern unsigned int __eram2_;
#define RAM_START                           0x24000000
#define RAM_SIZE                            (512*1024)

#define HEAP_START                          &__eram2_     
#define HEAP_END                            (RAM_START + RAM_SIZE)



#endif // !__H_MM_MAP_H_