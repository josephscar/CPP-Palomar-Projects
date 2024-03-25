# Project Status

## Current State

- [x] Initial setup and configuration

- [ ] Matrix class implementation
    - [x] Addition operator overloading
    - [x] Multiplication operator overloading
    - [ ] Subtraction operator overloading
    - [x] COUT operator overloading
    - [ ] ++, --, post and pre operations (pending)
    - [ ] Support all number type matrixes (pending)

- [ ] Parsing implementation
    - [x] Parses input and can complete basic matrix creation or matrix manipulation.
    - [ ]Current parsing algorithm ONLY supports single digit matrixes (and single digit outputs)

- [ ] Documentation
    - [ ] Code comments
    - [ ] User guide
    - [ ] Organize files

## Known Issues

- Parser does not support the subtraction operator resulting in negatives because it returns all numbers as postiive
- Issue with operator overloading not handling multiple-digit numbers correctly (because of parsing).
- Cannot correctly handle multi-digit outputs either (parsing problem as well).
- The program is supposed to be able to handle matrices of all types (float, int, etc.) via the template but can only handle ints.

## Next Steps

- Most issues are with the parser because they assume simplicity (single digit input/output and non negatives);
  Allow parser to extract data from strings into VECTORS and pass those vectors to functions (perserving digits and sign)
  
- Start working on user documentation.

