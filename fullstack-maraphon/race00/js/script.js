function clearDisplay() {
    document.getElementById('current-expretion').textContent = '0';
    document.getElementById('previous-expretion').textContent = '';
}

function appendNumber(number) {
    let currentExpression =
        document.getElementById('current-expretion').textContent;

    if (currentExpression === '0' || currentExpression === 'Error') {
        document.getElementById('current-expretion').textContent = number;
    } else {
        document.getElementById('current-expretion').textContent += number;
    }
}

function appendOperator(operator) {
    if (operator === '+/-') {
        let currentExpression =
            document.getElementById('current-expretion').textContent;
        for (let i = currentExpression.length - 1; i >= 0; i--) {
            if (currentExpression[i] === '*' || currentExpression[i] === '/') {
                break;
            }
            if (currentExpression[i] === '-') {
                document.getElementById('current-expretion').textContent =
                    currentExpression.slice(0, i) +
                    currentExpression.slice(i + 1);
                return;
            }

            if (currentExpression[i] === '+' || i === 0) {
                document.getElementById('current-expretion').textContent =
                    currentExpression.slice(0, i) +
                    '-' +
                    currentExpression.slice(i);
                return;
            }
        }

        return;
    }
    if (operator === '%') {
        let currentExpression =
            document.getElementById('current-expretion').textContent;
        for (let i = currentExpression.length - 1; i >= 0; i--) {
            if (
                currentExpression[i] === '*' ||
                currentExpression[i] === '/' ||
                currentExpression[i] === '+' ||
                currentExpression[i] === '-'
            ) {
                document.getElementById('current-expretion').textContent =
                    currentExpression.slice(0, i + 1) +
                    parseFloat(currentExpression.slice(i + 1)) / 100;
                return;
            }
        }
        return;
    }
    let currentExpression =
        document.getElementById('current-expretion').textContent;

    if (['+', '-', '*', '/'].includes(currentExpression.slice(-1))) {
        document.getElementById('current-expretion').textContent =
            currentExpression.slice(0, -1) + operator;
    } else {
        document.getElementById('current-expretion').textContent += operator;
    }
}

function calculateResult() {
    let currentExpression =
        document.getElementById('current-expretion').textContent;

    try {
        let result = eval(currentExpression);
        document.getElementById('previous-expretion').textContent =
            currentExpression;
        document.getElementById('current-expretion').textContent = result;
    } catch (error) {
        document.getElementById('current-expretion').textContent = 'Error';
    }
}
