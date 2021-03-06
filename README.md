## Highcall-Library

Designed to avoid generic methods used in windows, avoiding common detection routines, while being a helpful library to work with in general. Residing in usermode, it communicates with the kernel through system calls, without leaving a trace.

Supported systems are Windows 7, Windows 8, Windows 8.1, Windows 10.

* External/Internal Process 
  * List, find and open processes.
  * Enumerate Ldr/No PE/No Ldr modules.
  * Manipulate virtual memory
  * Kill/Suspend/Resume any process
  * Configure access tokens
  * Static module reading
  * Code pattern searching
* Internal Process
  * Locate export addresses without LdrGetProcedureAddress
  * Relocate/Restore functions
  * Hook functions with relocation fixes
  * Handy safe reading functions
  * String helpers (such as ignore case comparison, validation, tokenizing)
  * Error setting (compatible with WINAPI) includes notes
