function checkBrackets(str) {
    if (typeof str !== 'string') {
        return -1;
    }

    let stack = 0;
    let mismatch = 0;

    for (let char of str) {
        if (char === '(') {
            stack++;
        } else if (char === ')') {
            if (stack === 0) {
                mismatch++;
            } else {
                stack--;
            }
        }
    }
    return stack + mismatch;
}
