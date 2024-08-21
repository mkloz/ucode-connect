function Avenger(option) {
  let Avenger = () =>
    `${option.alias.toUpperCase()}\n${option.powers.join('\n')}`;

  Avenger.toString = () =>
    `name: ${option.name}\ngender: ${option.gender}\nage: ${option.age}`;

  return Avenger;
}
module.exports = { Avenger };
