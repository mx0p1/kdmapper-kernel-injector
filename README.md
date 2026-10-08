#  DLL Injector & Mapper

<p align="center">
  <b> User-Mode (Ring 3) & Kernel-Mode (Ring 0) DLL Injection and Manual Mapping </b>
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
🚀 Key Features

Manual Mapping: Custom PE parser, section allocation, and IAT resolution without LoadLibrary.

Kernel Communication: Secure Ring 3 to Ring 0 IOCTL interface.

Anti-Analysis: PE header erasure and compile-time XOR string obfuscation.

Evasion: Dynamic multi-threaded process monitoring and window scrambling.

🛠️ Setup & Build

Requirements: Visual Studio (2019/2022) 

Configuration: Build solution in Release / x64 mode.

Payload: Place test DLL as test.dll in the output directory.

Execution: Load the test-mode kernel driver, then run the EXE as Administrator.


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
👤 Author
Developed with ❤️ by mx0p1
