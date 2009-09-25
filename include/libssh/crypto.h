/*
 * This file is part of the SSH Library
 *
 * Copyright (c) 2003,2009 by Aris Adamantiadis
 *
 * The SSH Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * The SSH Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the SSH Library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

/*
 * crypto.h is an include file for internal cryptographic structures of libssh
 */

#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include "config.h"
#ifdef cbc_encrypt
#undef cbc_encrypt
#endif
#ifdef cbc_decrypt
#undef cbc_decrypt
#endif

#ifdef HAVE_LIBGCRYPT
#include <gcrypt.h>
#endif

struct crypto_struct {
    const char *name; /* ssh name of the algorithm */
    unsigned int blocksize; /* blocksize of the algo */
    unsigned int keylen; /* length of the key structure */
#ifdef HAVE_LIBGCRYPT
    gcry_cipher_hd_t *key;
#elif defined HAVE_LIBCRYPTO
    void *key; /* a key buffer allocated for the algo */
#endif
    unsigned int keysize; /* bytes of key used. != keylen */
#ifdef HAVE_LIBGCRYPT
    /* sets the new key for immediate use */
    int (*set_encrypt_key)(struct crypto_struct *cipher, void *key, void *IV);
    int (*set_decrypt_key)(struct crypto_struct *cipher, void *key, void *IV);
    void (*cbc_encrypt)(struct crypto_struct *cipher, void *in, void *out,
        unsigned long len);
    void (*cbc_decrypt)(struct crypto_struct *cipher, void *in, void *out,
        unsigned long len);
#elif defined HAVE_LIBCRYPTO
    /* sets the new key for immediate use */
    int (*set_encrypt_key)(struct crypto_struct *cipher, void *key);
    int (*set_decrypt_key)(struct crypto_struct *cipher, void *key);
    void (*cbc_encrypt)(struct crypto_struct *cipher, void *in, void *out,
        unsigned long len, void *IV);
    void (*cbc_decrypt)(struct crypto_struct *cipher, void *in, void *out,
        unsigned long len, void *IV);
#endif
};

/* vim: set ts=2 sw=2 et cindent: */
#endif /* _CRYPTO_H_ */
