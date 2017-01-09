#!/usr/bin/python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals
from twx.botapi import TelegramBot

import traceback

class DigestBot(object):
    token = 'WRITE_YOUR_TOKEN_HERE'
    stack_list = []
    admin = 'exlmoto'

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
        text = text.strip()
        digest_tag = '#digest'
        print('Got message: \33[0;32m{0}\33[0m from chat: {1}'.format(text, chat))
        try:
            if text == '/digest':
                bot_answer = 'There is your digest:\n'
                try:
                    for struct in self.stack_list:
                        if struct['chat_id'] == chat.id:
                            bot_answer += struct['chat_message']
                            bot_answer += '\n'
                    bot_answer = bot_answer[:-1]
                    bot_answer += '.'
                    self.bot.send_message(chat.id, bot_answer)
                except Exception:
                    self.bot.send_message(chat.id, 'Unknow error. Sorry.')
            if text == '/stackView':
                list_answer = 'There is my stack list:\n'
                try:
                    if message.message.sender.username == self.admin:
                        for (index, d) in enumerate(self.stack_list):
                            list_answer += str(index + 1)
                            list_answer += ' ' + str(d['chat_id'])
                            list_answer +=' ' + d['chat_message']
                            list_answer += '\n'
                        list_answer = list_answer[:-1]
                        self.bot.send_message(chat.id, list_answer)
                    else:
                        raise Exception('You do not access for this function.')
                except Exception as ex_acc:
                    answer = ex_acc.args
                    self.bot.send_message(chat.id, answer)
            if digest_tag in text:
                try:
                    text = text.replace(digest_tag, '')
                    text = text.strip()
                    struct = { 'chat_id': chat.id, 'chat_message': text }
                    self.stack_list.append(struct.copy())
                    self.bot.send_message(chat.id, 'Done. I append your digest-message in my stack list.')
                except Exception:
                    self.bot.send_message(chat.id, 'There is error. Sorry.')
        except Exception:
            pass

    def run(self):
        print('Main loop started')
        while True:
            updates = self.bot.get_updates(offset=self.last_update_id).wait()
            try:
                for update in updates:
                    if int(update.update_id) > int(self.last_update_id):
                        self.last_update_id = update.update_id
                        self.process_message(update)
            except Exception as ex:
                print(traceback.format_exc())

if __name__ == '__main__':
    try:
        DigestBot().run()
    except KeyboardInterrupt:
        print('Exiting...')
