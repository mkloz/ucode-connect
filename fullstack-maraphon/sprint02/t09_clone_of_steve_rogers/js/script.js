function copyObj(obj) {
    let copy = {};

    for (let value in obj) {
        copy[value] = obj[value];

        if (typeof obj[value] === 'object') {
            copy[value] = copyObj(obj[value]);
        }
    }

    return copy;
}
