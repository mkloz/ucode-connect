function concat(str1, str2) {
    let count = 0;

    if (typeof str2 === 'undefined') {
        return function () {
            count++;
            return str1 + ' ' + prompt('Enter the second string:');
        };
    } else {
        return str1 + ' ' + str2;
    }
}
