# SYNOPSIS

```lua
local berint = require('berint')

-- encode positive integer to BER
ber_encoded = berint.int2ber(value)

-- decode BER-encoded positive integer
value = berint.ber2int(ber_encoded)

-- decode BER-encoded positive integer at the start of binary data and get offset of the rest data
value, offset = berint.ber2int(binary_string)

-- decode BER-encoded positive integer at the midde of binary data and get offset of the rest data
value, offset = berint.ber2int(binary_string, ber_position)
```

# BUILD

```bash
gcc -lm -shared -fPIC -std=c99 -O2 -o berint.so berint.c
```
