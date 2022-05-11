var TelegramBot = require('node-telegram-bot-api');

var token = '260383185:AAGsZqBsXY_-yOoYrRQwnCqfUku6i_u_wSE';
var botOptions = {
    polling: true
};

var bot = new TelegramBot(token, botOptions);

var f1 = [ 'траурный', 'плюшевый', 'бешеный', 'памятный', 'трепетный', 'базовый', 'скошенный', 'преданный', 'ласковый', 'пойманный', 'радужный', 'огненный', 'радостный', 'тензорный', 'шёлковый', 'пепельный', 'ламповый', 'жареный', 'загнанный' ];
var f2 = [ 'зайчик', 'Верник', 'глобус', 'ветер', 'щавель', 'песик', 'копчик', 'пандыш', 'стольник', 'мальчик', 'дольщик', 'Игорь', 'невод', 'егерь', 'пончик', 'лобсгср', 'жемчуг', 'кольщик', 'йогурт', 'овод' ];
var f3 = [ 'стеклянного', 'ванильного', 'резонного', 'широкого', 'дешёвого', 'горбатого', 'собачьего', 'исконного', 'волшебного', 'картонного', 'лохматого', 'арбузного', 'огромного', 'запойного', 'великого', 'бараньего', 'ванлаального', 'едрёного', 'парадного', 'укромного' ];
var f4 = [ 'глаза', 'плова', 'Пельша', 'мира', 'деда', 'жира', 'мема', 'ада', 'бура', 'жала', 'нёба', 'гунна', 'хлама', 'шума', 'воза', 'сала', 'фена', 'Зала', 'рака' ];

bot.on('text', function(msg) {
    var messageChatId = msg.chat.id;
    var messageText = msg.text;

    if (messageText.indexOf('/sing') === 0) {
        sendMessageByBot(messageChatId, sing());
    }
});

function sendMessageByBot(aChatId, aMessage) {
    bot.sendMessage(aChatId, aMessage, { caption: 'I\'m a cute bot!' });
}

function getRandomInt(aMin, aMax) {
    return Math.floor(Math.random() * (aMax - aMin + 1)) + aMin;
}

function capitalizeFirstLetter(aString) {
    return aString[0].toUpperCase() + aString.substr(1);
}

function sing() {
    var stringAnswer = '';
    for (var i = 1; i <= 40; ++i) {
        stringAnswer += capitalizeFirstLetter(f1[getRandomInt(0, f1.length - 1)]) + ' ';
        stringAnswer += f2[getRandomInt(0, f2.length - 1)] + ' ';
        stringAnswer += f3[getRandomInt(0, f3.length - 1)] + ' ';
        stringAnswer += f4[getRandomInt(0, f4.length - 1)] + '.\n';
        if (i % 10 == 0 && i != 40) {
            stringAnswer += '\n';
        }
    }
    return stringAnswer;
}
