String.prototype.removeDuplicates = function () {
    return this.replace(/\b(\w+)\b\s*(?=\b\1\b)/gi, '').trim();
};
