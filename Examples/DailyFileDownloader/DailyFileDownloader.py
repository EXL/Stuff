#!/usr/bin/env python3

import os
import gzip
import urllib.request
import urllib.error

FILE_NAME = 'epg_lite.xml'
GZ_FILE_NAME = FILE_NAME + '.gz'

URL_PATH = 'https://iptvx.one/epg/' + GZ_FILE_NAME
OUT_PATH = '/var/www/html/online/tv3/' + FILE_NAME
TMP_PATH = '/tmp/' + GZ_FILE_NAME


def main():
    res = download_gz_file(URL_PATH, TMP_PATH)
    if res:
        decompress_and_dump_file(TMP_PATH, OUT_PATH)
        delete_file_if_exist(TMP_PATH)
    else:
        exit(-1)


def check_xml_data(data):
    return data.startswith(b'<?xml')


def decompress_and_dump_file(file_name, out_path):
    global file_content
    try:
        with gzip.open(file_name, 'rb') as file:
            file_content = file.read()
        file.close()
    except OSError:
        delete_file_if_exist(TMP_PATH)
        print('[ERROR]: GZip error!')
        exit(-2)
    res = check_xml_data(file_content)
    if res:
        delete_file_if_exist(OUT_PATH)
        with open(out_path, 'wb') as file:
            file.write(file_content)
        file.close()
    else:
        print('[ERROR]: XML data mismatch!')
        exit(-3)


def delete_file_if_exist(file_name):
    try:
        os.remove(file_name)
    except OSError as ex:
        print('[WARN]: ' + str(ex.filename) + ': ' + str(ex.strerror))


def download_gz_file(url, path):
    try:
        urllib.request.urlretrieve(url, path)
    except urllib.error.URLError as ex:
        print('[ERROR]: File downloading error: ' + str(ex.reason))
        return False
    return True


if __name__ == '__main__':
    main()
