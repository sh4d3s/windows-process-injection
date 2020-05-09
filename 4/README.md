# Shellcode execution from PE Resources

## Overview

1. Generate a payload using msfvenom and save it as a raw file. Add the binary file as a resource in the VC++ project.
1. The remote process handle is obtained using the PID.
1. Memory is allocated in the remote process using the `VirtualAllocEx()` function.
1. After memory is allocated, the DLL path is copied to the allocated address using the `WriteProcessMemory()` function.
1. The address of `LoadLibrary` in searched in own malicious process which will be the same as the address of `LoadLibrary` in the victim process. Thus choosing Kernel32
1. The evil DLL is loaded using `CreateRemoteThread()` function bypassing the location of DLL path in memory and the address of the LoadLibrary function.

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

- `MEM_COMMIT` : Allocates memory charges (from the overall size of memory and the paging files on disk) for the specified reserved memory pages. The function also guarantees that when the caller later initially accesses the memory, the contents will be zero.

- `MEM_RESERVE` : Reserves a range of the process's virtual address space without allocating any actual physical storage in memory or in the paging file on disk.

To reserve and commit pages in one step, call VirtualAlloc with `MEM_COMMIT | MEM_RESERVE`.

### `flProtect`

The memory protection for the region of pages to be allocated.
`PAGE_EXECUTE_READWRITE`: Enables execute, read-only, or read/write access to the committed region of pages.

## `FindResource()` Reference

```c++
HRSRC FindResourceA(
  HMODULE hModule,
  LPCSTR  lpName,
  LPCSTR  lpType
);
```

### `hModule`

A handle to the module whose portable executable file or an accompanying MUI file contains the resource. If this parameter is NULL, the function searches the module used to create the current process.

### `lpName`

The name of the resource. Alternately, rather than a pointer, this parameter can be MAKEINTRESOURCE(ID), where ID is the integer identifier of the resource.

### `lpType`

The resource type. Alternately, rather than a pointer, this parameter can be MAKEINTRESOURCE(ID), where ID is the integer identifier of the given

## `LoadResource()` Reference

```c++
HGLOBAL LoadResource(
  HMODULE hModule,
  HRSRC   hResInfo
);
```

### `hModule`

A handle to the module whose executable file contains the resource. If hModule is NULL, the system loads the resource from the module that was used to create the current process.

### `hResInfo`

A handle to the resource to be loaded. This handle is returned by the `FindResource()`.
