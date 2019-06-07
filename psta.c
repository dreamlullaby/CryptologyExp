#include <linux/linkage.h>
#include <linux/types.h>
#include <linux/psta.h>
#include <linux/kernel.h>

asmlinkage int sys_psta(struct pinfo *buf){
	printk("hello this is a new systemcall by lxd\n");
	return 0;
}
