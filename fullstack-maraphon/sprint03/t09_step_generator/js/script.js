function* numberGenerator() {
    let previousResult = 1;
    while (true) {
        const userInput = prompt(
            `Previous result: ${previousResult}. Enter a new number:`,
        );
        let newNumber = parseFloat(userInput);
        if (isNaN(newNumber)) {
            console.log('Invalid number!');
            continue;
        }
        previousResult += newNumber;
        if (previousResult > 10000) {
            previousResult = 1;
        }
        yield previousResult;
    }
}
