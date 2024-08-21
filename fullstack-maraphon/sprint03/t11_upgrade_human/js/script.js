class Human {
    constructor(firstName, lastName, gender, age, calories) {
        this.firstName = firstName || prompt('Enter First Name:');
        this.lastName = lastName || prompt('Enter Last Name:');
        this.gender = gender || prompt('Enter Gender:');
        this.age = age || parseInt(prompt('Enter Age:'));
        this.calories = calories || 0;
        this.updateInfo();
        this.hungryTimer = setTimeout(() => {
            this.displayMessage("I'm hungry!");

            this.caloriesDecriser = setInterval(() => {
                if (this.calories <= 0) {
                    setHumanImg('assets/images/hungry.jpeg');
                }
                this.calories = this.calories <= 0 ? 0 : this.calories - 200;
                this.updateInfo();
                if (this.calories < 500) {
                    this.displayMessage("I'm hungry!");
                }
            }, 60000);
        }, 5000);
    }

    sleepFor(seconds) {
        this.displayMessage(`I'm sleeping for ${seconds} seconds.`);
        setTimeout(() => {
            this.displayMessage("I'm awake now.");
        }, seconds * 1000);
    }

    feed() {
        if (this.calories > 500) {
            this.displayMessage("I'm not hungry.");
        } else {
            this.displayMessage('Nom nom nom');
            this.calories += 200;
            this.updateInfo();
            if (this.calories < 500) {
                this.displayMessage("I'm still hungry.");
            }
        }
    }

    turnIntoSuperhero() {
        if (this.calories > 500) {
            clearTimeout(this.hungryTimer);
            clearInterval(this.caloriesDecriser);
            document.getElementById('superheroContainer').style.display =
                'block';
            document.getElementById('humanContainer').style.display = 'none';
            this.displayMessage("I've transformed into a Superhero!");
        } else {
            this.displayMessage('I need more calories to become a Superhero!');
        }
    }

    displayMessage(message) {
        alert(message);
    }

    updateInfo() {
        document.getElementById('humanInfo').innerHTML = `
        <li>First Name: ${this.firstName}</li>
        <li>Last Name: ${this.lastName}</li>
        <li>Gender: ${this.gender}</li>
        <li>Age: ${this.age}</li>
        <li>Calories: ${this.calories}</li>
      `;
    }
}

class Superhero extends Human {
    constructor(firstName, lastName, gender, age, calories) {
        super(firstName, lastName, gender, age, calories);
    }

    fly() {
        this.displayMessage("I'm flying!");
        setTimeout(() => {
            this.displayMessage("I'm done flying.");
        }, 10000);
    }

    fightWithEvil() {
        this.displayMessage('Khhhh-chh... Bang-g-g-g... Evil is defeated!');
    }

    updateInfo() {
        document.getElementById('superheroInfo').innerHTML = `
        <li>First Name: ${this.firstName}</li>
        <li>Last Name: ${this.lastName}</li>
        <li>Gender: ${this.gender}</li>
        <li>Age: ${this.age}</li>
        <li>Calories: ${this.calories}</li>`;
    }
}
const human = new Human();
const superhero = new Superhero(
    human.firstName,
    human.lastName,
    human.gender,
    human.age,
    human.calories,
);

function setHumanImg(photo) {
    document.getElementsById('human-img').src = photo;
}

document
    .getElementById('sleepButton')
    .addEventListener('click', () => human.sleepFor(5));
document
    .getElementById('feedButton')
    .addEventListener('click', () => human.feed());
document
    .getElementById('turnSuperheroButton')
    .addEventListener('click', () => human.turnIntoSuperhero());

document
    .getElementById('flyButton')
    .addEventListener('click', () => superhero.fly());
document
    .getElementById('fightWithEvilButton')
    .addEventListener('click', () => superhero.fightWithEvil());
