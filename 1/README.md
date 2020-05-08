# Executing Shellcode in Local Process

## Overview
1. Memory is allocated using the `VirtualAlloc()` function.
1. After memory is allocated, the shellcode is copied to the allocated address using the `memcpy()` function.
1. The copied shellcode is executed.


## `VirtualAlloc()` Reference

```c++
LPVOID VirtualAlloc(
  LPVOID lpAddress,
  SIZE_T dwSize,
  DWORD  flAllocationType,
  DWORD  flProtect
);
```

### `lpAddress`
If this parameter is NULL, the system determines where to allocate the region.

### `dwSize`
The size of the region, in bytes. If the lpAddress parameter is NULL, this value is rounded up to the next page boundary.

### `flAllocationType`
The type of memory allocation.

* `MEM_COMMIT` : Allocates memory charges (from the overall size of memory and the paging files on disk) for the specified reserved memory pages. The function also guarantees that when the caller later initially accesses the memory, the contents will be zero.

* `MEM_RESERVE` : Reserves a range of the process's virtual address space without allocating any actual physical storage in memory or in the paging file on disk.

To reserve and commit pages in one step, call VirtualAlloc with `MEM_COMMIT | MEM_RESERVE`.

### `flProtect`
The memory protection for the region of pages to be allocated. 
`PAGE_EXECUTE_READWRITE`: Enables execute, read-only, or read/write access to the committed region of pages.
