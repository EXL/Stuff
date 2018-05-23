// Telegram Bot for crawling #news
// License: MIT
// (c) EXL, 11-APR-2018, email: exlmotodev@gmail.com

// Fix deprecated warnings
process.env["NTBA_FIX_319"] = 1;
process.env["NTBA_FIX_350"] = 1;

var MySql = require("mysql");
var TelegramBot = require('node-telegram-bot-api');

var TgUtils = require('./TgUtils.js');

var Bot = new TelegramBot(TgUtils.settings.token, { polling: true });
var connectedToDb = false;
var Conn;

function main() {
    console.log("++++= Started at: " + Date());
    toMotoFanCMS_DB();
}

function toMotoFanCMS_DB() {
    var con = MySql.createConnection({
        host:       TgUtils.settings.host,
        user:       TgUtils.settings.user,
        password:   TgUtils.settings.pass,
        database:   TgUtils.settings.db_wp,
        charset:    TgUtils.settings.charset
    });

    con.connect(function(err) {
        if (err) {
            throw err;
        }
        console.log('MotoFan CMS DB: Connected!');
        TgUtils.runSqlQuery(con, 'CREATE TABLE IF NOT EXISTS tg_news (id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, ' +
            'date TEXT, post TEXT, user TEXT, chatId TEXT, msgId TEXT) ' +
            'CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;');
        connectedToDb = true;
        Conn = con;
    });
}

main();

Bot.on('text', function(msg) {
    var messageChatId = msg.chat.id;
    var messageText = msg.text;
    var messageDate = msg.date;
    var messsageId = msg.message_id;
    var messageUserName = msg.from.username;

    // console.log(msg);

    if (msg.forward_date) { // Skip All Forward Messages
        return;
    }

    // News Tag
    if (messageText.indexOf(TgUtils.settings.newsTag) >= 0) {
        if (TgUtils.userIsAdmin(messageUserName) || TgUtils.settings.skipAdmins) {
            if (messageText.length < 400) {
                if (connectedToDb) {
                    insertIntoDbTable(Conn, messageDate, normalizeMessage(messageText), messageUserName, messageChatId, messsageId);
                    if (TgUtils.settings.showAnswer) {
                        sendMessageByBot(messageChatId, TgUtils.getLocaleString('wrt'), messsageId);
                    }
                } else {
                    sendMessageByBot(messageChatId, TgUtils.getLocaleString('dbErr'), messsageId);
                }
            } else {
                sendMessageByBot(messageChatId, TgUtils.getLocaleString('lenErr'), messsageId);
            }
        } else {
            sendMessageByBot(messageChatId, TgUtils.getLocaleString('admErr'), messsageId);
        }
    }

    // List Command
    else if (messageText.indexOf(TgUtils.settings.listCmd) === 0) {
        if (TgUtils.userIsAdmin(messageUserName) || TgUtils.settings.skipAdmins) {
            // https://stackoverflow.com/a/12125925
            Conn.query('SELECT * FROM (SELECT * FROM tg_news ORDER BY id DESC LIMIT ' + TgUtils.settings.limit +
                ') sub ORDER BY id ASC', function (err, result) {
                if (err) {
                    sendMessageByBot(messageChatId, err.toString(), messsageId);
                } else if (!TgUtils.isEmpty(result)) {
                    sendMessageByBot(messageChatId, getLatestDataBaseStrings(result), messsageId);
                } else {
                    sendMessageByBot(messageChatId, TgUtils.getLocaleString('emtErr'), messsageId);
                }
            });
        } else {
            sendMessageByBot(messageChatId, TgUtils.getLocaleString('admErr'), messsageId);
        }
    }

    // Delete Command
    else if (messageText.indexOf(TgUtils.settings.deleteCmd) === 0) {
        if (TgUtils.userIsAdmin(messageUserName) || TgUtils.settings.skipAdmins) {
            var chunksMsg = messageText.split(' ');
            if (chunksMsg.length === 2) {
                var delArg = parseInt(chunksMsg[1]);
                if (delArg) {
                    Conn.query('DELETE FROM tg_news WHERE id = ' + delArg, function (err, result) {
                        if (err) {
                            sendMessageByBot(messageChatId, err.toString(), messsageId);
                        } else if (!TgUtils.isEmpty(result)) {
                            sendMessageByBot(messageChatId, TgUtils.getLocaleString('delOk') + delArg + '.', messsageId);
                        } else {
                            sendMessageByBot(messageChatId, TgUtils.getLocaleString('emtErr'), messsageId);
                        }
                    });
                } else {
                    sendMessageByBot(messageChatId, TgUtils.getLocaleString('argErr'), messsageId);
                }
            } else {
                sendMessageByBot(messageChatId, TgUtils.getLocaleString('argErr'), messsageId);
            }
        } else {
            sendMessageByBot(messageChatId, TgUtils.getLocaleString('admErr'), messsageId);
        }
    }
});

function getLatestDataBaseStrings(aResult, aEnd) {
    var resStr = '';
    aResult.forEach(function (el) {
        resStr += el.id + ': ' + el.post + '\n';
    });
    return '```\n' + resStr + '\n```';
}

function normalizeMessage(aMessage) {
    var normalMessage = aMessage.replace('#news', '');
    normalMessage = normalMessage.trim();
    if (TgUtils.isEmpty(aMessage)) {
        normalMessage = TgUtils.getLocaleString('emtErr');
    } else {
        // Remove all html tags and 'danger' words
        normalMessage = normalMessage.replace(/(<([^>]+)>)/ig, '');
        normalMessage = normalMessage.replace(/DROP /ig, '');
        normalMessage = normalMessage.replace(/DELETE /ig, '');
        normalMessage = normalMessage.replace(/TRUNCATE /ig, '');
        normalMessage = normalMessage.replace(/SELECT /ig, '');
    }
    return normalMessage;
}

function insertIntoDbTable(aConn, aDate, aPost, aUser, aChatId, aId) {
    TgUtils.runSqlQuery(aConn, "INSERT INTO tg_news (date, post, user, chatId, msgId) VALUES ('" +
        TgUtils.escSqlString(aDate.toString()) + "', '" +
        TgUtils.escSqlString(aPost.toString()) + "', '" +
        TgUtils.escSqlString(aUser.toString()) + "', '" +
        TgUtils.escSqlString(aChatId.toString()) + "', '" +
        TgUtils.escSqlString(aId.toString()) + "');");
}

function sendMessageByBot(aChatId, aMessage, aReplyId) {
    Bot.sendMessage(aChatId, aMessage, {
        disable_web_page_preview: true,
        disable_notification: true,
        reply_to_message_id: aReplyId,
        parse_mode: 'markdown'
    });
}

// https://stackoverflow.com/a/14032965
function exitHandler() {
    Conn.end();
    TgUtils.toExit();
}

process.on('exit', exitHandler.bind());
process.on('SIGINT', exitHandler.bind());
process.on('SIGUSR1', exitHandler.bind());
process.on('SIGUSR2', exitHandler.bind());
process.on('uncaughtException', exitHandler.bind());
process.stdin.resume();
