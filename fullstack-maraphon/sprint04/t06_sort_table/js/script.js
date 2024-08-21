let head = ['Name', 'Strength', 'Age'];
let heroes = [
    { name: `Black Panther`, strength: 66, age: 53 },
    { name: `Captain America`, strength: 79, age: 137 },
    { name: `Captain Marvel`, strength: 97, age: 26 },
    { name: `Hulk`, strength: 80, age: 49 },
    { name: `Iron Man`, strength: 88, age: 48 },
    { name: `Spider-Man`, strength: 78, age: 16 },
    { name: `Thanos`, strength: 99, age: 1000 },
    { name: `Thor`, strength: 95, age: 1000 },
    { name: `Yon-Rogg`, strength: 73, age: 52 },
];

let sortState = {
    Name: false,
    Strength: false,
    Age: false,
};

const notification = document.querySelector('#notification');
const placeholder = document.getElementById('placeholder');

function createTable(heroesArr) {
    let tbl = document.createElement('table');
    tbl.appendChild(createHeader());
    heroesArr.forEach((hero) => {
        let row = document.createElement('tr');
        insertCell(hero.name, row);
        insertCell(hero.strength, row);
        insertCell(hero.age, row);
        tbl.appendChild(row);
    });
    placeholder.innerHTML = '';
    placeholder.appendChild(tbl);
}

function insertCell(str, row) {
    let cell = document.createElement('td');
    cell.innerText = str;
    row.appendChild(cell);
}

function createHeader() {
    let row = document.createElement('tr');
    head.forEach((header, index) => {
        let cell = document.createElement('th');
        cell.innerText = header;
        cell.setAttribute('onclick', `sort(${index})`);
        row.appendChild(cell);
    });
    return row;
}

function sort(index) {
    console.log(sortState);
    const prop = index === 0 ? 'name' : index === 1 ? 'strength' : 'age';
    const isAscending = !sortState[head[index]];
    heroes.sort((a, b) => {
        if (a[prop] === b[prop]) return 0;
        return isAscending
            ? a[prop] < b[prop]
                ? -1
                : 1
            : a[prop] > b[prop]
            ? -1
            : 1;
    });
    sortState[head[index]] = isAscending;
    notification.innerHTML = `Sort by ${head[index]}, order: ${
        isAscending ? 'ASC' : 'DESC'
    }`;
    createTable(heroes);
}

createTable(heroes);
