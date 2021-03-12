#ifndef __INITCALL_H__
#define __INITCALL_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*initcall_t)(void);

#define __init __attribute__ ((__section__ (".init.text")))

#define __define_initcall(level, fn, id) \
	static const initcall_t __initcall_##fn##id \
	__attribute__((__used__, __section__(".initcall_" level ".text"))) = fn






#ifdef __cplusplus
}
#endif

#endif /* __INITCALL_H__ */
