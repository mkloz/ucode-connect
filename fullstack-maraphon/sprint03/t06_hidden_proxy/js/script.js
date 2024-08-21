const person = {
    name: 'John',
    age: 30,
    city: 'New York',
};

const validator = new Proxy(person, {
    get(target, prop, receiver) {
        console.log(`Trying to access the property '${prop}'...`);
        if (!(prop in target)) {
            return false;
        }
        return Reflect.get(target, prop, receiver);
    },
    set(target, prop, value, receiver) {
        console.log(`Setting value '${value}' to '${prop}'...`);
        if (prop === 'age') {
            if (typeof value !== 'number' || !Number.isInteger(value)) {
                throw new Error('The age is not an integer.');
            }
            if (value < 0 || value > 200) {
                throw new Error('The age is invalid.');
            }
        }
        return Reflect.set(target, prop, value, receiver);
    },
});

// Example usage:
console.log(validator.name); // Trying to access the property 'name'...
console.log(validator.age); // Trying to access the property 'age'...
validator.age = 40; // Setting value '40' to 'age'...
console.log(validator.age); // Trying to access the property 'age'...
validator.age = 'thirty'; // Throws: The age is not an integer.
validator.age = 300; // Throws: The age is invalid.
