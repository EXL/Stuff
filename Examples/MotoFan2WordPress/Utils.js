// Utility functions and settings library
// (c) EXL, 03-MAR-2018, email: exlmotodev@gmail.com

module.exports = {
    settings: {
        url:            'http://motofan.ru/',
        url_img:        'http://motofan.ru',
        host:           'localhost',
        user:           'root',
        pass:           'hidden',
        db_mf:          'admin_motofan',
        db_wp:          'mydb',
        charset:        'utf8mb4',
        db_file:        'IntenseDebate.xml',
        only_posts:     false,
        timeout:        12000,
        end_post:       1838,
        end_cat:        10,
        offset:         1000
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

    hackDataBaseOffset: function(aNum) {
        var n = parseInt(aNum);
        if (n <= module.exports.settings.end_post) {
            return n;
        } else {
            return n + module.exports.settings.offset;
        }
    }
};
