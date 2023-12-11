# Blank-Encryption Project
Implement simple stream-cipher symmetric encrytion/decryption algorithm, and encode the encrypted text into a "blank" text file.

# How To Build
## On Ubuntu 22.04
Change into the the project root directory, and then type the following commands in the terminal:
```shell
mkdir build
cd build
cmake ..
make
```

Thereafter the binary executable can be found at `build/bin/blank_encrypt`.

## On Windows 11
In Visual Studio Community, exclude the source file `src\product\ascii_prn.cc` from build.

# Quick Start
Place the built binary executable in a standalone directory/folder.
## Generate Encryption Key
### On Ubuntu 22.04
```shell
./blank_encrypt -g newkey.txt -e -i dummyin -o dummyout
```

### On Windows 11
```ps1
blank_encrypt.exe -g newkey.txt -e -i dummyin -o dummyout
```

## Peform Encrytion
Replace the `unencrypted.txt` and `encrypted.txt` with you file names in the following commands in this section.

### On Ubuntu 22.04
```shell
./blank_encrypt -k newkey.txt -f -e -i unencrypted.txt -o encrypted.txt
```

### On Windows 11
```ps1
blank_encrypt.exe -k newkey.txt -f -e -i unencrypted.txt -o encrypted.txt
```

## Perform Decryption
Replace the `encrypted.txt` and `decrypted.txt` with you file names in the following commands in this section.

### On Ubuntu 22.04
```shell
./blank_encrypt -k newkey.txt -f -d -i encrypted.txt -o decrypted.txt
```

### On Windows 11
```ps1
blank_encrypt.exe -k newkey.txt -f -d -i encrypted.txt -o decrypted.txt
```

# Input Arguments
Run the built executable with the flag `-h` to see a description of the input arguments. Following is a snapshot
```shell
Usage: blank_encrypt.exe [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -e,--encrypt                Perform encryption.
  -d,--decrypt                Perform decryption.
  -i,--input TEXT             Specify the input file name
  -o,--output TEXT            Specify the output file name
  -g,--generateKet TEXT       Generate an encryption key and store it in the specified directory
  -k,--key TEXT               Specify the encryption key in hexadecimal format
  -n,--notsequential          Do not process sequentially
  -f,--flush                  Flush output file
```
