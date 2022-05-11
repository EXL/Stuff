var FileSystem = require('fs');
var catchPhrases = getCatchPhrases();

console.log(catchPhrases.digestCommandHello[0]);

function getCatchPhrases()
{
    return getJSONFileFromFileSystem('CatchPhrases.json');
}

function getJSONFileFromFileSystem(aFileName)
{
    var dotSlashName = './' + aFileName
    return JSON.parse(FileSystem.readFileSync(dotSlashName, 'utf-8'));
}
