#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

// Fetch the uint64 at addr from the current process.

uint64
sys_sysinfo(void) {
  uint64 addr;
  if(argaddr(0, &addr) < 0) {
    return -1;
  }
  struct sysinfo info;
  info.freemem = freemem();
  info.nproc = nproc();
  if(copyout(myproc()->pagetable, addr,  (char*)&info, sizeof(info)) < 0) {
    return -1;
  }
  return 0;
}
