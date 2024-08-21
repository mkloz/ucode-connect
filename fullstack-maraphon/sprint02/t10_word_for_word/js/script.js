function addWords(obj, wrds) {
    const wordsArr = wrds.split(/\s+/).filter((word) => word.trim() !== '');
    const currentWordsArr = obj.words
        .split(/\s+/)
        .filter((word) => word.trim() !== '');
    const newWordsArr = [...new Set([...currentWordsArr, ...wordsArr])];
    obj.words = newWordsArr.join(' ');
}

function removeWords(obj, wrds) {
    const wordsArr = wrds.split(/\s+/).filter((word) => word.trim() !== '');
    const currentWordsArr = obj.words
        .split(/\s+/)
        .filter((word) => word.trim() !== '');
    const newWordsArr = currentWordsArr.filter(
        (word) => !wordsArr.includes(word),
    );
    obj.words = newWordsArr.join(' ');
}

function changeWords(obj, oldWrds, newWrds) {
    const oldWordsArr = oldWrds
        .split(/\s+/)
        .filter((word) => word.trim() !== '');
    const newWordsArr = newWrds
        .split(/\s+/)
        .filter((word) => word.trim() !== '');
    const currentWordsArr = obj.words
        .split(/\s+/)
        .filter((word) => word.trim() !== '');

    oldWordsArr.forEach((oldWord) => {
        currentWordsArr.forEach((word, index) => {
            if (word === oldWord) {
                currentWordsArr[index] = newWordsArr.shift();
            }
        });
    });

    obj.words = [...new Set(currentWordsArr)].join(' ');
}
