var normalMessage = normalizeMessage('проверка #digest тест');
console.log(normalMessage);

function normalizeMessage(aMessage) {
    var normalMessage = '';

    if (!isEmpty(aMessage)) {
        // Delete #digest tag from message
        normalMessage = aMessage.replace('#digest', '');

        // Ttrim all trailing spaces
        if (!(isBlank(normalMessage))) {
            normalMessage = normalMessage.trim();
        }

        if (!(isBlank(normalMessage))) {
            normalMessage = normalMessage.replace(/\s\s+/g, ' ');
        }

        // Capitalize the first letter of message
        if (!(isBlank(normalMessage))) {
            normalMessage = capitalizeFirstLetterOfString(normalMessage);
        }
    }
    return normalMessage;
}

function capitalizeFirstLetterOfString(aString) {
    return aString.charAt(0).toUpperCase() + aString.slice(1);
}

function isEmpty(aString) {
    return (!aString || 0 === aString.length);
}

function isBlank(aString) {
    return (!aString || /^\s*$/.test(aString));
}
