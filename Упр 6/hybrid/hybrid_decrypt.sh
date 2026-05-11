#!/bin/bash

# RSA → получаем AES ключ обратно
openssl pkeyutl -decrypt \
-in encrypted_aes_key.enc \
-inkey private.pem \
-pkeyopt rsa_padding_mode:oaep \
-out aes_key.bin

# AES → расшифровка файла
openssl enc -d -aes-256-cbc \
-pass file:./aes_key.bin \
-in data.enc \
-out decrypted.txt

rm aes_key.bin

echo "DONE: decrypted.txt"
