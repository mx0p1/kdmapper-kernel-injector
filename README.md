#  DLL Injector & Mapper

<p align="center">
  <b>Hybrid User-Mode (Ring 3) & Kernel-Mode (Ring 0) DLL Injection and Manual Mapping Framework</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows" alt="Platform">
  <img src="https://img.shields.io/badge/Architecture-x64-red?style=for-the-badge" alt="Architecture">
  <img src="https://img.shields.io/badge/Language-C%2F++-yellow?style=for-the-badge&logo=cplusplus" alt="Language">
  <img src="https://img.shields.io/badge/License-Educational-green?style=for-the-badge" alt="License">
</p>

---

## ⚠️ Strict Warning & Disclaimer 

This software, manual mapping logic, and kernel driver communication interface are provided **strictly and exclusively** for educational, research, and self-improvement purposes in controlled environments.

* **DO NOT USE THIS SOFTWARE OR ITS CODE ON ANY VIDEO GAME, ONLINE SERVICE, ANTI-CHEAT PROTECTED ENVIRONMENT, OR PRODUCTION SYSTEM.** 
* Using or testing this tool against protected software (such as Vanguard, BattlEye, Easy Anti-Cheat, commercial games, or third-party applications without explicit authorization) will result in permanent account bans, system instability, kernel panics, or severe violations of terms of service and cyber security laws.
* The author and contributors assume **absolute zero liability** and are not responsible for any misuse, data loss, system damage, BSOD (Blue Screen of Death), or legal consequences resulting from the use or distribution of this software.

---

## 🏛️ Architecture Overview

The project relies on a hybrid User-Mode and Kernel-Mode communication channel to bypass standard API hooks and execute manual mapping safely.

```text
+-----------------+        IOCTL / Ring 0        +------------------+
|   Loader (EXE)  | ----------------------------> |   Kernel Driver  |
| (Manual Mapper) |                               | (System Ring 0)  |
+-----------------+                               +------------------+
         |                                                 |
         | Maps Sections & Resolves Imports                | Writes Memory via MmCopy
         v                                                 v
+-----------------------------------------------------------------+
|                          Target Process                         |
|   +---------------------------------------------------------+   |
|   |                 Injected Payload (DLL)                  |   |
|   +---------------------------------------------------------+   |
+-----------------------------------------------------------------+

`````
🚀 Key Features & Capabilities
Automatic Administrator Elevation: Enforces ForceAdmin privileges on startup.

Advanced Manual Mapping: Custom PE parser, section allocation, base relocation handling, and Import Address Table (IAT) resolution without LoadLibrary.

Kernel-Level Communication: Secure IOCTL interface bridging User-Mode (Ring 3) and Kernel-Mode (Ring 0) for privileged memory operations.

Evasion & Anti-Analysis: PE header erasure and memory discardable sections cleanup post-injection.

Compile-Time String Obfuscation: Built-in XOR encryption macros to protect sensitive strings against static analysis tools (IDA Pro, Ghidra).

Dynamic Multi-Threaded Obfuscation: Dynamic window title scrambling and process monitoring routines.


🛠️ Prerequisites & Setup
Development Environment: Microsoft Visual Studio (2019/2022 recommended) with Windows Driver Kit (WDK) installed.

Target Configuration: Compile the entire solution exclusively in Release / x64 mode. Debug builds might cause signature/structure mismatches.

Test Payload: Place your compiled safe testing DLL in the output directory and rename it to test.dll (or modify main.cpp path macros accordingly).

Safe Target: Ensure a controlled safe application (e.g., notepad.exe) is running on a test machine or isolated VM.


⚙️ Build & Execution Instructions
Open the solution file (.sln) in Visual Studio.

Set the solution configuration to Release and platform to x64.

Build the solution (Build -> Build Solution).

Load the signed/test-mode kernel driver safely onto your test environment.

Run the generated executable strictly as Administrator.


📂 Project Structure & Code Organization

```text
📦 Injector
 ┣ 📂 driver/
 ┃ ┣ 📜 driver.h / cpp        # Kernel communication interface and IOCTL handler
 ┃ ┣ 📜 map.h                 # PE sections mapping and relocation handlers
 ┃ ┣ 📜 sys.h                 # System structures, native APIs, and NT definitions
 ┃ ┗ 📜 defines.h             # IOCTL control codes, structures, and definitions
 ┣ 📂 Injection/
 ┃ ┣ 📜 injector.h            # Core manual mapping execution and allocation logic
 ┃ ┗ 📜 Utils.h               # Injection helper functions and memory utilities
 ┣ 📂 Communication/
 ┃ ┣ 📜 api.h                 # Core communication APIs and wrapper definitions
 ┃ ┗ 📜 shellcode.h           # Loader stub and execution shellcode mapping
 ┃ ┣ 📜 Utils.h               # General helpers and process snapshot utilities
 ┃ ┗ 📜 xor.h                 # Compile-time string encryption templates
 ┗ 📜 main.cpp                # Entry point, initialization, and UI/monitoring thread
````
