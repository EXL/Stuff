# -*- coding: utf8 -*-
"""
The approach will mostly work in Python3, where strings are real character strings and not byte-strings.  However, the
gsm_encode function will need to be fixed to work in Python3, like so:
"""

import binascii
gsm = ("@£$¥èéùìòÇ\nØø\rÅåΔ_ΦΓΛΩΠΨΣΘΞ\x1bÆæßÉ !\"#¤%&'()*+,-./0123456789:;<=>?"
       "¡ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÑÜ`¿abcdefghijklmnopqrstuvwxyzäöñüà")
ext = ("````````````````````^```````````````````{}`````\\````````````[~]`"
       "|````````````````````````````````````€``````````````````````````")

def gsm_encode(plaintext):
    res = bytearray()
    for c in plaintext:
        idx = gsm.find(c);
        if idx != -1:
            res.append(idx)
            continue
        idx = ext.find(c)
        if idx != -1:
            res.append(27)
            res.append(idx)
    return binascii.hexlify(res)

print(gsm_encode("*102#"))
