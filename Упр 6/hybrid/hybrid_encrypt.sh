#!/bin/bash

# AES ключ
openssl rand -out aes_key.bin 32

# IV
openssl rand -out iv.bin 16

# AES encrypt
openssl enc -aes-256-cbc \
-pass file:./aes_key.bin \
-in big_data.txt \
-out data.enc \
-Iv $(xxd -p iv.bin)

# RSA encrypt AES key
openssl pkeyutl -encrypt \
-in aes_key.bin \
-pubin \
-inkey public.pem \
-pkeyopt rsa_padding_mode:oaep \
-out encrypted_aes_key.enc

rm aes_key.bin

echo "ENCRYPT DONE"
