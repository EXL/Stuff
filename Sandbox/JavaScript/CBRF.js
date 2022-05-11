var TelegramBot = require('node-telegram-bot-api');
var http = require('http');

var token = '131721696:AAHXLEFi10kTvFxFfcGHyGIsqnB6yobW77A';
var botOptions = {
    polling: true
};

var bot = new TelegramBot(token, botOptions);

var options = {
    host: "www.cbr.ru",
    port: 80,
    path: "/scripts/XML_daily.asp?"
};

var content = "";

bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

bot.on('text', function(msg)
{
    var messageChatId = msg.chat.id;
    var messageText = msg.text;
    var messageDate = msg.date;
    var messageUser = msg.from.username;

    if (messageText.indexOf('/currency') === 0) {
        updateGlobalCurrencyList(messageChatId);
    }
});

function sendMessageByBot(aChatId, aMessage)
{
    bot.sendMessage(aChatId, aMessage, { caption: 'I\'m a cute bot!' });
}

function updateGlobalCurrencyList(aMessageChatId)
{
    var req = http.request(options, function(res) {
        res.setEncoding("utf8");
        res.on("data", function(chunk) {
            content += chunk;
        });
        res.on("end", function() {
            sendMessageByBot(aMessageChatId, shittyParseXML(content));
        });
    });
    req.end();
}

function generateBotAnswer(aCurrencyList)
{
    var currencyTable = 'CURRENCY:\n';
    currencyTable += '1 USD = ' + aCurrencyList.USD + ' ' + 'RUB' + ';\n';
    currencyTable += '1 EUR = ' + aCurrencyList.EUR + ' ' + 'RUB' + ';\n';
    currencyTable += '1 UAH = ' + aCurrencyList.UAH + ' ' + 'RUB' + ';\n';
    currencyTable += '1 KZT = ' + aCurrencyList.KZT + ' ' + 'RUB' + ';\n';
    currencyTable += '1 BYR = ' + aCurrencyList.BYR + ' ' + 'RUB' + ';\n';
    currencyTable += '1 GBP = ' + aCurrencyList.GBP + ' ' + 'RUB' + '.';
    return currencyTable;
}

function shittyParseXML(aAllXml)
{
    var currencyList = {
        'USD': 0.0,
        'EUR': 0.0,
        'UAH': 0.0,
        'KZT': 0.0,
        'BYR': 0.0,
        'GBP': 0.0
    };

    currencyList.USD = getCurrentValue('USD', aAllXml);
    currencyList.EUR = getCurrentValue('EUR', aAllXml);
    currencyList.UAH = getCurrentValue('UAH', aAllXml);
    currencyList.KZT = getCurrentValue('KZT', aAllXml);
    currencyList.BYR = getCurrentValue('BYR', aAllXml);
    currencyList.GBP = getCurrentValue('GBP', aAllXml);

    return generateBotAnswer(currencyList);
}

function getCurrentValue(aCurrency, aString)
{
    var nominal = parseFloat(replaceCommasByDots(getStringBelow(aString.indexOf(aCurrency), 1, aString)));
    var value = parseFloat(replaceCommasByDots(getStringBelow(aString.indexOf(aCurrency), 3, aString)));

    return (value / nominal).toFixed(4);
}

function removeTags(aString)
{
    return aString.replace(/(<([^>]+)>)/ig, '');
}

function getStringBelow(aStart, aBelow, aString)
{
    var textSize = aString.length;
    var countOfLineEndings = 0;
    var getLineWith = 0;

    for (var i = aStart; i < textSize; ++i) {
        if (countOfLineEndings === aBelow) {
            getLineWith = i;
            break;
        }
        if (aString[i] === '\n') {
           countOfLineEndings++;
        }
    }

    return getLineFromXml(getLineWith, aString);
}

function replaceCommasByDots(aString)
{
    return aString.replace(',', '.');
}

function getLineFromXml(aStart, aString)
{
    var textSize = aString.length;
    var targetString = '';
    for (var i = aStart; i < textSize; ++i) {
        if (aString[i] === '\n') {
            break;
        }
        targetString += aString[i];
    }

    return removeTags(targetString.trim());
}
