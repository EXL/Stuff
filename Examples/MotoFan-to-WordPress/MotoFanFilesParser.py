#!/usr/bin/env python3

# MotoFanFilesParser
#  Utility for parsing MotoFan.Ru site for file links and catalogs.
#
#  Written by EXL, 13-Apr-2019
#
# Install dependencies:
#  $ sudo pip3 install bs4

import os
import csv
import requests

from datetime import datetime
from multiprocessing import Pool

from bs4 import BeautifulSoup

HOST = "http://motofan.ru"
ITEMS_PER_PAGE = 20
THREADS_COUNT = 40
PAGE_AUX_PART = "&phone=&order=postdate&desc=1&start="

FILE_LINK = 0
FILE_PHONE = 1
FILE_DATE = 2
FILE_SIZE = 3

FIRMWARES_FILE = "firmwares.csv"
SOFTWARES_FILE = "softwares.csv"
ARTWORKS_FILE = "artworks.csv"


def parse_firmwares(url):
    print("==> Start parsing firmwares...")

    print("===> Gathering paged links...")
    paged_links = grab_outer_links(get_raw_html(url))

    print("===> Gathering all firmware links...")
    firmware_links = grab_inner_links(paged_links)

    print("===> Gathering descriptions...")
    firmware_list = grab_descriptions(firmware_links)

    print("===> Gathering section icons...")
    firmware_list = grab_section_icons(firmware_list, get_raw_html(url))

    print("===> Sorting list...")
    firmware_list.sort(key=lambda x: x[0])

    print('===> Writing "' + FIRMWARES_FILE + '" file...')
    write_csv(FIRMWARES_FILE, firmware_list)

    print("==> End parsing firmwares.")


def get_raw_html(url):
    return requests.get(url).text


def grab_section_icons(firmware_list, html):
    icon_list = {}
    soup = BeautifulSoup(html, "lxml")
    tds = soup.find_all("td", class_="listPhotoTD")
    for td in tds:
        icon_list[td.find("img").get("alt")] = HOST + td.find("img").get("src")
    for element in firmware_list:
        element.append(icon_list[element[2]])
    return firmware_list


def grab_outer_links(html):
    soup = BeautifulSoup(html, "lxml")
    tds = soup.find_all("td", class_="phoneListItem")
    links = []
    for td in tds:
        links_info = [int(int(td.find("small", class_="hidden").text.strip().split(" ")[0]) / ITEMS_PER_PAGE) + 1,
                      HOST + td.find("a").get("href")]
        links.append(links_info)
    paged_links = []
    for link_aux in links:
        for i in range(0, link_aux[0]):
            paged_links.append(link_aux[1] + PAGE_AUX_PART + str(i + 1))
    return paged_links


def grab_inner_links(paged_links):
    link_info = []
    count_all = 1
    for link in paged_links:
        soup = BeautifulSoup(get_raw_html(link), "lxml")
        tds = soup.find_all("td", class_="phoneListItem")
        count_group = FILE_LINK
        data = []
        for td in tds:
            if count_group is FILE_LINK:
                data.append(count_all)
                data.append("Site name: " + td.text)
                data.append(HOST + td.find("a").get("href"))
            elif count_group is FILE_PHONE:
                data.append(td.text)
            elif count_group is FILE_DATE:
                data.append(td.text)
            elif count_group is FILE_SIZE:
                data.append(HOST + td.find("a").get("href"))
                data.append(td.find("small", class_="hidden").text)
                data.append(td.find_all("small")[1].text.split(" ")[0])
                data.append(td.find("a").get("href").split("id=")[1])
            count_group += 1
            if count_group > FILE_SIZE:
                count_group = FILE_LINK
                link_info.append(data)
                count_all += 1
                data = []
    return link_info


def grab_descriptions(firmware_links):
    with Pool(THREADS_COUNT) as p:
        total_links = p.map(gathering_description, firmware_links)
    return total_links


def gathering_description(firmware_link):
    soup = BeautifulSoup(get_raw_html(firmware_link[2]), "lxml")
    section = soup.find_all("td", class_="listRightTD")[1].text
    desc = "".join([str(x) for x in soup.find("td", class_="listLeftTD j").contents])
    firmware_link.insert(2, section)
    firmware_link.append(desc)
    return firmware_link


def write_csv(filename, data):
    with open(filename, "a") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def remove_files():
    print("==> Deleting *.cvs files...")
    try:
        os.remove(FIRMWARES_FILE)
        os.remove(SOFTWARES_FILE)
        os.remove(ARTWORKS_FILE)
    except Exception as exp:
        pass


def main():
    start = datetime.now()
    print("=> Started on: " + str(start))

    remove_files()

    parse_firmwares(HOST + "/firmware/")
    # parse_softwares(HOST + "/soft/")
    # parse_artworks(HOST + "/themes/")

    end = datetime.now()
    print("=> Parsed in: " + str(end - start))
    exit(0)


if __name__ == '__main__':
    main()
