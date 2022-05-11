// WeatherBot.js

var TelegramBot = require('node-telegram-bot-api');
var request = require('request');
var cheerio = require('cheerio');

var token = '71419188:AAEJpctHcjmba7t5B8Zy5WyYyQHvrZkAv7I';
var botOptions = {
    polling: true
};

var bot = new TelegramBot(token, botOptions);

var timerId = setInterval(function() {
    weatherFunction(false);
}, 10 * 1000); // Once every 10 sec

var weatherStack = [];

bot.getMe().then(function(me) {
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
    console.log('Chat id: ' + bot.getChat("-1001409101770"));
});

bot.on('text', function(msg) {
    var messageText = msg.text;
    var messageChatId = msg.chat.id;
    if (messageText.indexOf('/weather') === 0) {
        if (weatherStack.length > 0) {
            console.log('Stack Not Empty, size: ' + weatherStack.length);
            bot.sendMessage(messageChatId, weatherStack[weatherStack.length - 1]);
        } else {
            console.log('Stack Empty');
            weatherFunction(messageChatId);
        }
    }
});

function weatherFunction(messageChatId) {
    var url = "http://www.wunderground.com/cgi-bin/findweather/getForecast?&query=Saransk";
    request(url, function (error, response, body) {
        if (!error) {
            var $ = cheerio.load(body),
                temperature = $("[data-variable='windchill'] .wx-value").html(),
                bufer = "Температура воздуха (с учетом ветра)  " + temperature + "\xB0C";
            if (weatherStack.length > 10) { console.log('Too long stack, drop it!'); weatherStack = []; }
            weatherStack.push(bufer);
            if (messageChatId) {
                bot.sendMessage(messageChatId, bufer);
            }
            console.log('Weather Stack Updated! Size: ' + weatherStack.length);
        }
    });
}

