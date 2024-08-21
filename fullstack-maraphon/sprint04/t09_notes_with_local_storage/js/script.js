const clearButton = document.querySelector('#clear');
const addButton = document.querySelector('#add');
const outputElement = document.querySelector('#output');

let itemCount = localStorage.length;
localStorage.clear();

addButton.addEventListener('click', addToLocalStorage);
clearButton.addEventListener('click', clearLocalStorage);

function addToLocalStorage() {
    const textareaValue = document.querySelector('#textarea').value;
    if (textareaValue === '') {
        alert('It\'s empty. Try to input something in "Text input"');
    } else {
        const newItem = `${textareaValue} ${generateDate()}`;
        localStorage.setItem(itemCount.toString(), newItem);
        displayStoredItems();
        itemCount++;
    }
}

function clearLocalStorage() {
    const confirmation = confirm('Delete cookies?');
    if (confirmation) {
        localStorage.clear();
        itemCount = 0;
        displayStoredItems();
    }
}

function generateDate() {
    const date = new Date();
    return `[${String(date.getDate()).padStart(2, '0')}.${String(
        date.getMonth() + 1,
    ).padStart(2, '0')}.${date.getFullYear()}, ${String(
        date.getHours(),
    ).padStart(2, '0')}:${String(date.getMinutes()).padStart(2, '0')}:${String(
        date.getSeconds(),
    ).padStart(2, '0')}]`;
}

function displayStoredItems() {
    if (localStorage.length === 0) {
        outputElement.innerHTML = '[Empty]';
    } else {
        outputElement.innerHTML = '';
        for (let i = 0; i < localStorage.length; i++) {
            const key = localStorage.getItem(i.toString());
            outputElement.insertAdjacentHTML(
                'beforeend',
                `<div>--> ${key}</div>`,
            );
        }
    }
}

displayStoredItems();
