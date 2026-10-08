================================================================================
                        ADVANCED DLL INJECTOR & MAPPER
================================================================================

[!] STRICT WARNING & DISCLAIMER 

This software, manual mapping logic, and kernel driver communication interface 
are provided strictly and exclusively for educational, research, and self-improvement 
purposes in controlled environments.

DO NOT USE THIS SOFTWARE OR ITS CODE ON ANY VIDEO GAME, ONLINE SERVICE, 
ANTI-CHEAT PROTECTED ENVIRONMENT, OR PRODUCTION SYSTEM. 
Using or testing this tool against protected software (such as Vanguard, BattlEye, 
Easy Anti-Cheat, commercial games, or third-party applications without explicit 
authorization) will result in permanent account bans, system instability, kernel 
panics, or severe violations of terms of service and cyber security laws. 

The author and contributors assume absolute zero liability and are not responsible 
for any misuse, data loss, system damage, BSOD (Blue Screen of Death), or legal 
consequences resulting from the use or distribution of this software.


--------------------------------------------------------------------------------
 1. ARCHITECTURE OVERVIEW
--------------------------------------------------------------------------------
The project relies on a hybrid User-Mode and Kernel-Mode communication channel 
to bypass standard API hooks and execute manual mapping safely.

 +-----------------+       IOCTL / Ring 0      +------------------+
 |   Loader (EXE)  | ------------------------> |   Kernel Driver  |
 | (Manual Mapper) |                           | (System Ring 0)  |
 +-----------------+                           +------------------+
          |                                             |
          | Maps Sections & Resolves Imports            | Writes Memory via MmCopy
          v                                             v
 +-----------------------------------------------------------------+
 |                        Target Process                           |
 |  +-----------------------------------------------------------+  |
 |  |                  Injected Payload (DLL)                   |  |
 |  +-----------------------------------------------------------+  |
 +-----------------------------------------------------------------+


--------------------------------------------------------------------------------
 2. KEY FEATURES & CAPABILITIES
--------------------------------------------------------------------------------

- Automatic Administrator Elevation: Enforces `ForceAdmin` privileges on startup.
- Advanced Manual Mapping: Custom PE parser, section allocation, base relocation 
  handling, and Import Address Table (IAT) resolution without `LoadLibrary`.
- Kernel-Level Communication: Secure IOCTL interface bridging User-Mode (Ring 3) 
  and Kernel-Mode (Ring 0) for privileged memory operations.
- Evasion & Anti-Analysis: PE header erasure and memory discardable sections 
  cleanup post-injection.
- Compile-Time String Obfuscation: Built-in XOR encryption macros to protect 
  sensitive strings against static analysis tools (IDA Pro, Ghidra).
- Dynamic Multi-Threaded Obfuscation: Dynamic window title scrambling and process 
  monitoring routines.


--------------------------------------------------------------------------------
 3. PREREQUISITES & SETUP
--------------------------------------------------------------------------------

1. Development Environment: Microsoft Visual Studio (2019/2022 recommended) with 
   Windows Driver Kit (WDK) installed.
2. Target Configuration: Compile the entire solution exclusively in 
   **Release / x64** mode. Debug builds might cause signature/structure mismatches.
3. Test Payload: Place your compiled safe testing DLL in the output directory 
   and rename it to `test.dll` (or modify `main.cpp` path macros accordingly).
4. Safe Target: Ensure a controlled safe application (e.g., `notepad.exe`) is running 
   on a test machine or isolated VM.


--------------------------------------------------------------------------------
 4. BUILD & EXECUTION INSTRUCTIONS
--------------------------------------------------------------------------------

1. Open the solution file (`.sln`) in Visual Studio.
2. Set the solution configuration to `Release` and platform to `x64`.
3. Build the solution (Build -> Build Solution).
4. Load the signed/test-mode kernel driver safely onto your test environment.
5. Run the generated executable strictly as **Administrator**.


--------------------------------------------------------------------------------
 5. PROJECT STRUCTURE & CODE ORGANIZATION
--------------------------------------------------------------------------------
- main.cpp                    : Entry point, initialization, and UI/monitoring thread.
- Injection/injector.h        : Core manual mapping execution and allocation logic.
- Injection/Utils.h           : Injection helper functions and memory utilities.
- Communication/api.h         : Core communication APIs and wrapper definitions.
- Communication/shellcode.h   : Loader stub and execution shellcode mapping.
- Communication/Utils.h       : General helpers and process snapshot utilities.
- Communication/xor.h         : Compile-time string encryption templates.
- driver/driver.h / cpp       : Kernel communication interface and IOCTL handler.
- driver/map.h                : PE sections mapping and relocation handlers.
- driver/sys.h                : System structures, native APIs, and NT definitions.
- driver/defines.h            : IOCTL control codes, structures, and definitions.
================================================================================
