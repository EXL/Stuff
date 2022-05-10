#!/usr/bin/env python3

# MotoFanDbShrinker
#  Utility for shrink MotoFan DB and drop outdated information.
#
#  Written by EXL, 19-Apr-2019
#
# Install dependencies:
#  $ sudo pip3 install mysql-connector
#
# Documentation:
# 1. https://dev.mysql.com/doc/connector-python/en/connector-python-example-ddl.html
# 2. https://dev.mysql.com/doc/connector-python/en/connector-python-example-ddl.html
# 3. https://dev.mysql.com/doc/connector-python/en/connector-python-example-cursor-select.html
# 4. https://dev.mysql.com/doc/connector-python/en/connector-python-example-cursor-transaction.html

import mysql.connector
from mysql.connector import errorcode

DATABASE_OLD = "motofan"
DATABASE_NEW = "motofan_files"

DB_CONFIG = {
    "user": "username",
    "password": "*********",
    "host": "localhost"
}

TABLES = {
    "phones": (
        "CREATE TABLE `phones`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `title` varchar(255) NOT NULL,"
        "     PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "firmware": (
        "CREATE TABLE `firmware`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `cat_id` mediumint(8) unsigned NOT NULL,"
        "    `phone_id` mediumint(8) unsigned NOT NULL,"
        "    `title` varchar(100) NOT NULL,"
        "    `description` text,"
        "    `filename` varchar(255) NOT NULL,"
        "    `filesize` int(11) unsigned,"
        "    `date` datetime NOT NULL,"
        "    `views` mediumint(8) unsigned,"
        "    `poster` varchar(32),"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "firmware_cat": (
        "CREATE TABLE `firmware_cat`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `title` char(50) NOT NULL,"
        "    `image` char(50) NOT NULL,"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "soft": (
        "CREATE TABLE `soft`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `cat_id` mediumint(8) unsigned NOT NULL,"
        "    `phone_id` varchar(255) NOT NULL,"
        "    `additional_id` mediumint(8) unsigned,"
        "    `title` varchar(100) NOT NULL,"
        "    `description` text,"
        "    `image` varchar(255),"
        "    `filename` varchar(255) NOT NULL,"
        "    `filesize` int(11) unsigned,"
        "    `date` datetime NOT NULL,"
        "    `views` mediumint(8) unsigned,"
        "    `poster` varchar(32),"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "soft_cat": (
        "CREATE TABLE `soft_cat`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `title` char(50) NOT NULL,"
        "    `image` char(50) NOT NULL,"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "themes": (
        "CREATE TABLE `themes`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `cat_id` mediumint(8) unsigned NOT NULL,"
        "    `phone_id` varchar(255) NOT NULL,"
        "    `title` varchar(100) NOT NULL,"
        "    `description` text,"
        "    `image` varchar(255),"
        "    `filename` varchar(255) NOT NULL,"
        "    `filesize` int(11) unsigned,"
        "    `date` datetime NOT NULL,"
        "    `views` mediumint(8) unsigned,"
        "    `poster` varchar(32),"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    ),
    "themes_cat": (
        "CREATE TABLE `themes_cat`("
        "    `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,"
        "    `title` char(50) NOT NULL,"
        "    `image` char(50) NOT NULL,"
        "    PRIMARY KEY(`id`)"
        ") CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ENGINE=MyISAM"
    )
}

RENAMES = ["phones", "firmwares", "firmwares_cat", "files", "files_cat", "arts", "arts_cat"]


class DataBaseWorker:
    def rename_tables(self):
        self.use_database(DATABASE_NEW)
        i = 0
        for table in TABLES:
            try:
                self.cursor.execute("ALTER TABLE " + table + " RENAME TO " + RENAMES[i])
            except mysql.connector.Error as error:
                print("Error renaming table '{}' to '{}': {}.".format(table, RENAMES[i], error))
            else:
                print("Table '{}' renamed to '{}'.".format(table, RENAMES[i]))
            i = i + 1

    def insert_general_data(self, query, insert):
        data = []
        self.use_database(DATABASE_OLD)
        self.cursor.execute(query)
        for tup in self.cursor:
            data.append(tup)
        data.sort(key=lambda x: x[0])
        self.use_database(DATABASE_NEW)
        for tup in data:
            print("Commit '{}' record to '{}' table.".format(tup[0], insert.split(" ")[2]))
            self.cursor.execute(insert, tup)
            self.connection.commit()

    def read_and_write_data(self):
        for table in TABLES:
            if table == "phones":
                self.insert_general_data("SELECT id, model FROM " + table,
                                         "INSERT INTO " + table + " (id, title) VALUES (%s, %s)")
            elif table == "firmware_cat" or table == "soft_cat" or table == "themes_cat":
                self.insert_general_data("SELECT id, title, image FROM " + table,
                                         "INSERT INTO " + table + " (id, title, image) VALUES (%s, %s, %s)")
            elif table == "firmware":
                self.insert_general_data(
                    "SELECT id, cat_id, phone_id, title, textbody, fname, fsize, postdate, views, poster FROM " + table,
                    "INSERT INTO " + table + " (id, cat_id, phone_id, title, description, filename, filesize, date, "
                                             "views, poster) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)")
            elif table == "soft":
                self.insert_general_data(
                    "SELECT id, cat_id, phone_id, patch_for, title, textbody, scrshot, fname, fsize, postdate, views, "
                    "poster FROM " + table,
                    "INSERT INTO " + table + " (id, cat_id, phone_id, additional_id, title, description, image, "
                                             "filename, filesize, date, views, poster) VALUES (%s, %s, %s, %s, %s, "
                                             "%s, %s, %s, %s, %s, %s, %s)")
            elif table == "themes":
                self.insert_general_data(
                    "SELECT id, cat_id, phone_id, title, textbody, scrshot, fname, fsize, postdate, views, "
                    "poster FROM " + table,
                    "INSERT INTO " + table + " (id, cat_id, phone_id, title, description, image, "
                                             "filename, filesize, date, views, poster) VALUES (%s, %s, %s, %s, %s, "
                                             "%s, %s, %s, %s, %s, %s)")

    def create_tables(self):
        self.use_database(DATABASE_NEW)
        for table in TABLES:
            table_scheme = TABLES[table]
            try:
                print("Creating table '{}': ".format(table), end='')
                self.cursor.execute(table_scheme)
            except mysql.connector.Error as error:
                if error.errno == errorcode.ER_TABLE_EXISTS_ERROR:
                    print("already exists.")
                else:
                    print(error.msg)
            else:
                print("OK")

    def use_database(self, database):
        try:
            self.cursor.execute("USE {}".format(database))
        except mysql.connector.Error as error:
            print("Failed to choose DataBase '{}': {}".format(database, error))
        else:
            print("DataBase '{}' is chosen.".format(database))

    def drop_database(self, database):
        try:
            self.cursor.execute("DROP DATABASE IF EXISTS {}".format(database))
        except mysql.connector.Error as error:
            print("Failed to drop DataBase '{}': {} ".format(database, error))
            return
        print("DataBase '{}' dropped.".format(database))

    def create_database(self):
        try:
            self.cursor.execute("CREATE DATABASE IF NOT EXISTS {} CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci"
                                .format(DATABASE_NEW))
        except mysql.connector.Error as error:
            print("Failed creating DataBase: {}".format(error))
            exit(1)
        else:
            print("DataBase '{}' is created.".format(DATABASE_NEW))

    @staticmethod
    def connect():
        try:
            connection = mysql.connector.connect(**DB_CONFIG)
        except mysql.connector.Error as error:
            if error.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("Something is wrong with your username or password.")
            elif error.errno == errorcode.ER_BAD_DB_ERROR:
                print("DataBase does not exist.")
            else:
                print(error)
            exit(1)
        else:
            print("Connected to DataBase.")
            return connection

    def __init__(self):
        self.connection = self.connect()
        self.cursor = self.connection.cursor()

    def __del__(self):
        self.cursor.close()
        self.connection.close()


def main():
    worker = DataBaseWorker()
    worker.drop_database(DATABASE_NEW)
    worker.create_database()
    worker.create_tables()
    worker.read_and_write_data()
    worker.rename_tables()


if __name__ == "__main__":
    main()
