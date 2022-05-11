#!/usr/bin/env python3

import os
import gzip
import urllib.request
import urllib.error
import tempfile
import sys

# https://epg.it999.ru/edem.xml.gz
# https://iptvx.one/epg/epg_lite.xml.gz
# http://api.torrent-tv.ru/ttv.xmltv.xml.gz
# /var/www/html/online/tv3/epg_lite.xml

def start():
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
    except OSError:
        delete_file_if_exist(TMP_PATH)
        print('[ERROR]: GZip error!')
        exit(-2)
    res = check_xml_data(file_content)
    if res:
        delete_file_if_exist(OUT_PATH)
        with open(out_path, 'wb') as file:
            file.write(file_content)
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
    if len(sys.argv) != 3:
        print('[ERROR]: Wrong count of arguments.\n\tUsage ./DailyFileDownloader.py https://url.path/to/channels.xml.gz /path/to/store/')
        exit(-4)

    gz_filename = sys.argv[1].split('/')[-1]
    filename = gz_filename[:-3]
    url_link = sys.argv[1][:-len(gz_filename)]
    path = sys.argv[2]

    print('[INFO]: U: ' + url_link + '\n[INFO]: F: ' + filename + '\n[INFO]: G: ' + gz_filename + '\n[INFO]: P: ' + path)

    global URL_PATH
    global OUT_PATH
    global TMP_PATH

    URL_PATH = url_link + gz_filename
    OUT_PATH = os.path.join(path, filename)
    TMP_PATH = os.path.join(tempfile.gettempdir(), gz_filename)

    start()
