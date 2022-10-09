
# kitty-decryptpassword.exe

A simple program to decrypt/unobfuscate KiTTY (fork of PuTTY) saved passwords which are stored in `C:/Users/<user>/AppData/Roaming/KiTTY/kitty.sav`.

Saving passwords in KiTTY is not secure, you should really be using ssh keys to authenticate!

## KiTTY passwords

I wanted to get saved passwords out of KiTTY and found no simple way to do so, except [enabling logging and read it from logs](https://serverfault.com/a/716152), which is annoying.

The saved passwords are not in plaintext but "encrypted" with key which is present in source code, so it does not add much real security, only [security through obscurity](https://en.wikipedia.org/wiki/Security_through_obscurity). The settings (including the passwords) are readable from `C:/Users/<user>/AppData/Roaming/KiTTY/kitty.sav`.

Encryption key is `KiTTY` (mode 1) or `<host><termtype>KiTTY` (mode 0). I think mode 0 is default behavior.
See source code here: https://github.com/cyd01/KiTTY/blob/v0.76.0.11/kitty_crypt.c

Encryption algo is obfuscated. From its name, I assume, it is [Blowfish](https://en.wikipedia.org/wiki/Blowfish_(cipher)),
but it is probably little modified because I could not make it work with just Blowfish. Or it could be named after win32 bcrypt.h. I gave up trying to understand the Assemply code.
The password is [Base64 encoded](https://en.wikipedia.org/wiki/Base64) but it uses keymap in order of [azerty keyboard layout](https://en.wikipedia.org/wiki/AZERTY) `AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn0123456789+/` (the KiTTY author is french).
See static library here: https://github.com/cyd01/KiTTY/tree/v0.76.0.11/bcrypt

So I made for myself this simple program which uses KiTTY code to decrypt password. Here it is for other people so they don't have to repeat what I did.

## Compile

Requirements: bash, sudo, docker, wine (if on linux)

Run `build.sh` which compiles 'kitty-decryptpassword.exe' inside of docker and puts it into '/builds'.
I tried to make it compile without the docker and wine but I failed. This is [the way](https://www.9bis.net/kitty/#!pages/HowToCompile.md) KiTTY is compiled and it is pretty much the only way it worked.

I'm including the compiler binary in the repository. You can download it [here](https://raw.githubusercontent.com/PetrP/kitty-decryptpassword/master/builds/kitty-decryptpassword.exe).

## Usage

Disclaimer: I haven't tried to compile or run it on windows only on linux with wine. And I don't really know C so it barely work and your milage may vary.

```
PASSWORD=<password> kitty-decryptpassword.exe <mode> <host> [<termtype>]

PASSWORD=<password> WINEDEBUG='-all' wine kitty-decryptpassword.exe <mode> <host> [<termtype>]

kitty-decryptpassword.exe --help
```
Where:
- `<password>` is 'Password' from 'kitty.sav'.
- `<mode>` is 0 or 1. Probably should be 0.
- `<host>` is 'HostName' from 'kitty.sav'.
- `<termtype>` is 'TerminalType' from 'kitty.sav', default 'xterm'.
- The decrypted password is printed to stdout. No integrity checks so the output is random for wrong mode/host/termtype.

## License

KiTTY and PuTTY code is under the MIT License. The stuff in this repository is licensed under `GPLv3.0`.
