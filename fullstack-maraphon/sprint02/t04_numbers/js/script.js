// Function to prompt the user for beginning and end of range, and call checkDivision function
function promptAndCheckDivision() {
    const beginRange =
        parseInt(prompt('Enter the beginning of the range (inclusive):')) || 1;
    const endRange =
        parseInt(prompt('Enter the end of the range (inclusive):')) || 100;
    checkDivision(beginRange, endRange);
}

function checkDivision(beginRange = 1, endRange = 100) {
    for (let i = beginRange; i <= endRange; i++) {
        let description = i + ' - ';
        if (i % 2 === 0) {
            description += 'is even';
        }
        if (i % 3 === 0) {
            description +=
                (description.endsWith('even') ? ', ' : '') +
                'is a multiple of 3';
        }
        if (i % 10 === 0) {
            description +=
                (description.endsWith('3')
                    ? ', '
                    : description.endsWith('even')
                    ? ', '
                    : '') + 'is a multiple of 10';
        }
        console.log(description);
    }
}

promptAndCheckDivision();
