// Function to prompt the user for input and validate it
function getUserInput() {
    let input;
    do {
        input = prompt('Please enter a number from 1 to 10:');
    } while (!isValidInput(input));
    return parseInt(input);
}

// Function to check if the input is valid (a number from 1 to 10)
function isValidInput(input) {
    return !isNaN(input) && parseInt(input) >= 1 && parseInt(input) <= 10;
}

// Function to display idiom based on input value
function displayIdiom(input) {
    let idiom;
    switch (input) {
        case 1:
            idiom = 'Back to square 1';
            break;
        case 2:
            idiom = 'Goody 2-shoes';
            break;
        case 3:
        case 6:
            idiom = "Two's company, three's a crowd";
            break;
        case 4:
        case 9:
            idiom = 'Counting sheep';
            break;
        case 5:
            idiom = 'Take five';
            break;
        case 7:
            idiom = 'Seventh heaven';
            break;
        case 8:
            idiom = 'Behind the eight-ball';
            break;
        case 10:
            idiom = 'Cheaper by the dozen';
            break;
        default:
            idiom = 'Invalid input';
    }
    alert(idiom);
}

const userInput = getUserInput();
displayIdiom(userInput);
