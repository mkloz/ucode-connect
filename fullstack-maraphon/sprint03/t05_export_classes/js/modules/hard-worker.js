class HardWorker {
    constructor() {
        this._name = '';
        this._age = null;
        this._salary = null;
    }

    get name() {
        return this._name;
    }

    set name(name) {
        this._name = name;
    }

    get age() {
        return this._age;
    }

    set age(age) {
        if (age >= 1 && age < 100) {
            this._age = age;
        } else {
            console.log('Error: Age must be between 1 and 99.');
        }
    }

    get salary() {
        return this._salary;
    }

    set salary(salary) {
        if (salary >= 100 && value < 10000) {
            this._salary = salary;
        } else {
            console.log('Error: Salary must be between 100 and 9999.');
        }
    }

    toObject() {
        return {
            name: this._name,
            age: this._age,
            salary: this._salary,
        };
    }
}

export { HardWorker };
