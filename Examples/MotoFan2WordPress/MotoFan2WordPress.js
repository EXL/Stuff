// Import MotoFan.Ru news to the WordPress site.
// Usage:
//  1. Install all dependencies:
//      $ npm install .
//  2. Check max size of the max_allowed_packet:
//      $ cat /etc/mysql/my.cnf | grep max_allowed_packet
//      max_allowed_packet = 64M
//      max_allowed_packet = 16M
//  3. Patch RedWaves theme.
//  4. Run import Script:
//      $ node MotoFan2WordPress
// License: MIT
// (c) EXL, 02-MAR-2018

const MySql = require("mysql");
const Request = require('sync-request');
const Url = require('url');

const Settings = {
    url:            'http://localhost/',
    host:           'localhost',
    user:           'root',
    pass:           'hidden',
    db_mf:          'admin_motofan',
    db_wp:          'mydb',
    charset:        'utf8mb4',
    timeout:        12000
};

function main() {
    console.log("++++= Started at: " + Date());
    toMotoFanCMS_DB();
}

function toMotoFanCMS_DB() {
    var con = MySql.createConnection({
        host:       Settings.host,
        user:       Settings.user,
        password:   Settings.pass,
        database:   Settings.db_mf,
        charset:    Settings.charset
    });

    con.connect(function(err) {
        if (err) {
            throw err;
        }
        console.log('MotoFan CMS DB: Connected!');
        con.query('SELECT * FROM news', function (err, result, fields) {
            if (err) {
                throw err;
            }
            con.end();
            handleMotoFanDB(result);
        });
    });
}

function formatDateToMySQL(aDate) {
    return aDate.toISOString().replace(/T/, ' ').replace(/\..+/, '');
}

function toExit() {
    console.log("Ended at: " + Date());
    process.exit(0);
}

function getSaveUsername(aUn) {
    return aUn.toLowerCase().replace(/[.,\/#!$%\^&\*;:{}=\-_`~()]/g,"-");
}

function createAuthorsMatrix(aNews) {
    var users = new Map();
    users.set('EXL', { id: '1', un: 'EXL', unn: 'exl', email: 'exl@bk.ru',
                  pass: '$P$BuTtc7RgaVQ5b64N/I/XI4IC2/EMJu/', date: formatDateToMySQL(new Date()) });
    users.set('Zorge.R', { id: '2', un: 'Zorge.R', unn: 'zorge-r', email: 'zorg.rhrd@gmail.com',
                  pass: '$P$BuTtc7RgaVQ5b64N/I/XI4IC2/EMJu/', date: formatDateToMySQL(new Date()) });
    aNews.forEach(function each(el, index, array) {
        if (!users.get(el.author.toLowerCase()) && !users.get(el.author)) {
            users.set(el.author, { id: (users.size + 1) + '', un: el.author, unn: getSaveUsername(el.author),
                      email: getSaveUsername(el.author) + '@noreply.com', pass: '$P$BuTtc7RgaVQ5b64N/I/XI4IC2/EMJu/',
                      date: formatDateToMySQL(new Date())});
        }
    });
    return users;
}

function getCountNewsInTerm(aTerm, aNews) {
    var cnt = 0;
    aNews.forEach(function each(el, index, array) {
        if (el.cat_id == aTerm) {
            cnt++;
        }
    });
    return cnt + '';
}

function createTermsMatrix(aNews) {
    var terms = [];
    terms.push({ count: getCountNewsInTerm('1', aNews), name: 'О Motorola', slug: 'motorola' });
    terms.push({ count: getCountNewsInTerm('2', aNews), name: 'О Сайте', slug: 'news-mf' });
    terms.push({ count: getCountNewsInTerm('3', aNews), name: 'О Форуме', slug: 'news-forum' });
    terms.push({ count: getCountNewsInTerm('4', aNews), name: 'Об Операторах', slug: 'carrier' });
    terms.push({ count: getCountNewsInTerm('5', aNews), name: 'Другие новости', slug: 'other' });
    terms.push({ count: getCountNewsInTerm('6', aNews), name: 'Объявления', slug: 'advert' });
    terms.push({ count: getCountNewsInTerm('7', aNews), name: 'Обзоры', slug: 'review' });
    terms.push({ count: getCountNewsInTerm('8', aNews), name: 'Moto-Россия', slug: 'moto-russia' });
    terms.push({ count: getCountNewsInTerm('9', aNews), name: 'Motorola Solutions', slug: 'solutions' });
    terms.push({ count: getCountNewsInTerm('10', aNews), name: 'Motorola Home', slug: 'home' });
    return terms;
}

function processTermsTaxonomy(aUsers, aNews, aTerms, con) {
    var times = aTerms.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " term taxonomies are stored to the DB.");
            processPosts(aUsers, aNews, con);
            return;
        }
        process.stdout.write("Commit term taxonomy #" + (current+1) + "... ");
        runSqlQuery(con, "INSERT INTO wp_term_taxonomy (term_taxonomy_id, term_id, taxonomy, description, parent, count) VALUES ('" +
                    escSqlString((current+1) + '') + "', '" +
                    escSqlString((current+1) + '') + "', '" +
                    escSqlString('category') + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString('0') + "', '" +
                    escSqlString(aTerms[current].count) + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function processTermsRels(aUsers, aNews, aTerms, con) {
    var times = aNews.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " term relationships are stored to the DB.");
            processTermsTaxonomy(aUsers, aNews, aTerms, con);
            return;
        }
        process.stdout.write("Commit term relationship #" + (current+1) + "... ");
        runSqlQuery(con, "INSERT INTO wp_term_relationships (object_id, term_taxonomy_id, term_order) VALUES ('" +
                    escSqlString((current+1) + '') + "', '" +
                    escSqlString(aNews[current].cat_id + '') + "', '" +
                    escSqlString('0') + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function processTerms(aUsers, aNews, aTerms, con) {
    var times = aTerms.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " terms are stored to the DB.");
            processTermsRels(aUsers, aNews, aTerms, con);
            return;
        }
        process.stdout.write("Commit term #" + (current+1) + "... ");
        runSqlQuery(con, "INSERT INTO wp_terms (term_id, name, slug, term_group) VALUES ('" +
                    escSqlString((current+1) + '') + "', '" +
                    escSqlString(aTerms[current].name) + "', '" +
                    escSqlString(aTerms[current].slug) + "', '" +
                    escSqlString('0') + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function processUsers(aUsers, aNews, aTerms, con) {
    var users = Array.from(aUsers);
    var times = users.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " users are stored to the DB.");
            processTerms(aUsers, aNews, aTerms, con);
            return;
        }
        process.stdout.write("Commit user #" + (current+1) + "... ");
        runSqlQuery(con, "INSERT INTO wp_users (ID, user_login, user_pass, user_nicename, user_email, user_url, \
                                                user_registered, user_activation_key, user_status, display_name) VALUES ('" +
                    escSqlString(users[current][1].id) + "', '" +
                    escSqlString(users[current][1].un) + "', '" +
                    escSqlString(users[current][1].pass) + "', '" +
                    escSqlString(users[current][1].unn) + "', '" +
                    escSqlString(users[current][1].email) + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString(users[current][1].date) + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString('0') + "', '" +
                    escSqlString(users[current][1].un) + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function processPosts(aUsers, aNews, con) {
    var times = aNews.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " news are stored to the DB.");
            con.end();
            toExit();
            return;
        }
        process.stdout.write("Commit post #" + (current+1) + "... ");
        runSqlQuery(con, "INSERT INTO wp_posts (ID, post_author, post_date, post_date_gmt, post_content, post_title, \
                                                post_excerpt, post_status, comment_status, ping_status, post_password, \
                                                post_name, to_ping, pinged, post_modified, post_modified_gmt, \
                                                post_content_filtered, post_parent, guid, menu_order, post_type, \
                                                post_mime_type, comment_count) VALUES ('" +
                    escSqlString((current + 1) + '') + "', '" +
                    escSqlString(getUserId(aUsers, aNews[current].author)) + "', '" +
                    escSqlString(formatDateToMySQL(aNews[current].date)) + "', '" +
                    escSqlString(formatDateToMySQL(aNews[current].date)) + "', '" +
                    escSqlString(aNews[current].body) + "', '" +
                    escSqlString(aNews[current].title) + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString('publish') + "', '" +
                    escSqlString('open') + "', '" +
                    escSqlString('open') + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString(aNews[current].title) + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString(formatDateToMySQL(aNews[current].date)) + "', '" +
                    escSqlString(formatDateToMySQL(aNews[current].date)) + "', '" +
                    escSqlString(aNews[current].preview_url) + "', '" +
                    escSqlString('0') + "', '" +
                    escSqlString(Settings.url + '?p=' + (current + 1)) + "', '" +
                    escSqlString('0') + "', '" +
                    escSqlString('post') + "', '" +
                    escSqlString('') + "', '" +
                    escSqlString('0') + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function getUserId(aUsers, aUser) {
    var user;
    try {
        user = aUsers.get(aUser).id;
    } catch (err) {
        user = aUsers.get(aUser.toLowerCase()).id;
    }
    return user;
}

function toMotoFanWordpress_DB(aNews) {
    var con = MySql.createConnection({
        host:       Settings.host,
        user:       Settings.user,
        password:   Settings.pass,
        database:   Settings.db_wp,
        charset:    Settings.charset
    });

    con.connect(function(err) {
        if (err) {
            throw err;
        }
        console.log('MotoFan WordPress DB: Connected!');

        runSqlQuery(con, 'TRUNCATE TABLE wp_posts');
        runSqlQuery(con, 'TRUNCATE TABLE wp_users');
        runSqlQuery(con, 'TRUNCATE TABLE wp_terms');
        runSqlQuery(con, 'TRUNCATE TABLE wp_term_relationships');
        runSqlQuery(con, 'TRUNCATE TABLE wp_term_taxonomy');
        runSqlQuery(con, 'TRUNCATE TABLE wp_termmeta');

        //processPosts(createAuthorsMatrix(aNews), aNews, con);
        processUsers(createAuthorsMatrix(aNews), aNews, createTermsMatrix(aNews), con);
    });
}

// https://stackoverflow.com/a/7760578
function escSqlString(str) {
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
}

function detectImage(aUrl) {
    return ((aUrl.indexOf('.jpg') !== -1) || (aUrl.indexOf('.jpeg') !== -1) || (aUrl.indexOf('.png') !== -1) ||
        (aUrl.indexOf('.gif') !== -1) || (aUrl.indexOf('.JPG') !== -1) || (aUrl.indexOf('.JPEG') !== -1) ||
        (aUrl.indexOf('.PNG') !== -1) || (aUrl.indexOf('.GIF') !== -1) || (aUrl.indexOf('googleusercontent') !== -1));
}

function getPreviewUrl(aBody) {
    var matches = aBody.match(/(\b(https?|ftp|file):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|])/ig);
    var img_link = '';
    if (matches != null) {
        for (var i = 0; i < matches.length; ++i) {
            var i_url = matches[i];
            if (detectImage(i_url)) {
                return i_url;
            }
        }
    }
    return img_link;
}

function testImageOn404(aBody, aNum) {
    var img_src = getPreviewUrl(aBody);
    if (img_src === '') {
        return '';
    }
    try {
    var res = Request('GET', img_src, { timeout: Settings.timeout });
    var check = res && res.headers && res.headers['content-type'] &&
            res.headers['content-type'].match(/(image)+\//g) &&
            ((res.headers['content-type'].match(/(image)+\//g)).length != 0);
    if (check) {
        console.log('Image #' + aNum + ':\tGood: ' + img_src);
    } else {
        throw 'err';
    }
    } catch (err) {
        console.log('Image #' + aNum + ':\tBad: ' + img_src);
        img_src = '';
    }

    return img_src;
}

function getShortLink(aLink) {
    return Url.parse(aLink).hostname;
}

function createLink(aLink) {
    if (aLink.indexOf('http') != -1) {
        return '<a href="' + aLink + '" title="' + aLink + '" target="_blank">' + getShortLink(aLink) + '</a>';
    } else {
        return aLink;
    }
}

function filterBody(aBody, aSource, aOther) {
    return aBody + '\n\n' + '<em><strong>Источник</strong>: ' + createLink(aSource) + '</em>';
}

function handleMotoFanDB(aResult) {
    var news = [];
    console.log("Checking broken images...");
    aResult.forEach(function each(el, index, array) {
        news.push({ cat_id: el.category_id, date: el.date, author: el.poster,
                      title: el.title, body: filterBody(el.body, el.source, el.poster),
                      preview_url: testImageOn404(el.body, index + 1) });
    });
    console.log("Checking broken images... done!");
    toMotoFanWordpress_DB(news);
}

function runSqlQuery(aCon, aQuery) {
    return new Promise(function(resolve) {
        aCon.query(aQuery, function(err, result) {
            if (err) {
                throw err;
            }
            if (result) {
                resolve(aCon);
            }
        });
    });
}

main();
