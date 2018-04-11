// Utility functions and settings library
// License: MIT
// (c) EXL, 11-APR-2018, email: exlmotodev@gmail.com

module.exports = {
    settings: {
        host:           'localhost',
        token:          'hidden',
        user:           'hidden',
        pass:           'hidden',
        db_wp:          'hidden',
        charset:        'utf8mb4',
        admins:         ['exlmoto', 'ZorgeR'],
        skipAdmins:     false,
        limit:          8,
        newsTag:        '#news',
        deleteCmd:      '/rem',
        listCmd:        '/list',
        lang:           'ru',
        showAnswer:     true
    },

    // https://stackoverflow.com/a/7760578
    escSqlString: function(str) {
        return (str) ? str.replace(/[\0\x08\x09\x1a\n\r"'\\%]/g, function(char) {
            switch (char) {
                case "%":
                    return char;
                case "\0":
                    return "\\0";
                case "\x08":
                    return "\\b";
                case "\x09":
                    return "\\t";
                case "\x1a":
                    return "\\z";
                case "\n":
                    return "\\n";
                case "\r":
                    return "\\r";
                case "\"":
                case "'":
                case "\\":
                    return "\\"+char; // prepends a backslash to backslash, percent,
                    // and double/single quotes
            }
        }) : "";
    },

    toExit: function() {
        console.log('++++= Ended at: ' + Date());
        process.exit(0);
    },

    runSqlQuery: function(aCon, aQuery) {
        return new Promise(function (resolve) {
            aCon.query(aQuery, function (err, result) {
                if (err) {
                    throw err;
                }
                if (result) {
                    resolve(aCon);
                }
            });
        });
    },

    userIsAdmin: function(aUserName) {
        for (var i = 0; i < module.exports.settings.admins.length; ++i) {
            if (aUserName === module.exports.settings.admins[i]) {
                return true;
            }
        }
        return false;
    },

    getLocaleString: function(aString) {
        var langRu = {
            'dbErr': 'Ошибка соединения с БД!',
            'lenErr': 'Слишком длинное сообщение, нельзя такое добавлять в БД. Лимит -- 400 символов.',
            'admErr': 'Вы не являетесь администратором этого бота.',
            'wrt': 'Запись добавлена на сайт MotoFan.Ru!',
            'emtErr': 'Запись пустая!',
            'argErr': 'Ошибка команды удаления! Используйте следующий синтаксис: `' + module.exports.settings.deleteCmd + ' [число ID]`',
            'delOk': 'Из БД удалена запись под номером: '
        };
        var langEn = {
            'dbErr': 'DataBase connection error!'
        };
        var lang;
        switch (module.exports.settings.lang) {
            default:
            case 'ru':
                lang = langRu;
                break;
            case 'en':
                lang = langEn;
                break;
        }
        return lang[aString];
    },

    hackDataBaseOffset: function(aNum) {
        var n = parseInt(aNum);
        if (n <= module.exports.settings.end_post) {
            return n;
        } else {
            return n + module.exports.settings.offset;
        }
    },

    isEmpty: function(aString) {
        return (!aString || 0 === aString.length);
    }
};
