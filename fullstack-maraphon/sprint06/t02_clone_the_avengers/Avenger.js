class Avenger {
  constructor({ name, alias, gender, age, powers, hp }) {
    this.name = name;
    this.alias = alias;
    this.gender = gender;
    this.age = age;
    this.powers = powers;
    this.hp = hp;
  }

  toString() {
    return `name: ${this.name}\ngender: ${this.gender}\nage: ${this.age}`;
  }

  [Symbol.toPrimitive](hint) {
    if (hint === 'string') {
      return this.toString();
    }
    return null;
  }

  [Symbol.toStringTag]() {
    return 'Avenger';
  }
}

module.exports = { Avenger };
