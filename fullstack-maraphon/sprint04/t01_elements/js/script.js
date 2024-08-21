const outputDataChar = document.getElementById('characters').children;

Array.from(outputDataChar).forEach((char) => {
    let outputData = char.getAttribute('data-element');

    if (!char.classList.contains('good') && !char.classList.contains('evil')) {
        char.className = 'unknown';
    }

    if (!outputData) {
        outputData = 'none';
        char.setAttribute('data-element', outputData);
    }

    char.appendChild(document.createElement('br'));

    if (outputData === 'none') {
        const circle = document.createElement('div');
        const line = document.createElement('div');

        circle.className = `elem ${outputData}`;
        line.className = 'line';

        circle.appendChild(line);
        char.appendChild(circle);
        return;
    }
    outputData.split(' ').forEach((elem) => {
        const circle = document.createElement('div');

        circle.className = `elem ${elem}`;
        char.appendChild(circle);
    });
});
