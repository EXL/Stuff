/* 
 * IntenseDebate comment importer for MotoFan.Ru and WordPress
 * Do not forget update comments counts: https://wordpress.org/plugins/web-ninja-comment-count-fixer/
 * License: MIT
 * (c) EXL, 03-MAR-2018, email: exlmotodev@gmail.com
 */

const MySql = require("mysql");
const Fs = require('fs');
const Xml = require('xml2js');

const Utils = require('./Utils.js');

function main() {
    console.log('++++= Started at: ' + Date());
    readXmlFile(Utils.settings.db_file);
}

function processComments(aComments, con) {
    var times = aComments.length;
    var current = 0;
    (function nextLapDb() {
        if (current >= times) {
            console.log("SQL: " + current + " comments are stored to the DB.");
            con.end();
            Utils.toExit();
            return;
        }
        process.stdout.write("Commit comment #" + (current+1) + "... ");
        Utils.runSqlQuery(con, "INSERT INTO wp_comments (comment_ID, comment_post_ID, comment_author, comment_author_email, \
                                       comment_author_url, comment_author_IP, comment_date, comment_date_gmt, \
                                       comment_content, comment_karma, comment_approved, comment_agent, comment_type, \
                                       comment_parent, user_id) VALUES ('" +
                    Utils.escSqlString((current+1) + '') + "', '" +
                    Utils.escSqlString(Utils.hackDataBaseOffset(aComments[current].guid) + '') + "', '" +
                    Utils.escSqlString(aComments[current].name) + "', '" +
                    Utils.escSqlString(aComments[current].email) + "', '" +
                    Utils.escSqlString(aComments[current].url) + "', '" +
                    Utils.escSqlString(aComments[current].ip) + "', '" +
                    Utils.escSqlString(aComments[current].date) + "', '" +
                    Utils.escSqlString(aComments[current].gmt) + "', '" +
                    Utils.escSqlString(aComments[current].text) + "', '" +
                    Utils.escSqlString(aComments[current].score + '') + "', '" +
                    Utils.escSqlString('1') + "', '" +
                    Utils.escSqlString('') + "', '" +
                    Utils.escSqlString('') + "', '" +
                    Utils.escSqlString('0') + "', '" +
                    Utils.escSqlString(aComments[current].uid + '') + "');").then(function() {
                        process.stdout.write("done.\n");
                        ++current;
                        nextLapDb();
        });
    })();
}

function toMotoFanWordpress_DB(aComments) {
    var con = MySql.createConnection({
        host:       Utils.settings.host,
        user:       Utils.settings.user,
        password:   Utils.settings.pass,
        database:   Utils.settings.db_wp,
        charset:    Utils.settings.charset
    });

    con.connect(function(err) {
        if (err) {
            throw err;
        }
        console.log('MotoFan WordPress DB: Connected!');
        Utils.runSqlQuery(con, 'TRUNCATE TABLE wp_comments');
        processComments(aComments, con);
    });
}

function getNewsId(aGuid) {
    return aGuid.slice(aGuid.indexOf('id=') + 3);
}

function filterName(aName) {
    return aName.replace('@', '');
}

function getUserId(aName) {
    switch (aName) {
        case 'EXL':
            return 1;
        case 'Osta':
            return 18;
        case 'NoPH8':
            return 20;
        case 'stigr':
        case 'стигр':
        case 'ыешпк':
            return 17;
        case 'lordawerd':
        case 'Awerd':
        case 'awerd':
        case 'LordAwerd':
        case 'Lord Awerd':
        case 'lord.awerd':
        case 'Lord':
        case 'motorola':
        case 'vkcommotorolaclub':
        case 'MotorolaClub':
        case 'AWERD':
            return 23;
        case 'zorgrhrd':
        case 'Zorge_R':
        case 'тов. Ящкпук':
        case 'тов. Ящкпу.К':
        case 'тов.Ящкпу.К':
            return 2;
        case 'Воха':
        case 'Voha888':
        case 'voha888':
            return 4;
        default:
            return 0;
    }
}

function createCommentsList(aComments) {
    var comments = [];
    aComments.forEach(function(el) {
        var guid = getNewsId(el.guid[0]);
        el.comments[0].comment.forEach(function(elc) {
            comments.push({ name: filterName(elc.name[0]), email: elc.email[0], url: elc.url[0],
                            ip: elc.ip[0], text: elc.text[0],
                            date: elc.date[0], gmt: elc.gmt[0], score: elc.score[0], guid: guid,
                            uid: getUserId(filterName(elc.name[0]))});
        });
    });
    toMotoFanWordpress_DB(comments);
}

function readXmlFile(aFile) {
    var xmlParser = new Xml.Parser();
    try {
        Fs.readFile(aFile, function(err, data) {
            if (!data || err) {
                throw new Error('Cannot open file: "' + Utils.settings.db_file + '"!');
            }
            xmlParser.parseString(data, function(err, json) {
                if (err) {
                    throw new SyntaxError('Wrong XML file: "' + Utils.settings.db_file + '"!');
                }
                createCommentsList(json.output.blogpost);
            });
        });
    } catch (err) {
        console.error(err.toString());
        Utils.toExit();
    }
}

main();
