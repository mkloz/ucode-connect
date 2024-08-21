function greetUser() {
    const firstName = getName('Enter your first name:');
    const lastName = getName('Enter your last name:');
    const fullName = firstName + ' ' + lastName;

    alert('Hello, ' + fullName + '!');
    console.log('Hello, ' + fullName + '!');
}

function getName(text) {
    let name;

    do {
        name = prompt(text);
        if (!isValidName(name)) {
            alert('Wrong input!');
            console.log('Wrong input!');
        }
    } while (!isValidName(name));

    return capitalize(name);
}

function isValidName(name) {
    return /^[a-zA-Z]+$/.test(name);
}

function capitalize(name) {
    return name.charAt(0).toUpperCase() + name.slice(1);
}

greetUser();
