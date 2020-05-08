# Shellcode execution in remote process
## Overview
1. The remote process handle is obtained using the PID.
1. Memory is allocated in the remote process using the `VirtualAllocEx()` function.
1. After memory is allocated, the shellcode is copied to the allocated address using the `WriteProcessMemory()` function.
1. The copied shellcode is executed using `CreateRemoteThread()` function.


## `VirtualAllocEx()` Reference

```c++
LPVOID VirtualAllocEx(
  HANDLE hProcess,
  LPVOID lpAddress,
  SIZE_T dwSize,
  DWORD  flAllocationType,
  DWORD  flProtect
);
```
### `hProcess`
The handle to a process. The function allocates memory within the virtual address space of this process.

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

## `WriteProcessMemory()` Reference
```c++
BOOL WriteProcessMemory(
  HANDLE  hProcess,
  LPVOID  lpBaseAddress,
  LPCVOID lpBuffer,
  SIZE_T  nSize,
  SIZE_T  *lpNumberOfBytesWritten
);
```
### `hProcess`

A handle to the process memory to be modified.

### `lpBaseAddress`

A pointer to the base address in the specified process to which data is written. 

### `lpBuffer`

A pointer to the buffer that contains data to be written in the address space of the specified process.

### `nSize`

The number of bytes to be written to the specified process.

### `lpNumberOfBytesWritten`

A pointer to a variable that receives the number of bytes transferred into the specified process. This parameter is optional. If lpNumberOfBytesWritten is NULL, the parameter is ignored.

## `CreateRemoteThread()` Reference
```c++
HANDLE CreateRemoteThread(
  HANDLE                 hProcess,
  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
  SIZE_T                 dwStackSize,
  LPTHREAD_START_ROUTINE lpStartAddress,
  LPVOID                 lpParameter,
  DWORD                  dwCreationFlags,
  LPDWORD                lpThreadId
);
```
### `hProcess`

A handle to the process in which the thread is to be created.

### `lpThreadAttributes`

If lpThreadAttributes is NULL, the thread gets a default security descriptor and the handle cannot be inherited.

### `dwStackSize`

The initial size of the stack, in bytes. The system rounds this value to the nearest page. If this parameter is 0 (zero), the new thread uses the default size for the executable.

### `lpStartAddress`

A pointer to the application-defined function of type LPTHREAD_START_ROUTINE to be executed by the thread and represents the starting address of the thread in the remote process.
### `lpParameter`

A pointer to a variable to be passed to the thread function.

### `dwCreationFlags`

The flags that control the creation of the thread.

* 0: The thread runs immediately after creation.
* CREATE_SUSPENDED: The thread is created in a suspended state, and does not run until the ResumeThread function is called.

### `lpThreadId`

A pointer to a variable that receives the thread identifier. If this parameter is NULL, the thread identifier is not returned.