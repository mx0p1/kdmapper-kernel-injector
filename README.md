===============================================
                        ADVANCED DLL INJECTOR & MAPPER
============================================

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

```text
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
