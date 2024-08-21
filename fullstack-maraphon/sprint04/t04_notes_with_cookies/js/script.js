const clearButton = document.querySelector('#clear');
const addButton = document.querySelector('#add');
const outputElement = document.querySelector('#output');

addButton.addEventListener('click', addToCookie);
clearButton.addEventListener('click', clearCookies);

function addToCookie() {
    const textareaValue = document.querySelector('#textarea').value;
    if (textareaValue === '') {
        alert('It\'s empty. Try to input something in "Text input"');
    } else {
        const newItem = `${textareaValue} ${generateDate()}`;
        document.cookie = `item${getCookieItemCount()}=${encodeURIComponent(
            newItem,
        )}`;
        displayStoredItems();
    }
}

function clearCookies() {
    const confirmation = confirm('Delete cookies?');
    if (confirmation) {
        const cookies = document.cookie.split(';');
        for (let i = 0; i < cookies.length; i++) {
            const cookie = cookies[i];
            const eqPos = cookie.indexOf('=');
            const name = eqPos > -1 ? cookie.substr(0, eqPos) : cookie;
            document.cookie = `${name}=;expires=Thu, 01 Jan 1970 00:00:00 GMT;`;
        }
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

function getCookieItemCount() {
    const cookies = document.cookie.split(';');
    return (
        cookies.filter((cookie) => cookie.trim().startsWith('item')).length + 1
    );
}

function displayStoredItems() {
    const cookies = document.cookie.split(';');
    let output = '';
    let empty = true;
    cookies.forEach((cookie) => {
        const [name, value] = cookie.split('=');
        if (name.trim().startsWith('item')) {
            output += `--> ${decodeURIComponent(value)}<br>`;
            empty = false;
        }
    });
    outputElement.innerHTML = empty ? '[Empty]' : output;
}

displayStoredItems();
