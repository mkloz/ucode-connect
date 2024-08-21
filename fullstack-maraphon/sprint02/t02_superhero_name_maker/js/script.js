// Function to prompt the user for input
function getUserInput(promptMessage, regexPattern) {
    let input;
    do {
        input = prompt(promptMessage).trim();
    } while (!input.match(regexPattern));
    return input;
}

function generateSuperheroName() {
    const animalName = getUserInput(
        'What animal is the superhero most similar to?',
        /^[a-zA-Z]{1,20}$/,
    );

    const gender = getUserInput(
        'Is the superhero male or female? Leave blank if unknown or other.',
        /^(male|female|)$/i,
    );

    const age = getUserInput('How old is the superhero?', /^[1-9][0-9]{0,4}$/);

    let description;
    if (gender.toLowerCase() === 'male') {
        description = parseInt(age) < 18 ? 'boy' : 'man';
    } else if (gender.toLowerCase() === 'female') {
        description = parseInt(age) < 18 ? 'girl' : 'woman';
    } else {
        description = parseInt(age) < 18 ? 'kid' : 'hero';
    }

    alert('The superhero name is: ' + animalName + '-' + description + '!');
}

generateSuperheroName();
