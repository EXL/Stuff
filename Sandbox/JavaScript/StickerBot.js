var TelegramBot = require('node-telegram-bot-api');

var token = '71419188:AAEJpctHcjmba7t5B8Zy5WyYyQHvrZkAv7I';
var botOptions = {
    polling: true
};
var bot = new TelegramBot(token, botOptions);

var stickersList = [
    'BQADAgADfgADEag0Bb5mxH0gvtktAg',
    'BQADAgADowADEag0BQs_xQSkcIFKAg',
    'BQADAgAD1wADEag0BTEYGb09JERjAg',
    'BQADAgAD5wADEag0BZAwDWvpwGrtAg',
    'BQADAgADxQADEag0BRBpCE1JOT4sAg',
    'BQADAgADwwADEag0BbGlUZ12nxZ8Ag',
    'BQADAgADvwADEag0Bf5nBjEjQyUYAg',
    'BQADAgADyQADEag0BYauZXVnHFqOAg'
];

bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

bot.on('sticker', function(msg)
{
    var messageChatId = msg.chat.id;
    var messageStickerId = msg.sticker.file_id;
    var messageDate = msg.date;
    var messageUsr = msg.from.username;

    sendStickerByBot(messageChatId, stickersList[getRandomInt(0, stickersList.length)]);

    console.log(msg);
});

function getRandomInt(aMin, aMax)
{
    return Math.floor(Math.random() * (aMax - aMin + 1)) + aMin;
}

function sendStickerByBot(aChatId, aStickerId)
{
    bot.sendSticker(aChatId, aStickerId, { caption: 'I\'m a cute bot!' });
}
