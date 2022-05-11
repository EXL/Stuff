#!/usr/bin/env python3
from urllib.request import urlopen
from datetime import datetime
from lxml.etree import parse, XMLParser

tree = parse('/home/exl/Downloads/f.xml', XMLParser())

def rnd(value):
    return " " + str(round(float(value)))

def get(query, ctx = tree):
    return ctx.xpath(query)

def time(date_f, date_t):
    f = datetime.strptime(date_f, '%Y-%m-%dT%H:%M:%S')
    t = datetime.strptime(date_t, '%Y-%m-%dT%H:%M:%S')
    return f.strftime('%a') + ' ' + f.strftime('%H:%M') + '-' + t.strftime('%H:%M') + ': '

print(get('string(/weatherdata/location/name)') + ', ' + get('string(/weatherdata/location/country)') + '\n')
for el in get('/weatherdata/forecast/time'):
    print(time(el.attrib['from'], el.attrib['to']) + get('string(symbol/@name)', el))
    print(rnd(get('string(temperature/@value)', el)) + '°C, ' + get('string(humidity/@value)', el) + '%')
    print(rnd(get('string(windSpeed/@mps)', el)) + ' m/s, (' + get('string(windDirection/@code)', el) + ')')
    print(" " + get('string(clouds/@all)', el) + '%, clouds\n\n')
