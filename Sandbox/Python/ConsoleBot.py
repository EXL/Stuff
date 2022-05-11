#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals
from twx.botapi import TelegramBot
from subprocess import Popen, PIPE, STDOUT

import traceback

class ConsoleBot(object):
    token = '71419188:AAEJpctHcjmba7t5B8Zy5WyYyQHvrZkAv7I'

    def __init__(self):
        self.bot = TelegramBot(self.token)
        self.bot.get_me()
        last_updates = self.bot.get_updates(offset=0).wait()
        try:
            self.last_update_id = list(last_updates)[-1].update_id
        except IndexError:
            self.last_update_id = None
        print('last update id: {0}'.format(self.last_update_id))

    def process_message(self, message):
        text = message.message.text
        chat = message.message.chat
        cmd = text.strip()
        answer = ''
        try:
            p = Popen(cmd.split(), stdin=PIPE, stdout=PIPE, stderr=STDOUT)
            stdouterr, err = p.communicate(b"input data that is passed to subprocess' stdin")
            answer = '```' + stdouterr.decode("utf-8") + '```'
        except Exception as ex:
            answer = traceback.format_exc()
        finally:
            self.bot.send_message(chat.id, answer)

    def run(self):
        print('Main loop started')
        while True:
            updates = self.bot.get_updates(offset=self.last_update_id).wait()
            try:
                for update in updates:
                    if int(update.update_id) > self.last_update_id:
                        self.last_update_id = update.update_id
                        self.process_message(update)
            except Exception as ex:
                print(traceback.format_exc())

if __name__ == '__main__':
    try:
        ConsoleBot().run()
    except KeyboardInterrupt:
        print('Exiting...')
