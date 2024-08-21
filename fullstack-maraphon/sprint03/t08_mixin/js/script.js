const houseMixin = {
    wordReplace(oldWord, newWord) {
        this.description = this.description.replace(
            new RegExp(oldWord, 'g'),
            newWord,
        );
    },

    wordInsertAfter(targetWord, newWord) {
        this.description = this.description.replace(
            new RegExp(`(${targetWord}\\b)`, 'g'),
            `$1 ${newWord}`,
        );
    },

    wordDelete(targetWord) {
        this.description = this.description.replace(
            new RegExp(`\\b${targetWord}\\b`, 'g'),
            '',
        );
    },

    wordEncrypt() {
        this.description = this.description.replace(/[a-zA-Z]/g, function (c) {
            return String.fromCharCode(
                (c <= 'Z' ? 90 : 122) >= (c = c.charCodeAt(0) + 13)
                    ? c
                    : c - 26,
            );
        });
    },

    wordDecrypt() {
        this.wordEncrypt();
    },
};

Object.assign(house, houseMixin);
