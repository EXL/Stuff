#!/usr/bin/env python3
# -*- coding: utf-8 -*-

NAME = 0
MODE = 1
MLST = 2
ONLN = 3
COMM = 4

MAPS = []

class MapInstance:
	def __init__(self, name, mode, in_maplist, online, comment):
		self.name = name
		self.mode = mode
		self.in_maplist = in_maplist
		self.online = online
		self.comment = comment
		self.previews = self.__generate_previews()

	def __generate_previews(self):
		previews = ''
		for i in range(3):
			previews += '<a href="images/{}000{}.jpg" title="Map Screenshot {}" target="_blank"><img src="images/thumbs/{}000{}.jpg" alt="Map Screenshot {}" style="border: 1px solid darkgray;"></a> '.format(self.name, i, self.name, self.name, i, self.name)
		return previews

	def get_name(self):
		return '<h2>' + self.name + '</h2>'

	def get_mode(self):
		return self.mode

	def get_in_maplist(self):
		return '<img src="images/thumbs/Yes.png" title="Будет добавлена в CTF-маплист" alt="Yes" style="border: 1px solid darkgray;">' if self.in_maplist == 'Yes' else '<img src="images/thumbs/No.png" title="Не будет добавлена в CTF-маплист" alt="No" style="border: 1px solid darkgray;">'

	def __get_online_color(self):
		if self.online == '5':
			return '<font color="green">Отличный</font>'
		elif self.online == '4':
			return '<font color="lightgreen">Хороший</font>'
		elif self.online == '3':
			return '<font color="orange">Посредственный</font>'
		else:
			return '<font color="#FA8072">Плохой</font>'

	def get_online(self):
		return '<br><br><strong>Online: ' + self.__get_online_color() + '</strong>'

	def get_comment(self):
		return '<br><strong>Comment:</strong> ' + self.comment

	def get_previews(self):
		return self.previews

def generate_map_list(file_name):
	with open(file_name, 'w', encoding='utf8') as file:
		for map in MAPS:
			if map.in_maplist == 'Yes':
				file.write(map.name + '\n')

def write_map_info(file, map):
	file.write(map.get_name())
	file.write(map.get_previews())
	file.write(map.get_in_maplist())
	file.write(map.get_online())
	file.write(map.get_comment())
	file.write('<hr style="border: 1px solid darkgray; margin-top: 25px;">')

def generate_html(file_name):
	discarded_maps = []
	other_maps = []
	with open(file_name, 'w', encoding='utf8') as file:
		file.write('<!DOCTYPE html><html><head><meta charset="utf-8"><title>Half-Life Maps</title><style> ::selection { background: black; color: #fff; text-shadow: none; } ::-moz-selection { background: black; color: #fff; text-shadow: none; } body{ background-color: #2E3436; }</style></head><body><font color="#babdb6">')
		file.write('<h1>CTF-карты для Half-Life</h1>')
		file.write('<hr style="border: 1px solid darkgray; margin-top: 25px;">')
		for map in MAPS:
			if map.get_mode() == 'ctf':
				if map.in_maplist == 'Yes':
					write_map_info(file, map)
				else:
					discarded_maps.append(map)
			else:
				other_maps.append(map)
		for map in discarded_maps:
			write_map_info(file, map)
		file.write('<h1>DM-карты для Half-Life</h1>')
		file.write('<hr style="border: 1px solid darkgray; margin-top: 25px;">')
		for map in other_maps:
			write_map_info(file, map)
		file.write('</font></body></html>')

def decode_line(content):
	for string in content:
		if string.startswith('#'):
			continue
		tokens = string.split('|')
		map = MapInstance(tokens[NAME] if len(tokens) > NAME else '',
		                  tokens[MODE] if len(tokens) > MODE else '',
						  tokens[MLST] if len(tokens) > MLST else False,
						  tokens[ONLN] if len(tokens) > ONLN else '',
						  tokens[COMM] if len(tokens) > COMM else '')
		MAPS.append(map)

def parse_file(file_name):
	with open(file_name, encoding='utf8') as file:
		content = file.readlines()
	decode_line([string.strip() for string in content])

if __name__ == '__main__':
	parse_file('maplist_desc.txt')
	generate_html('index.html')
	generate_map_list('maplist.txt')
