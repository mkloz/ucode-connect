const guestList = new Set(['Alice', 'Bob', 'Charlie', 'David', 'Eve']);

guestList.add('Frank');
guestList.delete('Bob');

console.log('Guest List:');
guestList.forEach((guest) => console.log(guest));

console.log('Is Alice invited?', guestList.has('Alice'));

const menu = new Map([
    ['Pizza', 10],
    ['Burger', 8],
    ['Salad', 6],
    ['Pasta', 12],
    ['Soup', 5],
]);

console.log('\nMenu:');
menu.forEach((price, dish) => console.log(`${dish}: $${price}`));

console.log('Price of Pizza:', menu.get('Pizza'));

const vault = new WeakMap();
const credentials1 = { key: 'key123', combination: '456' };
const contents1 = { money: 1000 };
const credentials2 = { key: 'key456', combination: '789' };
const contents2 = { jewelry: 'diamonds' };

vault.set(credentials1, contents1);
vault.set(credentials2, contents2);

console.log('\nBank Vault Contents:');
console.log('Box 1:', vault.get(credentials1));
console.log('Box 2:', vault.get(credentials2));

const coinCollection = new WeakSet();
const coin1 = { type: 'Gold', year: 1920 };
const coin2 = { type: 'Silver', year: 1950 };
const coin3 = { type: 'Bronze', year: 1980 };

coinCollection.add(coin1);
coinCollection.add(coin2);
coinCollection.add(coin3);

console.log('\nCoin Collection:');
console.log('Is coin1 in the collection?', coinCollection.has(coin1));
console.log('Is coin2 in the collection?', coinCollection.has(coin2));
console.log('Is coin3 in the collection?', coinCollection.has(coin3));
